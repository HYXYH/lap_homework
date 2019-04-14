//
// Created by Оскар on 13.02.19.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "Complex.h"

TEST_CASE("Arithmetics") {
  Complex a(5, 5);
  Complex b(0, -5);

  Complex sum = a + b;
  Complex diff = a - b;
  Complex mult = a * b;
  Complex div = a / b;

  REQUIRE(a.get_real() == 5);
  REQUIRE(a.get_imag() == 5);
  REQUIRE(b.get_real() == 0);
  REQUIRE(b.get_imag() == -5);

  REQUIRE(sum.get_real() == 5);
  REQUIRE(sum.get_imag() == 0);
  REQUIRE(diff.get_real() == 5);
  REQUIRE(diff.get_imag() == 10);
  REQUIRE(mult.get_real() == 25);
  REQUIRE(mult.get_imag() == -25);
  REQUIRE(div.get_real() == -1);
  REQUIRE(div.get_imag() == 1);
}