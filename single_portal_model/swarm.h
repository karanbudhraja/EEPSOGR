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
 * Swarm.h                                             *
 *******************************************************
 * Model used for a swarm of particles                 *
 *******************************************************/

#ifndef _SWARM_H_
#define _SWARM_H_

#include "Particle.h"                                   /* A swarm consists of many particles */

class Swarm                                             /** \brief Definition of a swarm */
{
    public:
        Particle Birds[SwarmSize];                      ///< Brief : Swarm of birds 
        int Best;                                       ///< Brief : Index of global best solution 

        Swarm();                                        ///< Brief : Constructor to initialize swarm 
        void Move();                                    ///< Brief : Each particle makes one move 
        void GetGBestIndex();                           ///< Brief : Read index of global best solution 
};

#endif /* _SWARM_H_ */
