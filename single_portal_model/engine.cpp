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
	extern Real RoE;									/* defined in portal.cpp */
	extern Real InitialRoE;								
	extern Real RoEIncreaseFactor;
	extern Real RoEDecreaseFactor;
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
	
	unsigned int runCount = 0;

	srand((unsigned int)time(NULL));					/* initialize seed so that we get different results every time */
	
	switch(argc)										/* if the parameters have been entered */
	{
		case 2:	
		{
			InitialRoE = argv[0];						
			
			break;
		}

		case 3:
		{
			InitialRoE = argv[0];						
			RoEIncreaseFactor = argv[1];
			
			break;
		}

		case 4:
		{
			InitialRoE = argv[0];						
			RoEIncreaseFactor = argv[1];
			RoEDecreaseFactor = argv[2];
			
			break;
		}

		case 5:
		{
			InitialRoE = argv[0];						
			RoEIncreaseFactor = argv[1];
			RoEDecreaseFactor = argv[2];
			TeleportTypeChangeInterval = argv[3];

			break;
		}

		default: 
		{
			break;
		}
	}		

														/* display parameters */
	cout<<"Parameters: "<<" "<<InitialRoE<<" "<<RoEIncreaseFactor<<" "<<RoEDecreaseFactor<<" "<<TeleportTypeChangeInterval;

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
			cout<<"\t(SUB)Teleports : "<<GetInTeleports()<<" "<<GetOutTeleports();
			cout<<"\t(SUB)RoE : "<<RoE;
#endif

			avg+=S->Birds[S->Best].GetFitness();
            delete(S);
    }
									
	Real averageFitness = avg/executions;
	
	cout<<"\n\nAverage Fitness = "<<averageFitness;		/* display result */
    
	cin.get();
	
	return 0;
}

