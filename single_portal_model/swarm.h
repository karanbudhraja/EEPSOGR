/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any       *
* purpose.											   *
********************************************************
* Swarm.h											   *
********************************************************
* Model used for a swarm of particles			       *
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

#ifndef _SWARM_H_
#define _SWARM_H_

#include "Particle.h"									/* a swarm consists of many particles */

class Swarm 
{
	public:
		Particle Birds[SwarmSize];						/* swarm of birds */
		int Best;										/* index of global best solution */

		Swarm();										/* constructor to initialize swarm */
		void Move();									/* each particle makes one move */
		void GetGBestIndex();							/* read index of global best solution */
};

#endif /* _SWARM_H_ */
