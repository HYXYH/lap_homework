//
// Created by Оскар on 10.03.19.
//

#include <cmath>
#include <stdexcept>
#include "Complex.h"

double Complex::get_real() {
  return _real;
}

double Complex::get_imag() {
  return _imag;
}

Complex Complex::conj() {
  return Complex(_real, -_imag);
}

double Complex::abs() {
  return sqrt(_real * _real + _imag * _imag);
}

Complex Complex::operator+(Complex& c) {
  return Complex(_real + c._real, _imag + c._imag);
}

Complex Complex::operator+(double& d) {
  return Complex(_real + d, _imag);
}

Complex Complex::operator-(Complex& c) {
  return Complex(_real - c._real, _imag - c._imag);
}

Complex Complex::operator-(double& d) {
  return Complex(_real - d, _imag);
}

Complex Complex::operator*(Complex& c) {
  double newReal = _real * c._real + _imag * c._imag * -1;
  double newImag = _real * c._imag + _imag * c._real;
  return Complex(newReal, newImag);
}

Complex Complex::operator*(double& d) {
  return {_real * d, _imag * d};
}

Complex Complex::operator/(Complex& c) {
  if (c._real == 0 && c._imag == 0) {
    throw std::invalid_argument("division by zero");
  }

  double real_numenator = _real * c._real + _imag * c._imag;
  double imag_numenator = _imag * c._real - _real * c._imag;
  double denumenator = c._real * c._real + c._imag * c._imag;

  return {real_numenator / denumenator, imag_numenator / denumenator};
}

Complex Complex::operator/(double& d) {
  if (d == 0) {
    throw std::invalid_argument("division by zero");
  }
  return Complex(_real / d, _imag);
}

Complex::Complex(Complex &&c) noexcept {
  std::swap(_real, c._real);
  std::swap(_imag, c._imag);
}

Complex Complex::operator=(Complex& c) const {
  return Complex(0);
}
