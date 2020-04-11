#include "Promotion.h"
#include "..\Rest\Restaurant.h"
#include"..\Generic_DS\PriorityData.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"Event.h"
Promotion::Promotion()
{

}
Promotion::Promotion(int etime, int orderid, double exmon) :Event(etime, orderid)
{
	extraMoney = exmon;
}

void Promotion::Execute(Restaurant *pRest)
{
	Order* pOrd = new Order(0, TYPE_NRM, 0, 0, 0);  //check this lw feh moshkela
	bool found = false;
	int i = 0;
	while (found==false){


		pRest->getEntryNormal(i, pOrd);
		if (pOrd->GetID() == OrderID)
		{
			pRest->removeNormal(i);
			found = true;
		}
		else
		{i++;}
	}
	PriorityData<Order*> prom;
	pOrd->setType(TYPE_VIP);
	pOrd->incrementTotalMoney(extraMoney);
	prom.setData(pOrd);
	prom.setPriority(1);       //h7ot l priority hena

	pRest->Add_OrderVip(prom);


}