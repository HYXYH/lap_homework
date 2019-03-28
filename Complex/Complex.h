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

	Complex(double real, double imaginary = 0) : _real(real), _imag(imaginary) {};
//	Complex(Complex&& c);

	Complex operator=(Complex c);

	Complex operator+(Complex c);
	Complex operator+(double d);
	Complex operator-(Complex c);
	Complex operator-(double d);
	Complex operator*(Complex c);
	Complex operator*(double d);
	Complex operator/(Complex c);
	Complex operator/(double d);

	double abs();
	Complex conj();
};


#endif //LAP_HOMEWORK_COMPLEX_H
