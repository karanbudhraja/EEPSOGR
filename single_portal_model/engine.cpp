/** \mainpage Summary
 *
 * This code is the implementation of the two portal 
 * model of PSO. The model has been proposed by the authors
 * as a variant of the basic version of PSO. Guided 
 * re-initialization is used to avoid premature 
 * convergence of particles.
 *
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
 * Engine.cpp                                          *
 *******************************************************
 * Single Portal model of PSO                          *
 *******************************************************/

#include<iostream>
#include<fstream>
#include<ctime>

#include "Swarm.h"                                      ///< definition of a swarm

using namespace std;

#ifdef PORTAL_TELEPORT
                                                        /* defined in portal.cpp */
    extern Real RoE;                                    ///< RoE of portal  
    extern Real InitialRoE;                             ///< Initial RoE of portal  
    extern Real RoEIncreaseFactor;                      ///< Rate of increase of RoE  
    extern Real RoEDecreaseFactor;                      ///< Rate of decrease of RoE  
    extern int TeleportTypeChangeInterval;              ///< Rate of conversion of particles from outer to inner teleportation 
#endif

/**
 *******************************************************
 * Perform several iterations of pso                    
 *                                                      
 * Input    : Parameters for teleportation (optional)    
 *                                                      
 * Output   : 0 (always)                                         
 *******************************************************
 */
int main(int argc, char *argv)
{
    const int executions = 10;                          /* number of times the program is executed */
    Real avg = 0;                                       /* average fitness value */
    
    unsigned int runCount = 0;

    srand((unsigned int)time(NULL));                    /* initialize seed so that we get different results every time */
    
    switch(argc)                                        /* if the parameters have been entered */
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
                    S->Move();                          /* every particle moves once */
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
    
    cout<<"\n\nAverage Fitness = "<<averageFitness;     /* display result */
    
    cin.get();
    
    return 0;
}

