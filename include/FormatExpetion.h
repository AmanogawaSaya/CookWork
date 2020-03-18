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

/*RangeExceeded*/
class REException : public exception {
public:
	const string info() const throw() {
		return "���귶Χ���ޣ�������(-100000, 100000)֮�����";
	}
};

/*Same Line*/
class SLException : public exception {
public:
	const string info() const throw() {
		return "������ֱ��������Ľ���";
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
		return "����������һ��(-100000, 100000)֮�����ǰ��0��׼����";
	}
};

/*RadicusInvaild*/
class RIException : public exception {
public:
	const string info() const throw() {
		return "Բ�İ뾶������С��0";
	}
};