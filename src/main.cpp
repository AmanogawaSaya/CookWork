#include "../include/head.h"
#include "../include/FormatExpetion.h"

using namespace std;

bool isNum(string s) {
	return regex_match(s, regex("(0|-?[1-9]\\d*)"));
}

bool rangeVaild(int n) {
	return n > -100000 && n < 100000;
}

void inputCheck(ifstream& fileIn, int& x1, int& y1, int& x2, int& y2) {
	string temp;
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	x1 = atoi(temp.c_str());
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	y1 = atoi(temp.c_str());
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	x2 = atoi(temp.c_str());
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	y2 = atoi(temp.c_str());
	if (x1 == x2 && y1 == y2) throw DSException();
	if (!rangeVaild(x1) || !rangeVaild(y1) || !rangeVaild(x2) || !rangeVaild(y2)) throw INException();
}

void inputCheck(ifstream& fileIn, int& x, int& y, int& r) {
	string temp;
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	x = atoi(temp.c_str());
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	y = atoi(temp.c_str());
	fileIn >> temp;
	if (!isNum(temp)) throw INException();
	r = atoi(temp.c_str());
	if (!rangeVaild(x) || !rangeVaild(y)) throw INException();
	if (r <= 0 || r >= 100000) throw RIException();
}

// calculate the intersections of two lines
Point* calLineLineIst(Line line1, Line line2) {
	int D;

	D = line1.a * line2.b - line2.a * line1.b;
	if (D == 0) {
		return NULL;
	}
	else {
		Point* point = new Point{
			(double)((double)line1.b * (double)line2.c - (double)line2.b * (double)line1.c) / (double)D,
			(double)((double)line2.a * (double)line1.c - (double)line1.a * (double)line2.c) / (double)D
		};
		return point;
	}
}

// calculate the intersections of line and Circle
vector<Point> calLineCircleIst(Line line, Circle circle) {
	long long int intercept;
	vector<Point> output;

	intercept = (long long int)((pow(circle.r, 2) * (pow(line.a, 2) + pow(line.b, 2)) -
		pow(line.a * circle.x + line.b * circle.y + line.c, 2)));

	if (intercept < 0) {
		return output;
	}

	Line tLine(line.b, -line.a, line.a * circle.y - line.b * circle.x);
	int D;
	D = tLine.a * line.b - line.a * tLine.b;

	// tPoint is the intersection of line and tLine
	Point tPoint(
		(double)((double)tLine.b * (double)line.c - (double)line.b * (double)tLine.c) / (double)D,
		(double)((double)line.a * (double)tLine.c - (double)tLine.a * +(double)line.c) / (double)D
	);

	switch (intercept)
	{
	case 0:	// line is tangent to circle
		output.push_back(tPoint);
		break;

	default:// line passes through circle
		double vecX;
		double vecY;
		double offset;

		// (vecX, vecY) is a unit vector
		vecX = (double)(line.b / sqrt(pow(line.a, 2) + pow(line.b, 2)));
		vecY = (double)(-line.a / sqrt(pow(line.a, 2) + pow(line.b, 2)));

		// Offset is half of the intercept
		offset = (double)sqrt(intercept / (pow(line.a, 2) + pow(line.b, 2)));

		// intersection = tPoint +/- vec*offset
		Point ist1 = {
			tPoint.x + vecX * offset,
			tPoint.y + vecY * offset
		};
		Point ist2 = {
			tPoint.x - vecX * offset,
			tPoint.y - vecY * offset
		};
		output.push_back(ist1);
		output.push_back(ist2);
		break;
	}
	return output;
}

// calculate intersections of two circles
vector<Point> calCircleCircleIst(Circle circle1, Circle circle2) {
	int radiusSum;
	int radiusDiff;
	int centerDis;

	vector<Point> point;
	radiusSum = (int)pow(circle1.r + circle2.r, 2);
	radiusDiff = (int)pow(circle1.r - circle2.r, 2);
	centerDis = (int)(pow(circle1.x - circle2.x, 2) + (int)pow(circle1.y - circle2.y, 2));

	// not intersect
	if (centerDis > radiusSum || centerDis < radiusDiff) {
		return point;
	}

	// line passes both two intersections of circles
	Line line(circle1.d - circle2.d, circle1.e - circle2.e, circle1.f - circle2.f);

	// the intersections of two circles are also the intersections of line and circle
	return calLineCircleIst(line, circle1);
}

