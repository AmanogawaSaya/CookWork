#include "pch.h"
#include "CppUnitTest.h"
#include"../include/head.h"
#include"../include/FormatExpetion.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		
		TEST_METHOD(isNumTest) {
			Assert::IsTrue(isNum("0"));
			Assert::IsTrue(isNum("1"));
			Assert::IsTrue(isNum("100"));
			Assert::IsTrue(isNum("-1"));
			Assert::IsTrue(isNum("-100"));
			Assert::IsFalse(isNum("001"));
			Assert::IsFalse(isNum("-001"));
			Assert::IsFalse(isNum("a"));
			Assert::IsFalse(isNum("0a"));
			Assert::IsFalse(isNum("-0a"));
		}

		TEST_METHOD(rangeVaildTest) {
			Assert::IsFalse(rangeVaild(-100330));
			Assert::IsFalse(rangeVaild(1033000));
			Assert::IsFalse(rangeVaild(-100000));
			Assert::IsFalse(rangeVaild(100000));
			Assert::IsTrue(rangeVaild(2000));
		}

		TEST_METHOD(inputCheckTest) {
			int x, y, s, t;
			ifstream testCase1 = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase1.txt");
			try {
				inputCheck(testCase1, x, y, s, t);
			}
			catch (INException e) {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(inputCheckTest2) {
			int x, y, r;
			ifstream testCase1 = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase2.txt");
			try {
				inputCheck(testCase1, x, y, r);
			}
			catch (INException e) {
				Assert::IsTrue(false);
			}
		}

		TEST_METHOD(calLineLineIstTest) {
			Line line = { 1, 2, 3 };
			Assert::AreEqual(1, line.a);
			Assert::AreEqual(2, line.b);
			Assert::AreEqual(3, line.c);
		}

		TEST_METHOD(calLineLineIstTest2) {
			Line l1 = { 1, 2, 3 };
			Line l2 = { -1, 5, -10 };
			Point* p = calLineLineIst(l1, l2);
			Assert::AreEqual((double)-5.0, p->x);
			Assert::AreEqual((double)1.0, p->y);
		}

		TEST_METHOD(calLineLineIstTest3) {
				Line l1 = { 1, 2, 3 };
				Line l2 = { -2, -4, -4 };
				Point* p = calLineLineIst(l1, l2);
				Assert::IsNull(p);
		}

		TEST_METHOD(calLineCircleIstTest) {
			Line a = Line(0, 0, 0, 1);
			Circle b = Circle(-1, 1, 1);
			vector<Point> c = calLineCircleIst(a, b);
			Assert::AreEqual((size_t)1, c.size());
			Assert::AreEqual(c[0].x, 0.0);
			Assert::AreEqual(c[0].y, 1.0);
		}

		TEST_METHOD(calLineCircleIstTest2) {
			Line a = Line(-1, 0, -1, 1);
			Circle b = Circle(-1, 1, 1);
			vector<Point> c = calLineCircleIst(a, b);
			Assert::AreEqual((size_t)2, c.size());
			Assert::AreEqual(c[0].x, -1.0);
			Assert::AreEqual(c[0].y, 2.0);
			Assert::AreEqual(c[1].x, -1.0);
			Assert::AreEqual(c[1].y, 0.0);
		}
		TEST_METHOD(calCircleCircleIstTest) {
			Circle a = Circle(1, 1, 1);
			Circle b = Circle(3, 3, 1);
			vector<Point> c = calCircleCircleIst(a, b);
			Assert::AreEqual(c.size(), (size_t)0);
		}

		TEST_METHOD(calCircleCircleIstTest2) {
			Circle a = Circle(1, 1, 1);
			Circle b = Circle(3, 1, 1);
			vector<Point> c = calCircleCircleIst(a, b);
			Assert::AreEqual(c.size(), (size_t)1);
			Assert::AreEqual(c[0].x, 2.0);
			Assert::AreEqual(c[0].y, 1.0);
		}
		
		TEST_METHOD(calCircleCircleIstTest3) {
			Circle a = Circle(1, 1, 2);
			Circle b = Circle(2, 1, 1);
			vector<Point> c = calCircleCircleIst(a, b);
			Assert::AreEqual(c.size(), (size_t)1);
			Assert::AreEqual(c[0].x, 3.0);
			Assert::AreEqual(c[0].y, 1.0);
		}

		TEST_METHOD(calCircleCircleIstTest4) {
			Circle a = Circle(0, 0, 1);
			Circle b = Circle(1, 1, 1);
			vector<Point> c = calCircleCircleIst(a, b);
			Assert::AreEqual(c.size(), (size_t)2);
			Assert::AreEqual(c[0].x, 1.0);
			Assert::AreEqual(c[0].y, 0.0);
			Assert::AreEqual(c[1].x, 0.0);
			Assert::AreEqual(c[1].y, 1.0);
		}

		TEST_METHOD(calculateTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase3.txt");
			ofstream b = ofstream("output.txt");
			calculate(a, b);
		}

		TEST_METHOD(commandLineErrorTest) {
			ifstream a;
			ofstream b;
			char* argv[5];
			argv[0] = "-i";
			argv[1] = "input.txt";
			argv[2] = "-o";
			argv[3] = "output.txt";
			argv[4] = "233";
			Assert::AreEqual(-2, commandLine(a, b, 5, argv));
			Assert::AreEqual(-1, commandLine(a, b, 4, argv));
		}

		TEST_METHOD(mainTest) {
			char* argv[5];
			argv[0] = "-i";
			argv[1] = "input.txt";
			argv[2] = "-o";
			argv[3] = "output.txt";
			argv[4] = "233";
			main(5, argv);
		}

		TEST_METHOD(RIExTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase4.txt");
			int d, b, c;
			try {
				inputCheck(a, d, b, c);
				Assert::IsTrue(false);
			}
			catch (RIException e) {

			}
		}

		TEST_METHOD(INExTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase5.txt");
			int d, b, c, e;
			try {
				inputCheck(a, d, b, c, e);
				Assert::IsTrue(false);
			}
			catch (INException e) {

			}
		}

		TEST_METHOD(TrExTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase6.txt");
			ofstream b;
			try {
				calculate(a, b);
			}
			catch (TException e) {
			}
		}

		TEST_METHOD(TfExTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase7.txt");
			ofstream b;
			try {
				calculate(a, b);
			}
			catch (TFException e) {
			}
		}
		TEST_METHOD(SLExTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase9.txt");
			ofstream b;
			try {
				calculate(a, b);
			}
			catch (SLException e) {
			}
		}
		TEST_METHOD(DSExTest) {
			ifstream a = ifstream("F:\\thisSemester\\softwareEngineer\\homework\\CoopWork\\test\\testcase8.txt");
			ofstream b;
			try {
				calculate(a, b);
			}
			catch (DSException e) {
			}
		}
	};
}
