#include "pri_main.h"
int l;

char *stdin_get_str(char *str)
{
	fgets(str,U_MAX,stdin);
	if(str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';
	return str;
}

char *fp_get_str(char *str, FILE *fp)
{
	fgets(str,U_MAX,fp);
	if(str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';
	return str;
}

char *fp_get_time(char *ttime, char *str)
{
	int len;
	int i;

	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] != ']') {
			ttime[i] = str[i];
		} else {
			ttime[i] = str[i];
			ttime[i+1] = '\0';
			return ttime;
		}
	}
	return NULL;
}

char *fp_get_time_easy(char *ttime, char *str)
{
	int len;
	int i;
	int j = 0;

	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] == 'Y') {
			ttime[j] = str[i+2];
		}
	}
	return NULL;
}

char *fp_get_q921(char *tq921, char *str)
{
	int len;
	int i,j = 0;
	int count = 0;

	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] == '[') {
			count++;
		}
		if(count == 2) {
			if ((str[i] != ']') && (j < 13)) {
				tq921[j] = str[i];
				j++;
			} else {
				if (j >= 12) {
					tq921[j] = ' ';
					tq921[++j] = ']';
					tq921[++j] = '\0';
				} else {
					tq921[j] = str[i];
					tq921[++j] = '\0';
				}
				return tq921;
			}
		}
	}
	return NULL;
}

char *fp_get_q931(char *tq931, char *str)
{
	int len;
	int i,j = 0;
	int count = 0;

	len = strlen(str);
	for (i = 0; i < len; i++) {
		if (str[i] == '[') {
			count++;
		}
		if(count == 2) {
			if (str[i] != ']') {
				tq931[j] = str[i];
				j++;
			} else {
				if (j > 14) {
					tq931[j] = str[i];
					tq931[++j] = '\0';
				} else {
					tq931[0] = '\0';
				}
				return tq931;
			}
		}
	}
	return NULL;
}

int getInt(char *p)
{
	if (strcmp(p, "help") == 0) return 0;
	if (strcmp(p, "exit") == 0) return 1;
	if (strcmp(p, "clear") == 0) return 2;
	if (strcmp(p, "type") == 0) return 3;
	if (strcmp(p, "print") == 0) return 4;
	return -1;
}

int getInt1(char *p)
{
	if (strcmp(p, "q921") == 0) return 0;
	if (strcmp(p, "q931") == 0) return 1;
	return -1;
}

int getInt2(char *p)
{
	if (strcmp(p, "-s") == 0) return 0;
	return -1;
}

