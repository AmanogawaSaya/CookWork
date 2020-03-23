#pragma once
#include <exception>
#include<string>
using namespace std;

/*Too Few*/
class TFException : public exception {
public:
	const string info() const throw() {
		return "��������������ͼ�Σ�";
	}
};

/*DotSame*/
class DSException : public exception {
public:
	const string info() const throw() {
		return "����ȷ��ֱ�ߵ����㲻���غϣ�";
	}
};

/*Same Line*/
class SLException : public exception {
public:
	SLException(char a, int x1, int y1, int x2, int y2, char b, int x3, int y3, int x4, int y4) {
		cout << a << "(" << x1 << "," << y1 << "," << x2 << "," << y2 << ")" << endl;
		cout << b << "(" << x3 << "," << y3 << "," << x4 << "," << y4 << ")" << endl;
	}
	SLException(){}
	const string info() const throw() {
		return "����������ͼ��֮��������Ľ���";
	}
};

/*TypeError*/
class TException : public exception {
public:
	const string info() const throw() {
		return "֧�ֵ�ͼ�������Ϊ��C, L, S, R";
	}
};

/*IntegerNeeded*/
class INException : public exception {
public:
	const string info() const throw() {
		return "�����N������һ��(-100000, 100000)֮�����ǰ��0��׼����";
	}
};

/*RadicusInvaild*/
class RIException : public exception {
public:
	const string info() const throw() {
		return "Բ�İ뾶������С�ڻ����0���ߴ��ڻ����100000";
	}
};

class ArgumentError : public exception {
public:
	const string info() const throw() {
		return "���������ʽ: \n\tintersect.exe -i <input> -o <output>\n";
	}
};

class FileError : public exception {
public:
	const string info() const throw() {
		return "���ļ�ʧ�ܣ�";
	}
};