#ifndef __IMESSAGE_H__
#define __IMESSAGE_H__

class IMessage 
{
public:
	virtual bool   leaveTheGame()                               const = 0;
	virtual void   setPause()                                   const = 0;
	virtual int    startingMode()                               const = 0;
	virtual void   showStatistics(const int&,
		                          const string&, const double&) const = 0;
};

#endif