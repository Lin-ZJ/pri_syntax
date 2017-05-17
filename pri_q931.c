#include "pri_q931.h"

void syntax_q931_list(char *str)
{
}

void syntax_q931(char *str)
{
	int len = strlen(str);
	len = len/3-1;
	int octet[len];
	int i = 0;
	int bit = 0;
//	int statbit = 0;
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

//	statbit = 6+q931.L_c_ref;
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
				bit = Sending_complete(octet, bit, len, q931);
				break;

			case Rep_ind:
				bit = Repeat_indicator(octet, bit, len, q931);
				break;

			case Net_spe_fac:
				bit = Network_specific_facilities(octet, bit, len, q931);
				break;

			case Key_fac:
				bit = Keypad_facility(octet, bit, len, q931);
				break;

			case Cag_par_num:
				bit = Calling_party_number(octet, bit, len, q931);
				break;

			case Cag_par_sub:
				bit = Calling_party_subaddress(octet, bit, len, q931);
				break;

			case Cad_par_num:
				bit = Called_party_number(octet, bit, len, q931);
				break;

			case Cad_par_sub:
				bit = Called_party_subaddress(octet, bit, len, q931);
				break;

			case Tra_net_sel:
				bit = Transit_network_selection(octet, bit, len, q931);
				break;

			case Dat_tim:
				bit = Date_time(octet, bit, len, q931);
				break;

			case Pro_ind:
				bit = Progress_indicator(octet, bit, len, q931);
				break;

			case Sig:
				bit = Signal(octet, bit, len, q931);
				break;

			case Cau:
				bit = Cause(octet, bit, len, q931);
				break;

			case Cha_ide:
				bit = Channel_identification(octet, bit, len, q931);
				break;

			case Dis:
				bit = Display(octet, bit, len, q931);
				break;

			case Res_ind:
				bit = Restart_indicator(octet, bit, len, q931);
				break;

			case Bea_cap:
				bit = Bearer_capability(octet, bit, len, q931);
				break;

			case Low_lay_com:
				bit = Low_layer_compatibility(octet, bit, len, q931);
				break;

			case Hig_lay_com:
				bit = High_layer_compatibility(octet, bit, len, q931);
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
