/* Mocks for time related functions
 */

#ifndef _MOCK_TIME_H_
#define _MOCK_TIME_H_

#include <time.h>

void clock_gettime_will_return(int, struct timespec**);

#endif
