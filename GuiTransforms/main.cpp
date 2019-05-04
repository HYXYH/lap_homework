// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
#include <cv.h>
//#include <highgui.h>
#include <opencv2/core/types_c.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <string>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char *description) {
  std::cerr << "Glfw Error" << error << ": " << description << "\n";
}

GLFWwindow *initContext() {
  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit()) {
    std::cerr << "ERROR: could not start GLFW3\n";
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  int monitorsCount;
  GLFWmonitor **monitors = glfwGetMonitors(&monitorsCount);

  // The last monitor ever we choose.
  GLFWmonitor *demoMonitor = monitors[monitorsCount - 1];
  const GLFWvidmode *videoMode = glfwGetVideoMode(demoMonitor);

  // Create fullscreen window on the chosen monitor.
  GLFWwindow *window =
      glfwCreateWindow(videoMode->width, videoMode->height, "Dear ImGui GLFW+OpenGL3 example", demoMonitor, nullptr);

  if (!window) {
    std::cerr << "ERROR: could not open window with GLFW3\n";
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0); //Отключаем вертикальную синхронизацию
  return window;
}

void initGL() {
  glewExperimental = GL_TRUE;
  bool err = glewInit() != GLEW_OK;
  if (err) {
    std::cerr << "Failed to initialize OpenGL loader!\n";
    exit(1);
  }
  const GLubyte *renderer = glGetString(GL_RENDERER); //Получаем имя рендерера
  const GLubyte *version = glGetString(GL_VERSION); //Получаем номер версии
  const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL context version: " << version << std::endl;
  std::cout << "GLSL version: " << glslversion << std::endl;

  // Сбросим флаг ошибки.
  glGetError();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void initGui(GLFWwindow *window) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, false);
  const char *glsl_version = "#version 330";
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void updateGui() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void renderFrame(GLFWwindow *window) {
  // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwMakeContextCurrent(window);
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(0, 127, 127, 255);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwMakeContextCurrent(window);
  glfwSwapBuffers(window);
}

void showOutputCanvas(ImVector<ImVec2> &points) {
  bool p_open;
  if (!ImGui::Begin("Output canvas", &p_open)) {
    ImGui::End();
    return;
  }

  ImDrawList *draw_list = ImGui::GetWindowDrawList();

  ImVec2 canvas_pos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
  ImVec2 canvas_size = ImGui::GetContentRegionAvail();        // Resize canvas to what's available
  draw_list->AddRectFilledMultiColor(canvas_pos,
                                     ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                                     IM_COL32(50, 50, 50, 255),
                                     IM_COL32(50, 50, 60, 255),
                                     IM_COL32(60, 60, 70, 255),
                                     IM_COL32(50, 50, 60, 255));
  draw_list->AddRect(canvas_pos,
                     ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                     IM_COL32(255, 255, 255, 255));

  draw_list->PushClipRect(canvas_pos,
                          ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                          true);      // clip lines within the canvas (if we resize it, etc.)
  // draw lines
  for (int i = 0; i < points.size() - 1; i++) {
    draw_list->AddLine(ImVec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y),
                       ImVec2(canvas_pos.x + points[i + 1].x, canvas_pos.y + points[i + 1].y),
                       IM_COL32(255, 255, 0, 255),
                       2.0f);
  }
  draw_list->AddLine(ImVec2(canvas_pos.x + points[0].x, canvas_pos.y + points[0].y),
                     ImVec2(canvas_pos.x + points[points.size() - 1].x, canvas_pos.y + points[points.size() - 1].y),
                     IM_COL32(255, 255, 0, 255),
                     2.0f);
  draw_list->PopClipRect();
  ImGui::End();
}

bool isConvex(ImVector<ImVec2> &points) {
  //A = 0
  //B = 2
  //C = 1
  //D = 3

  ImVec2 a(points[2].x - points[0].x, points[2].y - points[0].y);
  ImVec2 b(points[3].x - points[1].x, points[3].y - points[1].y);

  float t1;
  float t2 = (points[0].y + a.y * ((points[1].x - points[0].x) / a.x) - points[1].y) / (b.y - (b.x * a.y / a.x));
  if (t2 > 1 || t2 < 0 || std::isnan(t2))
    return false;

  ImVec2 intersect(points[1].x + b.x * t2, points[1].y + b.y * t2);
  ImVec2 e(intersect.x - points[0].x, intersect.y - points[0].y);
  if (a.x != 0) {
    t1 = e.x / a.x;
  } else if (a.y != 0) {
    t1 = e.y / a.y;
  } else {
    std::cerr << "WTF??? vector [a] is zero!";
    return false;
  }
  if (t1 > 1 || t1 < 0 || std::isnan(t1))
    return false;

  return true;
}

