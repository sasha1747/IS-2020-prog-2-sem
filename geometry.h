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


class ClosedPolygonalChain
{
protected:
	int cnt;
	Point* a;
public:
	ClosedPolygonalChain();
	ClosedPolygonalChain(int _cnt, Point* _a) {
		cnt = _cnt;
		a = _a;
	}
	ClosedPolygonalChain(ClosedPolygonalChain& toCopy) {
		cnt = toCopy.cnt;
		a = toCopy.a;
	}
	int getN()const {
		return cnt;
	}
	Point getPoint(int i)const {
		return a[i];
	}
	int perimeter() const {
		int res = 0;
		for (int i = 0; i < cnt; i++) {
			res += a[i].dist(a[(i + 1) % cnt]);
		}
		return res;
	}
private:

};


class Polygon :public ClosedPolygonalChain
{
public:
	Polygon() :ClosedPolygonalChain()
	{}
	Polygon(int _cnt, Point* a) :ClosedPolygonalChain(_cnt, a)
	{}

private:

};


class Triangle :public ClosedPolygonalChain
{
public:
	Triangle() :ClosedPolygonalChain()
	{}
	Triangle(int _cnt, Point* a) :ClosedPolygonalChain(_cnt, a)
	{}

private:

};


class PolygonalChain :public ClosedPolygonalChain
{
public:
	PolygonalChain() :ClosedPolygonalChain()
	{}
	PolygonalChain(int _cnt, Point* a) :ClosedPolygonalChain(_cnt, a)
	{}
private:

};

class Trapezoid :public ClosedPolygonalChain
{
public:
	Trapezoid() :ClosedPolygonalChain()
	{}
	Trapezoid(int _cnt, Point* a) :ClosedPolygonalChain(_cnt, a)
	{}

private:

};

class RegularPolygon :public ClosedPolygonalChain
{
public:
	RegularPolygon() : ClosedPolygonalChain()
	{}
	RegularPolygon(int _cnt, Point* a) : ClosedPolygonalChain(_cnt, a)
	{}

private:

};
