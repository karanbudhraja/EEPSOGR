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
 * Two Portal model of PSO                             *
 *******************************************************/

#include<iostream>
#include<fstream>
#include<ctime>

#include "Swarm.h"                                      /* definition of a swarm */

using namespace std;

#ifdef PORTAL_TELEPORT                                  
                                                        /* defined in portal.cpp */
    extern Real OuterRoE;                               ///< RoE of outer portal                         
    extern Real InnerRoE;                               ///< RoE of inner portal 
    extern Real InitialOuterRoE;                        ///< Initial RoE of outer portal  
    extern Real InitialInnerRoE;                        ///< Initial RoE of inner portal  
    extern Real OuterRoEIncreaseFactor;                 ///< Rate of increase of outer RoE  
    extern Real InnerRoEDecreaseFactor;                 ///< Rate of decrease of inner RoE  
    extern int TeleportTypeChangeInterval;              ///< Rate of conversion of particles from outer portal to inner portal teleportation  
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
    
    srand((unsigned int)time(NULL));                    /* initialize seed so that we get different results every time */
    
    switch(argc)                                        /* if the parameters have been entered */
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
                    S->Move();                          /* every particle moves once */
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
                                                            
    cout<<"\n\nAverage Fitness = "<<avg/executions;     /* display result */
    
    cin.get();
    
    return 0;
}
