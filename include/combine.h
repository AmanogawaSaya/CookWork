#pragma once
#include<string>
#include<vector>
#include"../include/head.h"
#include"../include/FormatExpetion.h"
using namespace std;

extern "C" _declspec(dllexport) void __cdecl solve(vector < pair<double, double> >& realIntersections);
extern "C" _declspec(dllexport) void __cdecl addLine(double x1, double y1, double x2, double y2, int type);
extern "C" _declspec(dllexport) void __cdecl deleteLine(double x1, double y1, double x2, double y2, int type);
extern "C" _declspec(dllexport) void __cdecl addCircle(double c1, double c2, double r);
extern "C" _declspec(dllexport) void __cdecl deleteCircle(double c1, double c2, double r);
extern "C" _declspec(dllexport) void __cdecl deleteAll();
extern "C" _declspec(dllexport) void __cdecl ioHandler(string input);
