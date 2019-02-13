//
// Created by Оскар on 13.02.19.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bin_search.h"

TEST_CASE( "Binary search for existing elements", "[bin_search]" ) {
	std::vector<int> vect(1000);
	for (int i = 0; i < 1000; i++){
		vect.push_back(i);
	}

	REQUIRE( bin_search(vect, 0) == true );
	REQUIRE( bin_search(vect, 999) == true );
	REQUIRE( bin_search(vect, 500) == true );
	REQUIRE( bin_search(vect, 501) == true );
	REQUIRE( bin_search(vect, 499) == true );
}

TEST_CASE( "Binary search for not existing elements", "[bin_search]" ) {
	std::vector<int> vect(1000);
	for (int i = 0; i < 1000; i++){
		vect.push_back(i);
	}

	REQUIRE( bin_search(vect, -10) == false );
	REQUIRE( bin_search(vect, -1) == false );
	REQUIRE( bin_search(vect, 1000) == false );
	REQUIRE( bin_search(vect, 1001) == false );
}

TEST_CASE( "Binary search for vector with missed elements", "[bin_search]" ) {
	std::vector<int> vect(1000);
	for (int i = 0; i < 1000; i++){
		if (i % 5 == 0 )
		vect.push_back(i);
	}

	REQUIRE( bin_search(vect, -1) == false );
	REQUIRE( bin_search(vect, 0) == true );
	REQUIRE( bin_search(vect, 1) == false );
	REQUIRE( bin_search(vect, 2) == false );
	REQUIRE( bin_search(vect, 3) == false );
	REQUIRE( bin_search(vect, 4) == false );
	REQUIRE( bin_search(vect, 5) == true );
	REQUIRE( bin_search(vect, 6) == false );
	REQUIRE( bin_search(vect, 7) == false );
	REQUIRE( bin_search(vect, 120) == true );
	REQUIRE( bin_search(vect, 121) == false );
	REQUIRE( bin_search(vect, 700) == true );
	REQUIRE( bin_search(vect, 800) == true );
	REQUIRE( bin_search(vect, 995) == true );
	REQUIRE( bin_search(vect, 999) == false );
	REQUIRE( bin_search(vect, 1000) == false );
}