void calculate(ifstream &fileIn, ofstream &fileOut) {
	int N;
	char type;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	int x = 0, y = 0, r = 0;
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
		string temp;
		fileIn >> temp;
		if (!isNum(temp)) throw INException();
		N = atoi(temp.c_str());
		if (N < 2) throw TFException();

		for (int i = 0; i < N; i++) {
			fileIn >> type;
			switch (type) {
			case 'L':
				inputCheck(fileIn, x1, y1, x2, y2);
				line = Line(x1, y1, x2, y2);
				for (Line it : lines) {
					if (line.isSame(it)) throw SLException(type, x1, y1, x2, y2, 'L', it.x1, it.y1, it.x2, it.y2);
					Point* temp = calLineLineIst(line, it);
					if (temp) points.insert(*temp);
				}
				for (Ray it : rays) {
					if (line.isSame(it)) throw SLException(type, x1, y1, x2, y2, 'R', it.x1, it.y1, it.x2, it.y2);
					Point* temp = calLineLineIst(line, it);
					if (temp && it.vaild(*temp)) points.insert(*temp);
				}
				for (Segment it : segments) {
					if (line.isSame(it)) throw SLException(type, x1, y1, x2, y2, 'S', it.x1, it.y1, it.x2, it.y2);
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
				inputCheck(fileIn, x1, y1, x2, y2);
				ray = Ray(x1, y1, x2, y2);
				for (Line it : lines) {
					if (it.isSame(ray)) throw SLException(type, x1, y1, x2, y2, 'L', it.x1, it.y1, it.x2, it.y2);
					Point* temp = calLineLineIst(ray, it);
					if (temp && ray.vaild(*temp)) points.insert(*temp);
				}
				for (Ray it : rays) {
					if (it.isCoincide(ray) == 1) throw SLException(type, x1, y1, x2, y2, 'R', it.x1, it.y1, it.x2, it.y2);
					else if (it.isCoincide(ray) > 1) {
						points.insert(Point(ray.x1, ray.y1));
						continue;
					}
					Point* temp = calLineLineIst(ray, it);
					if (temp && it.vaild(*temp) && ray.vaild(*temp)) points.insert(*temp);
				}
				for (Segment it : segments) {
					if (it.isCoincide(ray) == 1) throw SLException(type, x1, y1, x2, y2, 'S', it.x1, it.y1, it.x2, it.y2);
					else if (it.isCoincide(ray) > 1) {
						points.insert(Point(ray.x1, ray.y1));
						continue;
					}
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
				inputCheck(fileIn, x1, y1, x2, y2);
				segment = Segment(x1, y1, x2, y2);
				for (Line it : lines) {
					if (it.isSame(segment)) throw SLException(type, x1, y1, x2, y2, 'L', it.x1, it.y1, it.x2, it.y2);
					Point* temp = calLineLineIst(segment, it);
					if (temp && segment.vaild(*temp)) points.insert(*temp);
				}
				for (Ray it : rays) {
					if (segment.isCoincide(it) == 1) throw SLException(type, x1, y1, x2, y2, 'R', it.x1, it.y1, it.x2, it.y2);
					else if (segment.isCoincide(it) > 1) {
						points.insert(Point(it.x1, it.y1));
						continue;
					}
					Point* temp = calLineLineIst(segment, it);
					if (temp && it.vaild(*temp) && segment.vaild(*temp)) points.insert(*temp);
				}
				for (Segment it : segments) {
					if (it.isCoincide(segment) == 1) throw SLException(type, x1, y1, x2, y2, 'S', it.x1, it.y1, it.x2, it.y2);
					else if (it.isCoincide(segment) == 2) {
						points.insert(Point(it.x1, it.y1));
						continue;
					}
					else if (it.isCoincide(segment) == 3) {
						points.insert(Point(it.x2, it.y2));
						continue;
					}
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
				inputCheck(fileIn, x, y, r);
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
		fileOut << points.size();
		cout << points.size() << endl;
	}
	catch (INException e) { cout << e.info() << endl; }
	catch (TFException e) { cout << e.info() << endl; }
	catch (DSException e) { cout << e.info() << endl; }
	catch (SLException e) { cout << e.info() << endl; }
	catch (TException e) { cout << e.info() << endl; }
	catch (RIException e) { cout << e.info() << endl; }
}

int main(int argc, char* argv[]) {
	ifstream fileIn;
	ofstream fileOut;
	try {
		if (argc != 5) throw ArgumentError();
		for (int i = 0; i < argc; i++) {
			if ((string)argv[i] == "-i") {
				fileIn = ifstream(argv[i + 1]);
			}
			else if ((string)argv[i] == "-o") {
				fileOut = ofstream(argv[i + 1]);
			}
		}
		if (!fileIn) throw FileError();
	}
	catch (ArgumentError e) {
		cout << e.info() << endl;
	}
	catch (FileError e) {
		cout << e.info() << endl;
	}
	calculate(fileIn, fileOut);
	return 0;
}