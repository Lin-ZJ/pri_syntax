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

