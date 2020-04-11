#ifndef _Cook_H__
#define _Cook_H__
#include "Order.h"

#include"..\Defs.h"


class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)

	COOK_STATUS status;  // --> avaialable, assigned or on_break

	int AssigOrderTime;  // --> time at which order was assigned to cook ( must be set when moving cook to assigned sorted list )
	Order* AssignedOrder;

	int breakDuration;         // --> the timstep at which an a cook takes a break after completing " breakNumber " dishes ( const for all cooks of the same type )
	int breakNumber;           // --> the no of dishes a cook has to completes before he takes a break ( const for all cooks of ALL types )
	int finishedDishesCount;   // --> to keep track of number of dished cook has finished SINCE HE LAST TOOK A BREAK
	int beginBreakTime;        // --> the timestep at which the cook began his break

	int FinishOrderOrBreakTime;  // --> the time at which cook finishes his order or break and is ready to be moved from assigned sorted list or on_break sorted list


public:

	Cook();             // ---> constructor: sebt ID, speed, type, AssigOrderTime, breakDuration, breakNumber, beginBreakTime, FinishOrderOrBreakTime 3alshan el mafrood amelohom se, w hayb2o garbage law ma3amltsh

	void setID ( int );   // --> momken a3mel count static member y-increment ma3 kol mara a3mel object men cook ykoon howa el ID ( see if that is needed in phase 2 )
	int GetID () const;

	void setType( ORD_TYPE ) ;
	ORD_TYPE GetType() const;

	void setSpeed ( int s );     // -->
	int getSpeed ( ) const;     // --> for finding FinishOrderOrBreakTime before moving to assigned queue

	void setStatus ( COOK_STATUS st );  // -->
	COOK_STATUS getStatus () const;     // -->

	void setAssigOrderTime ( int t );  // --> set when moving to assigned queue
	int getAssigOrderTime () const;    // --> for finding FinishOrderOrBreakTime before moving to assigned queue

	void setAssignedOrder ( Order* order );  // -->
	Order* getAssignedOrder () const;       // -->

	void setBreakDuration ( int bd );   // -->
	int getBreakDuration () const;     // --> for finding FinishOrderOrBreakTime before moving to on_break queue

	void setBreakNumber ( int bn );   // -->
	int getBreakNumber () const;     // --> to check if a cook needs a break

	void setFinishedDishesCount ( int c );  // --> 3alshan asafaro lama y5rog men on_break sorted list aw a-increment bi 3adad el dishes el haymelha 7alan
	int getFinishedDishesCount () const;    // --> 3alshan a3raf el adeem w a-increment 3aleh w a-shoof el cook hay5od break wala la2

	void setbeginBreakTime ( int t );    // --> 
	int getbeginBreakTime () const;      // --> for finding FinishOrderOrBreakTime before moving to on_break queue

	void setFinishOrderOrBreakTime ( int fobt );   // --> to be set before moving to on_break or assigned sorted lists
	int getFinishOrderOrBreakTime () const;        // --> for removing finished/ready cooks from on_break or assigned sorted lists

	bool operator < ( Cook acook );
	bool operator <= ( Cook acook );


	virtual ~Cook();

};
#endif