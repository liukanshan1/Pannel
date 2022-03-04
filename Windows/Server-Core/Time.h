#ifndef TIME_H
#define TIME_H
class Time
{
public:
    Time();
    Time(bool loacl);
    //���¶�̬��Ϣ
    void updateTime();
    //������Ϣ
    int getDate();
    int getMon();
    int getYear();
    int getDay();
    int getSec();
    int getMin();
    int getHour();
    int getTimeZone();
private:
    //��̬��Ϣ
    int date;  // һ���еĵڼ��죬��Χ�� 1 �� 31
    int mon;   // �£���Χ�� 0 �� 11
    int year;  // ��
    int day;  // һ���еĵڼ��죬��Χ�� 0 �� 6��������������
    int sec;   // �룬������Χ�� 0 �� 59���������� 61
    int min;   // �֣���Χ�� 0 �� 59
    int hour;  // Сʱ����Χ�� 0 �� 23
    int timeZone; //ʱ��
};
#endif