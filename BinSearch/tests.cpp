//
// Created by Оскар on 13.02.19.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "bin_search.hpp"
typedef std::vector<int>::iterator iter_int;

TEST_CASE("Binary search for existing elements", "[bin_search<iter_int>]") {
  std::vector<int> vect;
  vect.reserve(1000);
for (int i = 0; i < 1000; i++) {
    vect.push_back(i);
  }

  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 0) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 999) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 500) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 501) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 499) == true);
}

TEST_CASE("Binary search for not existing elements", "[bin_search<iter_int>]") {
  std::vector<int> vect;
  vect.reserve(1000);
for (int i = 0; i < 1000; i++) {
    vect.push_back(i);
  }

  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), -10) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), -1) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 1000) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 1001) == false);
}

TEST_CASE("Binary search for vector with missed elements", "[bin_search<iter_int>]") {
  std::vector<int> vect;
  vect.reserve(1000);
  for (int i = 0; i < 1000; i++) {
    if (i % 5 == 0) {
      vect.push_back(i);
    }
  }

  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), -1) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 0) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 1) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 2) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 3) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 4) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 5) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 6) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 7) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 120) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 121) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 700) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 800) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 995) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 999) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 1000) == false);
}

TEST_CASE("Binary search for descending sorted vector", "[bin_search<iter_int>]") {
  std::vector<int> vect;
  vect.reserve(1000);
  for (int i = 1000; i > 0; i--) {
    vect.push_back(i);
  }

  REQUIRE(vect.back() != 0);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 0) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 999) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 500) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 501) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 499) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), -10) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), -1) == false);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 1000) == true);
  REQUIRE(bin_search<iter_int>(vect.begin(), vect.end(), 1001) == false);
}
