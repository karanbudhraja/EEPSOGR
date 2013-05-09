/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any       *
* purpose.											   *
********************************************************
* Particle.cpp										   *
********************************************************
* Implementation file for Particle.h				   *
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
#define _USE_MATH_DEFINES								/* for M_PI */
#include <math.h>

#include "Particle.h"									/* definition of a particle */
#include "Portal.h"										/* portal related definitions */

using namespace std;

/*******************************************************
* Particle::Initialize								   *
********************************************************
* initialize personal best fitness value for particle  *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Particle::Initialize()
{
	Evaluate();											/* evaluate fitness value for particle */
	BestFitness = Fitness;								/* particle only has one value of fitness for personal best */
}

/*******************************************************
* Particle::Evaluate								   *
********************************************************
* evaluate fitness value for particle				   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Particle::Evaluate()
{
	Fitness = 0;										/* functions defined here */
	Real Sum = 0, Product = 1;
	Real finalVal = 0;									/* final value to be attained */

#if FUNCTION == DE_JONG
	/**************************
	*DeJong 
	***************************/
	Sum = 0, Product = 1;

	for(int i = 0; i < Dimension; i++)
	{
		Sum += (X[i] * X[i]);
	}

	Fitness = Sum;
	//Real Fitness_DeJong = Sum;
	/**************************/

#elif FUNCTION == GRIEWANK
	/**************************
	*Griewank 
	***************************/
	Sum = 0, Product = 1;

	for(int i = 0; i < Dimension; i++)
	{
		Sum += ((X[i] * X[i]) / 4000);
		Product *= (cos(X[i]) / sqrt(Real(i+1)));		
	}

	Fitness = Sum - Product + 1;
	//Real Fitness_Griewank = Sum - Product; 
	/**************************/

#elif FUNCTION == RASTRIGIN_F1
	/****************************
	*Rastrigin F1
	*****************************/
	Sum = 0, Product = 1;

	for(int i = 0; i < Dimension; i++)
	{
		Sum += ((X[i] * X[i]) - (10 * cos( 2 * M_PI * X[i] )));
	}

	Fitness = Sum + 10 * Dimension;
	//Real Fitness_RastriginF1 = Sum + 10 * Dimension; 
	/**************************/

#elif FUNCTION == SCHAFFER_F6
	/****************************
	*Schaffer F6
	****************************/
	Sum = 0, Product = 1;

	for(int i = 0; i < Dimension; i++)
	{
		Sum += (X[i] * X[i]);
	}

	Fitness = .5 + (pow(sin(pow((double)Sum,0.5)), 2) - .5) / pow((double)(1 + .001 * Sum), 2);
	//Real Fitness_SchafferF6 = .5 + (pow(sin(sqrt(Sum)), 2) - .5) / pow((1 + .001 * Sum), 2);
	/**************************/

#elif FUNCTION == ROSENBROCK
	/***************************
	*RosenBrock
	****************************/
	Sum = 0, Product = 1;

	for(int i = 0; i < Dimension-1; i++)
	{
		Sum += pow((X[i+1] - pow(X[i], 2)), 2) + pow((1 - X[i]), 2);
	}

	Fitness = 100 * Sum;
	//Real Fitness_Rosenbrock = 100 * Sum;
	/**************************/

#endif

#if 0
	Fitness = Fitness_DeJong \								/* overall tuning */
			+ Fitness_Griewank \
			+ Fitness_RastriginF1 \
			+ Fitness_Rosenbrock \
			+ Fitness_SchafferF6;
	
	Fitness = Fitness_DeJong + Fitness_Rosenbrock;			/* unimodal tuning */
	
															/* multimodal tuning */
	Fitness = Fitness_Griewank + Fitness_RastriginF1 + Fitness_SchafferF6;	
	
	Fitness = Fitness_Griewank;								/* specific tuning */
#endif

	if(Fitness < 0.0)
		Fitness = -Fitness;

	//Fitness=Precision*ceil(Fitness/Precision);			/* TODO: implement precision limit on iterations */

	//if(Fitness < BestFitness)
															/* check for closeness to the final value */
	if(abs(Fitness - finalVal) < abs(BestFitness - finalVal))
