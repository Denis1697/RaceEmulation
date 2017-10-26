#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	Timer();

	void	start();
	void	pause();
	void	showTime();
	void	calculateTime();
private:
	int		currentTime_;
	int		seconds_;
	int		minutes_;
	int		hours_;

	const int SECONDS_PER_MINUTE	= 60;
	const int MINUTES_PER_SECONDS	= 60;
};

#endif