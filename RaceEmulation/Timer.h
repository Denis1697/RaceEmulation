#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	Timer();
	Timer(const Timer& timer);
	Timer& operator=(const Timer& timer);

	void        start();
	void        pause();
	void        calculateTime();
	void        showTime()       const;
	string      getTime()        const;
private:
	int         currentTime_;
	int         seconds_;
	int         minutes_;
	int         hours_;

	const int   SECONDS_PER_MINUTE = 60;
	const int   MINUTES_PER_SECONDS = 60;
};

#endif