#include "pri_q931.h"

void syntax_q931(char *str)
{
	int len = strlen(str);
	len = len/3-1;
	int octet[len];
	int i = 0;
	int bit = 0;
	int statbit = 0;
	_q931 q931;

	for (i = 0; i < len; i++) {
		octet[i] = convert(str[3*(i+1)-1])*16+convert(str[3*(i+1)]);
	}

	switch (octet[2] & _frame_flag) {
		case 0:
		case 2:
			printf("Informational frame:\n");
			break;

		case 1:
			printf("Supervisory frame:\n");
			break;

		case 3:
			printf("Unnumbered frame:\n");
			break;

		default:
			break;
	}

	q931.SAPI = (octet[0] & 0xfc) >> 2;
	q931.C_R = (octet[0] & 0x02) >> 1;
	q931.EA_0 = (octet[0] & 0x01) >> 0;
	q931.TEI = (octet[1] & 0xfe) >> 1;
	q931.EA_1 = (octet[1] & 0x01) >> 0;
	q931.N_S = (octet[2] & 0xfe) >> 1;
	q931.ZERO = (octet[2] & 0x01) >> 0;
	q931.N_R = (octet[3] & 0xfe) >> 1;
	q931.P = (octet[3] & 0x01) >> 0;
	q931.Pr_di = (octet[4] & 0xff) >> 0;
	q931.L_c_ref = (octet[5] & 0x0f) >> 0;
	q931.flag = (octet[6] & 0x80) >> 7;

	printf("SAPI: 0x%x	C/R: %x	EA: %x\n", q931.SAPI, q931.C_R, q931.EA_0);
	printf(" TEI: 0x%x		EA: %x\n", q931.TEI, q931.EA_1);
	printf("N(S): 0x%x	0: %x\n", q931.N_S, q931.ZERO);
	printf("N(R): 0x%x	P: %x\n", q931.N_R, q931.P);
	printf("%ld bytes of data\n", sizeof(octet)/sizeof(int)-4);

	if (q931.Pr_di < 8) {
		printf("Protocol Discriminator: Unknown (%d)\n", q931.Pr_di);
	}
	else if (q931.Pr_di == 8) {
		printf("Protocol Discriminator: Q.931/I.451 (%d)  len=%d\n", q931.Pr_di, len-4);
	}
	else if (q931.Pr_di == 9) {
		printf("Protocol Discriminator: Q.2931 (%d)  len=%d\n", q931.Pr_di, len-4);
	}
	else if ((q931.Pr_di > 15) && (q931.Pr_di < 64)) {
		printf("Protocol Discriminator: X.25 (%d)  len=%d\n", q931.Pr_di, len-4);
	}
	else if ((q931.Pr_di > 63) && (q931.Pr_di  < 80)) {
		printf("Protocol Discriminator: National (%d)\n", q931.Pr_di);
	}
	else if ((q931.Pr_di > 79) && (q931.Pr_di < 255)) {
		printf("Protocol Discriminator: X.25 (%d)  len=%d\n", q931.Pr_di, len-4);
	}

	if (q931.flag == 1) {
		printf("TEI=%d Call Ref: len= %d (Sent to originator)\n", q931.TEI, q931.L_c_ref);
	} else if ((octet[6]&0x80) == 0) {
		printf("TEI=%d Call Ref: len= %d (Sent from originator)\n", q931.TEI, q931.L_c_ref);
	}

	statbit = 6+q931.L_c_ref;
	bit = 6+q931.L_c_ref;
	q931.Mes_Typ = (octet[bit] & 0x7f) >> 0;

	switch (q931.Mes_Typ) {
		case ALERTING:
			printf("Message Type: ALERTING (1)\n");
			bit++;
			break;

		case CALL_PROCEEDING:
			printf("Message Type: CALL PROCEEDING (2)\n");
			bit++;
			break;

		case CONNECT:
			printf("Message Type: CONNECT (7)\n");
			bit++;
			break;

		case CONNECT_ACKNOWLEDGE:
			printf("Message Type: CONNECT ACKNOWLEDGE (15)\n");
			bit++;
			break;

		case PROGRESS:
			printf("Message Type: PROGRESS (3)\n");
			bit++;
			break;
		case SETUP:
			printf("Message Type: SETUP (5)\n");
			bit++;
			break;

		case SETUP_ACKNOWLEDGE:
			printf("Message Type: SETUP ACKNOWLEDGE (13)\n");
			bit++;
			break;
		case RESUME:
			printf("Message Type: RESUME (38)\n");
			bit++;
			break;

		case RESUME_ACKNOWLEDGE:
			printf("Message Type: RESUME ACKNOWLEDGE (46)\n");
			bit++;
			break;
		case RESUME_REJECT:
			printf("Message Type: RESUME REJECT (34)\n");
			bit++;
			break;

		case SUSPEND:
			printf("Message Type: SUSPEND (37)\n");
			bit++;
			break;

		case SUSPEND_ACKNOWLEDGE:
			printf("Message Type: SUSPEND ACKNOWLEDGE (45)\n");
			bit++;
			break;

		case SUSPEND_REJECT:
			printf("Message Type: SUSPEND REJECT (33)\n");
			bit++;
			break;

		case USER_INFORMATION:
			printf("Message Type: USER INFORMATION (32)\n");
			bit++;
			break;

		case DISCONNECT:
			printf("Message Type: DISCONNECT (69)\n");
			bit++;
			break;

		case RELEASE:
			printf("Message Type: RELEASE (77)\n");
			bit++;
			break;

		case RELEASE_COMPLETE:
			printf("Message Type: RELEASE COMPLETE (90)\n");
			bit++;
			break;

		case RESTART:
			printf("Message Type: RESTART (70)\n");
			bit++;
			break;

		case RESTART_ACKNOWLEDGE:
			printf("Message Type: RESTART ACKNOWLEDGE (78)\n");
			bit++;
			break;

		case SEGMENT:
			printf("Message Type: SEGMENT (96)\n");
			bit++;
			break;

		case CONGESTION_CONTROL:
			printf("Message Type: CONGESTION CONTROL (121)\n");
			bit++;
			break;

		case INFORMATION:
			printf("Message Type: INFORMATION (123)\n");
			bit++;
			break;

		case NOTIFY:
			printf("Message Type: NOTIFY (110)\n");
			bit++;
			break;

		case STATUS:
			printf("Message Type: STATUS (125)\n");
			bit++;
			break;

		case STATUS_ENQUIRY:
			printf("Message Type: STATUS ENQUIRY (117)\n");
			bit++;
			break;

		default:
			printf("Message Type: Unknown (%d)\n", q931.Mes_Typ);
			goto out;
			break;
	}

	while (bit < len)
	{
		switch (octet[bit]) {
			case Sen_com:
				printf("\n[ a1 ]\n");
				printf("   |-----> Sending complete (len= 1)\n");
				bit++;
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Rep_ind | 0x80:
			case Rep_ind:
				printf("\n[ 50 ]\n");
				printf("   |-----> Repeat indicator (len= 1)\n");
				bit++;
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Net_spe_fac:
				printf("\n[ 20");
				bit++;
				if (bit < len) {
					if ((bit+octet[bit]) < len) {
						for(i = 0; i <= octet[bit]; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						printf(" ]\n");
						printf("   |-----> Network-specific facilities (len= %d)\n", octet[bit]);
						bit += octet[bit]+1;
					}
					else {
						for(i = 0; i < len-bit; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						bit += len-bit+1;
						printf(" :::::Incomplete Date\n");
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Key_fac:
				printf("\n[ 2c");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Key_fac_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Keypad facility (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Keypad facility is %d\n", Key_fac_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Cag_par_num:
				printf("\n[ 6c");
				bit++;
				if (bit < len) {
					if ((bit+octet[bit]) < len) {
						for(i = 0; i <= octet[bit]; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						printf(" ]\n");
						printf("   |-----> Calling party number (len= %d)\n", octet[bit]);
						bit += octet[bit]+1;
					}
					else {
						for(i = 0; i < len-bit; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						bit += len-bit+1;
						printf(" :::::Incomplete Date\n");
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Cag_par_sub:
				printf("\n[ 6d");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Cag_par_sub_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Calling party subaddress (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Calling party subaddress is %d\n", Cag_par_sub_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Cad_par_num:
				printf("\n[ 70");
				bit++;
				if (bit < len) {
					if ((bit+octet[bit]) < len) {
						for(i = 0; i <= octet[bit]; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						printf(" ]\n");
						printf("   |-----> Called party number (len= %d)\n", octet[bit]);
						bit += octet[bit]+1;
					}
					else {
						for(i = 0; i < len-bit; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						bit += len-bit+1;
						printf(" :::::Incomplete Date\n");
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Cad_par_sub:
				printf("\n[ 71");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Cad_par_sub_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Called party subaddress (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Called party subaddress is %d\n", Cad_par_sub_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Tra_net_sel:
				printf("\n[ 78");
				bit++;
				if (bit < len) {
					if ((bit+octet[bit]) < len) {
						for(i = 0; i <= octet[bit]; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						printf(" ]\n");
						printf("   |-----> Transit network selection (len= %d)\n", octet[bit]);
						bit += octet[bit]+1;
					}
					else {
						for(i = 0; i < len-bit; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						bit += len-bit+1;
						printf(" :::::Incomplete Date\n");
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Dat_tim:
				printf("\n[ 29");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Dat_tim_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Date/time (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Date/time is %d\n", Dat_tim_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
					case CONNECT:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Pro_ind:
				printf("\n[ 1e");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Pro_ind_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Progress indicator (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Progress indicator is %d\n", Pro_ind_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
					case CONNECT:
					case DISCONNECT:
					case ALERTING:
					case CALL_PROCEEDING:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Sig:
				printf("\n[ 34");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Sig_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Signal (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Signal is %d\n", Sig_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case SETUP:
					case CONNECT:
					case DISCONNECT:
					case ALERTING:
					case RELEASE:
					case CONNECT_ACKNOWLEDGE:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Cau:
				printf("\n[ 08");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Cau_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Cause (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Cause is %d\n", Cau_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case DISCONNECT:
					case RELEASE:
					case RELEASE_COMPLETE:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Cha_ide:
				printf("\n[ 18");
				bit++;
				if (bit < len) {
					if ((bit+octet[bit]) < len) {
						for(i = 0; i <= octet[bit]; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						printf(" ]\n");
						printf("   |-----> Channel identification (len= %d)\n", octet[bit]);
						bit += octet[bit]+1;
					}
					else {
						for(i = 0; i < len-bit; i++) {
							if (octet[bit+i] < 16) {
								printf(" 0%x", octet[bit+i]);
							}
							else {
								printf(" %x", octet[bit+i]);
							}
						}
						bit += len-bit+1;
						printf(" :::::Incomplete Date\n");
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case CONNECT:
					case RESTART_ACKNOWLEDGE:
					case ALERTING:
					case CALL_PROCEEDING:
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Dis:
				printf("\n[ 28");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Dis_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Display (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Display is %d\n", Dis_max);
					}
				}
				else {
					printf(" :::::Incomplete Date");
				}
				switch (q931.Mes_Typ) {
					case CONNECT:
					case RELEASE_COMPLETE:
					case RELEASE:
					case DISCONNECT:
					case CONNECT_ACKNOWLEDGE:
					case RESTART_ACKNOWLEDGE:
					case ALERTING:
					case CALL_PROCEEDING:
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Res_ind:
				printf("\n[ 79");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Res_ind_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Restart indicator (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Restart indicator is %d\n", Res_ind_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case RESTART_ACKNOWLEDGE:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Bea_cap:
				printf("\n[ 04");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Bea_cap_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Bearer capability (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Bearer capability is %d\n", Bea_cap_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case CONNECT:
					case ALERTING:
					case CALL_PROCEEDING:
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Low_lay_com:
				printf("\n[ 7c");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Low_lay_com_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> Low layer compatibility (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of Low layer compatibility is %d\n", Low_lay_com_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case CONNECT:
					case SETUP:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			case Hig_lay_com:
				printf("\n[ 7d");
				bit++;
				if (bit < len) {
					if (octet[bit] <= Hig_lay_com_max) {
						if ((bit+octet[bit]) < len) {
							for(i = 0; i <= octet[bit]; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							printf(" ]\n");
							printf("   |-----> High layer compatibility (len= %d)\n", octet[bit]);
							bit += octet[bit]+1;
						}
						else {
							for(i = 0; i < len-bit; i++) {
								if (octet[bit+i] < 16) {
									printf(" 0%x", octet[bit+i]);
								}
								else {
									printf(" %x", octet[bit+i]);
								}
							}
							bit += len-bit+1;
							printf(" :::::Incomplete Date\n");
						}
					}
					else {
						printf(" ]\n   |-----> Error! Max Lenght of High layer compatibility is %d\n", Hig_lay_com_max);
					}
				}
				else {
					printf(" :::::Incomplete Date\n");
				}
				switch (q931.Mes_Typ) {
					case CONNECT:
					case SETUP:
					case ALERTING:
					case CALL_PROCEEDING:
						break;
					default:
						printf("   |-----> [ Not Allow Appear ]\n");
				}
				break;

			default:
				if (octet[bit] < 16) {
					printf("\n[ 0%x ]\n   |-----> Unknown\n", octet[bit]);
				}
				else {
					printf("\n[ %x ]\n   |-----> Unknown\n", octet[bit]);
				}
				bit++;
				break;
		}
	}

out:printf("\n");
}
