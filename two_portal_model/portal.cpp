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

Real InnerPortal[Dimension];                            /* current position of inner portal */
Real InnerRoE;

Real OuterPortal[Dimension];                            /* current position of outer portal */
Real OuterRoE;

#if 0													/* abstract values */
	Real InitialOuterRoE = 0.001;
	Real InitialInnerRoE = 0.001;

	Real OuterRoEIncreaseFactor = 1.1;
	Real InnerRoEDecreaseFactor = 1.1;
	int TeleportTypeChangeInterval = 40;				/* iterations / swarm size for a uniform distribution */
#elif 1													/* tuned for unimodal functions */
	Real InitialOuterRoE = 0.048579;
	Real InitialInnerRoE = 0.999;

	Real OuterRoEIncreaseFactor = 9.999;
	Real InnerRoEDecreaseFactor = 9.999;
	int TeleportTypeChangeInterval = 1;					
#else													/* tuned for multimodal functions */
	Real InitialOuterRoE = 0.0461647;					/* RoE of outer portal */
	Real InitialInnerRoE = 0.999;						/* RoE of inner portal */

	Real OuterRoEIncreaseFactor = 1.001;				/* rate of increase of outer RoE */
	Real InnerRoEDecreaseFactor = 9.84579;				/* rate of decrease of inner RoE */
	int TeleportTypeChangeInterval = 999;				/* rate of conversion of particles from outer portal to inner portal teleportation */
#endif

int OuterPortalTeleports = 0;							/* count of outer portal teleports */
int InnerPortalTeleports = 0;							/* count of inner portal teleports */

/*******************************************************
* GenerateOuterPortal								   *
********************************************************
* Generate outer portal with specified centre		   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void GenerateOuterPortal(Real* Position)
{
	int Count;											

	if(IsInsideOuterPortal(Position) == 0)
	{
		InitializeOuterRoE();							/* if our new point is inside roe, make a fresh portal */
	}

	for(Count = 0; Count < Dimension; Count++)
	{
		OuterPortal[Count] = Position[Count];			/* initialize outer portal */
	}
}

/*******************************************************
* GenerateOuterPortal								   *
********************************************************
* Generate inner portal with specified centre		   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void GenerateInnerPortal(Real* Position)
{
	int Count;											

														/* if outer roe is within limits, then we may increase it */
	if(IsOutsideInnerPortal(Position) == OUTER_ROE_LIMIT_NOT_REACHED)
	{
		InitializeInnerRoE();							/* if our new point is outside roe, make a fresh portal */		
	}

	for(Count = 0; Count < Dimension; Count++)
	{
		InnerPortal[Count] = Position[Count];			/* initialize inner portal */
	}
}

/*******************************************************
* InitializeOuterRoE								   *
********************************************************
* Reset radius of outer portal						   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void InitializeOuterRoE()
{
	OuterRoE = InitialOuterRoE;							/* set initial value of outer RoE */
}

/*******************************************************
* InitializeInnerRoE								   *
********************************************************
* Reset radius of inner portal						   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void InitializeInnerRoE()
{
	InnerRoE = InitialInnerRoE;							/* set initial value of inner RoE */
}

/*******************************************************
* IncreaseOuterRoE									   *
********************************************************
* Increase radius of outer portal					   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void IncreaseOuterRoE()
{
														/* if outer roe is within limits, then we may increase it */
	if(CheckOuterPortalRoELimit() == OUTER_ROE_LIMIT_NOT_REACHED)					
	{
		OuterRoE *= OuterRoEIncreaseFactor;
	}

	OuterPortalTeleports++;								/* a teleport has occured */
}

/*******************************************************
* DecreaseInnerRoE									   *
********************************************************
* Decrease radius of inner portal					   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void DecreaseInnerRoE()
{
	InnerRoE /= InnerRoEDecreaseFactor;					/* no lower limit made on the inner roe */

	InnerPortalTeleports++;								/* a teleport has occurred */
}

