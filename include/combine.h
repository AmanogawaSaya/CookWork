#pragma once
#include<string>
#include<vector>
#include"../include/head.h"
#include"../include/FormatExpetion.h"
using namespace std;

__declspec(dllexport) void solve(vector < pair<double, double> >& realIntersections);
__declspec(dllexport) void addLine(double x1, double y1, double x2, double y2, int type);
__declspec(dllexport) void deleteLine(double x1, double y1, double x2, double y2, int type);
__declspec(dllexport) void addCircle(double c1, double c2, double r);
__declspec(dllexport) void deleteCircle(double c1, double c2, double r);
__declspec(dllexport) void deleteAll();
__declspec(dllexport) void ioHandler(string input);
