#include"../include/combine.h"
using namespace std;

vector<Line> lineAll;
vector<Ray> rayAll;
vector<Segment> segmentAll;
vector<Circle> circleAll;

void  __cdecl solve(vector <pair<double, double> >& realIntersections) {
	MySet points;
	for (Line line : lineAll) {
		for (Line it : lineAll) {
			Point* temp = calLineLineIst(line, it);
			if (temp) points.insert(*temp);
		}
		for (Ray it : rayAll) {
			Point* temp = calLineLineIst(line, it);
			if (temp && it.vaild(*temp)) points.insert(*temp);
		}
		for (Segment it : segmentAll) {
			Point* temp = calLineLineIst(line, it);
			if (temp && it.vaild(*temp)) points.insert(*temp);
		}
		for (Circle it : circleAll) {
			vector<Point> temp = calLineCircleIst(line, it);
			for (Point i : temp) points.insert(i);
		}
	}
	for (Ray ray : rayAll) {
		for (Ray it : rayAll) {
			Point* temp = calLineLineIst(ray, it);
			if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
		}
		for (Segment it : segmentAll) {
			Point* temp = calLineLineIst(ray, it);
			if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
		}
		for (Circle it : circleAll) {
			vector<Point> temp = calLineCircleIst(ray, it);
			for (Point i : temp) if (ray.vaild(i)) points.insert(i);
		}
	}
	for (Segment segment : segmentAll) {
		for (Segment it : segmentAll) {
			Point* temp = calLineLineIst(segment, it);
			if (temp && it.vaild(*temp) && segment.vaild(*temp)) points.insert(*temp);
		}
		for (Circle it : circleAll) {
			vector<Point> temp = calLineCircleIst(segment, it);
			for (Point i : temp) if (segment.vaild(i)) points.insert(i);
		}
	}
	for (Circle circle : circleAll) {
		for (Circle it : circleAll) {
			if (it.x == circle.x && it.y == circle.y && it.r == circle.r) continue;
			vector<Point> temp = calCircleCircleIst(it, circle);
			for (Point i : temp) points.insert(i);
		}
	}
	for (auto i : points) {
		realIntersections.push_back(pair<double, double>(i.x, i.y));
	}
	cout << points.size() << endl;
}

void  __cdecl ioHandler(string input) {
	ifstream inputfile(input);
	int n;
	inputfile >> n;
	for (int i = 0; i < n; i++)
	{
		char type;
		inputfile >> type;
		if (type == 'L' || type == 'R' || type == 'S')
		{
			double x1, x2, y1, y2;
			inputfile >> x1 >> y1 >> x2 >> y2;
			if (type == 'L')
				lineAll.push_back(Line(x1, y1, x2, y2));
			else if (type == 'R')
				rayAll.push_back(Ray(x1, y1, x2, y2));
			else if (type == 'S')
				segmentAll.push_back(Segment(x1, y1, x2, y2));
		}
		else if (type == 'C')
		{
			double c1, c2, r;
			inputfile >> c1 >> c2 >> r;
			circleAll.push_back(Circle(c1, c2, r));
		}
	}
}

void __cdecl  addLine(double x1, double y1, double x2, double y2, int type) {
	switch (type) {
	case 0:
		lineAll.push_back(Line(x1, y1, x2, y2));
		break;
	case 1:
		rayAll.push_back(Ray(x1, y1, x2, y2));
		break;
	case 2:
		segmentAll.push_back(Segment(x1, y1, x2, y2));
		break;
	default:
		break;
	}
}

void  __cdecl deleteLine(double x1, double y1, double x2, double y2, int type) {
	switch (type) {
	case 0:
		for (vector<Line>::iterator it = lineAll.begin(); it != lineAll.end();) {
			if (it->x1 == x1 && it->x2 == x2 && it->y1 == y1 && it->y2 == y2)
				it = lineAll.erase(it); 
			else
				++it;
		}
		break;
	case 1:
		for (vector<Ray>::iterator it = rayAll.begin(); it != rayAll.end();) {
			if (it->x1 == x1 && it->x2 == x2 && it->y1 == y1 && it->y2 == y2)
				it = rayAll.erase(it);
			else
				++it;
		}
		break;
	case 2:
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

void  __cdecl addCircle(double c1, double c2, double r) {
	circleAll.push_back(Circle(c1, c2, r));
}

void  __cdecl deleteCircle(double c1, double c2, double r) {
	for (vector<Circle>::iterator it = circleAll.begin(); it != circleAll.end();) {
		if (it->x == c1 && it->y == c2 && it->r == r)
			it = circleAll.erase(it);
		else
			++it;
	}
}

void  __cdecl deleteAll() {
	lineAll.clear();
	rayAll.clear();
	segmentAll.clear();
	circleAll.clear();
}