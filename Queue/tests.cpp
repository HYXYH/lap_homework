//
// Created by Оскар on 13.02.19.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Queue.h"

TEST_CASE("List basic tests") {
  Queue<int> queue;

  for (int i = 0; i < 5; i++) {
    queue.push(i);
  }

  REQUIRE(queue.isEmpty() == false);
  REQUIRE(queue.top() == 0);
  queue.pop();
  REQUIRE(queue.top() == 1);
  queue.push(7);
  REQUIRE(queue.top() == 1);
  queue.pop();
  queue.pop();
  queue.pop();
  queue.pop();
  REQUIRE(queue.top() == 7);
  queue.pop();
  REQUIRE(queue.isEmpty() == true);


  for (int i = 0; i < 5; i++) {
    queue.push(i);
  }
  Queue<int> queue2(std::move(queue));
  REQUIRE(queue.isEmpty() == true);
  REQUIRE(queue2.isEmpty() == false);
  REQUIRE(queue2.top() == 0);
  queue2.pop();
  REQUIRE(queue2.top() == 1);
  queue2.push(7);
  REQUIRE(queue2.top() == 1);
  queue2.pop();
  queue2.pop();
  queue2.pop();
  queue2.pop();
  REQUIRE(queue2.top() == 7);
  queue2.pop();
  REQUIRE(queue2.isEmpty() == true);
}
