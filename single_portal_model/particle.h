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
 * Particle.h                                          *
 *******************************************************
 * Model used for a particle and its properties        *
 *******************************************************/

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Defines.h"                                    /* include constants defined for particles */

#ifdef PORTAL_TELEPORT                                  /* if teleportation is enabled */
#include "Portal.h"                                     /* include portal related definitions */
#endif

const Real Vmax = ((UpperLimit-LowerLimit)*1);          ///< Maximum value of particle velocity

enum e_TeleportType{STAY_OUTSIDE, STAY_INSIDE};         ///< Whether particle shall remain inside or outside of portal

class Particle                                          /** \brief Definition of a particle */
{
    private:
        Real X[Dimension];                              ///< Position of particle  
        Real V[Dimension];                              ///< Velocity of particle  
        Real PBest[Dimension];                          ///< Location of personal best solution  
        
        Real Fitness;                                   ///< Fitness value at current position  
        Real BestFitness;                               ///< Fitness value at personal best soluton  
        
    public:
        e_TeleportType TeleportType;                    ///< Brief : Nature of teleportation for particle  

        void Initialize();                              ///< Brief : Initialize the particle  
        void Evaluate();                                ///< Brief : Evaluate fitness value at current position  
        void Update(Particle GBest);                    ///< Brief : Update global best position value if needed  

        Real* GetPosition();                            ///< Brief : Read position  
        Real GetFitness();                              ///< Brief : Read fitness value at current position  
        Real GetBestFitness();                          ///< Brief : Read fitness value at personal best solution  
        void TeleportRandom();                          ///< Brief : Reset position to a random value  
        void SetPosition(Real *Position);               ///< Brief : Explicitly set the position of the particle  
};

#endif /* _PARTICLE_H_ */
