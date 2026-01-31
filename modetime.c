#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
time_t now;
time(&now);
printf("Current System Time: %s", ctime(&now));
long long sum = 0;
for (long long i = 0; i < 500000000; i++)
{
sum += i;
}
printf("Dummy computation result: %lld\n", sum);
FILE *fp = fopen("/proc/self/stat", "r");
if (fp == NULL) {
perror("Error opening /proc/self/stat");
return 1;
}
int i;
char buffer[4096];
long utime_ticks, stime_ticks;
fgets(buffer, sizeof(buffer), fp);
fclose(fp);
char *token = strtok(buffer, " ");
for (i = 1; i <= 15; i++)
{
if (i == 14) utime_ticks = atol(token);
if (i == 15) stime_ticks = atol(token);
token = strtok(NULL, " ");
}
long ticks_per_sec = sysconf(_SC_CLK_TCK);
double user_time_sec = (double) utime_ticks / ticks_per_sec;
double kernel_time_sec = (double) stime_ticks / ticks_per_sec;
printf("\n=== Process CPU Usage ===\n");
printf("User mode time : %.6f seconds\n", user_time_sec);
printf("Kernel mode time : %.6f seconds\n", kernel_time_sec);
return 0;
}
