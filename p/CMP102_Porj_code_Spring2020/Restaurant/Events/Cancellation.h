#ifndef __CANCELLATION_H_
#define __CANCELLATION_H_

#include "Event.h"
class Cancellation :public Event
{
public:
	Cancellation(int etime,int ordID);

	virtual void Execute(Restaurant* pRest);






};
#endif