/*******************************************************
* IsInsideOuterPortal								   *
********************************************************
* Check if particle is inside outer portal			   *
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
*	INSIDE_OUTER_PORTAL								   *
*		if particle is inside of outer portal		   *
*	NOT_INSIDE_OUTER_PORTAL							   *
*		if particle is outside of outer portal		   *
*													   *
*******************************************************/
int IsInsideOuterPortal(Real* Position)
{
	Real DistanceSquared = GetOuterPortalDistanceSquared(Position);
														/* check if particle is inside portal roe */
	if((DistanceSquared < OuterRoE*OuterRoE)&&(DistanceSquared))
	{
		return INSIDE_OUTER_PORTAL;						
	}
    else
	{
		return NOT_INSIDE_OUTER_PORTAL;
	}
}

/*******************************************************
* IsOutsideInnerPortal								   *
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
*	OUTSIDE_INNER_PORTAL							   *
*		if particle is outside of inner portal		   *
*	NOT_OUTSIDE_INNER_PORTAL						   *
*		if particle is inside of outer portal		   *
*													   *
*******************************************************/
int IsOutsideInnerPortal(Real* Position)
{
	Real DistanceSquared = GetInnerPortalDistanceSquared(Position);
														/* check if particle is outside portal roe */
	if((DistanceSquared > InnerRoE*InnerRoE)&&(DistanceSquared))
	{
		return OUTSIDE_INNER_PORTAL;
	}
    else
	{
		return NOT_OUTSIDE_INNER_PORTAL;
	}
}

/*******************************************************
* GetOuterPortalDistanceSquared						   *
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
Real GetOuterPortalDistanceSquared(Real* Position)
{
    int Count;
    Real DistanceSquared = 0.0;

    for(Count = 0; Count < Dimension; Count++)			/* get distance of particle from center of outer portal */
	{
		DistanceSquared += (OuterPortal[Count] - Position[Count])*(OuterPortal[Count] - Position[Count]);
	}

    return DistanceSquared;
}

/*******************************************************
* GetInnerPortalDistanceSquared						   *
********************************************************
* Square of distance from centre of inner portal	   *
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
Real GetInnerPortalDistanceSquared(Real* Position)
{
    int Count;
    Real DistanceSquared = 0.0;

    for(Count = 0; Count < Dimension; Count++)			/* get distance of particle from center of inner portal */
	{
		DistanceSquared += (InnerPortal[Count] - Position[Count])*(InnerPortal[Count] - Position[Count]);
	}

    return DistanceSquared;
}