void showInputCanvas(ImVector<ImVec2> &points, ImVec2& canvas_size) {
  bool p_open;
  if (!ImGui::Begin("Input canvas", &p_open, ImGuiWindowFlags_NoMove)) {
    ImGui::End();
    return;
  }

  ImDrawList *draw_list = ImGui::GetWindowDrawList();
  if (ImGui::Button("Reset")) {
    points.clear();
  }
  ImGui::SameLine();
  ImGui::Text("Left-click and drag to move vertex");

  ImVec2 canvas_pos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
  canvas_size = ImGui::GetContentRegionAvail();        // Resize canvas to what's available
  draw_list->AddRectFilledMultiColor(canvas_pos,
                                     ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                                     IM_COL32(50, 50, 50, 255),
                                     IM_COL32(50, 50, 60, 255),
                                     IM_COL32(60, 60, 70, 255),
                                     IM_COL32(50, 50, 60, 255));
  draw_list->AddRect(canvas_pos,
                     ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                     IM_COL32(255, 255, 255, 255));

  static ImU32 statusColor = IM_COL32(0, 255, 0, 255);
  static ImU32 color = IM_COL32(0, 255, 0, 255);
  static int drag_idx = -1;

  if (points.Size == 0){
    ImGui::End();
    return;
  }

  int clickZoneRadius = 15;

  for (int i = 0; i < points.size(); i++) {
    float diffx = points[i].x - (ImGui::GetIO().MousePos.x - canvas_pos.x);
    float diffy = points[i].y - (ImGui::GetIO().MousePos.y - canvas_pos.y);
    float dist = std::sqrt(diffx * diffx + diffy * diffy);
    if (dist < clickZoneRadius) {
      drag_idx = i;
    }
    if (ImGui::IsMouseDown(0)) {
      if (drag_idx != -1) {
        ImVec2 oldp = points[drag_idx];
        points[drag_idx].x = (ImGui::GetIO().MousePos.x - canvas_pos.x);
        points[drag_idx].y = (ImGui::GetIO().MousePos.y - canvas_pos.y);

        if (isConvex(points)) {
          statusColor = IM_COL32(0, 255, 0, 255);
        } else {
          statusColor = IM_COL32(255, 0, 0, 255);
          points[drag_idx] = oldp;
        }
      }
    } else {
      drag_idx = -1;
    }
  }

  draw_list->PushClipRect(canvas_pos,
                          ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y),
                          true);      // clip lines within the canvas (if we resize it, etc.)
  for (int i = 0; i < points.size(); i++) {
    if (i != drag_idx) {
      color = IM_COL32(255, 255, 0, 255);
    } else {
      color = statusColor;
    }
    draw_list->AddCircleFilled(ImVec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y),
                               5,
                               color,
                               12);

    if (i != points.Size - 1) {
      draw_list->AddLine(ImVec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y),
                         ImVec2(canvas_pos.x + points[i + 1].x, canvas_pos.y + points[i + 1].y),
                         IM_COL32(255, 255, 0, 255),
                         2.0f);
    }
  }
  draw_list->AddLine(ImVec2(canvas_pos.x + points[0].x, canvas_pos.y + points[0].y),
                     ImVec2(canvas_pos.x + points[points.Size - 1].x, canvas_pos.y + points[points.Size - 1].y),
                     IM_COL32(255, 255, 0, 255),
                     2.0f);
  draw_list->PopClipRect();

  ImGui::End();
}

cv::Mat resetPoints(ImVector<ImVec2> &points, int edge, ImVec2 canvas_size){
  float offsety = canvas_size.y / 2;
  float offsetx = canvas_size.x / 2;
  points.push_back(ImVec2(offsetx - edge + rand() % 100, offsety - edge + rand() % 100));
  points.push_back(ImVec2(offsetx + edge + rand() % 100, offsety - edge + rand() % 100));
  points.push_back(ImVec2(offsetx + edge + rand() % 100, offsety + edge + rand() % 100));
  points.push_back(ImVec2(offsetx - edge + rand() % 100, offsety + edge + rand() % 100));

  std::vector<cv::Point2f> srcPoints;
  for (int i = 0; i < points.Size; i++) {
    srcPoints.push_back(cv::Point2f(points[i].x, points[i].y));
  }

  std::vector<cv::Point2f> dstPoints;
  dstPoints.push_back(cv::Point2f(offsetx - edge, offsety - edge));
  dstPoints.push_back(cv::Point2f(offsetx + edge, offsety - edge));
  dstPoints.push_back(cv::Point2f(offsetx + edge, offsety + edge));
  dstPoints.push_back(cv::Point2f(offsetx - edge, offsety + edge));

  return cv::findHomography(srcPoints, dstPoints, CV_RANSAC);
}

int main() {
  // Setup window
  GLFWwindow *window = initContext();

  // Initialize OpenGL loader
  initGL();

  //Dear imgui
  initGui(window);

  int width, height;
  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  width = mode->width;
  height = mode->height;

  ImVec2 windowSize(400, 560);
  ImVec2 canvasSize;
  int edge = 100;
  ImVector<ImVec2> points;
  cv::Mat H;

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    updateGui();

    {
      ImGui::SetNextWindowPos(ImVec2(width / 2 - windowSize.x, (height - windowSize.y) / 2));
      ImGui::SetNextWindowSize(windowSize);
      showInputCanvas(points, canvasSize);

      if (points.size() == 0) {
        H = resetPoints(points, edge, canvasSize);
      }

      std::vector<cv::Point2f> srcPoints;
      for (int i = 0; i < points.size(); i++) {
        srcPoints.push_back(cv::Point2f(points[i].x, points[i].y));
      }
      std::vector<cv::Point2f> dstPoints(4);
      perspectiveTransform( srcPoints, dstPoints, H);

      ImVector<ImVec2> points2;
      for (int i = 0; i < dstPoints.size(); i++) {
        points2.push_back(ImVec2(dstPoints[i].x, dstPoints[i].y));
      }

      ImGui::SetNextWindowPos(ImVec2(width / 2, (height - windowSize.y) / 2));
      ImGui::SetNextWindowSize(windowSize);
      showOutputCanvas(points2);
    }

    renderFrame(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}