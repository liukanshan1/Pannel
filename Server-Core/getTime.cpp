#include <cstdio>
#include <ctime>
#include "getTime.h"
getTime::getTime()
{
    date = -1; 
    mon = -1;  
    year = -1; 
    day = -1;  
    sec = -1;  
    min = -1;  
    hour = -1;
    timeZone = 0;
    updateTime();
}
void getTime::updateTime()
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
int getTime::getDate()
{
    return date;
}
int getTime::getMon()
{
    return mon;
}
int getTime::getYear()
{
    return year;
}
int getTime::getDay()
{
    return day;
}
int getTime::getSec()
{
    return sec;
}
int getTime::getMin()
{
    return min;
}
int getTime::getHour()
{
    return hour;
}
int getTime::getTimeZone()
{
    return timeZone;
}