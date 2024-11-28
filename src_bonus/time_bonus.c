#include "../include/philosophers_bonus.h"

long long time_diff(long long past, long long present)
{
    return (present - past);
}

void precise_sleep(long long time)
{
    long long start;
    long long elapsed;

    start = get_time();
    while(1)
    {
        elapsed = time_diff(start, get_time());
        if(elapsed >= time)
            break;
        usleep(50);
    }
}

long long get_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return (error_msg("gettimeofday() failed"));
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
