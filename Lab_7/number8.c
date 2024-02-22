#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim;

    getrlimit(RLIMIT_FSIZE, &rlim);
    printf("Limit: %lu bytes\n", rlim.rlim_max);

}