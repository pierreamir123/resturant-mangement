#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(ORD_TYPE oType,int eTime, int oID ,int osize,double money):Event(eTime, oID)
{
	OrdType = oType;
	OrdSize = osize;
	OrdMoney = money;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(OrderID, OrdType,EventTime ,OrdSize, OrdMoney);
	pRest->Add_Order(pOrd);

}
