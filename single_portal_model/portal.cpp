/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any       *
* purpose.											   *
********************************************************
* Portal.cpp										   *
********************************************************
* Implementation file for Portal.h				       *
*													   *
* @author Karan Kumar Budhraja						   *
* @email karank.budhraja@gmail.com					   *
* @author Ashutosh Singh							   *
* @email ashutoshs89@gmail.com						   *
* @author Gaurav Dubey								   *
* @email gaurav311086@gmail.com						   *
*													   *
* @date 28/08/2011									   *
*													   *
* @ver 0.1											   *
*													   *
*******************************************************/

#include <iostream>
#include <cmath>

#include "Portal.h"										/* portal related functions */
#include "Particle.h"									/* definition of a particle */

using namespace std;

Real Portal[Dimension];									/* current position of portal */
Real RoE;

#if 0													/* abstract values */
	Real InitialRoE = 1.0;

	Real RoEIncreaseFactor = 1.1;
	Real RoEDecreaseFactor = 1.1;
	int TeleportTypeChangeInterval = 40;				/* iterations / swarm size for a uniform distribution */
#elif 0													/* tuned for unimodal functions */	
	Real InitialRoE = 0.86135;							/* RoE of portal */

	Real RoEIncreaseFactor = 3.34975;					/* rate of increase of outer RoE */
	Real RoEDecreaseFactor = 7.84616;					/* rate of decrease of inner RoE */
	int TeleportTypeChangeInterval = 52;				/* rate of conversion of particles from outer portal to inner portal teleportation */
#else													/* tuned for multiimodal functions */
	Real InitialRoE = 0.0162373;

	Real RoEIncreaseFactor = 5.11948;
	Real RoEDecreaseFactor = 6.33022;
	int TeleportTypeChangeInterval = 775;				
#endif

int outTeleports = 0;									/* count of outer teleports */
int inTeleports = 0;									/* count of inner portal teleports */

/*******************************************************
* GeneratePortal									   *
********************************************************
* Generate portal with specified centre				   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void GeneratePortal(Real* Position)
{
     int Count;
     
	 if(IsOutsideRoE(Position))
	 {
		InitializeRoE();								/* if our new point is inside roe, make a fresh portal */
	 }

	 for(Count=0; Count<Dimension; Count++)
	 {
		Portal[Count] = Position[Count];				/* initialize portal */
	 }
}

/*******************************************************
* InitializeRoE										   *
********************************************************
* Reset radius of portal							   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void InitializeRoE()
{
     RoE = 0.001;
}

/*******************************************************
* IncreaseRoE										   *
********************************************************
* Increase radius of portal							   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void IncreaseRoE()
{
	/* corrrection in code. added limit check*/
	if(CheckRoELimit() == ROE_LIMIT_NOT_REACHED)		/* if outer roe is within limits, then we may increase it */
	{
		RoE *= 1.1;
	}

    outTeleports++;										/* a teleport has occured */
}

/*******************************************************
* DecreaseRoE										   *
********************************************************
* Decrease radius of portal							   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void DecreaseRoE()
{
	RoE /= 1.1;											/* no lower limit made on the inner roe */

	inTeleports++;										/* a teleport has occurred */
}

/*******************************************************
* IsInsidePortal									   *
********************************************************
* Check if particle is inside portal				   *
********************************************************
*													   *
* Input												   *
*													   *
* Real* Position			: Position of particle	   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	INSIDE_PORTAL									   *
*		if particle is inside of outer portal		   *
*	NOT_INSIDE_PORTAL								   *
*		if particle is outside of outer portal		   *
*													   *
*******************************************************/
int IsInsideRoE(Real* Position)
{
    Real DistanceSquared = GetDistanceSquared(Position);
    
    if((DistanceSquared < RoE*RoE)&&(DistanceSquared))	/* check if particle is outside inner portal roe */
	{
		return INSIDE_PORTAL;
	}
    else
	{
		return NOT_INSIDE_PORTAL;
	}
}

/*******************************************************
* IsOutsidePortal								       *
********************************************************
* Check if particle is outside inner portal			   *
********************************************************
*													   *
* Input												   *
*													   *
* Real* Position			: Position of particle	   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	OUTSIDE_PORTAL									   *
*		if particle is outside of inner portal		   *
*	NOT_OUTSIDE_PORTAL								   *
*		if particle is inside of outer portal		   *
*													   *
*******************************************************/
int IsOutsideRoE(Real* Position)
{
    Real DistanceSquared = GetDistanceSquared(Position);
    
    if((DistanceSquared > RoE*RoE)&&(DistanceSquared)) /* check if particle is outside inner portal roe */
	{
		return OUTSIDE_PORTAL;
	}
    else
	{
		return NOT_OUTSIDE_PORTAL;
	}
}

/*******************************************************
* GetDistanceSquared								   *
********************************************************
* Square of distance from centre of outer portal	   *
********************************************************
*													   *
* Input												   *
*													   *
* Real* Position			: Position of particle	   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	Distance squared								   *
*													   *
*******************************************************/
Real GetDistanceSquared(Real* Position)
{
    int Count;
    Real DistanceSquared = 0.0;

    for(Count = 0; Count < Dimension; Count++)				/* get distance of particle from center of outer portal */
	{
                 DistanceSquared += (Portal[Count] - Position[Count])*(Portal[Count] - Position[Count]);
	}

    return DistanceSquared;
}

