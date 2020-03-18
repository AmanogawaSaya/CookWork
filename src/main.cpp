#include "../include/head.h"
#include "../include/FormatExpetion.h"

using namespace std;

bool isNum(string s) {
	if (s == "0") return true;
	if (s[0] == '0') return false;
	for (auto i : s) {
		if (!(i >= '0' && i <= '9')) return false;
	}
	return true;
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
}

// calculate the intersections of two lines
Point* calLineLineIst(Line line1, Line line2, MySet& points) {
	int D;

	D = line1.a * line2.b - line2.a * line1.b;
	if (D == 0) {
		if (line1.a * line2.c == line1.c * line2.a) throw SLException();
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
void calLineCircleIst(Line line, Circle circle, MySet& points) {
	int intercept;

	intercept = (int)(pow(circle.r, 2) -
		pow(line.a * circle.x + line.b * circle.y + line.c, 2) / (pow(line.a, 2) + pow(line.b, 2)));

	if (intercept < 0) {
		return;
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
		points.insert(tPoint);
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
		points.insert(ist1);
		points.insert(ist2);
		break;
	}
}

// calculate intersections of two circles
void calCircleCircleIst(Circle circle1, Circle circle2, MySet& points) {
	int radiusSum;
	int radiusDiff;
	int centerDis;

	radiusSum = (int)pow(circle1.r + circle2.r, 2);
	radiusDiff = (int)pow(circle1.r - circle2.r, 2);
	centerDis = (int)(pow(circle1.x - circle2.x, 2) + pow(circle1.y - circle2.y, 2));

	// not intersect
	if (centerDis > radiusSum || centerDis < radiusDiff) {
		return;
	}

	// line passes both two intersections of circles
	Line line(circle1.d - circle2.d, circle1.e - circle2.e, circle1.f - circle2.f);

	// the intersections of two circles are also the intersections of line and circle
	calLineCircleIst(line, circle1, points);
}

int main(int argc, char* argv[]) {
	ifstream fileIn;
	ofstream fileOut;
	/*if (argc != 5) {
		cout << "Please check your Format: \n\tintersect.exe -i <input> -o <output>\n";
		exit(0);
	}

	string fout_name;
	for (int i = 0; i < argc; i++) {
		if ((string)argv[i] == "-i") {
			fileIn = ifstream(argv[i + 1]);
		}
		else if ((string)argv[i] == "-o") {
			fileOut = ofstream(argv[i + 1]);
			fout_name = argv[i + 1];
		}
	}

	if (!fileIn) {
		cout << "Please add your input file.";
		exit(0);
	}

	cout << "Start working ......\n";
	*/
	fileIn = ifstream("input.txt");
	fileOut = ofstream("output.txt");
	
	int N;
	char type;
	int x1 = 0, y1 = 0;
	int x2 = 0, y2 = 0;
	int x = 0, y = 0, r = 0;
	Line line;
	Circle circle;
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
				if (x1 == x2 && y1 == y2) throw DSException();
				if (!rangeVaild(x1) || !rangeVaild(y1) || !rangeVaild(x2) || !rangeVaild(y2)) throw INException();

				line = Line(x1, y1, x2, y2);
				for (Line it : lines) {
					calLineLineIst(line, it, points);
				}
				for (Circle it : circles) {
					calLineCircleIst(line, it, points);
				}
				lines.emplace_back(line);
				break;
			case 'R':

			case 'S':

			case 'C':
				inputCheck(fileIn, x, y, r);
				if (!rangeVaild(x) || !rangeVaild(y)) throw INException();
				if (r <= 0 || r >= 100000) throw RIException();

				circle = Circle(x, y, r);
				for (Line it : lines) {
					calLineCircleIst(it, circle, points);
				}
				for (Circle it : circles) {
					if (it.x == circle.x && it.y == circle.y && it.r == circle.r) throw SLException();
					calCircleCircleIst(it, circle, points);
				}
				circles.emplace_back(circle);
				break;
			default:
				throw TException();
				break;
			}
		}
		fileOut << points.size();
	}
	catch (INException e) { cout << e.info() << endl; }
	catch (TFException e) { cout << e.info() << endl; }
	catch (DSException e) { cout << e.info() << endl; }
	catch (SLException e) { cout << e.info() << endl; }
	catch (TException e) { cout << e.info() << endl; }
	catch (RIException e) { cout << e.info() << endl; }

	//cout << "Finish!!!   Result is in \"" << fout_name << "\"";
	return 0;
}