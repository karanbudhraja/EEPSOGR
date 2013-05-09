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

#define INSIDE_PORTAL				1					/* particle is inside outer portal */
#define NOT_INSIDE_PORTAL			0					/* particle is not inside inner portal */
#define OUTSIDE_PORTAL				1					/* particle is outside inner portal */
#define NOT_OUTSIDE_PORTAL			0					/* particle is outside inner portal */
#define ROE_LIMIT_REACHED			1					/* outer portal has reached its limit */
#define ROE_LIMIT_NOT_REACHED		0					/* outer portal has reached its limit */

/* TODO: move into a class */

void GeneratePortal(Real* Position);					/* generate a Portal at a position */
void InitializeRoE();									/* initialize the RoE for the portal */
void IncreaseRoE();										/* increase the RoE of portal */
void DecreaseRoE();										/* decrease the RoE of portal */
int IsInsideRoE(Real* Position);						/* check for position inside portal */
int IsOutsideRoE(Real* Position);						/* check for position outside portal */
int CheckRoELimit();									/* check the RoE for its limit */
void TeleportOutsideRoE(Real *X);						/* teleport to a location outside portal */
void TeleportInsideRoE(Real *X);						/* teleport to a location inside portal */

Real GetDistanceSquared(Real* Position);				/* read the square of distance from portal */
int GetOutTeleports();									/* read total number of teleports out of portal */
int GetInTeleports();									/* read total number of teleports into portal */

#endif /* _PORTAL_H_ */
