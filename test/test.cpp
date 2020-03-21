#include "pch.h"
#include "CppUnitTest.h"
#include"../include/head.h"

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
			ifstream testCase1 = ifstream("testcase1.txt");
		}

		TEST_METHOD(calLineLineIstTest) {

		}

		TEST_METHOD(calLineCircleIstTest) {

		}

		TEST_METHOD(calCircleCircleIstTest) {

		}
		
	};
}
