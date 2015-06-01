										ReadMe.txt
									=============================	
Project Name 
=======================
Operating System Project2 - Cost Measurements of TLB

Team Members
=======================
Sai Kiran Reddy Malikireddy
Kiranmayi Karri

Overview
=======================
In this project, we implemented functionality for measuring the costs taken by TLB access. This functionality has been tested on 4 systems with different architectures.
For any further details , please refer to "OS_Project2_Report.pdf"

Note: rdtsc.h file should be included in the folder from which the below codes are going to be executed. rdtsc.h is available in zip file.
 
To compile the codes 
=======================
use makefile (we have used gcc compiler)
'make' command

To execute the codes 
=======================
tlb.c 
-------------------------------------------------------------------
./tlb arg1 arg2

Note: For our analysis and understanding, we have conducted various experiments using different timers, which have been coded in tlb.c, whenever the cost is calculated with the use of one timer, the logic using the other two timers have been commented.

where arg1 is 'number of pages' and arg2- 'number of trials' (this can range from 10000 to 10000000)

run.c - to run tlb.c using system() command
------------------------------------------------------------------------------------------------
./run

The System Prompts to Enter the Number of Trials we want to test the Code in the following format

Now Press Enter. The Resulting <Num of Pages> and <Access Times> are displayed.