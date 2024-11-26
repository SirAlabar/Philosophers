
#include "../include/philosophers.h"

long long time_diff(long long past, long long present)
{
    return (present - past);
}

void precise_slepp(long long time)
{
    long long start;
    long long elapsed;

    start = get_time();
    while(1)
    {
        elapsed = time_diff(start, get_time());
        if(elapsed >= time)
            break;
        usleep(100);
    }
}
