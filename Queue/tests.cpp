//
// Created by Оскар on 13.02.19.
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "queue.h"


TEST_CASE( "List basic tests" ) {
	Queue<int> queue;

	for(int i=0; i < 5; i++){
		queue.push(i);
	}

	REQUIRE( queue.getSize() == 5 );
	REQUIRE( queue.top() == 0 );
	queue.pop();
	REQUIRE( queue.getSize() == 4 );
	REQUIRE( queue.top() == 1 );
	queue.push(7);
	REQUIRE( queue.getSize() == 5 );
	REQUIRE( queue.top() == 1 );
	queue.pop();
	REQUIRE( queue.getSize() == 4 );
	queue.pop();
	queue.pop();
	queue.pop();
	REQUIRE( queue.top() == 7 );
	REQUIRE( queue.getSize() == 1 );
	queue.pop();
	REQUIRE( queue.getSize() == 0 );

}
