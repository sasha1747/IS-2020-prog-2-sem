#include "polynomial.h"
Polynomial::Polynomial() {
	minPower_ = 0;
	maxPower_ = 0;
	factors_ = new int[1];
	factors_[0] = 0;
}

Polynomial::Polynomial(int minPower, int maxPower, int* factors) {
	minPower_ = minPower;
	maxPower_ = maxPower;
	factors_ = new int[maxPower - minPower + 1];
	for (int i = 0; i < maxPower - minPower + 1; i++)
		factors_[i] = factors[i];
}

Polynomial::Polynomial(const Polynomial& other) {
	minPower_ = other.minPower_;
	maxPower_ = other.maxPower_;
	factors_ = new int[maxPower_ - minPower_ + 1];
	for (int i = 0; i < maxPower_ - minPower_ + 1; i++)
		factors_[i] = other.factors_[i];
}

Polynomial::~Polynomial() {
	delete[] factors_;
}

double Polynomial::get(int x) const {
	double sum = 0;
	double curr = pow(x, minPower_);

	for (int i = 0; i < maxPower_ - minPower_ + 1; i++) {
		sum += factors_[i] * curr;
		curr *= x;
	}

	return sum;
}

Polynomial& Polynomial::operator= (Polynomial& other) {
	if (*this == other)
		return *this;

	minPower_ = other.minPower_;
	maxPower_ = other.maxPower_;
	int* copy = new int[maxPower_ - minPower_ + 1];

	for (int i = 0; i < maxPower_ - minPower_ + 1; i++)
		copy[i] = other.factors_[i];

	delete[] factors_;
	factors_ = copy;
	return *this;
}

bool Polynomial::operator== (const Polynomial& other) const {
	int minPower, maxPower;
	if (minPower_ > other.minPower_)
		minPower = other.minPower_;
	else
		minPower = minPower_;

	if (maxPower_ > other.maxPower_)
		maxPower = maxPower_;
	else
		maxPower = other.maxPower_;

	for (int i = minPower; i < maxPower; i++) {
		if (other[i] != this->operator[](i))
			return 0;
	}

	return 1;
}

bool Polynomial::operator!= (const Polynomial& other) const {
	return !(*this == other);
}


Polynomial& Polynomial::operator+= (const Polynomial& rhs) {
	return forPlusMinus(rhs, 1);
}

Polynomial& Polynomial::operator-= (const Polynomial& rhs) {
	return forPlusMinus(rhs, -1);
}

Polynomial& Polynomial::forPlusMinus(const Polynomial& rhs, int multiplier) {
	int minPower, maxPower;
	if (minPower_ > rhs.minPower_)
		minPower = rhs.minPower_;
	else
		minPower = minPower_;

	if (maxPower_ > rhs.maxPower_)
		maxPower = maxPower_;
	else
		maxPower = rhs.maxPower_;

	int* copy = new int[maxPower - minPower + 1];
	for (int i = 0; i < maxPower - minPower + 1; i++)
		copy[i] = 0;

	for (int i = 0; i < maxPower_ - minPower_ + 1; i++)
		copy[minPower_ - minPower + i] = factors_[i];

	for (int i = 0; i < rhs.maxPower_ - rhs.minPower_ + 1; i++)
		copy[rhs.minPower_ - minPower + i] = copy[rhs.minPower_ - minPower + i] + multiplier * rhs.factors_[i];

	delete[] factors_;

	factors_ = copy;
	minPower_ = minPower;
	maxPower_ = maxPower;

	return *this;
}

Polynomial& Polynomial::operator*= (const Polynomial& rhs) {
	int minPower = minPower_ + rhs.minPower_;
	int maxPower = maxPower_ + rhs.maxPower_;

	int* copy = new int[maxPower - minPower + 1];

	for (int i = 0; i < maxPower - minPower + 1; i++)
		copy[i] = 0;

	for (int i = 0; i < maxPower_ - minPower_ + 1; i++)
		for (int j = 0; j < rhs.maxPower_ - rhs.minPower_ + 1; j++)
			copy[i + j] += factors_[i] * rhs.factors_[j];

	minPower_ = minPower;
	maxPower_ = maxPower;

	delete[] factors_;
	factors_ = copy;

	return *this;
}

