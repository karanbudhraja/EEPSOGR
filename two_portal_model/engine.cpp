/*******************************************************
* This software is in the public domain, furnished "as *
* is", without technical support, and with no warranty,*
* express or implied, as to its usefulness for any                                                           *
* purpose.											   *
********************************************************
* Engine.cpp										   *
********************************************************
* Exexution of multiple iterations of algorithm        *
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

#include<iostream>
#include<fstream>
#include<ctime>

#include "Swarm.h"										/* definition of a swarm */

using namespace std;

#ifdef PORTAL_TELEPORT
	extern Real OuterRoE, InnerRoE;						/* defined in portal.cpp */
	extern Real InitialOuterRoE;					
	extern Real InitialInnerRoE;					
	extern Real OuterRoEIncreaseFactor;				
	extern Real InnerRoEDecreaseFactor;				
	extern int TeleportTypeChangeInterval;			
#endif
	
/*******************************************************
* main												   *
********************************************************
* Perform several iterations of pso					   *
********************************************************
*													   *
* Input						: Parameters (optional)	   *
*													   *
********************************************************
*													   *
* Output											   *
*													   *
*	0 (always)										   *
*													   *
*******************************************************/
int main(int argc, char *argv)
{
	const int executions = 10;							/* number of times the program is executed */
	Real avg = 0;										/* average fitness value */
	
	srand((unsigned int)time(NULL));					/* initialize seed so that we get different results every time */
	
	switch(argc)										/* if the parameters have been entered */
	{
		case 2:	
		{
			InitialOuterRoE = argv[1];						
			
			break;
		}

		case 3:
		{
			InitialOuterRoE = argv[1];						
			InitialInnerRoE = argv[2];
			
			break;
		}

		case 4:
		{
			InitialOuterRoE = argv[1];						
			InitialInnerRoE = argv[2];
			OuterRoEIncreaseFactor = argv[3];
			
			break;
		}

		case 5:
		{
			InitialOuterRoE = argv[1];						
			InitialInnerRoE = argv[2];
			OuterRoEIncreaseFactor = argv[3];
			InnerRoEDecreaseFactor = argv[4];

			break;
		}

		case 6:
		{
			InitialOuterRoE = argv[1];						
			InitialInnerRoE = argv[2];
			OuterRoEIncreaseFactor = argv[3];
			InnerRoEDecreaseFactor = argv[4];
			TeleportTypeChangeInterval = argv[5];

			break;
		}

		default: 
		{
			break;
		}
	}			
														/* display parameters */
	cout<<"Parameters: "<<" "<<InitialOuterRoE<<" "<<InitialInnerRoE<<" "<<OuterRoEIncreaseFactor<<" "<<InnerRoEDecreaseFactor<<" "<<TeleportTypeChangeInterval;

	for(int x = 0; x < executions; x++)
	{
            Swarm *S = new Swarm;
			
            for(int i = 0; i < 1000; i++)
			{
                    S->Move();							/* every particle moves once */
			}

            cout<<"\n\nRun  :  "<<x+1<<"\tFitness : "<<S->Birds[S->Best].GetFitness();

#ifdef PORTAL_TELEPORT
														/* display run details */
			cout<<"\tTeleports : "<<GetOuterPortalTeleports()<<" "<<GetInnerPortalTeleports();
			cout<<"\tRoE : "<<OuterRoE<<" "<<InnerRoE;
#endif

            avg+=S->Birds[S->Best].GetFitness();
            delete(S);
    }
														    
	cout<<"\n\nAverage Fitness = "<<avg/executions;		/* display result */
    
	cin.get();
    
	return 0;
}
