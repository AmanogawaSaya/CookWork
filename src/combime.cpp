#include"../include/combine.h"
using namespace std;

vector<Line> lineAll;
vector<Ray> rayAll;
vector<Segment> segmentAll;
vector<Circle> circleAll;

void solve(vector <pair<double, double> >& realIntersections) {

}

void addLine(double x1, double y1, double x2, double y2, int type) {
	switch (type) {
	case 'L':
		lineAll.push_back(Line(x1, y1, x2, y2));
		break;
	case 'R':
		rayAll.push_back(Ray(x1, y1, x2, y2));
		break;
	case 'S':
		segmentAll.push_back(Segment(x1, y1, x2, y2));
		break;
	default:
		break;
	}
}

void deleteLine(double x1, double y1, double x2, double y2, int type) {
	switch (type) {
	case 'L':
		for (vector<Line>::iterator it = lineAll.begin(); it != lineAll.end();) {
			if (it->x1 == x1 && it->x2 == x2 && it->y1 == y1 && it->y2 == y2)
				it = lineAll.erase(it); 
			else
				++it;
		}
		break;
	case 'R':
		for (vector<Ray>::iterator it = rayAll.begin(); it != rayAll.end();) {
			if (it->x1 == x1 && it->x2 == x2 && it->y1 == y1 && it->y2 == y2)
				it = rayAll.erase(it);
			else
				++it;
		}
		break;
	case 'S':
		for (vector<Segment>::iterator it = segmentAll.begin(); it != segmentAll.end();) {
			if (it->x1 == x1 && it->x2 == x2 && it->y1 == y1 && it->y2 == y2)
				it = segmentAll.erase(it);
			else
				++it;
		}
		break;
	default:
		break;
	}
}

void addCircle(double c1, double c2, double r) {
	circleAll.push_back(Circle(c1, c2, r));
}

void deleteCircle(double c1, double c2, double r) {
	for (vector<Circle>::iterator it = circleAll.begin(); it != circleAll.end();) {
		if (it->x == c1 && it->y == c2 && it->r == r)
			it = segmentAll.erase(it);
		else
			++it;
	}
}

void deteleAll() {
	lineAll.clear();
	rayAll.clear();
	segmentAll.clear();
	circleAll.clear();
}