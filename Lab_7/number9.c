/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number9.c

Question 9 in Lab 7
******************************************/
#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim;

    getrlimit(RLIMIT_OFILE, &rlim);
    printf("Limit open files hard limit: %lu files\n", rlim.rlim_max);

}