int main(int argc, char **argv)
{
	FILE *fp;
	int i = 0;
	int len = 0;
	int count = 0;
	char str[4];
	char c[200] = {0};
	char ttime[100] = {0};
	char tq[100] = {0};
	char *words = NULL;
	char *opts[100];
	int c1_flag, c2_flag, c3_flag;

	if (argc < 2) {
		printf("Usage : ");
		printf("%s <Your Path (txt)>\n", argv[0]);
	} else if (argc > 2) {
		printf("Usage : ");
		printf("%s <Your Path (txt)>\n", argv[0]);
		printf("No more parameters needed\n");
	} else {
		len = strlen(argv[1]);
		for (i = len-4; i <= len; i++) {
			str[i-len+4] = argv[1][i];
		}
		if (strcmp(str, ".txt")) {
			printf("Usage : ");
			printf("%s <Your Path (txt)>\n", argv[0]);
			printf("Must be a text file\n");
		} else {
			fp = fopen(argv[1], "a+");
			if (fp != NULL) {
				if (modify_log(log_path, argv[1]) != 0) return 0;
			} else return 0;
			fclose(fp);
			while(1)
			{
				c1_flag = 0;
				c2_flag = 0;
				c3_flag = 0;
				memset(c, 0, 200);
				memset(ttime, 0, 100);
				memset(tq, 0, 100);
				memset(opts, 0, 100);

				printf("CLI > ");
				stdin_get_str(c);

				words = strtok(c, " ");
				while(words != NULL)
				{
					opts[count] = words;
					count++;
					words = strtok(NULL, " ");
				}
				/*for (i = 0; i < count; i++) {
					printf("%s\n", opts[i]);
				}*/
				switch(count) {
					case 0:
						break;
c1:					case 1:
						switch(getInt(opts[0])) {
							case 0:
								if (count == 1) {
help:								printf("Usage :\n");
									printf("	help  : get help message\n");
									printf("	exit  : exit this program\n");
									printf("	clear : clear the screen\n");
									printf("	type <q921|q931> [-s]\n");
								} else {
									printf("Error Commond, No More Parameter\n");
								}
								break;
							case 1:
								if (count == 1) {
									return 0;
								} else {
									printf("Error Commond, No More Parameter\n");
								}
								break;
							case 2:
								if (count == 1) {
									system("clear");
								} else {
									printf("Error Commond, No More Parameter\n");
								}
								break;
							case 3:
								if ((count < 2) || (count > 3)) {
									printf("Usage : type <q921|q931> [-s]\n");
								} else {
									c1_flag = 1;
									goto c2;
								}
								break;
							default:
                                goto help;
								break;
						}
						break;
c2:					case 2:
						if (!c1_flag)
							goto c1;
						switch(getInt1(opts[1])*10+getInt(opts[0])) {
							case 3:
								if (count == 2) {
									printf("Type is q921\n");
									fp = fopen(argv[1], "a+");
									if (fp != NULL) {
										while(!feof(fp))
										{
											fp_get_str(c, fp);
											if(strcmp(c, "\0") != 0) {
												fp_get_time(ttime, c);
												fp_get_q921(tq, c);
												if (strcmp(tq, "\0") != 0)
													printf("%s %s\n", ttime, tq);
											}
										}
									}
									fclose(fp);
								} else if (count == 3) {
									c2_flag = 1;
									goto c3;
								}
								break;
							case 13:
								if (count == 2) {
									printf("type is q931\n");
									fp = fopen(argv[1], "a+");
									if (fp != NULL)	{
										while(!feof(fp))
										{
											fp_get_str(c, fp);
											if(strcmp(c, "\0") != 0) {
												fp_get_time(ttime, c);
												fp_get_q931(tq, c);
												if (strcmp(tq, "\0") != 0)
													printf("%s %s\n", ttime, tq);
											}
										}
									}
									fclose(fp);
								} else if (count == 3) {
									c2_flag = 1;
									goto c3;
								}
								break;
							default:
								goto help;
								break;
						}
						break;
c3:					case 3:
						if (!c2_flag)
							goto c2;
						switch(getInt2(opts[2])*100+getInt1(opts[1])*10+getInt(opts[0])) {
							case 3:
								printf("syntax q921\n");
								fp = fopen(argv[1], "a+");
								if (fp != NULL) {
									while(!feof(fp))
									{
										fp_get_str(c, fp);
										if(strcmp(c, "\0") != 0) {
											fp_get_time(ttime, c);
											fp_get_q921(tq, c);
											if (strcmp(tq, "\0") != 0) {
												printf("%s %s\n", ttime, tq);
                                                syntax_q921(tq);
                                            }
										}
									}
								}
								fclose(fp);
                                break;
							case 13:
								printf("syntax q931\n");
								fp = fopen(argv[1], "a+");
								if (fp != NULL) {
									while(!feof(fp))
									{
										fp_get_str(c, fp);
										if(strcmp(c, "\0") != 0) {
											fp_get_time(ttime, c);
											fp_get_q931(tq, c);
											if (strcmp(tq, "\0") != 0) {
												printf("%s %s\n", ttime, tq);
                                                syntax_q931(tq);
                                            }
										}
									}
								}
								fclose(fp);
								break;
							default:
								break;
						}
						break;
					case 4:
						if (!c3_flag)
							goto c3;
						break;
					default:
						goto help;
						break;
				}
				count = 0;
			}
		}
	}

	return 0;
}
