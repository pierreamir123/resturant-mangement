#include "Order.h"

Order :: Order(int id, ORD_TYPE r_Type, int arrtime, int size, double money)      // --> ma3mltesh intialize le finish time w distance 3alshan law tel3o garbage a3raf eni ma3mltlhomsh set
{
	ID = ( id > 0 && id < 1000 ) ? id : 0;  	//1<ID<999    
	type = r_Type;
	status = WAIT;
	ArrTime = arrtime;
	Size = size;
	totalMoney = money;
	WaitTime = 0;
	ServTime = 0;
}

Order::~Order()
{
}

int Order::GetID() const       
{
	return ID;
}

void Order :: setType ( ORD_TYPE t )
{
	type = t;
}

ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d > 0 ? d : 0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

double Order ::  getTotalMoney() const
{
	return totalMoney;
}

void Order :: incrementTotalMoney( double money )
{
	totalMoney += money;
}

void Order :: incrementWaitTime ()
{
	WaitTime++;
}

void Order :: incrementServTime ()
{
	ServTime++;
}

void Order :: updateFinishTime ()
{
	FinishTime = ArrTime + WaitTime + ServTime;
}

int Order :: getArrTime () const
{
	return ArrTime;
}

int Order :: getWaitTime () const
{
	return WaitTime;
}

int Order :: getServTime () const
{
	return ServTime;
}

int Order :: getFinishTime () const
{
	return FinishTime;
}

int Order :: getSize () const
{
	return Size;
}