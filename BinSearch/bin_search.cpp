//
// Created by Оскар on 12.02.19.
//

#include <iostream>
#include "bin_search.h"

bool bin_search( std::vector<int>::iterator first,  std::vector<int>::iterator last, const int& value )
{
	bool is_ascending = true;
	if (first == last)
	{
		return false;
	}
	if (*first > *(last - 1))
	{
		is_ascending = false;
	}

	long begin = 0, end = last-first;
	long mid = end / 2;
	long old_mid = -1;
	while (mid != old_mid){
		if(*(first + mid) == value){
			return true;
		}

		if (*(first + mid) < value){
			if (is_ascending)
			{
				begin = mid;
			}
			else
			{
				end = mid;
			}
		}
		else {
			if (is_ascending)
			{
				end = mid;
			}
			else
			{
				begin = mid;
			}
		}
		old_mid = mid;
		mid = (begin + end) / 2;
	}
	return false;
}