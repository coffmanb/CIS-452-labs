/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number11.c

Question 11 in Lab 7
******************************************/
#include <stdio.h>
#include <unistd.h>

int main()
{
   long ticksPerSec = sysconf(_SC_CLK_TCK);
   
   printf("Clock resolution: %f milliseconds\n", 1000.0/ticksPerSec);

}