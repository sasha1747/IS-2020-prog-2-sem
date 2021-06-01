#pragma once
#include <cmath>
#include <sstream>
class Polynomial {
private:
	int minPower_, maxPower_;
	int* factors_;

public:
	Polynomial();

	Polynomial(int minPower, int maxPower, int* factors);

	Polynomial(const Polynomial& other);

	~Polynomial();

	double get(int x) const;

	Polynomial& operator= (Polynomial& other);

	bool operator== (const Polynomial& other) const;

	bool operator!= (const Polynomial& other) const;

	friend const Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs);
	friend const Polynomial operator- (const Polynomial& lhs, const Polynomial& rhs);
	friend const Polynomial operator* (const Polynomial& lhs, const Polynomial& rhs);
	friend const Polynomial operator* (int lhs, const Polynomial& rhs);
	friend const Polynomial operator* (const Polynomial& lhs, int rhs);
	friend const Polynomial operator/ (const Polynomial& lhs, int rhs);
	friend std::stringstream& operator<< (std::stringstream& lhs, const Polynomial& rhs);

	Polynomial& operator+= (const Polynomial& rhs);

	Polynomial& operator-= (const Polynomial& rhs);

	Polynomial& forPlusMinus(const Polynomial& rhs, int multiplier);

	Polynomial& operator*= (const Polynomial& rhs);

	Polynomial& operator/= (int rhs);

	Polynomial operator- ();

	int operator[] (int i) const;

	int& operator[] (int i);
};