/*******************************************************
* GetOutTeleports									   *
********************************************************
* Get number of teleports outside portal			   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	Number of teleports 							   *
*													   *
*******************************************************/
int GetOutTeleports()
{
    return outTeleports;
}

/*******************************************************
* GetInTeleports									   *
********************************************************
* Get number of teleports inside portal				   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	Number of teleports 							   *
*													   *
*******************************************************/
int GetInTeleports()
{
    return inTeleports;
}

/*******************************************************
* CheckRoELimit										   *
********************************************************
* Check for upper limit of radius of portal			   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	ROE_LIMIT_REACHED								   *
*		if limit has been reached					   *
*	ROE_LIMIT_NOT_REACHED							   *
*		if limit has not been reached				   *
*													   *
*******************************************************/
int CheckRoELimit()
{
														/* get a point on the hypersphere at random */
	Real X0[Dimension], X1[Dimension], X2[Dimension], X3[Dimension];
	Particle P0, P1, P2, P3;							/* evaluate for particles given those positions */

	Real LowerLim, UpperLim;							/* limits for internal use */
	Real SumOfSquares = 0;								/* for measuring distance */
	int i;

	for(i=0;i<Dimension;i++) 
    {
		LowerLim = Portal[i] - RoE;						/* select a random point in the portal region */
		UpperLim = Portal[i] + RoE;

		X0[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		SumOfSquares += X0[i]*X0[i];
    }

	/* calculate the value for one random dimension using the distance formula to put it on hypersphere */
	i = ((int)rand())%Dimension;

	SumOfSquares -= X0[i]*X0[i];
	X0[i] = sqrt(RoE*RoE - SumOfSquares);

	/* get other points (3) */
	SumOfSquares = 0;									/* correction in code */

	for(i=0;i<Dimension;i++) 
    {
		LowerLim = Portal[i] - RoE;						/* select a random point in the portal region */
		UpperLim = Portal[i] + RoE;

		X2[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		SumOfSquares += X2[i]*X2[i];
    }

	/* calculate the value for one random dimension using the distance formula to put it on hypersphere */
	i = ((int)rand())%Dimension;

	SumOfSquares -= X2[i]*X2[i];
	X2[i] = sqrt(RoE*RoE - SumOfSquares);
	
	/* calculate X1, X3 which are diagonally opposite points to X0, X1 respectively
	p1 p2 p3

	p2 = p1 + (p3-p1)/2
	2(p2-p1) = p3-p1
	p3 = 2p2-p1*/
	
	for(i=0;i<Dimension;i++) 
    {
		X1[i] = 2*Portal[i] - X0[i];
    }

	for(i=0;i<Dimension;i++) 
    {
		X3[i] = 2*Portal[i] - X2[i];
    }

	/* check fitness value at all points */
	P0.SetPosition(X0);									/* place particles at specified locations */
	P1.SetPosition(X1);
	P2.SetPosition(X2);
	P3.SetPosition(X3);

	P0.Evaluate();										/* evaluate fitness */
	P1.Evaluate();
	P2.Evaluate();
	P3.Evaluate();

	/* return based on comparison with central point */
	Particle P_Portal;

	P_Portal.SetPosition(Portal);
	P_Portal.Evaluate();
	
	if( ( P1.GetFitness() > P_Portal.GetFitness()) && ( P0.GetFitness() > P_Portal.GetFitness()) )
	{
		if( ( P3.GetFitness() > P_Portal.GetFitness()) && ( P2.GetFitness() > P_Portal.GetFitness()) )
		{
														/* we have started to climb a "mountain." stop here. this condition must be reversed in case optimum is a maximum */
			return ROE_LIMIT_REACHED;
		}

		return ROE_LIMIT_NOT_REACHED;
	}
	else
	{
		return ROE_LIMIT_NOT_REACHED;
	}
}

/*******************************************************
* TeleportOutside	   							       *
********************************************************
* Place particle outside portal						   *
********************************************************
*													   *
* Input												   *
*													   *
* Real* Position			: Position of particle	   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void TeleportOutsideRoE(Real *X)
{
	Real LowerLim, UpperLim;
	int i, Direction;

	Direction = ((int)rand())%2;						/* random direction in reference to portal boundary and center of portal */
	
	if(Direction == 1)
	{
		/* positive direction */
		for(i = 0; i < Dimension; i++) 
		{
			LowerLim = Portal[i] + RoE;					/* limits for local use */
			UpperLim = UpperLimit;

			if(UpperLim < LowerLim)						/* correction in code. limit relative correctness check added */
			{											/* checking for validity. apparently this .001 is a nice number */
				LowerLim = UpperLim - .001;									
			}

			X[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		}
	}
	else
	{
		/* negative direction */
		for(i = 0; i < Dimension; i++) 
		{
			LowerLim = LowerLimit;						/* limits for local use */	
			UpperLim = Portal[i] - RoE;

			if(UpperLim < LowerLim)
			{											/* checking for validity. apparently this .001 is a nice number */
				UpperLim = LowerLim + .001;									
			}

			X[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		}
	}
}

/*******************************************************
* TeleportInsideRoE									   *
********************************************************
* Place particle inside inner portal				   *
********************************************************
*													   *
* Input												   *
*													   *
* Real* Position			: Position of particle	   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void TeleportInsideRoE(Real *X)
{
	Real LowerLim, UpperLim;
														/* place a particle in the inner portal */
	for(int i = 0; i < Dimension; i++) 
    {
		LowerLim = Portal[i] - RoE;						/* limits for local use */
		UpperLim = Portal[i] + RoE;

		X[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
    }
}