/*******************************************************
* GetOuterPortalTeleports						       *
********************************************************
* Get number of teleports with respect to outer portal *
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
int GetOuterPortalTeleports()
{
	return OuterPortalTeleports;
}

/*******************************************************
* GetInnerPortalTeleports						       *
********************************************************
* Get number of teleports with respect to inner portal *
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
int GetInnerPortalTeleports()
{
	return InnerPortalTeleports;
}

/*******************************************************
* CheckOuterPortalRoELimit						       *
********************************************************
* Check for upper limit of radius of outer portal	   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	OUTER_ROE_LIMIT_REACHED							   *
*		if limit has been reached					   *
*	OUTER_ROE_LIMIT_NOT_REACHED						   *
*		if limit has not been reached				   *
*													   *
*******************************************************/
int CheckOuterPortalRoELimit()
{
														/* get points on the hypersphere at random */
	Real X0[Dimension], X1[Dimension], X2[Dimension], X3[Dimension];
	Particle P0, P1, P2, P3;							/* evaluate for particles given those positions */

	Real LowerLim, UpperLim;							/* limits for internal use */
	Real SumOfSquares = 0;								/* for measuring distance */
	int i;

	for(i = 0; i < Dimension; i++) 
    {
		LowerLim = OuterPortal[i] - OuterRoE;			/* select a random point in the outer portal region */
		UpperLim = OuterPortal[i] + OuterRoE;

		X0[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		SumOfSquares += X0[i]*X0[i];
    }

	/* calculate the value for one random dimension using the distance formula to put it on hypersphere */
	i = ((int)rand())%Dimension;

	SumOfSquares -= X0[i]*X0[i];
	X0[i] = sqrt(OuterRoE*OuterRoE - SumOfSquares);

	/* get other points (3) */
	SumOfSquares = 0;									/* correction in code */
	
	for(i=0;i<Dimension;i++) 
    {
		LowerLim = OuterPortal[i] - OuterRoE;			/* select a random point in the outer portal region */
		UpperLim = OuterPortal[i] + OuterRoE;

		X2[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		SumOfSquares += X2[i]*X2[i];
    }

	/* calculate the value for one random dimension using the distance formula to put it on hypersphere */
	i = ((int)rand())%Dimension;

	SumOfSquares -= X2[i]*X2[i];
	X2[i] = sqrt(OuterRoE*OuterRoE - SumOfSquares);
	
	/* calculate X1, X3 which are diagonally opposite points to X0, X1 respectively
	p1 p2 p3

	p2 = p1 + (p3-p1)/2
	2(p2-p1) = p3-p1
	p3 = 2p2-p1*/
	
	for(i=0;i<Dimension;i++) 
    {
		X1[i] = 2*OuterPortal[i] - X0[i];
    }

	for(i=0;i<Dimension;i++) 
    {
		X3[i] = 2*OuterPortal[i] - X2[i];
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
	Particle P_InnerPortal;								/* evaluate fitness value at central point */

	P_InnerPortal.SetPosition(InnerPortal);
	P_InnerPortal.Evaluate();
	
	if( ( P1.GetFitness() > P_InnerPortal.GetFitness()) && ( P0.GetFitness() > P_InnerPortal.GetFitness()) )
	{
		if( ( P3.GetFitness() > P_InnerPortal.GetFitness()) && ( P2.GetFitness() > P_InnerPortal.GetFitness()) )
		{
														/* we have started to climb a "mountain." stop here. this condition must be reversed in case optimum is a maximum */
			return OUTER_ROE_LIMIT_REACHED;
		}

		return OUTER_ROE_LIMIT_NOT_REACHED;
	}
	else
	{
		return OUTER_ROE_LIMIT_NOT_REACHED;
	}
}

/*******************************************************
* TeleportIntoOuterPortal							   *
********************************************************
* Place particle inside outer portal				   *
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
void TeleportIntoOuterPortal(Real *X)
{
	Real LowerLim, UpperLim;
	int i, Direction;

	Direction = ((int)rand())%2;						/* random direction in reference to portal boundary and center of portal */
														
	if(Direction == 1)
	{
		/* positive direction */
		for(i = 0; i < Dimension; i++) 
		{
			LowerLim = OuterPortal[i] + OuterRoE;		/* limits for local use */
			UpperLim = UpperLimit;

			if(UpperLim < LowerLim)
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
			LowerLim = LowerLimit;						/* local limits */
			UpperLim = OuterPortal[i] - OuterRoE;

			if(UpperLim < LowerLim)
			{											/* checking for validity. apparently this .001 is a nice number */
				UpperLim = LowerLim + .001;									
			}
			
			X[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
		}
	}
}

/*******************************************************
* TeleportIntoInnerPortal							   *
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
void TeleportIntoInnerPortal(Real *X)
{
	Real LowerLim, UpperLim;
														/* place a particle in the inner portal */
	for(int i = 0; i < Dimension; i++) 
    {
		LowerLim = InnerPortal[i] - InnerRoE;			/* limits for local use */
		UpperLim = InnerPortal[i] + InnerRoE;

		X[i] = LowerLim + ((double)rand()/(RAND_MAX + 1))*(UpperLim-LowerLim);
    }
}
