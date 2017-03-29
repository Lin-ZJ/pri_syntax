#include "pri_syntax.h"

int Reserved(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Shift(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int More_data(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Sending_complete(int octet[], int bit, int len, _q931 q931)
{
	printf("\n[ a1 ]\n");
	printf("   |-----> Sending complete (len= 1)\n");
	bit++;
	switch (q931.Mes_Typ) {
		case SETUP:
			break;
		default:
			printf("   |-----> [ Not Allow Appear ]\n");
	}
	return bit;
}

int Congestion_level(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Repeat_indicator(int octet[], int bit, int len, _q931 q931)
{
	printf("\n[ 50 ]\n");
	printf("   |-----> Repeat indicator (len= 1)\n");
	bit++;
	switch (q931.Mes_Typ) {
		case SETUP:
			break;
		default:
			printf("   |-----> [ Not Allow Appear ]\n");
	}
	return bit;
}

int Segmented_message(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Bearer_capability(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Bearer capability (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Cause(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Cause (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Call_identity(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Call_state(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Channel_identification(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
			printf("   |-----> Channel identification (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Progress_indicator(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Progress indicator (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Network_specific_facilities(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
			printf("   |-----> Network-specific facilities (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Notification_indicator(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Display(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Display (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Date_time(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Date/time (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Keypad_facility(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Keypad facility (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Signal(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Signal (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Information_rate(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int End_to_end_transit_delay(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Transit_delay_selection_and_indication(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Packet_layer_binary_parameters(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Packet_layer_window_size(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Packet_size(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Closed_user_group(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Reverse_charging_indication(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Calling_party_number(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
			printf("   |-----> Calling party number (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Calling_party_subaddress(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Calling party subaddress (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Called_party_number(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
			printf("   |-----> Called party number (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Called_party_subaddress(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Called party subaddress (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Redirecting_number(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Transit_network_selection(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
			printf("   |-----> Transit network selection (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Restart_indicator(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Restart indicator (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int Low_layer_compatibility(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> Low layer compatibility (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int High_layer_compatibility(int octet[], int bit, int len, _q931 q931)
{
	int i;
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
				printf("   |-----> High layer compatibility (len= %d)\n", octet[bit]+2);
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
	return bit;
}

int User_user(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

int Escape_for_extension(int octet[], int bit, int len, _q931 q931)
{
	return 0;
}

/*
 * You can add new status here.
 * Parameter <bit> is the first bit of function packet.
 * <bit+1> generally used to describe the length of the packet.
 * <len> is the length of the whole packet, including packet header.
 */
