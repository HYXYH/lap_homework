//
// Created by Оскар on 2019-04-14.
//

#include <cstdint>
#include <iostream>

struct EmptyStruct{

};

struct BaseS{
  char a{0};
  char b{0};
  int64_t x{0};
};

struct BaseInverseS{
  int64_t x{0};
  char a{0};
  char b{0};
};

struct ChildS1: public BaseS{

};

struct ChildS2: public BaseS{
  char c{0};
};

struct ChildS3: public BaseS{
  char c{0};
  char d{0};
};


struct ChildS4: public BaseS, BaseInverseS {

};


int main(){

  std::cout << "size of empty struct: " << sizeof(EmptyStruct) << "\n";
  std::cout << "size of int64_t: " << sizeof(int64_t) << "\n";
  std::cout << "size of BaseS struct: " << sizeof(BaseS) << "\n";
  std::cout << "size of BaseInverseS struct: " << sizeof(BaseInverseS) << "\n";
  std::cout << "size of ChildS1 struct: " << sizeof(ChildS1) << "\n";
  std::cout << "size of ChildS2 struct: " << sizeof(ChildS2) << "\n";
  std::cout << "size of ChildS3 struct: " << sizeof(ChildS3) << "\n";
  std::cout << "size of ChildS4 struct: " << sizeof(ChildS4) << "\n";
}