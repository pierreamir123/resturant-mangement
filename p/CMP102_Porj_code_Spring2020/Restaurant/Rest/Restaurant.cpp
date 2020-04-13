#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string.h>
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
		W_Order_Normal.insertSorted(o) ;
	}
	if (o->GetType()== TYPE_VGAN )
	{
		W_Order_Vegan.enqueue(o);

	}
	if(o->GetType()== TYPE_VIP)
	{
		int pri = 100;
		PriorityData<Order*> pop (o,pri);
		W_Order_VIP.Enqueue(pop);
		pri--;
	}
}
void Restaurant::Add_OrderVip(PriorityData<Order*> o)
{
	W_Order_VIP.Enqueue(o);
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



		for(int ID=1;ID<=N;ID++)
		{
			OrType = TYPE_NRM;
			Cook* NormalCook=new Cook();  // variables tet3emel fe class cook we ne3mel constructor keda

			NormalCook->setType(OrType);
			NormalCook->setBreakDuration(BN);
			NormalCook->setID(ID);
			NormalCook->setSpeed(SN);
			AV_Cooks_Normal.enqueue(NormalCook);    //ne3mel cook object fe class cook
		}
		for(int ID=1;ID<=G;ID++)
		{
			OrType = TYPE_VGAN;
			Cook* VeganCook=new Cook();
			VeganCook->setType(OrType);
			VeganCook->setBreakDuration(BG);
			VeganCook->setID(ID);
			VeganCook->setSpeed(SG);
			AV_Cooks_vegan.enqueue(VeganCook);
		}
		for(int ID=1;ID<=V;ID++)
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
		
		char temp,orderType;
		int one ,two , three,four;

		for(int l=1; l<=M; l++)
		{
			input>>temp>>orderType>>one>>two>>three>>four;//one =ts , two=id,three=size,4=money 
			if(temp == 'R')
			{
				if(orderType=='N')
					OrType=TYPE_NRM;
				if(orderType=='G')
					OrType=TYPE_VGAN;
				if(orderType=='V')
					OrType=TYPE_VIP;

				
				Event* event= new ArrivalEvent((ORD_TYPE)OrType,one,two,three,four); // variables tet7at fel class we ne3melhom fe constructor
				EventsQueue.enqueue(event);
			}
			if(temp== 'X')
			{
				
				Event* event= new Cancellation(one,two);
				EventsQueue.enqueue(event);
			}
			if(temp=='P')
			{
				
				Event* event= new Promotion (one,two,three);
				EventsQueue.enqueue(event);
			}
		}
		pGUI->PrintMessage("loaded");
		pGUI->waitForClick();
		input.close();
	}
	else
	{pGUI->PrintMessage ("Unable to open file");
	
	pGUI->waitForClick();

	}
}




void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Simple_simulator();
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	//case MODE_DEMO:
		

	};

}


//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() != CurrentTimeStep )	//no more events at current timestep
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

	W_Order_Normal.getEntry( position, p);
	return true;
}

bool Restaurant::removeNormal(int i)
{
	W_Order_Normal.remove(i);
	return true;
}
void Restaurant::FillDrawingList()
{

	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

	Order*pOrd;
	Cook*pCc;
	int size = 999;
	Order** WN_Orders_Array = W_Order_Normal.toArray(size);
	for(int i=0; i<size; i++)
	{
		pOrd = WN_Orders_Array[i];
		pGUI->AddToDrawingList(pOrd);
	}

	Order** WV_Orders_Array = W_Order_Vegan.toArray(size);
	for(int i=0; i<size; i++)
	{
		pOrd = WV_Orders_Array[i];
		pGUI->AddToDrawingList(pOrd);
	}

	PriorityData<Order*>* WVIP_Orders_Array = W_Order_VIP.toArray(size); 
	for(int i=0; i<size; i++)
	{
		pOrd=(WVIP_Orders_Array->getData());
		pGUI->AddToDrawingList(pOrd);
	}
	
	Cook**N_Cook=AV_Cooks_Normal.toArray(size);
	for(int i=0; i<size; i++)
	{
		pCc=N_Cook[i];
		pGUI->AddToDrawingList(pCc);
	}

	Cook**Ve_Cook=AV_Cooks_vegan.toArray(size);
	for(int i=0; i<size; i++)
	{
		pCc=Ve_Cook[i];
		pGUI->AddToDrawingList(pCc);
	}

	Cook**Vip_Cook=Av_cooks_VIP.toArray(size);
	for(int i=0; i<size; i++)
	{
		pCc=Vip_Cook[i];
		pGUI->AddToDrawingList(pCc);
	}
	
}
	/*for(int i=0; i<size; i++)
	{
		pCc=N_Cook[i];
		pGUI->AddToDrawingList(pCc);
	}*/
	

