//
// Created by Оскар on 12.02.19.
//

#include <iostream>
#include "bin_search.h"

bool bin_search( std::vector<int>::iterator first,  std::vector<int>::iterator last, const int& value )
{
	if (first == last)
	{
		return false;
	}

	long begin = 0, end = last-first;
	long mid = end / 2;
	long old_mid = -1;
	while (mid != old_mid){
		if(*(first + mid) == value){
			return true;
		}

		if (*(first + mid) < value){
			begin = mid;
		}
		else {
			end = mid;
		}
		old_mid = mid;
		mid = (begin + end) / 2;
	}
	return false;
}