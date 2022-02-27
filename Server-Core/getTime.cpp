#include <cstdio>
#include <ctime>
#include "getTime.h"
Time::Time()
{
    updateTime();
}
void Time::updateTime()
{
    time_t t = time(NULL);
    struct tm local;
    struct tm utc;
    localtime_s(&local ,&t);
    gmtime_s(&utc, &t);
    date = local.tm_mday;
    mon = local.tm_mon;
    year = local.tm_year+ 1900;
    day = local.tm_wday;
    sec = local.tm_sec;
    min = local.tm_min;
    hour = local.tm_hour;
    timeZone = local.tm_hour - utc.tm_hour;
}
int Time::getDate()
{
    return date;
}
int Time::getMon()
{
    return mon;
}
int Time::getYear()
{
    return year;
}
int Time::getDay()
{
    return day;
}
int Time::getSec()
{
    return sec;
}
int Time::getMin()
{
    return min;
}
int Time::getHour()
{
    return hour;
}
int Time::getTimeZone()
{
    return timeZone;
}