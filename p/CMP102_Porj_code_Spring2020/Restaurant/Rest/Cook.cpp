#include "Cook.h"


Cook::Cook()
{
	status = AVAILABLE;
	AssignedOrder = nullptr;
	finishedDishesCount = 0;
}


void Cook::setID (int id)
{
	ID = id;
}


int Cook::GetID () const
{
	return ID;
}


void Cook::setType(ORD_TYPE t)
{
	type = t;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook :: setSpeed ( int s )
{
	speed = s;
}


int Cook :: getSpeed ( ) const
{
	return speed;
}


void Cook :: setStatus ( COOK_STATUS st )
{
	status = st;
}


COOK_STATUS Cook :: getStatus () const
{
	return status;
}


void Cook :: setAssigOrderTime ( int t )
{
	AssigOrderTime = t;
}


int Cook :: getAssigOrderTime () const
{
	return AssigOrderTime;
}


void Cook :: setAssignedOrder ( Order* order )
{
	AssignedOrder = order;
}


Order* Cook :: getAssignedOrder () const
{
	return AssignedOrder;
}


void Cook :: setBreakDuration ( int bd )
{
	breakDuration = bd;
}


int Cook :: getBreakDuration () const
{
	return breakDuration;
}

void Cook :: setBreakNumber ( int bn )
{
	breakNumber = bn;
}

int Cook :: getBreakNumber () const
{
	return breakNumber;
}


void Cook :: setFinishedDishesCount ( int c )
{
	finishedDishesCount = c;
}


int Cook :: getFinishedDishesCount () const
{
	return finishedDishesCount;
}


void Cook :: setbeginBreakTime ( int t )
{
	beginBreakTime = t;
}


int Cook :: getbeginBreakTime () const
{
	return beginBreakTime;
}


bool Cook :: operator < ( Cook acook )
{
	return ( finishedDishesCount < acook.finishedDishesCount );
}


bool Cook :: operator <= ( Cook acook )
{
	return ( finishedDishesCount <= acook.finishedDishesCount );
}


Cook::~Cook()
{
}