void Restaurant::Simple_simulator()
{
	ifstream fofo;
	string filename;	
	//Order* pOrd;
	//Event* pEv;


	pGUI->PrintMessage("Simple simulator.    I/P filename:");
	 
	fofo.open(pGUI->GetString());
	LoadingFunction(fofo);

	pGUI->PrintMessage("Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	int CurrentTimeStep = 1;
	
	pGUI->UpdateInterface();
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty() || !In_service.isEmpty() )
	{
		//print current timestep
		char timestep[100];
		itoa(CurrentTimeStep,timestep,100);	
		pGUI->PrintMessage(timestep);
		Order*poord;
		ExecuteEvents(CurrentTimeStep);
		//execute all events at current time step
		FillDrawingList();
		pGUI->UpdateInterface();
		
		if (!W_Order_Normal.isEmpty())
			{
				W_Order_Normal.getEntry(0,poord);
				W_Order_Normal.remove(0);
				poord->setStatus(SRV);
				In_service.enqueue (poord);
					pGUI->AddToDrawingList(poord);

			}
		if(!W_Order_Vegan.isEmpty())
			{
				W_Order_Vegan.dequeue(poord);
				poord->setStatus(SRV);
				In_service.enqueue (poord);
				
				pGUI->AddToDrawingList(poord);
			}
		if(!W_Order_VIP.isEmpty())
			{
				PriorityData<Order*> temp;
				W_Order_VIP.Dequeue(temp);
				poord->setStatus(SRV);
				In_service.enqueue (temp.getData());
					pGUI->AddToDrawingList(poord);
			}
		/*//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		FillDrawingList();
		pGUI->UpdateInterface();*/

		/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks

		Order*pooord;
		if (CurrentTimeStep % 5==0)
		{   
			if ( !In_service.isEmpty() )
			{
				for ( int i=0; i<3; i++ )
				{
					In_service.dequeue(pooord);
					pooord->setStatus(DONE);
					finished.enqueue(pooord);
					pGUI->AddToDrawingList(pooord);
				}
			}
		}
		
		pGUI->UpdateInterface();
			CurrentTimeStep++;
			pGUI->ResetDrawingList();
			int count;
			Order** poooord= finished.toArray(count);
			for(int i=0;i<+count;i++)

			{
				pGUI->AddToDrawingList(poooord[i]);
			}
		pGUI->waitForClick();
	}
	
	pGUI->PrintMessage("generation done, click to END program");
		pGUI->waitForClick();
	}




	//////////////////////////////////////////////////////////////////////////////////////////////
	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2

	//Begin of DEMO-related functions

	//This is just a demo function for project introductory phase
	//It should be removed starting phase 1
	/**void Restaurant::Just_A_Demo()
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


	}**/
	////////////////

	/*void Restaurant::AddtoDemoQueue(Order *pOrd)
	{
		DEMO_Queue.enqueue(pOrd);
	}*/

	/// ==> end of DEMO-related function
	//////////////////////////////////////////////////////////////////////////////////////////////


