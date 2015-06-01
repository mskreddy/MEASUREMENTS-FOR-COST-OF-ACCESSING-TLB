/*******************************************************************/
/*******************************************************************/
/*Filename 	:  tlb.c                                           */
/*Description	:  This program determines the cost of accessing   */
/*                 a TLB.                                          */
/*Method Used   :  To determine the accuracy in the cost we used   */
/*                 three timers                                    */
/*                 rdtsc()- Read time stamp counter(CPU clock cyls)*/
/*                 clock_gettime()- retrieves the time.            */
/*                 gettimeofday() -                                */ 
/*Input         :  Number of trials, Number of pages               */
/*Output	:  Returns cost of accessing a TLB.                */
/*Note:         :                                                  */
/*Refernces	: https://www.cs.rutgers.edu/~pxk/416/notes/       */ 
/*                c-tutorials/gettime.html                         */
/*                http://www.cs.loyola.edu/~jglenn/702/S2008/      */  
/*                Projects/P3/time.html                            */
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*******************************************************************/
/*******************************************************************/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <linux/sched.h>
#include <stdlib.h>
#include <stddef.h>
#include <sched.h>
#include "rdtsc.h"
#include <math.h>
#define BILLION 1000000000L   /*for conversion to nanosecs*/
#include <stdint.h>	/* for uint64 definition */


