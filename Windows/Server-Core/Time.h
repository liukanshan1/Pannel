#ifndef TIME_H
#define TIME_H
class Time
{
public:
    Time();
    Time(bool local);
    //更新动态信息
    void updateTime();
    //返回信息
    int getDate();
    int getMon();
    int getYear();
    int getDay();
    int getSec();
    int getMin();
    int getHour();
    int getTimeZone();
private:
    //动态信息
    int date;  // 一月中的第几天，范围从 1 到 31
    int mon;   // 月，范围从 0 到 11
    int year;  // 年
    int day;  // 一周中的第几天，范围从 0 到 6，从星期日算起
    int sec;   // 秒，正常范围从 0 到 59，但允许至 61
    int min;   // 分，范围从 0 到 59
    int hour;  // 小时，范围从 0 到 23
    int timeZone; //时区
};
#endif