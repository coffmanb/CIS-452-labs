#include <stdio.h>
#include <unistd.h>

int main()
{
   long ticksPerSec = sysconf(_SC_CLK_TCK);
   
   printf("Clock resolution: %f milliseconds\n", 1000.0/ticksPerSec);

}