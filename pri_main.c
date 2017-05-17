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
	if (strcmp(p, "help") == 0) return 1;
	if (strcmp(p, "exit") == 0) return 2;
	if (strcmp(p, "clear") == 0) return 3;
	if (strcmp(p, "type") == 0) return 4;
	if (strcmp(p, "print") == 0) return 5;
	if (strcmp(p, "syntax") == 0) return 6;
	return 0;
}

int getInt1(char *p)
{
	if (strcmp(p, "q921") == 0) return 1;
	if (strcmp(p, "q931") == 0) return 2;
	return 0;
}

int getInt2(char *p)
{
	if (strcmp(p, "-s") == 0) return 1;
	if (strcmp(p, "no") == 0) return 2;
	return 0;
}

int getInt3(char *p)
{
	return 0;
}

int getInt4(char *p)
{
	if (strcmp(p, "-o") == 0) return 1;
	return 0;
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
	int c1_flag, c2_flag, c3_flag, c4_flag, c5_flag;

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
				c4_flag = 0;
				c5_flag = 0;
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
							case 1:
								if (count == 1) {
help:								printf("Usage :\n");
									printf("	help  : get help message\n");
									printf("	exit  : exit this program\n");
									printf("	clear : clear the screen\n");
									printf("	type <q921|q931> [-s]\n");
									printf("	syntax <q931>\n");
									// uuid_t uu;
									// char str_uuid[100000][36];
									// for (i = 0; i < 100000; i++) {
        							// 	uuid_generate(uu);
									// 	uuid_unparse(uu, str_uuid[i]);
									// 	printf("	%s\n", str_uuid[i]);
									// }
									// int j = 0;
									// for (i = 0; i < 100000; i++) {
									// 	for (j = i+1; j < 100000; j++) {
									// 		if (strcmp(str_uuid[i], str_uuid[j]) == 0)
									// 			printf("same\n");
									// 	}
									// }
								} else {
									printf("Error Commond, No More Parameter\n");
								}
								break;
							case 2:
								if (count == 1) {
									return 0;
								} else {
									printf("Error Commond, No More Parameter\n");
								}
								break;
							case 3:
								if (count == 1) {
									system("clear");
								} else {
									printf("Error Commond, No More Parameter\n");
								}
								break;
							case 4:
								if ((count < 2) || (count > 3)) {
									printf("Usage : type <q921|q931> [-s]\n");
								} else {
									c1_flag = 1;
									goto c2;
								}
								break;
							case 6:
								if ((count < 2) || (count > 5)) {
									printf("Usage : syntax <q931>\n");
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
							case 14:
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
							case 24:
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
							case 26:
								if (count == 2) {
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
													syntax_q931_list(tq);
													printf("%s %s\n", ttime, tq);
												}
											}
										}
									}
									fclose(fp);
								} else if (count > 2){
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
							case 114:
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
							case 124:
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
							case 226:
								if (count == 4) {
									printf("syntax q931 no %s\n", opts[3]);
									char tmp[100];
									sprintf(tmp, "%s", opts[3]);
									fp = fopen(argv[1], "a+");
									if (fp != NULL) {
										while(!feof(fp))
										{
											fp_get_str(c, fp);
											if(strcmp(c, "\0") != 0) {
												fp_get_time(ttime, c);
												fp_get_q931(tq, c);
												if (strcmp(tq, "\0") != 0) {
													sprintf(c, "%d", syntax_q931_list_no(tq));
													if (strcmp(c, tmp) == 0) {
														printf("No: %s ", tmp);
														printf("%s %s\n", ttime, tq);
													}
												}
											}
										}
									}
									fclose(fp);
								} else if (count == 3) {
									printf("need a number\n");
								} else if (count == 5) {
									c4_flag = 1;
									goto c5;
								}
								break;
							default:
								goto help;
								break;
						}
						break;
c4:					case 4:
						if (!c3_flag)
							goto c3;
						break;
c5:					case 5:
						if (!c4_flag)
							goto c4;
						switch(getInt4(opts[4])*10000+getInt3(opts[3])*1000+getInt2(opts[2])*100+getInt1(opts[1])*10+getInt(opts[0])) {
							case 10226:
								printf("syntax q931 no %s -s\n", opts[3]);
								break;
							default:
								goto help;
								break;
						}
						break;
					case 6:
						if (!c5_flag)
							goto c5;
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