int main (int argc, char **argv)
 {    	
 
/*******set the CPU affinity , so that this process runs only on one core*****/
            cpu_set_t  mask;
            CPU_ZERO(&mask);
            CPU_SET(0, &mask);		
            sched_setaffinity(0, sizeof(mask), &mask);	  
/********end of set affinity code*******/

/********Initialization of variable*******/
long jump;
struct timespec ovr_start, ovr_end; //variables for calculation of loop overhead*/
struct timespec tlb_start,tlb_end;  //variables for cost calculation of TLB
struct timeval start, end;          //variables for cost calc using gettimeofday
k2struct timeval start_tlb, end_tlb;
 
/***Check whether the correct number of arguments are inputted***/

if(argc==3)
{
int MAX_NUM_TRIALS = atoi(argv[2]);
int NUMPAGES = atoi(argv[1]);
int PAGESIZE = 4096;
unsigned long long a,b,y,z;
double diff,diff_clock,diff_get,diff_rdtsc = 0.0;
double avg,avg_clock,avg_get,avg_getavg,avg_rdtsc = 0.0;
volatile int i,j,k,l,m,n;                                    //Volatile keyword is to avoid optimization for main loop
double ovr_clock,ovr_get,ovr_getavg,ovr_rdtsc=0.0;
int c[NUMPAGES*PAGESIZE/sizeof(int)];
int d[NUMPAGES*PAGESIZE/sizeof(int)];
int e[NUMPAGES*PAGESIZE/sizeof(int)];
jump = PAGESIZE/sizeof(int);

/** Loop overhead Calculation Clock_gettime() **/

      clock_gettime(CLOCK_MONOTONIC, &ovr_start);  //Start of timer
      for (i=0; i < MAX_NUM_TRIALS; i ++) 
      {
         for(j=0;j<NUMPAGES;j++)
         {
         }
      }
      clock_gettime(CLOCK_MONOTONIC, &ovr_end);   //End timer
      //Calculate the total elapsed time
      diff = BILLION * (ovr_end.tv_sec - ovr_start.tv_sec) + ovr_end.tv_nsec - ovr_start.tv_nsec;
      
      //Calculate the average time for loop overhead   
      ovr_clock=diff/(MAX_NUM_TRIALS*NUMPAGES);
        
/** Loop overhead Calculation Clock_get time end **/

/***Inorder to prevent optimization of main loop, we just increment the loop variable by 1,*****/
/***so that compiler ignores this loop to be optimized as it thinks that the variable will be used further****/
i+=1;

/***reinitialization of temporary variable***/	
diff=0.0;

/** Loop overhead Calculation using gettimeday() **/
    
    gettimeofday(&start,NULL);    //Start of timer
    for (i=0; i < MAX_NUM_TRIALS; i ++) 
      {
         for(j=0;j<NUMPAGES;j++)
         {
         }
      }
    gettimeofday(&end,NULL);    //End of timer
    
//Calculate the total elapsed time
    diff =(end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec);
//Calculate the average time for loop overhead    
    ovr_get=diff/(MAX_NUM_TRIALS*NUMPAGES);
    ovr_getavg=ovr_get*1000;

/** Loop overhead Calculation gettimeday end **/    
/***Inorder to prevent optimization of main loop, we just increment the loop variable by 1,*****/
/***so that compiler ignores this loop to be optimized as it thinks that the variable will be used further****/
i+=1;

//Reinitialize the temporary variable    
diff=0;

/** Loop overhead Calculation rdtsc() **/
    
    a=rdtsc();   //Start of timer
    for(i=0;i<MAX_NUM_TRIALS;i++)
    {
        for(j=0;j<NUMPAGES;j++)
        {
        }
    }
    b=rdtsc()-a;   //End of timer

/** Calculate the total elapsed time **/
    diff=b/(MAX_NUM_TRIALS*NUMPAGES);
    ovr_rdtsc=diff*0.29411;
    
/** Loop overhead Calculation rdtsc() end **/
/***Inorder to prevent optimization of main loop, we just increment the loop variable by 1,*****/
/***so that compiler ignores this loop to be optimized as it thinks that the variable will be used further****/
i+=1;
    

//MAIN CODE FOR PROJECT//
    
//using clock_gettime
clock_gettime(CLOCK_MONOTONIC, &tlb_start);  //Start the timer
for (j=0 ; j < MAX_NUM_TRIALS ; j++)         //Repeated the page access for number of trials
{
 
      for (i=0; i < NUMPAGES*jump; i += jump) //Access each page and update it using array c
{
        
        c[i] += 1;
        
 }
}
clock_gettime(CLOCK_MONOTONIC, &tlb_end);       //End timer
	
//Calculate the total elapsed time
diff_clock = BILLION * (tlb_end.tv_sec - tlb_start.tv_sec) + tlb_end.tv_nsec - tlb_start.tv_nsec;
//Average the cost of access
avg_clock=diff_clock/(MAX_NUM_TRIALS*NUMPAGES);
    
//Print the number of pages and access time in the required format
printf("<%d> \t \t <%f> \n",NUMPAGES,avg_clock-ovr_clock);
        
//end of this module
/***Inorder to prevent optimization of main loop, we just increment the loop variable by 1,*****/
/***so that compiler ignores this loop to be optimized as it thinks that the variable will be used further****/
j+=1;
    
/**************************Start of code comment to run each timer at a time
//Cost calculation using gettimeday
    
     gettimeofday(&start_tlb,NULL);		//Start timer
    for (j=0 ; j < MAX_NUM_TRIALS ; j++)        //Repeat the access for given number of trials
    {
 
      for (i=0; i < NUMPAGES*jump; i += jump)	//Access each page and update with the array 'd'
      {
        
        d[i] += 1;
        
        }
    }

    gettimeofday(&end_tlb,NULL);		//End timer
    
//Calculate the elapsed time and convert it to nanoseconds
    diff_get =(end_tlb.tv_sec * 1000000 + end_tlb.tv_usec)- (start_tlb.tv_sec * 1000000 + start_tlb.tv_usec);
    
//Average cost of each page access         
avg_get=diff_get/(MAX_NUM_TRIALS*NUMPAGES);
         
avg_getavg=(avg_get*1000);
    
//print in the required format
printf("<%d> \t \t <%f> \n",NUMPAGES,avg_getavg-ovr_getavg);
    
//end gettimeday
//***Inorder to prevent optimization of main loop, we just increment the loop variable by 1,
//***so that compiler ignores this loop to be optimized as it thinks that the variable will be used further
j+=1;
    
   
//Calculation using rdtsc
    
    y=rdtsc();				 //Start timer
    for (j=0 ; j < MAX_NUM_TRIALS ; j++) //Repeat the page access for given number of trials
    {
 
      for (i=0; i < NUMPAGES*jump; i += jump)  //access the page and update the page using array 'e' 
      {
        
        e[i] += 1;
        
        }
    }
    z=rdtsc()-y;   				//End timer
//Calculate the total elapsed time
    diff_rdtsc=z/(MAX_NUM_TRIALS*NUMPAGES);
//Average cost of access the page and convert clock cyles to ns using processor speed 
    avg_rdtsc=diff_rdtsc*0.29411;
//print the output in required format    
printf("<%d> \t \t <%f> \n",NUMPAGES,avg_rdtsc-ovr_rdtsc); 
    
//end rdtsc
//***Inorder to prevent optimization of main loop, we just increment the loop variable by 1,
//***so that compiler ignores this loop to be optimized as it thinks that the variable will be used further
j+=1;

end of code comment*********************/
}
else
{
printf("Incorrect number of arguments, please give 2 inputs\n");
}
}
    
