/*******************************************************************/
/*******************************************************************/
/*Filename 	:  run.c                                           */
/*Description	:  This program executes the tlb.c code using      */
/*                 system() command.                               */
/*Input         :  Number of trials                                */
/*Output	:  Returns cost of accessing a TLB.                */
/*Note:         :                                                  */
/*Refernces	: https://www.cs.rutgers.edu/~pxk/416/notes/       */ 
/*                c-tutorials/gettime.html                         */
/*                http://linux.die.net/man/3/system                */
/*                http://www.mcs.anl.gov/~kazutomo/rdtsc.h         */ 
/*******************************************************************/
/*******************************************************************/

#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

void main()
{
	/*****Initialization of variables********/
	int i,j;
	int MAX_NUM_TRIALS;
        int result1;

/*******set the CPU affinity , so that this process runs only on one core*****/
cpu_set_t  mask;
CPU_ZERO(&mask);
CPU_SET(0, &mask);		
result1 = sched_setaffinity(0, sizeof(mask), &mask);	  
/********end of set affinity code*******/

/*********Retrieve the input from command line*******/
printf("Enter the Maximum Number of Trials=");
scanf("%d",&MAX_NUM_TRIALS);
printf("Number of Pages \t Access time in ns \n");

/******** Repeat the loop for factors of two per iteration**********/
	for(i=0;i<14;i++)
	{
			j=(int)pow(2,i);
			char str[20];
			char str1[20];
			char str2[20];
			strcpy(str,"./tlb ");
			sprintf(str1,"%d",j);
			strcat(str,str1);
			strcat(str," ");
			sprintf(str2,"%d",MAX_NUM_TRIALS);
			strcat(str,str2);
    
			//commands which can be used to refresh caches
				system("echo 1 >/proc/sys/vm/drop_caches");
				system("echo 2 >/proc/sys/vm/drop_caches");
				system("echo 3 >/proc/sys/vm/drop_caches"); 
			
		/********command to execute the tlb.c*******/
			system(str);
	}


}


