#pragma once
#include<string>
#include<vector>
#include"../include/head.h"
#include"../include/FormatExpetion.h"
using namespace std;



vector<string> split(const string& str, const string& pattern) {
	vector<string> ret;
	if (pattern.empty())
		return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos) {
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

void inputCheck2(vector<string> input, int& x1, int& y1, int& x2, int& y2) {
	string temp;
	int index = 1;
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	x1 = atoi(temp.c_str());
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	y1 = atoi(temp.c_str());
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	x2 = atoi(temp.c_str());
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	y2 = atoi(temp.c_str());
	if (x1 == x2 && y1 == y2) throw DSException();
	if (!rangeVaild(x1) || !rangeVaild(y1) || !rangeVaild(x2) || !rangeVaild(y2)) throw INException();
}

void inputCheck2(vector<string> input, int& x, int& y, int& r) {
	string temp;
	int index = 1;
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	x = atoi(temp.c_str());
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	y = atoi(temp.c_str());
	temp = input[index++];
	if (!isNum(temp)) throw INException();
	r = atoi(temp.c_str());
	if (!rangeVaild(x) || !rangeVaild(y)) throw INException();
	if (r <= 0 || r >= 100000) throw RIException();
}

MySet result(vector<string> fileIn) {
	int N;
	char type;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	int x = 0, y = 0, r = 0;
	int index = 0;
	Line line;
	Circle circle;
	Ray ray;
	Segment segment;
	vector<Line> lines;
	vector<Ray> rays;
	vector<Segment> segments;
	vector<Circle> circles;

	// set of intersections
	MySet points;

	try {
		string temp = fileIn[index++];
		if (!isNum(temp)) throw INException();
		N = atoi(temp.c_str());
		if (N < 2) throw TFException();

		for (int i = 0; i < N; i++) {
			vector<string> input = split(fileIn[index++], " ");
			type = input[0][0];
			switch (type) {
			case 'L':
				inputCheck2(input, x1, y1, x2, y2);
				line = Line(x1, y1, x2, y2);
				for (Line it : lines) {
					if (line.isSame(it)) throw SLException();
					Point* temp = calLineLineIst(line, it);
					if (temp) points.insert(*temp);
				}
				for (Ray it : rays) {
					if (line.isSame(it)) throw SLException();
					Point* temp = calLineLineIst(line, it);
					if (temp && it.vaild(*temp)) points.insert(*temp);
				}
				for (Segment it : segments) {
					if (line.isSame(it)) throw SLException();
					Point* temp = calLineLineIst(line, it);
					if (temp && it.vaild(*temp)) points.insert(*temp);
				}
				for (Circle it : circles) {
					vector<Point> temp = calLineCircleIst(line, it);
					for (Point i : temp) points.insert(i);
				}
				lines.emplace_back(line);
				break;
			case 'R':
				inputCheck2(input, x1, y1, x2, y2);
				ray = Ray(x1, y1, x2, y2);
				for (Line it : lines) {
					if (it.isSame(ray)) throw SLException();
					Point* temp = calLineLineIst(ray, it);
					if (temp && ray.vaild(*temp)) points.insert(*temp);
				}
				for (Ray it : rays) {
					if (it.isCoincide(ray)) throw SLException();
					Point* temp = calLineLineIst(ray, it);
					if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
				}
				for (Segment it : segments) {
					if (it.isCoincide(ray)) throw SLException();
					Point* temp = calLineLineIst(ray, it);
					if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
				}
				for (Circle it : circles) {
					vector<Point> temp = calLineCircleIst(ray, it);
					for (Point i : temp) if (ray.vaild(i)) points.insert(i);
				}
				rays.emplace_back(ray);
				break;
			case 'S':
				inputCheck2(input, x1, y1, x2, y2);
				segment = Segment(x1, y1, x2, y2);
				for (Line it : lines) {
					if (it.isSame(segment)) throw SLException();
					Point* temp = calLineLineIst(segment, it);
					if (temp && segment.vaild(*temp)) points.insert(*temp);
				}
				for (Ray it : rays) {
					if (it.isCoincide(segment)) throw SLException();
					Point* temp = calLineLineIst(segment, it);
					if (temp && it.vaild(*temp) && segment.vaild(*temp)) points.insert(*temp);
				}
				for (Segment it : segments) {
					if (it.isCoincide(segment)) throw SLException();
					Point* temp = calLineLineIst(segment, it);
					if (temp && it.vaild(*temp) && segment.vaild(*temp)) points.insert(*temp);
				}
				for (Circle it : circles) {
					vector<Point> temp = calLineCircleIst(segment, it);
					for (Point i : temp) if (segment.vaild(i)) points.insert(i);
				}
				segments.emplace_back(segment);
				break;
			case 'C':
				inputCheck2(input, x, y, r);
				circle = Circle(x, y, r);
				for (Line it : lines) {
					vector<Point> temp = calLineCircleIst(it, circle);
					for (Point i : temp) points.insert(i);
				}
				for (Ray it : rays) {
					vector<Point> temp = calLineCircleIst(it, circle);
					for (Point i : temp) if (it.vaild(i)) points.insert(i);
				}
				for (Segment it : segments) {
					vector<Point> temp = calLineCircleIst(it, circle);
					for (Point i : temp) if (it.vaild(i)) points.insert(i);
				}
				for (Circle it : circles) {
					if (it.x == circle.x && it.y == circle.y && it.r == circle.r) throw SLException();
					vector<Point> temp = calCircleCircleIst(it, circle);
					for (Point i : temp) points.insert(i);
				}
				circles.emplace_back(circle);
				break;
			default:
				throw TException();
				break;
			}
		}
		cout << points.size() << endl;
	}
	catch (INException e) { cout << e.info() << endl; }
	catch (TFException e) { cout << e.info() << endl; }
	catch (DSException e) { cout << e.info() << endl; }
	catch (SLException e) { cout << e.info() << endl; }
	catch (TException e) { cout << e.info() << endl; }
	catch (RIException e) { cout << e.info() << endl; }

	//cout << "Finish!!!   Result is in \"" << fout_name << "\"";
	return points;
}