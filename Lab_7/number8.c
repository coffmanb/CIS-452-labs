
/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number8.c

Question 8 in Lab 7
******************************************/
#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim;

    getrlimit(RLIMIT_FSIZE, &rlim);
    printf("Limit: %lu bytes\n", rlim.rlim_max);

}