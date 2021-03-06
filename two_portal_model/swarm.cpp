/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any                                                           *
* purpose.											   *
********************************************************
* Swarm.cpp											   *
********************************************************
* Implementation file for Swarm.h				       *
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

#include "Swarm.h"										/* definition of a swarm */

#ifdef PORTAL_TELEPORT
	extern int OuterPortalTeleports;					/* defined in portal.cpp */
	extern int InnerPortalTeleports;
	extern int TeleportTypeChangeInterval;						

	int CurrentIteration = 1;							/* track of iterations to implement teleport type change */
#endif

static int ConvertedParticles = 0;						/* keep a count in case all particles available for conversion are exhausted */

/*******************************************************
* Swarm::Move										   *
********************************************************
* Move each particle in swarm once					   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Swarm::Move()
{
	GetGBestIndex();									/* calculate index of best particle */
	
#ifdef PORTAL_TELEPORT
														/* take a particle from outer portal and place it in inner portal */
	if((CurrentIteration % TeleportTypeChangeInterval == 0)&&(ConvertedParticles < SwarmSize))
	{
		ConvertedParticles++;							/* a particle has been converted */

		while(1)										
		{
			int ParticleIndex = (int)rand()%SwarmSize;	/* get random particle */

														/* if possible, change teleportation type. else get another particle */
			if(Birds[ParticleIndex].TeleportType == STAY_OUTSIDE)
			{
				Birds[ParticleIndex].TeleportType = STAY_INSIDE;
				break;
			}
		}
	}

	CurrentIteration++;

    GenerateOuterPortal(Birds[Best].GetPosition());		/* position of portal changed. it must also be resized to original size */
	GenerateInnerPortal(Birds[Best].GetPosition());
#endif
														/* each particle moves once */
	for(int birdNumber = 0; birdNumber < SwarmSize; birdNumber++)
	{
		Birds[birdNumber].Update(Birds[Best]);
	}
}


/*******************************************************
* Swarm::Swarm										   *
********************************************************
* Initialize swarm particles						   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
Swarm::Swarm() 
{
	Best=0;												/* swarm just made. best particle not known */

	for(int i = 0; i < SwarmSize; i++)
	{
		Birds[i].TeleportRandom();						/* place the particle at a random position */
		Birds[i].Initialize();							/* evaluate fitness of particle */

		Birds[i].TeleportType = STAY_OUTSIDE;			/* particles will initially be placed in outer portal */
	}

#ifdef PORTAL_TELEPORT
	OuterPortalTeleports = 0;							/* number of teleports is reset */
	InnerPortalTeleports = 0;

	InitializeOuterRoE();								/* radii of portals are reset */
	InitializeInnerRoE();
#endif

	ConvertedParticles = 0;								/* no particles have changed teleport type yet */
}

/*******************************************************
* Swarm::GetGBestIndex								   *
********************************************************
* Set index of particle with best fitness			   *
********************************************************
*													   *
* Input						: Nothing				   *
*													   *
********************************************************
*													   *
* Output					: Nothing				   *
*													   *
*******************************************************/
void Swarm::GetGBestIndex()
{
	Best=0;

	for(int i = 1; i < SwarmSize; i++)					/* compare fitness value of all particles to find best one */
	{
		if(Birds[Best].GetBestFitness() > Birds[i].GetBestFitness())
		{
			Best = i;
		}
	}
}
