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
 * Defines.h                                           *
 *******************************************************
 * Common definitions used for the model               *
 *******************************************************/

#ifndef _DEFINES_H_
#define _DEFINES_H_

#define DE_JONG             1                           ///< DeJong fitness function
#define GRIEWANK            2                           ///< Griewank fitness function
#define RASTRIGIN_F1        3                           ///< Rastrigin fitness function 1
#define SCHAFFER_F6         4                           ///< Schaffer fitness function 6
#define ROSENBROCK          5                           ///< Rosenbrock fitness function
                                                        /* Select function */
//#define FUNCTION          DE_JONG                     ///< Function to be optimized
//#define FUNCTION          GRIEWANK                    ///< Function to be optimized
#define FUNCTION            RASTRIGIN_F1                ///< Function to be optimized
//#define FUNCTION          SCHAFFER_F6                 ///< Function to be optimized
//#define FUNCTION          ROSENBROCK                  ///< Function to be optimized

#define SwarmSize           +25                         ///< Number of particles in swarm
#define Dimension           +10                         ///< Number of dimensions
#define LowerLimit          -5.12                       ///< Lowermost position value in a dimension
#define UpperLimit          +5.12                       ///< Uppermost position value in a dimension 
#define C1                  +1.8                        ///< Multiplication factor for personal best position pull 
#define C2                  +1.8                        ///< Multiplication factor for global best position pull 
#define Weight              +0.6                        ///< Weight of particle 
//#define Precision         0.00000001                  /* TODO: precision criteria for ending process */

#define PORTAL_TELEPORT                                 ///< Enable teleportation
//#define PORTAL_PULL                                   /* TODO: enable a pull towards the portal */

typedef long double  Real ;                             ///< Define a real number

#endif /* _DEFINES_H_ */
