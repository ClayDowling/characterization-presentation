#include "mock_time.h"

int clock_gettime_return_size = 0;
int clock_gettime_idx = 0;
struct timespec** clock_gettime_returns;

void clock_gettime_will_return(int size, struct timespec** returns)
{
    clock_gettime_idx = 0;
    clock_gettime_returns = returns;
    clock_gettime_return_size = size;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    if (clock_gettime_idx < clock_gettime_return_size) {
        struct timespec *thistime = &clock_gettime_returns[clock_gettime_idx++];
        tp->tv_sec = thistime->tv_sec;
        tp->tv_nsec = thistime->tv_nsec;
        return 0;
    }
    return 1;
}
