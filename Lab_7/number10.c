#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim;

    getrlimit(RLIMIT_OFILE, &rlim);
    printf("Limit open files soft limit: %lu files\n", rlim.rlim_cur);

}