/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any     *
* purpose.											   *
********************************************************
* Portal.h											   *
********************************************************
* Model used to depict inner and outer portals	       *
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

#ifndef _PORTAL_H_
#define _PORTAL_H_

#include "Defines.h"									/* include constants defined for portal */

#define INSIDE_OUTER_PORTAL			1					/* particle is inside outer portal */
#define NOT_INSIDE_OUTER_PORTAL		0					/* particle is not inside inner portal */
#define OUTSIDE_INNER_PORTAL		1					/* particle is outside inner portal */
#define NOT_OUTSIDE_INNER_PORTAL	0					/* particle is outside inner portal */
#define OUTER_ROE_LIMIT_REACHED		1					/* outer portal has reached its limit */
#define OUTER_ROE_LIMIT_NOT_REACHED 0					/* outer portal has reached its limit */

/* TODO: move into a class */

void GenerateOuterPortal(Real* Position);				/* generate a Portal at a position */
void GenerateInnerPortal(Real* Position);				/* generate a Portal at a position */

void InitializeOuterRoE();								/* initialize the RoE for the portal */
void InitializeInnerRoE();								/* initialize the RoE for the portal */

void IncreaseOuterRoE();								/* increase the RoE of portal */
void DecreaseInnerRoE();								/* decrease the RoE of portal */

int IsInsideOuterPortal(Real* Position);				/* check for position inside portal */
int IsOutsideInnerPortal(Real* Position);				/* check for position outside portal */

int CheckOuterPortalRoELimit();							/* check for maximum limit of outer portal radius */

void TeleportIntoOuterPortal(Real *X);					/* place particle in outer portal */
void TeleportIntoInnerPortal(Real *X);					/* place particle in inner portal */

Real GetOuterPortalDistanceSquared(Real* Position);		/* read the square of distance from portal */
Real GetInnerPortalDistanceSquared(Real* Position);		/* read the square of distance from portal */

Real GetOuterPortalPull(Real* Position);				/* read the pull towards portal for a certain position */
Real GetInnerPortalPull(Real* Position);				/* read the pull towards portal for a certain position */

int GetOuterPortalTeleports();							/* read total number of teleports out of portal */
int GetInnerPortalTeleports();							/* read total number of teleports into portal */

#endif /* _PORTAL_H_ */
