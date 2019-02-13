//
// Created by Оскар on 12.02.19.
//

#include <iostream>
#include "bin_search.h"

bool bin_search( const std::vector<int>& vect, const int& value )
{
	if (vect.empty())
	{
		return false;
	}

	long begin = 0, end = vect.size();
	long mid = end / 2;
	long old_mid = -1;
	while (mid != old_mid){
		if(vect[mid] == value){
			return true;
		}

		if (vect[mid] < value){
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