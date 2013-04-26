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

#define INSIDE_OUTER_PORTAL         1                   ///< Particle is inside outer portal  
#define NOT_INSIDE_OUTER_PORTAL     0                   ///< Particle is not inside inner portal  
#define OUTSIDE_INNER_PORTAL        1                   ///< Particle is outside inner portal  
#define NOT_OUTSIDE_INNER_PORTAL    0                   ///< Particle is outside inner portal  
#define OUTER_ROE_LIMIT_REACHED     1                   ///< Outer portal has reached its limit  
#define OUTER_ROE_LIMIT_NOT_REACHED 0                   ///< Outer portal has reached its limit  

/* TODO: move into a class */

void GenerateOuterPortal(Real* Position);               ///< Brief : Generate a Portal at a position  
void GenerateInnerPortal(Real* Position);               ///< Brief : Generate a Portal at a position  

void InitializeOuterRoE();                              ///< Brief : Initialize the RoE for the portal  
void InitializeInnerRoE();                              ///< Brief : Initialize the RoE for the portal  

void IncreaseOuterRoE();                                ///< Brief : Increase the RoE of portal  
void DecreaseInnerRoE();                                ///< Brief : Decrease the RoE of portal  

int IsInsideOuterPortal(Real* Position);                ///< Brief : Check for position inside portal  
int IsOutsideInnerPortal(Real* Position);               ///< Brief : Check for position outside portal  

int CheckOuterPortalRoELimit();                         ///< Brief : Check for maximum limit of outer portal radius  

void TeleportIntoOuterPortal(Real *X);                  ///< Brief : Place particle in outer portal  
void TeleportIntoInnerPortal(Real *X);                  ///< Brief : Place particle in inner portal  

Real GetOuterPortalDistanceSquared(Real* Position);     ///< Brief : Read the square of distance from portal  
Real GetInnerPortalDistanceSquared(Real* Position);     ///< Brief : Read the square of distance from portal  

Real GetOuterPortalPull(Real* Position);                ///< Brief : Read the pull towards portal for a certain position  
Real GetInnerPortalPull(Real* Position);                ///< Brief : Read the pull towards portal for a certain position  

int GetOuterPortalTeleports();                          ///< Brief : Read total number of teleports out of portal  
int GetInnerPortalTeleports();                          ///< Brief : Read total number of teleports into portal  

#endif /* _PORTAL_H_ */
