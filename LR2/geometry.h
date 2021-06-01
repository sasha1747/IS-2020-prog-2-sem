#pragma once


class Point {
private:
	int X;
	int Y;
public:
	Point(const Point& other);
	Point(int x = 0, int y = 0);
	Point& operator=(const Point& other);
	int getX() const { return X; }
	int getY() const { return Y; }
};
class PolygonalChain {
private:
	Point* _points;
	int _N;
public:
	PolygonalChain(int N, Point* points);
	PolygonalChain(const PolygonalChain& other);
	PolygonalChain& operator=(const PolygonalChain& other);
	~PolygonalChain();
	int getN() const { return _N; }
	Point getPoint(int num) const { return  _points[num]; }
	virtual double perimeter() const;
};
class ClosedPolygonalChain : public PolygonalChain {
public:
	ClosedPolygonalChain(int N, Point* points);
	ClosedPolygonalChain(const ClosedPolygonalChain& other);
	ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other);
	double perimeter() const override;
};
class Polygon : public ClosedPolygonalChain {
public:
	Polygon(int N, Point* points);
	Polygon(const Polygon& other);
	Polygon& operator=(const Polygon& other);
	virtual double area() const;
};
class Triangle : public Polygon {
public:
	Triangle(const Triangle& other);
	int hasRightAngle() const;
	Triangle(int N, Point* points);
	Triangle& operator=(const Triangle& other);
};
class Trapezoid : public Polygon {
public:
	Trapezoid& operator=(const Trapezoid& other);
	double height() const;
	Trapezoid(const Trapezoid& other);
	Trapezoid(int N, Point* points);
};
class RegularPolygon : public Polygon {
public:
	RegularPolygon(const RegularPolygon& other);
	double area() const override;
	RegularPolygon(int N, Point* points);
	double perimeter() const override;
	RegularPolygon& operator=(const RegularPolygon& other);
};




/*

class Point {
public:
	Point();
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void setX(int _x) {
		x = _x;
	}
	void setY(int _y) {
		y = _y;
	}
	int getX()const {
		return x;
	}
	int getY()const {
		return y;
	}
	int dist(Point b) {
		return(sqrt(pow(b.x - x, 2) + pow(b.y - y, 2)));
	}
private:
	int x, y;
};
*/