//
// Created by Оскар on 28.03.19.
//

#ifndef LAP_HOMEWORK_QUEUE_H
#define LAP_HOMEWORK_QUEUE_H


#include "../List/List.h"

template <class T>
class Queue {
	List<T> _queue;

	void checkSize(){
		if (getSize() <= 0)
		{
			throw std::range_error("top from empty queue");
		}
	}

public:
	T top(){
		checkSize();
		return *_queue[0];
	}

	void pop(){
		checkSize();
		_queue.pop_front();
	}

	void push(T value){
		_queue.push_back(value);
	}

	long getSize(){
		return _queue.getSize();
	}
};


#endif //LAP_HOMEWORK_QUEUE_H
