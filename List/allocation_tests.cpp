//
// Created by Оскар on 29.03.19.
//

#include "List.h"

#include <iostream>

class TestElement{
public:
	int value;

	static int global_counter;

	TestElement(){
		value = global_counter;
		global_counter++;
		std::cout << "constructed: " << value << "\n";
	}

	TestElement(TestElement&& te){
		value = te.value;
		std::cout << "copy&&: " << value << "\n";
	}

	TestElement(TestElement& te){
		value = te.value;
		std::cout << "copy&:  " << value << "\n";
	}

	~TestElement(){
		std::cout << "Deconstructed: " << value << "\n";
	}
};

int TestElement::global_counter = 0;


int main(){
	List<TestElement> list;
	std::cout << "PUSH" << "\n";

	for(int i=0; i < 5; i++){
		list.push_back(std::move(TestElement()));
	}

	list.pop_back();
	list.pop_front();



	return 0;
}