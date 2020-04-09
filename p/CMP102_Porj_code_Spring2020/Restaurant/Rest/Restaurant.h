#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"..\Generic_DS\SortedList.h"
#include"..\Generic_DS\PriorityData.h"

#include "Order.h"

// it is the maestro of the project

class Restaurant  
{	
private:
	GUI *pGUI;

	// data structure of events
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	
	
	// data structure of orders
	Queue<Order*> W_Vegan ;    //queue of waiting vegan orders
	PriorityQueue<PriorityData<Order>*> W_VIP;//priority queue of waiting vip orders
	Queue<Order*> In_service;//queue of orders that in service 
	Queue<Order*> finished ;// queue of finished orders
	SortedList<Order*>W_Normal;//sorted list of waiting normal orders
		
	
	//data structure of cooks 
	SortedList<Cook*> AV_Cooks;//avalible cooks
		Queue<Cook*>Busy_Cooks; // queue busy cooks 
		Queue<Cook*>Break_Cooks;// queue cooks who take break

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	
	Restaurant();
	~Restaurant();
	void Add_Order(Order*);
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	


	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//


/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 



};

#endif