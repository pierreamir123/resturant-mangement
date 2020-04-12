

#ifndef __Promotion_H_
#define __Promotion_H_

#include "Event.h"
#include"..\Rest\Restaurant.h"

class Promotion :public Event
{
private:
	double extraMoney; //l flos l zyada ely hydf3ha 3shan yget promoted
public:
	Promotion();
	Promotion(int,int,double);

	virtual void Execute(Restaurant* pRest);
};
#endif
