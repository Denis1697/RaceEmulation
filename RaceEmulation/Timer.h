#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	Timer();

	void     start();
	void     pause();
	void     calculateTime();
	void     showTime()       const;
	string   getTime()        const;
private:
	int      currentTime_;
	int      seconds_;
	int      minutes_;
	int      hours_;
};

#endif