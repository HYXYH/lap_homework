//
// Created by Оскар on 10.03.19.
//

#ifndef LAP_HOMEWORK_COMPLEX_H
#define LAP_HOMEWORK_COMPLEX_H

class Complex {
  double _real;
  double _imag;

 public:
  double get_real();
  double get_imag();

  explicit Complex(double real) : _real(real), _imag(0) {};

  Complex(double real, double imaginary) : _real(real), _imag(imaginary) {};
  Complex(Complex &&c) noexcept ;

  Complex operator=(Complex& c) const;

  Complex operator+(Complex& c);
  Complex operator+(double& d);
  Complex operator-(Complex& c);
  Complex operator-(double& d);
  Complex operator*(Complex& c);
  Complex operator*(double& d);
  Complex operator/(Complex& c);
  Complex operator/(double& d);

  double abs();
  Complex conj();
};

#endif //LAP_HOMEWORK_COMPLEX_H
