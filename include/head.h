#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <vector>
#include <set>
#include<string>
#include <unordered_set>

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
		if (fabs(x - other.x) <= EPS && fabs(y - other.y) <= EPS) {
			return false;
		}
		else {
			return (x != other.x) ? x < other.x : y < other.y;
		}
	}

};

// Line: ax + by + c = 0 (a^2+b^2!=0)
class Line
{
public:
	int a, b, c;

	Line() :a(), b(), c() {}

	Line(int a, int b, int c) :a(a), b(b), c(c) {}

	// ax1+by1+c=0, ax2+by2+c=0 
	// ==> a=y1-y2, b=x2-x1, c=x1*y2-x2*y1
	Line(int x1, int y1, int x2, int y2) :
		a(y1 - y2),
		b(x2 - x1),
		c(x1* y2 - x2 * y1)
	{}
};

// Circle: (x-x0)^2 + (y-y0)^2 = r0^2, x^2 + y^2 + dx + ey + f = 0
class Circle
{
public:
	int x, y, r;
	int d, e, f;

	Circle() :x(), y(), r(), d(), e(), f() {}

	// (x-x0)^2+(y-y0)^2=r0^2, x^2+y^2+dx+ey+f=0
	// ==> d=-2*x0, e=-2*y0, f=x0^2+y0^2-r0^2
	Circle(int x0, int y0, int r0) :
		x(x0),
		y(y0),
		r(r0),
		d(-2 * x0),
		e(-2 * y0),
		f((int)(pow(x0, 2) + pow(y0, 2) - pow(r0, 2)))
	{}

};

//hash of point set
struct PointHash
{
	std::size_t operator()(const Point& point) const
	{
		return std::hash<double>()(point.x) + (std::hash<double>()(point.y) << 16);
	}
};

typedef std::unordered_set<Point, PointHash> MySet;

bool isNum(std::string s);
// calculate the intersections of two lines
void calLineLineIst(Line& line1, Line& line2, MySet& points);

// calculate the intersections of line and Circle
void calLineCircleIst(Line& line, Circle& circle, MySet& points);

// calculate intersections of two circles
void calCircleCircleIst(Circle& circle1, Circle& circle2, MySet& points);

