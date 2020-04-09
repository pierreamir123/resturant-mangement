#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:

	int ID;              //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, WaitTime, ServTime, FinishTime;	//arrival, service start, and finish times
	
	int Size;

	//////////////////// -------->>>>> auto-promotion ??
	

public:

	Order(int ID, ORD_TYPE r_Type, int arrtime, int size, double money); 
	virtual ~Order();

	int GetID() const;    

	void setType ( ORD_TYPE t ); // --> 3alshan el promotion event
	ORD_TYPE GetType() const;

	void SetDistance(int d);
	int GetDistance() const;

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;

	double getTotalMoney() const;                // --> 3alshan lama arateb el VIPs fel queue beta3hom
	void incrementTotalMoney( double money );    // --> 3alshan el promotion event

	int getArrTime () const;      // --> 3alshan atala3ha fel O/P file

	void incrementWaitTime ();   // --> 3alshan a3ed el timesteps elli fedel feh el order fel waiting queues
	int getWaitTime () const;    // --> 3alshan atala3ha fel O/P file w asta5demha fel auto-promotion

	void incrementServTime ();   // --> 3alshan a3ed el timesteps elli fedel feh el order fel in-service list
	int getServTime () const;    // --> 3alshan atala3ha fel O/P file

	void updateFinishTime ();    // --> 3alshan y-update el finish time ba3d ma atala3 el order men el in-service list lel finished list
	int getFinishTime () const;  // --> 3alshan atala3ha fel O/P file

	int getSize () const;     // --> 3alshan lama arateb el VIPs fel queue beta3hom
	

};

#endif