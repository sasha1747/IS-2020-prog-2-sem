#include "geometry.h"
#include <iostream>
#include <cassert>
#include <math.h>
const double PI = 3.141592653;

Point::Point(int x, int y)
	: X(x)
	, Y(y)
{}
Point::Point(const Point& other)
	: X(other.X)
	, Y(other.Y)
{}

Point& Point:: operator= (const Point& other) {
	if (&other == this)
		return *this;

	X = other.X;
	Y = other.Y;

	return *this;
}

PolygonalChain::PolygonalChain(int N, Point* points) {
	_N = N;
	_points = new Point[N];
	for (int i = 0; i < N; i++) {
		_points[i] = points[i];
	}
}
PolygonalChain::PolygonalChain(const PolygonalChain& other) {
	_N = other._N;
	_points = new Point[_N];
	for (int i = 0; i < _N; i++)
		_points[i] = other._points[i];
}
PolygonalChain& PolygonalChain:: operator=(const PolygonalChain& other) {
	if (&other == this)
		return *this;
	delete[]_points;
	_N = other._N;
	_points = new Point[_N];
	for (int i = 0; i < _N; i++)
		_points[i] = other._points[i];

	return *this;
}
PolygonalChain::~PolygonalChain() {
	delete[] _points;
	_points = nullptr;
}
double PolygonalChain::perimeter() const {
	double perem = 0;
	for (int i = 0; i < getN() - 1; i++)
		perem += sqrt(pow(getPoint(i).getX() - getPoint(i + 1).getX(), 2) + pow(getPoint(i).getY() - getPoint(i + 1).getY(), 2));
	return perem;
}

ClosedPolygonalChain::ClosedPolygonalChain(int N, Point* points)
	:PolygonalChain(N, points)
{}
ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other)
	: PolygonalChain(other)
{}
ClosedPolygonalChain& ClosedPolygonalChain:: operator=(const ClosedPolygonalChain& other) {
	PolygonalChain:: operator=(other);
	return *this;
}
double ClosedPolygonalChain::perimeter() const {
	double per = PolygonalChain::perimeter();
	per += sqrt(pow(getPoint(getN() - 1).getX() - getPoint(0).getX(), 2) + pow(getPoint(getN() - 1).getY() - getPoint(0).getY(), 2));
	return per;
}

Polygon::Polygon(int N, Point* points)
	:ClosedPolygonalChain(N, points)
{}
Polygon::Polygon(const Polygon& other)
	: ClosedPolygonalChain(other)
{}
Polygon& Polygon:: operator=(const Polygon& other) {
	ClosedPolygonalChain:: operator=(other);
	return *this;
}
double Polygon::area() const {
	int S = 0;
	for (int i = 0; i < getN() - 1; i++)
		S += getPoint(i).getX() * getPoint(i + 1).getY() - getPoint(i + 1).getX() * getPoint(i).getY();
	S += getPoint(getN() - 1).getX() * getPoint(0).getY() - getPoint(0).getX() * getPoint(getN() - 1).getY();
	return (0.5 * abs(S));
}
Triangle::Triangle(int N, Point* points)
	: Polygon(N, points)
{}
Triangle::Triangle(const Triangle& other)
	: Polygon(other)
{}
Triangle& Triangle:: operator=(const Triangle& other) {
	Polygon:: operator=(other);
	return *this;
}
int Triangle::hasRightAngle() const {
	int w1x = getPoint(1).getX() - getPoint(0).getX();
	int w1y = getPoint(1).getY() - getPoint(0).getY();
	int w2x = getPoint(2).getX() - getPoint(1).getX();
	int w2y = getPoint(2).getY() - getPoint(1).getY();
	int w3x = getPoint(2).getX() - getPoint(0).getX();
	int w3y = getPoint(2).getY() - getPoint(0).getY();
	return ((w1x * w2x + w1y * w2y == 0)
		|| (w3x * w2x + w3y * w2y == 0)
		|| (w1x * w3x + w1y * w3y == 0));
}

Trapezoid::Trapezoid(int N, Point* points)
	: Polygon(N, points)
{}

Trapezoid::Trapezoid(const Trapezoid& other)
	: Polygon(other)
{}

Trapezoid& Trapezoid:: operator=(const Trapezoid& other) {
	Polygon:: operator=(other);
	return *this;
}
double Trapezoid::height() const {
	double Hei = (2 * area()) / ((sqrt(pow(getPoint(1).getX() - getPoint(2).getX(), 2) + pow(getPoint(1).getY() - getPoint(2).getY(), 2))) + (sqrt(pow(getPoint(3).getX() - getPoint(0).getX(), 2) + pow(getPoint(3).getY() - getPoint(0).getY(), 2))));
	return Hei;
}

RegularPolygon::RegularPolygon(int N, Point* points)
	: Polygon(N, points)
{}

RegularPolygon::RegularPolygon(const RegularPolygon& other)
	: Polygon(other)
{}

RegularPolygon& RegularPolygon:: operator=(const RegularPolygon& other) {
	Polygon:: operator=(other);
	return *this;
}

double RegularPolygon::perimeter() const {
	double s = sqrt(pow(getPoint(0).getX() - getPoint(1).getX(), 2) + pow(getPoint(0).getY() - getPoint(1).getY(), 2));
	return getN() * s;
}

double RegularPolygon::area() const {
	int side = pow(getPoint(0).getX() - getPoint(1).getX(), 2) + pow(getPoint(0).getY() - getPoint(1).getY(), 2);
	int num = getN() * side;
	double area = num / (tan(PI / getN()) * 4);
	return area;
}