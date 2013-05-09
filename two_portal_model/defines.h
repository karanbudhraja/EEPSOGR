/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any                                                           *
* purpose.											   *
********************************************************
* Defines.h											   *
********************************************************
* Common definitions used for the model			       *
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

#ifndef _DEFINES_H_
#define _DEFINES_H_

#define DE_JONG				1							/* enumerate functions */
#define GRIEWANK			2
#define RASTRIGIN_F1		3
#define SCHAFFER_F6			4
#define ROSENBROCK			5

//#define FUNCTION			DE_JONG						/* select function */
//#define FUNCTION			GRIEWANK
//#define FUNCTION			RASTRIGIN_F1
//#define FUNCTION			SCHAFFER_F6
#define FUNCTION			ROSENBROCK

#define SwarmSize			+25							/* number of particles in swarm */
#define Dimension			+10							/* number of dimensions */
#define LowerLimit			-5.12						/* lowermost position value in a dimension */
#define UpperLimit			+5.12						/* uppermost position value in a dimension */
#define C1					+1.8						/* multiplication factor for personal best position pull */
#define C2					+1.8						/* multiplication factor for global best position pull */
#define Weight				+.6							/* weight of particle */
//#define Precision			0.00000001					/* TODO: precision criteria for ending process */

#define PORTAL_TELEPORT									/* enable teleportation */
//#define PORTAL_PULL									/* TODO: enable a pull towards the portal */

typedef long double  Real ;								/* define a real number */

#endif /* _DEFINES_H_ */
