//
// Created by Оскар on 13.02.19.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "List.h"

TEST_CASE("List basic tests") {
  List<int> list;

  for (int i = 0; i < 50; i++) {
    list.push_back(i);
  }

  REQUIRE(list.getSize() == 50);
  REQUIRE(*list[0] == 0);
  REQUIRE(*list[1] == 1);
  REQUIRE(*list[49] == 49);
  REQUIRE(*list.pop_back() == 49);
  REQUIRE(list.getSize() == 49);
  list.push_back(100);
  REQUIRE(list.getSize() == 50);
  REQUIRE(*list[49] == 100);
  list.push_front(-5);
  REQUIRE(list.getSize() == 51);
  REQUIRE(*list[0] == -5);
  REQUIRE(*list.pop_front() == -5);
  REQUIRE(list.getSize() == 50);
  REQUIRE(*list[4] == 4);
  list.erase(4);
  REQUIRE(*list[4] == 5);
  REQUIRE(list.getSize() == 49);

  for (int i = 0; i < 49; i++) {
    list.pop_back();
  }
  REQUIRE(list.getSize() == 0);

  for (int i = 0; i < 500; i++) {
    list.push_front(i);
  }

  REQUIRE(list.getSize() == 500);
  for (int i = 0; i < 500; i++) {
    list.pop_front();
  }
  REQUIRE(list.getSize() == 0);
}
