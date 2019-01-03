#pragma once
#include <windows.h>

class Timer
{
	double Frequency;
	_int64 counterStart;
	double time;

public:
	Timer();
	double getTime();
	void start();
	void reset();
	double stop();
};