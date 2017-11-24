#include "timing/Quartz.h"
#include <stdint.h>

#if IOS
#include <mach/mach_time.h>

#elif __ANDROID__
#include <time.h>

#else

#include <windows.h>

#endif

namespace timing {
  Quartz::Quartz(void) {
    t = 0.0;
    currentTime = time();
    accumulator = 0.0;
    current.x = 100;
    current.v = 0;
    previous = current;
  }

  Quartz::~Quartz(void) {
  }

  float Quartz::update(void) {
    const float newTime = time();
    float deltaTime = newTime - currentTime;
    currentTime = newTime;
    return deltaTime;

    //State state = interpolate(previous, current, accumulator/dt);
  }

  float Quartz::time() {
#if IOS
    static bool started = false;
    static double conversion;
    if (!started) {
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        conversion = info.numer / (1e9 * info.denom);
        started = true;
    }
    return mach_absolute_time() * conversion;

#elif __ANDROID__
    static uint64_t start_time = 0;
    timespec info;
    if (start_time == 0) {
      clock_gettime(CLOCK_REALTIME, &info);
      start_time = (info.tv_sec * 1e9) + info.tv_nsec;
    }

    clock_gettime(CLOCK_REALTIME, &info);
    if ((info.tv_nsec - start_time) < 0) {
    start_time = start_time;
    }
    return ((info.tv_sec * 1e9) - start_time + info.tv_nsec) / 1e9;

#else
    static uint64_t start = 0;
    static uint64_t frequency = 0;

    if (start == 0) {
      QueryPerformanceCounter((LARGE_INTEGER *) &start);
      QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
      return 0.0f;
    }

    int64_t counter = 0;
    QueryPerformanceCounter((LARGE_INTEGER *) &counter);
    return (float) ((counter - start) / double(frequency));
#endif

  }
}