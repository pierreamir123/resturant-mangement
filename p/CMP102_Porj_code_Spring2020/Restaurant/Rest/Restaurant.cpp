#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"..\Generic_DS\SortedList.h"
#include"..\Generic_DS\PriorityData.h"

Restaurant::Restaurant() 
{
	pGUI = NULL;
}
void Restaurant::Add_Order(Order* o )
{
	if (o->GetType()== TYPE_NRM )
	{
		W_Normal.insertSorted(o) ;
	}
	if (o->GetType()== TYPE_VGAN )
	{
		W_Vegan.enqueue(o);

	}
	if(o->GetType()== TYPE_VIP)
	{
		PriorityData<Order*> pop (o,1);
		W_VIP.Enqueue(pop);
	}
}
void Restaurant::Add_OrderVip(PriorityData<Order*> o)
{
	W_VIP.Enqueue(o);
}
void Restaurant::LoadingFunction(ifstream & input) // note that we passed the ifstream by & (why?)
{
	int N,G,V;
	int SN,SG,SV;
	int BO,BN,BG,BV;
	int AutoP;
	int M;

	ORD_TYPE OrType;

	if (input.is_open())
	{
		input>>N>>G>>V;
		input>>SN>>SG>>SV;
		input>>BO>>BN>>BG>>BV;
		input>>AutoP;
		input>>M;



		for(int ID=0;ID<=N;ID++)
		{
			OrType = TYPE_NRM;
			Cook* NormalCook=new Cook();  // variables tet3emel fe class cook we ne3mel constructor keda
			
			NormalCook->setType(OrType);
			NormalCook->setBreakDuration(BN);
			NormalCook->setID(ID);
			NormalCook->setSpeed(SN);
			AV_Cooks_Normal.enqueue(NormalCook);    //ne3mel cook object fe class cook
		}
		for(int ID=0;ID<=G;ID++)
		{
			OrType = TYPE_VGAN;
			Cook* VeganCook=new Cook();
			VeganCook->setType(OrType);
			VeganCook->setBreakDuration(BG);
			VeganCook->setID(ID);
			VeganCook->setSpeed(SG);
			AV_Cooks_vegan.enqueue(VeganCook);
		}
		for(int ID=0;ID<=V;ID++)
		{
			OrType = TYPE_VIP;
			Cook* VipCook=new Cook();
			VipCook->setType(OrType);
			VipCook->setBreakDuration(BV);
			VipCook->setID(ID);
			VipCook->setSpeed(SV);

			Av_cooks_VIP.enqueue(VipCook);
		}
		/////////////////////////////////////////
		int TS,ID,SIZE,MONY;
		int ExMony;
		int temp,orderType;


		for(int l=0; l<M; l++)
		{
			input>>temp>>orderType;
			if(temp == 'R')
			{
				if(orderType=='N')
					OrType=TYPE_NRM;
				if(orderType=='G')
					OrType=TYPE_VGAN;
				if(orderType=='V')
					OrType=TYPE_VIP;

				input>>TS>>ID>>SIZE>>MONY;
				Event* event= new ArrivalEvent((ORD_TYPE)OrType,TS,ID,SIZE,MONY); // variables tet7at fel class we ne3melhom fe constructor
				EventsQueue.enqueue(event);
			}
			if(temp== 'X')
			{
				input>>TS>>ID;
				Event* event= new Cancellation(TS,ID);
				EventsQueue.enqueue(event);
			}
			if(temp=='P')
			{
				input>>TS>>ID>>ExMony;
				Event* event= new Promotion (TS,ID,ExMony);
				EventsQueue.enqueue(event);
			}
		}


		input.close();
	}
	else cout << "Unable to open file";
}




void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}


//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}
bool Restaurant::getEntryNormal(int position, Order*p)
{

	W_Normal.getEntry( position, p);
	return true;
}

bool Restaurant::removeNormal(int i)
{
	W_Normal.remove(i);
	return true;
}
void Restaurant::FillDrawingList()
{
	Order*pOrd;



	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	int size = 0;
	Order** Demo_Orders_Array = DEMO_Queue.toArray(size);

	for(int i=0; i<size; i++)
	{
		pOrd = Demo_Orders_Array[i];
		pGUI->AddToDrawingList(pOrd);
	}

}




//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{

	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2

	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;	
	Cook *pC = new Cook[C_count];
	int cID = 1;

	for(int i=0; i<C_count; i++)
	{
		cID+= (rand()%15+1);	
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand()%TYPE_CNT));
	}	


	int EvTime = 0;

	int O_id = 1;

	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		O_id += (rand()%4+1);		
		int OType = rand()%TYPE_CNT;	//Randomize order type		
		EvTime += (rand()%5+1);			//Randomize event time
		//pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}	

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file





	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step


		/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks

		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for(int i=0; i<C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);

		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);

		for(int i=0; i<size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete []pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();


}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////


