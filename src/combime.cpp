#include"../include/combine.h"
using namespace std;

vector<Line> lineAll;
vector<Ray> rayAll;
vector<Segment> segmentAll;
vector<Circle> circleAll;

void solve(vector <pair<double, double> >& realIntersections) {
	MySet points;
	for (Line line : lineAll) {
		for (Line it : lineAll) {
			if (line.isSame(it)) throw SLException();
			Point* temp = calLineLineIst(line, it);
			if (temp) points.insert(*temp);
		}
		for (Ray it : rayAll) {
			if (line.isSame(it)) throw SLException();
			Point* temp = calLineLineIst(line, it);
			if (temp && it.vaild(*temp)) points.insert(*temp);
		}
		for (Segment it : segmentAll) {
			if (line.isSame(it)) throw SLException();
			Point* temp = calLineLineIst(line, it);
			if (temp && it.vaild(*temp)) points.insert(*temp);
		}
		for (Circle it : circleAll) {
			vector<Point> temp = calLineCircleIst(line, it);
			for (Point i : temp) points.insert(i);
		}
	}
	for (Ray ray : rayAll) {
		for (Line it : lineAll) {
			if (it.isSame(ray)) throw SLException();
			Point* temp = calLineLineIst(ray, it);
			if (temp && ray.vaild(*temp)) points.insert(*temp);
		}
		for (Ray it : rayAll) {
			if (it.isCoincide(ray)) throw SLException();
			Point* temp = calLineLineIst(ray, it);
			if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
		}
		for (Segment it : segmentAll) {
			if (it.isCoincide(ray)) throw SLException();
			Point* temp = calLineLineIst(ray, it);
			if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
		}
		for (Circle it : circleAll) {
			vector<Point> temp = calLineCircleIst(ray, it);
			for (Point i : temp) if (ray.vaild(i)) points.insert(i);
		}
	}
	for (Segment segment : segmentAll) {
		for (Line it : lineAll) {
			if (it.isSame(segment)) throw SLException();
			Point* temp = calLineLineIst(segment, it);
			if (temp && segment.vaild(*temp)) points.insert(*temp);
		}
		for (Ray it : rayAll) {
			if (it.isCoincide(segment)) throw SLException();
			Point* temp = calLineLineIst(segment, it);
			if (temp && it.vaild(*temp) && segment.vaild(*temp)) points.insert(*temp);
		}
		for (Segment it : segmentAll) {
			if (it.isCoincide(segment)) throw SLException();
			Point* temp = calLineLineIst(segment, it);
			if (temp && it.vaild(*temp) && segment.vaild(*temp)) points.insert(*temp);
		}
		for (Circle it : circleAll) {
			vector<Point> temp = calLineCircleIst(segment, it);
			for (Point i : temp) if (segment.vaild(i)) points.insert(i);
		}
	}
	for (Circle circle : circleAll) {
		for (Line it : lineAll) {
			vector<Point> temp = calLineCircleIst(it, circle);
			for (Point i : temp) points.insert(i);
		}
		for (Ray it : rayAll) {
			vector<Point> temp = calLineCircleIst(it, circle);
			for (Point i : temp) if (it.vaild(i)) points.insert(i);
		}
		for (Segment it : segmentAll) {
			vector<Point> temp = calLineCircleIst(it, circle);
			for (Point i : temp) if (it.vaild(i)) points.insert(i);
		}
		for (Circle it : circleAll) {
			if (it.x == circle.x && it.y == circle.y && it.r == circle.r) throw SLException();
			vector<Point> temp = calCircleCircleIst(it, circle);
			for (Point i : temp) points.insert(i);
		}
	}
	for (auto i : points) {
		realIntersections.push_back(pair<double, double>(i.x, i.y));
	}
	cout << points.size() << endl;
}

void ioHandler(string input) {
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
			it = circleAll.erase(it);
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