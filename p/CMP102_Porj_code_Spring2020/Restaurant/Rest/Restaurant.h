#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

// Graphics includes
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
//data structude includes
#include "..\Generic_DS\Queue.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"..\Generic_DS\SortedList.h"
#include"..\Generic_DS\PriorityData.h"
//class includes
#include "Order.h"
#include "..\Defs.h"
//events includes
#include"..\Events\ArrivalEvent.h"
#include"..\Events\Cancellation.h"
#include"..\Events\Promotion.h"
#include "..\Events\Event.h"
//loading functions includes
#include<fstream>

// it is the maestro of the project

class Restaurant  
{	
private:
	GUI *pGUI;

	// data structure of events
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file


	// data structure of orders
	Queue<Order*> W_Vegan ;    //queue of waiting vegan orders
	PriorityQueue<PriorityData<Order*>> W_VIP;//priority queue of waiting vip orders
	Queue<Order*> In_service;//queue of orders that in service 
	Queue<Order*> finished ;// queue of finished orders
	SortedList<Order*>W_Normal;//sorted list of waiting normal orders


	//data structure of cooks 
	Queue<Cook*> AV_Cooks_Normal;//avalible cooks of normal cooks
	Queue<Cook*> AV_Cooks_vegan;//queue of avalible vegan cooks
	Queue<Cook*> Av_cooks_VIP;//queue of avalible vip cooks
	SortedList<Cook*>Assigned_Cooks; // queue busy cooks 
	SortedList<Cook*>ON_Break_Cooks;// queue cooks who take break

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
	void Add_OrderVip(PriorityData<Order*>o);
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void Simple_simulator();
	bool getEntryNormal(int position, Order*);
	bool removeNormal(int position);



	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//


	/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

	/// ================================================================================================== 


	/// ================================================================================================== 
	void LoadingFunction(ifstream & input); // note that we passed the ifstream by & (why?)


};

#endif