Polynomial& Polynomial::operator/= (int rhs) {
	for (int i = 0; i < maxPower_ - minPower_ + 1; i++)
		factors_[i] /= rhs;

	return *this;
}

Polynomial Polynomial::operator- () {
	int* copy = new int[maxPower_ - minPower_ + 1];
	for (int i = 0; i < maxPower_ - minPower_ + 1; i++)
		copy[i] = -factors_[i];
	return Polynomial(minPower_, maxPower_, copy);
}

int Polynomial::operator[] (int i) const {
	if (i < minPower_ || i > maxPower_)
		return 0;
	return factors_[i - minPower_];
}

int& Polynomial::operator[] (int i) {
	if (i >= maxPower_ - minPower_ + 1) {
		int* copy = new int[i - minPower_ + 1];
		for (int j = 0; j < i - minPower_ + 1; j++)
			copy[j] = 0;

		for (int j = 0; j < maxPower_ - minPower_ + 1; j++) {
			copy[j] = factors_[j];
		}
		maxPower_ = i;
		delete[] factors_;
		factors_ = copy;
	}
	return factors_[i - minPower_];
}

const Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial lhs_(lhs);
	return lhs_ += rhs;
}

const Polynomial operator- (const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial lhs_(lhs);
	return lhs_ -= rhs;
}

const Polynomial operator* (const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial lhs_(lhs);
	return lhs_ *= rhs;
}

const Polynomial operator* (int lhs, const Polynomial& rhs) {
	int* copy = new int[rhs.maxPower_ - rhs.minPower_ + 1];
	for (int i = 0; i < rhs.maxPower_ - rhs.minPower_ + 1; i++)
		copy[i] = lhs * rhs.factors_[i];
	return Polynomial(rhs.minPower_, rhs.maxPower_, copy);
}

//fixed copy-paste *
const Polynomial operator* (const Polynomial& lhs, const int rhs) {
	return rhs * lhs;
}


const Polynomial operator/ (const Polynomial& lhs, const int rhs) {
	Polynomial lhs_(lhs);
	return lhs_ /= rhs;
}

std::stringstream& operator<< (std::stringstream& lhs, const Polynomial& rhs) {
	for (int i = rhs.maxPower_ - rhs.minPower_; i >= 1; i--) {
		if (rhs.factors_[i] == 0)
			continue;

		if (rhs.factors_[i] == -1 && i == rhs.maxPower_ - rhs.minPower_)
			lhs << "-";

		if (rhs.minPower_ + i == 0) {
			lhs << rhs.factors_[i];
		}
		else if (rhs.minPower_ + i == 1) {
			if (rhs.factors_[i] == -1)
				lhs << "-x";
			else if (rhs.factors_[i] == 1)
				lhs << "x";
			else
				lhs << rhs.factors_[i] << "x";
		}
		else {
			if (rhs.factors_[i] != 1 && rhs.factors_[i] != -1)
				lhs << rhs.factors_[i] << "x^" << rhs.minPower_ + i;
			else
				lhs << "x^" << rhs.minPower_ + i;
		}

		if (rhs.factors_[i - 1] > 0)
			lhs << "+";
	}
	if (rhs.factors_[0] == 0 && rhs.minPower_ != rhs.maxPower_) {
		return lhs;
	}

	if (rhs.maxPower_ - rhs.minPower_ + 1 >= 2)
		if (rhs.factors_[1] == 0)
			if (rhs.factors_[0] == 1)
				lhs << "+";

	if (rhs.minPower_ == 0) {
		lhs << rhs.factors_[0];
	}
	else if (rhs.minPower_ == 1) {
		if (rhs.factors_[0] == -1)
			lhs << "-x";
		else if (rhs.factors_[0] == 1)
			lhs << "x";
		else
			lhs << rhs.factors_[0] << "x";
	}
	else {
		if (rhs.factors_[0] != 1 && rhs.factors_[0] != -1)
			lhs << rhs.factors_[0] << "x^" << rhs.minPower_;
		else
			lhs << "x^" << rhs.minPower_;
	}
	return lhs;
}