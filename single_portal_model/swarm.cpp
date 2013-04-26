/* 
 * \author Karan Kumar Budhraja 
 * (email : karank.budhraja@gmail.com)
 * \author Ashutosh Singh
 * (email : ashutoshs89@gmail.com)
 * \author Gaurav Dubey
 * (email : gaurav311086@gmail.com)
 * \version 0.1
 * \date 2011/08/28
 * \note This software is in the public domain, 
 * furnished "as is", without technical support, and  
 * with no warranty, express or implied, as to its  
 * usefulness for any purpose.                                             
 */

/*******************************************************
 * Swarm.cpp                                           *
 *******************************************************
 * Implementation file for Swarm.h                     *
 *******************************************************/

#include <iostream>

#include "Swarm.h"                                      /* definition of a swarm */

#ifdef PORTAL_TELEPORT
                                                        /* defined in portal.cpp */
    extern int outTeleports;                            ///< Count of outer teleports  
    extern int inTeleports;                             ///< Count of inner portal teleports  
    extern int TeleportTypeChangeInterval;              ///< Rate of conversion of particles from outer portal to inner portal teleportation  

    int CurrentIteration = 1;                           ///< Track of iterations to implement teleport type change  
#endif

static int ConvertedParticles = 0;                      ///< Keep a count in case all particles available for conversion are exhausted  

/**
 *******************************************************
 * Detail   : Move each particle in swarm once                     
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
void Swarm::Move()
{
    GetGBestIndex();                                    /* calculate index of best particle */
    
#ifdef PORTAL_TELEPORT
                                                        /* take a particle from outer portal and place it in inner portal */
    if((CurrentIteration%TeleportTypeChangeInterval == 0)&&(ConvertedParticles < SwarmSize))
    {
        ConvertedParticles++;                           /* a particle has been converted */

        while(1)
        {
                                                        /* get random particle */
            int ParticleIndex = (int)rand()%SwarmSize;

                                                        /* if possible, change teleportation type. else get another particle */
            if(Birds[ParticleIndex].TeleportType == STAY_OUTSIDE)
            {
                Birds[ParticleIndex].TeleportType = STAY_INSIDE;
                break;
            }
        }
    }

    CurrentIteration++;

    GeneratePortal(Birds[Best].GetPosition());          /* position of portal changed. it must also be resized to original size */
#endif

    for(int i = 0; i < SwarmSize; i++)                  /* each particle moves once */
    {
        Birds[i].Update(Birds[Best]);
    }
}

/**
 *******************************************************
 * Detail   : Initialize swarm particles                           
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
Swarm::Swarm() 
{
    Best=0;                                             /* swarm just made. best particle not known */

    for(int i = 0; i < SwarmSize; i++)
    {
        Birds[i].TeleportRandom();                      /* place the particle at a random position */
        Birds[i].Initialize();                          /* evaluate fitness of particle */

        Birds[i].TeleportType = STAY_OUTSIDE;           /* particles will initially be placed in outer portal */
    }
#ifdef PORTAL_TELEPORT
    outTeleports = 0;                                   /* number of teleports is reset */
    inTeleports = 0;

    InitializeRoE();                                    /* radius of portal are reset */
#endif

    ConvertedParticles = 0;                             /* no particles have changed teleport type yet */
}

/**
 *******************************************************
 * Detail   : Get index of particle with best fitness              
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
void Swarm::GetGBestIndex()
{
    Best = 0;
    
    for(int i = 1; i < SwarmSize; i++)                  /* compare fitness value of all particles to find best one */
    {
        if(Birds[Best].GetBestFitness() > Birds[i].GetBestFitness())
        {
            Best = i;
        }
    }
}
