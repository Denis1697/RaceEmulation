#include "Includes.h"

Timer::Timer() {
	currentTime_ = 0;
	seconds_     = 0;
	minutes_     = 0;
	hours_       = 0;
}

void
Timer::start() {
	currentTime_ = static_cast<int>(time(0));
}

void
Timer::pause() {
	currentTime_ = 0;
	seconds_     = 0;
	minutes_     = 0;
	hours_       = 0;
}

void
Timer::showTime() const {

	cout << setw(2);
	cout << hours_   << ":" << setw(2) <<
		    minutes_ << ":" << setw(2) << seconds_;
}

string Timer::getTime() const
{
	const int DECIMAL     = 10;
	const int BUFFER_SIZE = 4;
	char   buffer[BUFFER_SIZE];
	string time = "";

	_itoa_s(hours_,   buffer, BUFFER_SIZE, DECIMAL);

	time.append(buffer);
	time.append(":");

	_itoa_s(minutes_, buffer, BUFFER_SIZE, DECIMAL);

	time.append(buffer);
	time.append(":");

	_itoa_s(seconds_, buffer, BUFFER_SIZE, DECIMAL);

	time.append(buffer);

	return time;
}

void
Timer::calculateTime() {
	int newTime      = static_cast<int>(time(0));
	int estimateTime = newTime - currentTime_;

	seconds_ = estimateTime % SECONDS_PER_MINUTE;
	minutes_ = estimateTime / SECONDS_PER_MINUTE;
	hours_   = minutes_ / MINUTES_PER_SECONDS;
}


