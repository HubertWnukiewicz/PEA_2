#include "Timer.h"
#include <iostream>

Timer::Timer()
{
	this->counterStart = 0;
	this->Frequency = 0.0;
}

double Timer::getTime()
{
	return this->time;
}

void Timer::start()
{
	LARGE_INTEGER largeInt;
	if (!QueryPerformanceFrequency(&largeInt))
	{
		std::cout << "error 404 timer" << std::endl;
	}
	Frequency = (double)largeInt.QuadPart;

	QueryPerformanceCounter(&largeInt);
	counterStart = largeInt.QuadPart;
}

void Timer::reset()
{
	counterStart = 0;
	Frequency = 0.0;
}

double Timer::stop()
{
	LARGE_INTEGER largeInt;
	QueryPerformanceCounter(&largeInt);
	time = double(largeInt.QuadPart - counterStart) / Frequency;
	return time;

}
