#include "Includes.h"

Timer::Timer()
{
	currentTime_ = 0;
	seconds_ = 0;
	minutes_ = 0;
	hours_ = 0;
}

void 
Timer::start()
{
		currentTime_ = static_cast<int>(time(0));
}

void 
Timer::pause()
{
	currentTime_ = 0;
	seconds_ = 0;
	minutes_ = 0;
	hours_ = 0;
}

void 
Timer::showTime()
{
	calculateTime();

	cout << setw(2);
	cout << hours_ << ":" << setw(2) << minutes_ << ":" << setw(2) << seconds_;
}

void Timer::calculateTime()
{
	int newTime = static_cast<int>(time(0));

	int estimateTime = newTime - currentTime_;

	seconds_ = estimateTime % 60;
	minutes_ = estimateTime / 60;
	hours_ = minutes_ / 60;
}


