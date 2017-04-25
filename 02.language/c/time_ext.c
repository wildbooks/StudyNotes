#include <time.h>
#include <stdio.h>
#include <unistd.h>

#if 0
 struct tm {
               int tm_sec;    // Seconds (0-60) 秒
               int tm_min;    // Minutes (0-59) 分
               int tm_hour;   // Hours (0-23)   时
               int tm_mday;   // Day of the month (1-31) 天
               int tm_mon;    // Month (0-11)   月
               int tm_year;   // Year - 1900    年


               int tm_wday;   // Day of the week (0-6, Sunday = 0) 0代表星期日
               int tm_yday;   // Day in the year (0-365, 1 Jan = 0)
               int tm_isdst;  // Daylight saving time
           };
 time_t  <==> long

   相关函数原型：
       char *asctime(const struct tm *tm);
       char *asctime_r(const struct tm *tm, char *buf);

       char *ctime(const time_t *timep);
       char *ctime_r(const time_t *timep, char *buf);

       struct tm *gmtime(const time_t *timep);
       struct tm *gmtime_r(const time_t *timep, struct tm *result);

       struct tm *localtime(const time_t *timep);
       struct tm *localtime_r(const time_t *timep, struct tm *result);

       time_t mktime(struct tm *tm);

       time_t time(time_t *tloc);

       size_t strftime(char *s, size_t max, const char *format,
                       const struct tm *tm);

       char *strptime(const char *s, const char *format, struct tm *tm);//为解决

       double difftime(time_t time1, time_t time0);

#endif

int main(void)
{
  time_t now,end;
  struct tm curtime;
  char buffer[50];
  printf("\t\t获取日历时间\n");
  time(&now);
  printf("time() :\t\t%lds\n",now);

  printf("\n\t\t日历时间=>当地时间\n");
  printf("ctime():\t\t%s",ctime(&now));
  curtime=*localtime(&now);
  printf("localtime():\t\t%s",asctime(&curtime));
  //  日历时间 => 世界标准时间年月时分秒格式(即格林尼治时间)
  printf("\n\t\t日历时间=>格林尼治时间\n");
  curtime=*gmtime(&now);                      //
  printf("gmtime():\t\t%s",asctime(&curtime));

  printf("\n\t\t分解时间=>日历时间\n");
  printf("mktime():\t\t%lds\n",mktime(&curtime));

  printf("\n\t\t自定义时间格式\n");
  strftime(buffer,50,"Now it's %I:%M%p.",&curtime);
  puts(buffer);

  sleep(2);
  time(&end);
  printf("\n\t\t计算时间间隔\n");
  printf("difftime():\t\t%0.1fs\n",difftime(end, now));
  return 0;
}
