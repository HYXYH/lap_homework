//
// Created by Оскар on 28.03.19.
//

#ifndef LAP_HOMEWORK_LIST_H
#define LAP_HOMEWORK_LIST_H

#include <memory>
#include <stdexcept>

template<class T>
class List;

template<class T>
class Node {

  std::shared_ptr<T> _value;
  std::shared_ptr<Node<T>> _next;
  std::shared_ptr<Node<T>> _prev;

 public:
  Node() {};
  Node(T value) {
    _value = std::make_shared<T>(value);
  };

  friend class List<T>;
};

template<class T>
class List {
  std::shared_ptr<Node<T>> _first;
  std::shared_ptr<Node<T>> _last;
  long _size;

 public:
  List() : _size(0), _first(nullptr), _last(nullptr) {};

  void push_back(T value) {
    auto node = std::make_shared<Node<T>>(value);
    if (_size == 0) {
      _first = node;
      _last = node;
    } else {
      _last->_next = node;
      _last->_next->_prev = _last;
      _last = _last->_next;
    }
    _size++;
  }

  void push_front(T value) {
    auto node = std::make_shared<Node<T>>(value);
    if (_size == 0) {
      _first = node;
      _last = node;
    } else {
      _first->_prev = node;
      _first->_prev->_next = _first;
      _first = _first->_prev;
    }
    _size++;
  }

  std::shared_ptr<T> pop_back() {
    if (_size == 0) {
      throw std::range_error("pop_back from empty list");
    }
    auto retval = _last->_value;
    if (_size == 1) {
      _first = nullptr;
      _last = nullptr;
    } else {
      _last = _last->_prev;
      _last->_next = nullptr;
    }
    _size--;
    return retval;
  }

  std::shared_ptr<T> pop_front() {
    if (_size == 0) {
      throw std::range_error("pop_front from empty list");
    }
    auto retval = _first->_value;
    if (_size == 1) {
      _first = nullptr;
      _last = nullptr;
    } else {
      _first = _first->_next;
      _first->_prev = nullptr;
    }
    _size--;
    return retval;
  }

  long getSize() {
    return _size;
  }

  std::shared_ptr<T> operator[](long idx) {
    if (idx >= _size || idx < 0) {
      throw std::range_error("index out of range");
    }
    auto curr = _first;
    for (long i = 0; i < idx; i++) {
      curr = curr->_next;
    }
    return curr->_value;
  }

  void erase(long idx) {
    if (idx >= _size || idx < 0) {
      throw std::range_error("index out of range");
    }
    auto curr = _first;
    for (long i = 0; i < idx; i++) {
      curr = curr->_next;
    }
    if (curr != nullptr) {
      curr->_prev->_next = curr->_next;
      if (curr->_next != nullptr) {
        curr->_next->_prev = curr->_prev;
      }
    }
    _size--;
  }
};

#endif //LAP_HOMEWORK_LIST_H