//	if(abs(Fitness - 100) < abs(BestFitness - 100))			/* only for rosenbrock */
	{
		BestFitness = Fitness;
		for(int x = 0; x < Dimension; x++)
		{
			PBest[x] = X[x];									
		}	
	}

	//cout<<"\tFitness: "<<Fitness;							/* display information */
	//cout<<"\n Pos: "<<X[0]<<" "<<X[1]<<" "<<X[2]<<" "<<X[3]<<" "<<X[4]<<" "<<X[5]<<" "<<X[6]<<" "<<X[7]<<" "<<X[8]<<" "<<X[9];
}

/*******************************************************
* Particle::Update									   *
********************************************************
* move particle	once								   *
********************************************************
*													   *
* Input												   *
*													   *
* Particle GBest			: Best particle			   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Particle::Update(Particle GBest) 
{
#ifdef PORTAL_TELEPORT

	if(TeleportType == STAY_OUTSIDE)					/* check on teleportation property validity of particles */
	{
		if(IsInsideRoE(GetPosition()) == INSIDE_PORTAL)
		{
			if(CheckRoELimit() == ROE_LIMIT_NOT_REACHED)
				IncreaseRoE();
			
			TeleportOutsideRoE(X);						/* initialize the position */
			Initialize();								/* initialize the particle */
		}
	}
	else
	{
		if(IsOutsideRoE(GetPosition()) == OUTSIDE_PORTAL)
		{
			/* TODO: decrease criteria must be changed */
			DecreaseRoE();
			
			TeleportOutsideRoE(X);						/* initialize the position */
			Initialize();								/* initialize the particle */
		}
	}
#endif

      for(int i = 0 ; i < Dimension;i++) 
      {
        Real r1,r2;

		r1 = (double)(rand())/(RAND_MAX + 1);			/* generate random numbers */
        r2 = (double)(rand())/(RAND_MAX + 1);
		
		V[i] = Weight*V[i] + C1 * r1 * (PBest[i]-X[i])+ C2*r2 * (GBest.X[i]-X[i]);

        if(V[i] < -Vmax)								/* check added for velocity */
		{
			V[i] = -Vmax;
		}
        else if(V[i] > Vmax)
		{
            V[i] = Vmax;
		}

		X[i]+=V[i];										/* update position of particle */

        if(X[i]>UpperLimit)								/* boundary check on position */
        {
			X[i]=UpperLimit-.001;
			V[i]=0;
		}
		if(X[i]<LowerLimit) 
        {
			X[i]=LowerLimit+.001;
			V[i]=0;
		}
     }

	  Evaluate();										/* evaluate fitness value for particle */
}

/*******************************************************
* Particle::GetPosition							       *
********************************************************
* Get position of particle							   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	Position of particle 							   *
*													   *
*******************************************************/
Real* Particle::GetPosition()
{
	return X;
}

/*******************************************************
* Particle::GetFitness							       *
********************************************************
* Get current fitness value of particle				   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	Current fitness value of particle				   *
*													   *
*******************************************************/
Real Particle::GetFitness()
{
	return Fitness;
}

/*******************************************************
* Particle::GetFitness							       *
********************************************************
* Get best fitness value of particle				   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	Best fitness value of particle					   *
*													   *
*******************************************************/
Real Particle::GetBestFitness()
{
	return BestFitness;
}

/*******************************************************
* Particle::TeleportRandom							   *
********************************************************
* Place particle at random location in hyperspace      *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Particle::TeleportRandom()
{
	for(int i=0;i<Dimension;i++) 
    {
														/* teleport to a random location in the hyperspace */
		X[i] = LowerLimit + ((double)rand()/(RAND_MAX + 1))*(UpperLimit-LowerLimit);
		V[i] = -Vmax + ((double)rand()/(RAND_MAX + 1))*(2*Vmax);

		PBest[i]=X[i];									/* since we are initializing, personal best is also reset */
    }
}
/*******************************************************
* Particle::SetPosition								   *
********************************************************
* Place particle at specific position				   *
********************************************************
*													   *
* Input												   *
*													   *
* Real *Position			: position to be placed at *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Particle::SetPosition(Real *Position)
{														/* set position of particle */
	for(int i=0;i<Dimension;i++)
	{
		X[i] = Position[i];
	}
}
