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
 * Portal.h                                            *
 *******************************************************
 * Model used to depict inner and outer portals        *
 *******************************************************/

#ifndef _PORTAL_H_
#define _PORTAL_H_

#include "Defines.h"                                    /* include constants defined for portal */

#define INSIDE_PORTAL               1                   ///< Particle is inside outer portal  
#define NOT_INSIDE_PORTAL           0                   ///< Particle is not inside inner portal  
#define OUTSIDE_PORTAL              1                   ///< Particle is outside inner portal  
#define NOT_OUTSIDE_PORTAL          0                   ///< Particle is outside inner portal  
#define ROE_LIMIT_REACHED           1                   ///< Outer portal has reached its limit  
#define ROE_LIMIT_NOT_REACHED       0                   ///< Outer portal has reached its limit  

/* TODO: move into a class */

void GeneratePortal(Real* Position);                    ///< Brief : Generate a Portal at a position  
void InitializeRoE();                                   ///< Brief : Initialize the RoE for the portal  
void IncreaseRoE();                                     ///< Brief : Increase the RoE of portal  
void DecreaseRoE();                                     ///< Brief : Decrease the RoE of portal  
int IsInsideRoE(Real* Position);                        ///< Brief : Check for position inside portal  
int IsOutsideRoE(Real* Position);                       ///< Brief : Check for position outside portal  
int CheckRoELimit();                                    ///< Brief : Check the RoE for its limit  
void TeleportOutsideRoE(Real *X);                       ///< Brief : Teleport to a location outside portal  
void TeleportInsideRoE(Real *X);                        ///< Brief : Teleport to a location inside portal  

Real GetDistanceSquared(Real* Position);                ///< Brief : Read the square of distance from portal  
int GetOutTeleports();                                  ///< Brief : Read total number of teleports out of portal  
int GetInTeleports();                                   ///< Brief : Read total number of teleports into portal  

#endif /* _PORTAL_H_ */
