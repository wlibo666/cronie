#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LOGFILE_PREFIX "/var/log/crond"

int cron_log(char *content) {
    static char filename[64];
    static char date[32];
    time_t t;
    struct tm * lt;
    FILE *fp;

    memset(filename, 0, sizeof(filename));
    memset(date, 0, sizeof(date));
    time (&t);
    lt = localtime(&t);
    snprintf(date, sizeof(date)-1, "%04d-%02d-%02d %02d:%02d:%02d", lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    snprintf(filename, sizeof(filename)-1, "%s.%04d%02d%02d", LOGFILE_PREFIX, lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday);

    fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("fopen file:%s failed", filename);
        return -1;
    }
    fputs(date, fp);
    fputs(" | ", fp);
    fputs(content, fp);
    fputs("\n", fp);

    fclose(fp);
    return 0;
}
