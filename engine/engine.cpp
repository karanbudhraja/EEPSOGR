/** \mainpage Summary
 *
 * This code is the implementation of the basic model 
 * of PSO. It is and edited version of an earlier 
 * implementation written by Ashutosh Singh (code 
 * available at http://code.google.com/p/psoengine/)
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
 * Basic model of PSO                                  *
 *******************************************************/

#include<iostream>

#define _USE_MATH_DEFINES                               ///< For M_PI
#include<cmath>
#include<ctime>
#include<cstdlib>
                                                        /* Enumerate functions */
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

typedef long double  Real ;                             ///< Define a real number

const Real Vmax=((UpperLimit-LowerLimit)*1);            ///< Maximum velocity for particle update

using namespace std;

class Particle                                          /** \brief Definition of a particle */
{                                       
    private:
        Real X[Dimension];                              ///< Position of particle 
        Real V[Dimension];                              ///< Velocity of particle 
        Real PBest[Dimension];                          ///< Location of personal best solution 
        
        Real Fitness;                                   ///< Fitness value at current position 
        Real BestFitness;                               ///< Fitness value at personal best soluton 

    public:
        void Initialize();                              ///< Brief : Initialize the particle
        void Evaluate();                                ///< Brief : Evaluate particle fitness
        void Update(Particle GBest);                    ///< Brief : Move particle once

        Real GetFitness();                              ///< Brief : Get position of particle
        Real GetBestFitness();                          ///< Brief : Get fitness value at personal best solution
};

class Swarm                                             /** \brief Definition of a swarm */
{
    public:
        Particle Birds[SwarmSize];                      ///< Brief : Swarm of birds 
        int Best;                                       ///< Brief : Index of global best solution 

        Swarm();                                        ///< Brief : Constructor to initialize swarm 
        void Move();                                    ///< Brief : Each particle makes one move 
        void GetGBestIndex();                           ///< Brief : Read index of global best solution 
};

/**
 *******************************************************
 * Detail   : Perform several iterations of pso                    
 *                                                      
 * Input    : None    
 *                                                      
 * Output   : 0 (always)                                         
 *******************************************************
*/
int main()                                              /** \brief Brief : Main function */
{
    const int a=10;
    Real avg=0;

    srand((unsigned int)time(NULL));

    for(int x=0;x<a;x++)
    {
            Swarm *S=new Swarm;

            for(int i = 0; i < 1000; i++)
            {
                    S->Move();                          /* every particle moves once */
            }

            cout<<"\n\nRun  :  "<<x+1<<" \t\tFitness : "
                <<S->Birds[S->Best].GetFitness();

            avg+=S->Birds[S->Best].GetFitness();    
            delete(S);
    }
    
    cout<<"\n\nAverage Fitness = "<<avg/a;
    
    cin.get();
    
    return 0;
}

/**
 *******************************************************
 * Detail   : Move each particle in swarm once                     
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
void Swarm::Move()
{
    GetGBestIndex();                                    /* calculate index of best particle */

    for(int i=0;i<SwarmSize;i++)                        /* each particle moves once */
    {
        Birds[i].Update(Birds[Best]);
    }
}

/**
 *******************************************************
 * Detail   : Initialize swarm particles                           
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
Swarm::Swarm()
{
    Best=0;                                             /* swarm just made. best particle not known */

    for(int i=0;i<SwarmSize;i++)
    {
        Birds[i].Initialize();                          /* evaluate fitness of particle */
    }
}

/**
 *******************************************************
 * Detail   : Get index of particle with best fitness              
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
void Swarm::GetGBestIndex()
{
    Best=0;

    for(int i=1;i<SwarmSize;i++)                        /* compare fitness value of all particles to find best one */
    {
        if(Birds[Best].GetBestFitness()>Birds[i].GetBestFitness())
        {
            Best=i;
        }
    }
}

/**
 *******************************************************
 * Detail   : Initialize personal best fitness value for
 *            particle
 *
 * Input    : Nothing                  
 *                                                      
 * Output   : Nothing                  
 *******************************************************
*/
void Particle::Initialize()
{
    for(int i=0;i<Dimension;i++)
    {
        X[i]=LowerLimit + ((double)rand()/(RAND_MAX + 1))*(UpperLimit-LowerLimit);
        V[i]=     -Vmax + ((double)rand()/(RAND_MAX + 1))*(2*Vmax);
    
        PBest[i]=X[i];
    }

    Evaluate();                                         /* evaluate fitness value for particle */
    BestFitness=Fitness;                                /* particle only has one value of fitness for personal best */
}

