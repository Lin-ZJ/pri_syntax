#include "pri_func.h"

int convert(char a)
{
    if (a >= '0' && a <= '9') {
        return a - '0';
    } else if (a >= 'A' && a <= 'F') {
        return a - 'A' + 10;
    } else if (a >= 'a' && a <= 'f') {
        return a - 'a' + 10;
    } else {
        return -1;
    }
}

int modify_log(char *path, char *modify_path)
{
	FILE *fp;
	struct timeval now;
	struct tm *timenow;

	gettimeofday(&now, NULL);
	timenow = localtime(&now.tv_sec);

	fp = fopen(path, "a+");

	if (fp == NULL) return -1;
	if (feof(fp)) {
		if (!fseek(fp, -1, SEEK_END)) {
			if (fgetc(fp) != '\n') {
					fprintf(fp, "\n");
			}
			if(fseek(fp, 0, SEEK_END)) return -2;
		} else return -1;
	}
    fprintf(fp, "# [%d.%d.%d-%d:%d:%d-%ld] modify [%s] BY Loading\n", (1900+timenow->tm_year), (1+timenow->tm_mon), timenow->tm_mday, timenow->tm_hour, timenow->tm_min, timenow->tm_sec, now.tv_usec, modify_path);

	return 0;
}

void uuid_log(FILE *fp,char* str)
{
    char c[200] = {0};
    char ttime[100] = {0};
    char ttim[100] = {0};
    char tq[100] = {0};
    memset(c, 0, 200);
    memset(ttime, 0, 100);
    memset(ttim, 0, 100);
    memset(tq, 0, 100);
    if (fp != NULL) {
        while(!feof(fp))
        {
            fp_get_str(c, fp);
            if(strcmp(c, "\0") != 0) {
                fp_get_time_easy(ttime, c);
                fp_get_time(ttim, c);
                if (strcmp(ttime, str) == 0) {
                    fp_get(tq, c);
                    if (bool_q931_q921(tq) == 0) {
                        printf("%s %s\n", ttim, tq);
                        syntax_q921(tq);
                    } else if (bool_q931_q921(tq) == 1) {
                        printf("%s %s\n", ttim, tq);
                        syntax_q931(tq);
                    }
                }
            }
        }
    }
    fclose(fp);
}
