/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any       *
* purpose.											   *
********************************************************
* Particle.h										   *
********************************************************
* Model used for a particle and its properties	       *
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

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Defines.h"									/* include constants defined for particles */

#ifdef PORTAL_TELEPORT									/* if teleportation is enabled */
#include "Portal.h"							
#endif

const Real Vmax = ((UpperLimit-LowerLimit)*1);			/* maximum value of particle velocity */

enum e_TeleportType{STAY_OUTSIDE, STAY_INSIDE};			/* whether particle shall remain inside or outside of portal */

class Particle
{
	private:
		Real X[Dimension];								/* position of particle */
		Real V[Dimension];								/* velocity of particle */
		Real PBest[Dimension];							/* location of personal best solution */
		Real Fitness;									/* fitness value at current position */
		Real BestFitness;								/* fitness value at personal best soluton */

	public:
		e_TeleportType TeleportType;					/* nature of teleportation for particle */

		void Initialize();								/* initialize the particle */
		void TeleportRandom();							/* teleport to a random location */
		void Evaluate();								/* evaluate fitness value at current position */
		void Update(Particle GBest);					/* update global best position value if needed */
		Real* GetPosition();							/* read position */
		Real GetFitness();								/* read fitness value at current position */
		Real GetBestFitness();							/* read fitness value at personal best solution */
		void SetPosition(Real *Position);				/* set the position of a particle */
};

#endif /* _PARTICLE_H_ */
