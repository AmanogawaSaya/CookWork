#pragma once
#include<string>
#include<vector>
#include"../include/head.h"
#include"../include/FormatExpetion.h"
using namespace std;

void solve(vector < pair<double, double> >& realIntersections);
void addLine(double x1, double y1, double x2, double y2, int type);
void deleteLine(double x1, double y1, double x2, double y2, int type);
void addCircle(double c1, double c2, double r);
void deleteCircle(double c1, double c2, double r);
void deteleAll();
