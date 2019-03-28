//
// Created by Оскар on 13.02.19.
//

#include <vector>
#include <functional>

#ifndef BINSEARCH_BIN_SEARCH_H
#define BINSEARCH_BIN_SEARCH_H

#endif //BINSEARCH_BIN_SEARCH_H

template<class Iterator, class T = typename std::iterator_traits<Iterator>::value_type, class less = std::less<T>>
bool bin_search(Iterator first, Iterator last, const T& value )
{
	less comparator_less;
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

		if (comparator_less(*(first + mid), value))
		{
			if (is_ascending)
			{
				begin = mid;
			}
			else
			{
				end = mid;
			}
		}
		else if (comparator_less(value, *(first + mid)))
		{
			if (is_ascending)
			{
				end = mid;
			}
			else
			{
				begin = mid;
			}
		}
		else
		{
			return true;
		}
		old_mid = mid;
		if (begin % 2 == 1 && end % 2 == 1)
		{
			mid = (begin + 1) / 2 + end / 2;
		}
		else
		{
		mid = begin / 2 + end / 2;
		}
	}
	return false;
}