/**
 *******************************************************
 * Detail   : Evaluate fitness value at current position                                   
 *                                                      
 * Input    : None           
 *                                                      
 * Output   : Nothing                  
 *                                                      
 *******************************************************
*/
void Particle::Evaluate()
{
    Fitness = 0;                                        /* functions defined here */
    Real Sum = 0, Product = 1;
    Real finalVal = 0;                                  /* final value to be attained */

#if FUNCTION == DE_JONG
    /**************************
    *DeJong 
    ***************************/
    Sum = 0, Product = 1;

    for(int i = 0; i < Dimension; i++)
    {
        Sum += (X[i] * X[i]);
    }

    Fitness = Sum;
    //Real Fitness_DeJong = Sum;
    /**************************/

#elif FUNCTION == GRIEWANK
    /**************************
    *Griewank 
    ***************************/
    Sum = 0, Product = 1;

    for(int i = 0; i < Dimension; i++)
    {
        Sum += ((X[i] * X[i]) / 4000);
        Product *= (cos(X[i]) / sqrt(Real(i+1)));       
    }

    Fitness = Sum - Product + 1;
    //Real Fitness_Griewank = Sum - Product; 
    /**************************/

#elif FUNCTION == RASTRIGIN_F1
    /****************************
    *Rastrigin F1
    *****************************/
    Sum = 0, Product = 1;

    for(int i = 0; i < Dimension; i++)
    {
        Sum += ((X[i] * X[i]) - (10 * cos( 2 * M_PI * X[i] )));
    }

    Fitness = Sum + 10 * Dimension;
    //Real Fitness_RastriginF1 = Sum + 10 * Dimension; 
    /**************************/

#elif FUNCTION == SCHAFFER_F6
    /****************************
    *Schaffer F6
    ****************************/
    Sum = 0, Product = 1;

    for(int i = 0; i < Dimension; i++)
    {
        Sum += (X[i] * X[i]);
    }

    Fitness = .5 + (pow(sin(pow(Sum,0.5)), 2) - .5) / pow((1 + .001 * Sum), 2);
    //Real Fitness_SchafferF6 = .5 + (pow(sin(sqrt(Sum)), 2) - .5) / pow((1 + .001 * Sum), 2);
    /**************************/

#elif FUNCTION == ROSENBROCK
    /***************************
    *RosenBrock
    ****************************/
    Sum = 0, Product = 1;

    for(int i = 0; i < Dimension-1; i++)
    {
        Sum += pow((X[i+1] - pow(X[i], 2)), 2) + pow((1 - X[i]), 2);
    }

    Real Fitness = 100 * Sum;
    //Real Fitness_Rosenbrock = 100 * Sum;
    /**************************/

#endif

#if 0
    Fitness = Fitness_DeJong \                          /* overall tuning */
            + Fitness_Griewank \
            + Fitness_RastriginF1 \
            + Fitness_Rosenbrock \
            + Fitness_SchafferF6;
    
    Fitness = Fitness_DeJong + Fitness_Rosenbrock;      /* unimodal tuning */
    
                                                        /* multimodal tuning */
    Fitness = Fitness_Griewank + Fitness_RastriginF1 + Fitness_SchafferF6;  
    
    Fitness = Fitness_Griewank;                         /* specific tuning */
#endif

    if(Fitness < 0.0)
        Fitness = -Fitness;

    //Fitness=Precision*ceil(Fitness/Precision);        /* TODO: implement precision limit on iterations */

    //if(Fitness < BestFitness)
                                                        /* check for closeness to the final value */
    if(abs(Fitness - finalVal) < abs(BestFitness - finalVal))
    {
        BestFitness = Fitness;
        for(int x = 0; x < Dimension; x++)
        {
            PBest[x] = X[x];                                    
        }   
    }

    //cout<<"\tFitness: "<<Fitness;                     /* display information */
    //cout<<"\n Pos: "<<X[0]<<" "<<X[1]<<" "<<X[2]<<" "<<X[3]<<" "<<X[4]<<" "<<X[5]<<" "<<X[6]<<" "<<X[7]<<" "<<X[8]<<" "<<X[9];
}

/**
 *******************************************************
 * Detail   : Update particle position and global best 
 *            position value if needed                                   
 *                                                      
 * Input    : Particle GBest (Best particle)            
 *                                                      
 * Output   : Nothing                  
 *                                                      
 *******************************************************
*/
void Particle::Update(Particle GBest)
{
    for(int i = 0 ; i < Dimension;i++)
    {
        Real r1,r2;

        r1 = (double)(rand())/(RAND_MAX + 1);           /* generate random numbers */
        r2 = (double)(rand())/(RAND_MAX + 1);
            
        V[i]=Weight*V[i] + C1 * r1 * (PBest[i]-X[i])+ C2*r2 * (GBest.X[i]-X[i]);
        
        if(V[i] < -Vmax)                                /* check added for velocity */
        {
            V[i] = -Vmax;
        }
        if(V[i] > Vmax)
        {
            V[i] = Vmax;
        }
        
        X[i]+=V[i];
    
        if(X[i]>UpperLimit)                             /* correction in code. boundary check on position shifted down here */
        {
            X[i]=UpperLimit-.001;
            V[i]=0;
        }
        if(X[i]<LowerLimit) 
        {
            X[i]=LowerLimit+.001;
            V[i]=0;
        }
    }

    Evaluate();                                         /* correction in code. evaluate shifted outside loop */
}

/**
 *******************************************************
 * Detail   : Get current fitness value of particle                             
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Position of particle                               
 *******************************************************
*/
Real Particle::GetFitness()
{
    return Fitness;
}

/**
 *******************************************************
 * Detail   : Get fitness value at best position 
 *            traversed so far
 *                                                      
 * Input    : Nothing                  
 *                                                      
 * Output   : Current fitness value of particle                  
 *                                                      
 *******************************************************
*/
Real Particle::GetBestFitness()
{
    return BestFitness;
}
