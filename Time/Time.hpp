#ifndef TIME
#define TIME

#include <time.h>
#include <string>

time_t GetCurrentTimeStamp();

/* dateTime格式如: %d-%d-%d %d:%d:%d */
time_t TimeStrToTimeStamp(const std::string& dateTime);

void TimeStampToTimeStr(time_t timeStamp, std::string& ret_dateTime);

#endif // TIME