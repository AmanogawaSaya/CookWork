#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <vector>
#include <set>
#include<string>
#include <unordered_set>
#include<algorithm>
#include<regex>
using namespace std;
#define EPS 1e-7

// Point: (x, y)
struct Point
{
	double x, y;

	Point() :x(), y() {}

	Point(double x, double y) :x(x), y(y) {}

	bool operator == (const Point& other) const {
		return fabs(x - other.x) <= EPS && fabs(y - other.y) <= EPS;
	}

	bool operator < (const Point& other) const {
		if (fabs(x - other.x) <= EPS && fabs(y - other.y) <= EPS) return false;
		else return (x != other.x) ? x < other.x : y < other.y;
	}

};

// Line: ax + by + c = 0 (a^2+b^2!=0)
class Line
{
public:
	int a, b, c;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	Line() :a(), b(), c() {}

	Line(int a, int b, int c) :a(a), b(b), c(c) {}

	Line(int x1, int y1, int x2, int y2) : a(y1 - y2), b(x2 - x1), c(x1* y2 - x2 * y1),
	x1(x1), y1(y1), x2(x2), y2(y2){}

	bool isParel(Line B) {
		return a * B.b == B.a * b;
	}

	bool isSame(Line B) {
		return isParel(B) && a * B.c == c * B.a;
	}
};

// Circle: (x-x0)^2 + (y-y0)^2 = r0^2, x^2 + y^2 + dx + ey + f = 0
class Circle
{
public:
	int x, y, r;
	int d, e, f;

	Circle() :x(), y(), r(), d(), e(), f() {}

	Circle(int x0, int y0, int r0) :x(x0), y(y0), r(r0), d(-2 * x0), e(-2 * y0),
		f((int)(pow(x0, 2) + pow(y0, 2) - pow(r0, 2))) {}
};

class Ray : public Line {
public:

	Ray(int x1, int y1, int x2, int y2) :Line(x1, y1, x2, y2) {}

	Ray() : Line(){}

	int vaild(Point A) {
		/*和端点重合*/
		if (A.x == x1 && A.y == y1) {
			return 2;
		}
		/*在射线上*/
		else if ((A.x - x1) * ((double)x2 - x1) >= 0 && (A.y - y1) * ((double)y2 - y1) >= 0) {
			return 1;
		} 
		return 0;
	}

	int isCoincide(Ray A) {
		if (isSame(A) ) {
			/*方向相同*/
			if ((A.x1 - A.x2) * (x1 - x2) >= 0 && (A.y1 - A.y2) * (y1 - y2) >= 0) {
				return 1;
			}
			/*方向相反*/
			else if ((A.x1 - A.x2) * (x1 - x2) <= 0 && (A.y1 - A.y2) * (y1 - y2) <= 0) {
				return vaild(Point(A.x1, A.y1));
			}
		}
		return 0;
	}
};

class Segment : public Ray {
public:

	Segment() : Ray(){}

	Segment(int x1, int y1, int x2, int y2) : Ray(x1, y1, x2, y2) {
		if (x1 > x2) {
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}
	}

	int vaild(Point A) {
		/*和第一个端点重合*/
		if (A.x == x1 && A.y == y1) return 2;
		if (A.x == x2 && A.y == y2) return 3;
		return (A.x - x1) * (A.x - x2) <= 0 && (A.y - y1) * (A.y - y2) <= 0;
	}

	int isCoincide(Ray A) {
		return 0;
	}

	int isCoincide(Segment A) {
		if (!isSame(A)) return 0;
		int ret1 = vaild(Point(A.x1, A.y1));
		int ret2 = vaild(Point(A.x2, A.y2));
		if (ret1 == 1 || ret2 == 1) return 1;
		if (ret1 > 1 && ret2 > 1) return 1;
		return max(ret1, ret2);
	}
};

//hash of point set
struct PointHash {
	std::size_t operator()(const Point& point) const
	{
		return std::hash<double>()(point.x) + (std::hash<double>()(point.y) << 16);
	}
};

typedef std::unordered_set<Point, PointHash> MySet;

__declspec(dllexport) bool isNum(std::string s);
__declspec(dllexport) bool rangeVaild(int n);
__declspec(dllexport) void inputCheck(ifstream& fileIn, int& x1, int& y1, int& x2, int& y2);
__declspec(dllexport) void inputCheck(ifstream& fileIn, int& x, int& y, int& r);
// calculate the intersections of two lines
__declspec(dllexport) Point* calLineLineIst(Line line1, Line line2);

// calculate the intersections of line and Circle
__declspec(dllexport) vector<Point> calLineCircleIst(Line line, Circle circle);

// calculate intersections of two circles
__declspec(dllexport) vector<Point> calCircleCircleIst(Circle circle1, Circle circle2);


__declspec(dllexport) vector<string> split(const string& str, const string& pattern);

__declspec(dllexport) void inputCheck2(vector<string> input, int& x1, int& y1, int& x2, int& y2);

__declspec(dllexport) void inputCheck2(vector<string> input, int& x, int& y, int& r);

__declspec(dllexport) MySet result(vector<string> fileIn);