#include "pri_syntax.h"

int spare_0 = 0;

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

void _Bearer_capability(int octet[], int bit)
{
	int len = octet[bit];
	int statbit = bit;

	bit++;
	int ext = (octet[bit]&0x80) >> 7;
	printf("   |-----> | Ext: %x ", ext);
	int code_stand = (octet[bit]&0x60) >> 5;
	printf("| Code_stand: ");
	switch (code_stand) {
		case 0:
			printf("ITU-T standardized ");
			break;
		case 1:
			printf("ISO/IEC Standard ");
			break;
		case 2:
			printf("National standard ");
			break;
		case 3:
			printf("Standard defined for the network ");
			break;
		default:
			printf("Error ");
			break;
	}
	int info_trans_cap = (octet[bit]&0x1f);
	printf("| Info_trans_cap: ");
	switch (info_trans_cap) {
		case 0x00:
			printf("Speech\n");
			break;
		case 0x08:
			printf("Unrestricted digital info\n");
			break;
		case 0x09:
			printf("Restricted digital info\n");
			break;
		case 0x10:
			printf("3.1 kHz audio\n");
			break;
		case 0x11:
			printf("7 kHz audio (Unrestricted digital info)\n");
			break;
		case 0x18:
			printf("Video\n");
			break;
		default:
			printf("Error\n");
			break;
	}

	bit++;
	ext = (octet[bit]&0x80) >> 7;
	printf("   |-----> | Ext: %x ", ext);
	int trans_mode = (octet[bit]&0x60) >> 5;
	printf("| Trans_mode: ");
	switch (trans_mode) {
		case 0:
			printf("Circuit ");
			break;
		case 2:
			printf("Packet ");
			break;
		default:
			printf("Error ");
			break;
	}
	int info_trans_rate = (octet[bit]&0x1f);
	printf("| Info_trans_rate: ");
	switch (info_trans_rate) {
		case 0x00:
			printf("Used for packet-mode\n");
			break;
		case 0x10:
			printf("64 kbit/s\n");
			break;
		case 0x11:
			printf("2 × 64 kbit/s\n");
			break;
		case 0x13:
			printf("384 kbit/s\n");
			break;
		case 0x15:
			printf("1536 kbit/s\n");
			break;
		case 0x17:
			printf("1920 kbit/s\n");
			break;
		case 0x18:
			printf("Multirate (64 kbit/s base rate)\n");
			break;
		default:
			printf("Error\n");
			break;
	}

	if (info_trans_rate == 0x18) {
		bit++;
		ext = (octet[bit]&0x80) >> 7;
		printf("   |-----> | Ext: %x ", ext);
		int rate_mul = (octet[bit]&0x7f);
		printf("| Rate_mul: 0x%x\n", rate_mul);
	}

	while ((bit-statbit) < len) {
		bit++;
		int layer_id = (octet[bit]&0x60) >> 5;
		int user_info_lay_pro = 0;
		switch (layer_id) {
			case 1:
				ext = (octet[bit]&0x80) >> 7;
				printf("   |-----> | Ext: %x ", ext);
				printf("| Layer 1 ident ");
				user_info_lay_pro = (octet[bit]&0x1f);
				switch (user_info_lay_pro) {
					case 0x01:
						printf("| ITU-T standardized rate adaption V.110, I.460 and X.30\n");
						break;
					case 0x02:
						printf("| Recommendation G.711 u-law\n");
						break;
					case 0x03:
						printf("| Recommendation G.711 A-law\n");
						break;
					case 0x04:
						printf("| Recommendation G.721 32 kbit/s ADPCM and Recommendation I.460\n");
						break;
					case 0x05:
						printf("| Recommendation H.221 and H.242\n");
						break;
					case 0x06:
						printf("| Recommendation H.223 and H.245\n");
						break;
					case 0x07:
						printf("| Non-ITU_T standardized rate adaption\n");
						break;
					case 0x08:
						printf("| ITU-T standardized rate adaption V.120\n");
						break;
					case 0x09:
						printf("| ITU-T standardized rate adaption X.31\n");
					default:
						printf("| Error\n");
						break;
				}
				if (((info_trans_cap == 0x08) && ((user_info_lay_pro == 0x01) || (user_info_lay_pro == 0x08))) \
				 		|| ((info_trans_cap == 0x10) && ((user_info_lay_pro == 0x02) || (user_info_lay_pro == 0x03)))){
					if ((bit-statbit) < len) {
						bit++;
						ext = (octet[bit]&0x80) >> 7;
						printf("   |-----> | Ext: %x ", ext);
						int syn_asyn = (octet[bit]&0x40) >> 6;
						printf("| Syn_asyn: ");
						switch (syn_asyn) {
							case 0:
								printf("Synchronous data ");
								break;
							case 1:
								printf("Asynchronous data ");
								break;
							default:
								printf("Error ");
								break;
						}
						int nego = (octet[bit]&0x20) >> 5;
						printf("| Nego: ");
						switch (nego) {
							case 0:
								printf("In-band negotiation not possible ");
								break;
							case 1:
								printf("In-band negotiation possible ");
								break;
							default:
								printf("Error ");
								break;
						}
						int user_rate = (octet[bit]&0x1f);
						printf("| User_rate: ");
						switch (user_rate) {
							case 0:
								printf("I don't what it mean\n");
								break;
							case 1:
								printf("0.6 kbit/s Recommendation X.1\n");
								break;
							case 2:
								printf("1.2 kbit/s\n");
								break;
							case 3:
								printf("2.4 kbit/s Recommendation X.1\n");
								break;
							case 4:
								printf("3.6 kbit/s\n");
								break;
							case 5:
								printf("4.8 kbit/s Recommendation X.1\n");
								break;
							case 6:
								printf("7.2 kbit/s\n");
								break;
							case 7:
								printf("8 kbit/s Recommendation I.460\n");
								break;
							case 8:
								printf("9.6 kbit/s Recommendation X.1\n");
								break;
							case 9:
								printf("14.4 kbit/s\n");
								break;
							case 10:
								printf("16 kbit/s Recommendation I.460\n");
								break;
							case 11:
								printf("19.2 kbit/s\n");
								break;
							case 12:
								printf("32 kbit/s Recommendation I.460\n");
								break;
							case 13:
								printf("38.4 kbit/s Recommendation V.110\n");
								break;
							case 14:
								printf("48 kbit/s Recommendation X.1\n");
								break;
							case 15:
								printf("56 kbit/s\n");
								break;
							case 18:
								printf("57.6 kbit/s Recommendation V.14 extended\n");
								break;
							case 19:
								printf("28.8 kbit/s Recommendation V.110\n");
								break;
							case 20:
								printf("24 kbit/s Recommendation V.110\n");
								break;
							case 21:
								printf("0.1345 kbit/s Recommendation X.1\n");
								break;
							case 22:
								printf("0.100 kbit/s Recommendation X.1\n");
								break;
							case 23:
								printf("0.075/1.2 kbit/s Recommendation X.1\n");
								break;
							case 24:
								printf("1.2/0.075 kbit/s Recommendation X.1\n");
								break;
							case 25:
								printf("0.050 kbit/s Recommendation X.1\n");
								break;
							case 26:
								printf("0.075 kbit/s Recommendation X.1\n");
								break;
							case 27:
								printf("0.110 kbit/s Recommendation X.1\n");
								break;
							case 28:
								printf("0.150 kbit/s Recommendation X.1\n");
								break;
							case 29:
								printf("0.200 kbit/s Recommendation X.1\n");
								break;
							case 30:
								printf("0.300 kbit/s Recommendation X.1\n");
								break;
							case 31:
								printf("12 kbit/s\n");
								break;
							default:
								printf("Error\n");
								break;
						}
					}
				}
				if (user_info_lay_pro == 0x01) {
					if ((bit-statbit) < len) {
						bit++;
						ext = (octet[bit]&0x80) >> 7;
						printf("   |-----> | Ext: %x ", ext);
						int inter_rate = (octet[bit]&0x60) >> 5;
						printf("| Inter_rate: ");
						switch (inter_rate) {
							case 0:
								printf("Not used ");
								break;
							case 1:
								printf("8 kbit/s ");
								break;
							case 2:
								printf("16 kbit/s ");
								break;
							case 3:
								printf("32 kbit/s ");
								break;
							default:
								printf("Error ");
								break;
						}
						int NIC_on_Tx = (octet[bit]&0x10) >> 4;
						printf("| NIC_on_Tx: ");
						switch (NIC_on_Tx) {
							case 0:
								printf("Not required to send data with network independent clock ");
								break;
							case 1:
								printf("Requed to seng data with network independent clock ");
								break;
							default:
								printf("Error ");
								break;
						}
						int NIC_on_Rx = (octet[bit]&0x08) >> 3;
						printf("| NIC_on_Rx: ");
						switch (NIC_on_Rx) {
							case 0:
								printf("Cannot accept data with network independent clock ");
								break;
							case 1:
								printf("Can accept data with network independent clock ");
								break;
							default:
								printf("Error ");
								break;
						}
						int flow_ctr_on_Tx = (octet[bit]&0x04) >> 2;
						printf("| Flow_ctr_on_Tx: ");
						switch (flow_ctr_on_Tx) {
							case 0:
								printf("Not required to send data with flow control mechanism ");
								break;
							case 1:
								printf("required to send data with flow control mechanism ");
								break;
							default:
								printf("Error ");
								break;
						}
						int flow_ctr_on_Rx = (octet[bit]&0x02) >> 1;
						printf("| Flow_ctr_on_Rx: ");
						switch (flow_ctr_on_Rx) {
							case 0:
								printf("Cannot accept data with flow control mechanism ");
								break;
							case 1:
								printf("Can accept data with flow control mechanism ");
								break;
							default:
								printf("Error ");
								break;
						}
						spare_0 = (octet[bit]&0x01);
						printf("| spare_0: %x\n", spare_0);
					}
				}
				if (user_info_lay_pro == 0x08) {
					if ((bit-statbit) < len) {
						bit++;
						ext = (octet[bit]&0x80) >> 7;
						printf("   |-----> | Ext: %x ", ext);
						int hdr = (octet[bit]&0x40) >> 6;
						printf("| Hdr: ");
						switch (hdr) {
							case 0:
								printf("Rate adaption header not included ");
								break;
							case 1:
								printf("Rate adaption header included ");
								break;
							default:
								printf("Error ");
								break;
						}
						int mul = (octet[bit]&0x20) >> 5;
						printf("| Mul: ");
						switch (mul) {
							case 0:
								printf("Multiple frame establishment not supported ");
								break;
							case 1:
								printf("Multiple frame establishment supported ");
								break;
							default:
								printf("Error ");
								break;
						}
						int mode = (octet[bit]&0x10) >> 4;
						printf("| mode: ");
						switch (mode) {
							case 0:
								printf("Bit transparent mode of operation ");
								break;
							case 1:
								printf("Protocol sensitive mode of operation ");
								break;
							default:
								printf("Error ");
								break;
						}
						int LLI_negot = (octet[bit]&0x08) >> 3;
						printf("| LLI_negot: ");
						switch (LLI_negot) {
							case 0:
								printf("Default, LLI = 256 only ");
								break;
							case 1:
								printf("Full protocol negotiation ");
								break;
							default:
								printf("Error ");
								break;
						}
						int assignor = (octet[bit]&0x04) >> 2;
						printf("| Assignor: ");
						switch (assignor) {
							case 0:
								printf("Default assignee ");
								break;
							case 1:
								printf("Assignor only ");
								break;
							default:
								printf("Error ");
								break;
						}
						int in_band_neg = (octet[bit]&0x02) >> 1;
						printf("| In_band_neg: ");
						switch (in_band_neg) {
							case 0:
								printf("temporary signalling conn ");
								break;
							case 1:
								printf("logical link zero ");
								break;
							default:
								printf("Error ");
								break;
						}
						spare_0 = (octet[bit]&0x01);
						printf("| spare_0: %x\n", spare_0);
					}
				}
				if (((info_trans_cap == 0x08) && ((user_info_lay_pro == 0x01) || (user_info_lay_pro == 0x08))) \
				 		|| ((info_trans_cap == 0x10) && ((user_info_lay_pro == 0x02) || (user_info_lay_pro == 0x03)))){
					if ((bit-statbit) < len) {
						bit++;
						ext = (octet[bit]&0x80) >> 7;
						printf("   |-----> | Ext: %x ", ext);
						int num_stop_bits = (octet[bit]&0x60) >> 5;
						printf("| Num_stop_bits: ");
						switch (num_stop_bits) {
							case 0:
								printf("Not used ");
								break;
							case 1:
								printf("1 bit ");
								break;
							case 2:
								printf("1.5 bits ");
								break;
							case 3:
								printf("2 bit ");
								break;
							default:
								printf("Error ");
								break;
						}
						int num_data_bits = (octet[bit]&0x18) >> 3;
						printf("| Num_data_bits: ");
						switch (num_data_bits) {
							case 0:
								printf("Not used ");
								break;
							case 1:
								printf("5 bits ");
								break;
							case 2:
								printf("7 bits ");
								break;
							case 3:
								printf("8 bits ");
							default:
								printf("Error ");
								break;
						}
						int parity = (octet[bit]&0x07);
						printf("| Parity: ");
						switch (parity) {
							case 0:
								printf("Odd\n");
								break;
							case 2:
								printf("Even\n");
								break;
							case 3:
								printf("None\n");
								break;
							case 4:
								printf("Forced to 0\n");
								break;
							case 5:
								printf("Forced to 1\n");
								break;
							default:
								printf("Erro\n");
								break;
						}
					}
				}
				if (((info_trans_cap == 0x08) && ((user_info_lay_pro == 0x01) || (user_info_lay_pro == 0x08))) \
				 		|| ((info_trans_cap == 0x10) && ((user_info_lay_pro == 0x02) || (user_info_lay_pro == 0x03)))){
					if ((bit-statbit) < len) {
						bit++;
						ext = (octet[bit]&0x80) >> 7;
						printf("   |-----> | Ext: %x ", ext);
						int duplex_mode = (octet[bit]&0x40) >> 6;
						printf("| Duplex_mode: ");
						switch (duplex_mode) {
							case 0:
								printf("Half duplex ");
								break;
							case 1:
								printf("Full duplex ");
								break;
							default:
								printf("Error ");
								break;
						}
						int modem_type = (octet[bit]&0x3f);
						printf("| Modem_type: ");
						if ((modem_type > 0x00) && (modem_type < 0x05)) {
							printf("National use\n");
						}
						else if ((modem_type > 0x20) && (modem_type < 0x2f)) {
							printf("National use\n");
						}
						else if ((modem_type > 0x30) && (modem_type < 0x3f)) {
							printf("User specified\n");
						}
						else {
							switch (modem_type) {
								case 0x11:
									printf("Recommendation V.21\n");
									break;
								case 0x12:
									printf("Recommendation V.22\n");
									break;
								case 0x13:
									printf("Recommendation V.22 bis\n");
									break;
								case 0x14:
									printf("Recommendation V.23\n");
									break;
								case 0x15:
									printf("Recommendation V.26\n");
									break;
								case 0x16:
									printf("Recommendation V.26 bis\n");
									break;
								case 0x17:
									printf("Recommendation V.26 ter\n");
									break;
								case 0x18:
									printf("Recommendation V.27\n");
									break;
								case 0x19:
									printf("Recommendation V.27 bis\n");
									break;
								case 0x1a:
									printf("Recommendation V.27 ter\n");
									break;
								case 0x1b:
									printf("Recommendation V.29\n");
									break;
								case 0x1d:
									printf("Recommendation V.32\n");
									break;
								case 0x1e:
									printf("Recommendation V.34\n");
									break;
								default:
									printf("Error\n");
									break;
							}
						}
					}
				}
				break;
			case 2:
				ext = (octet[bit]&0x80) >> 7;
				printf("   |-----> | Ext: %x ", ext);
				printf("| Layer 2 ident ");
				user_info_lay_pro = (octet[bit]&0x1f);
				switch (user_info_lay_pro) {
					case 0x02:
						printf("| Recommendation Q.931/I.441\n");
						break;
					case 0x60:
						printf("| Recommendation X.25, link layer\n");
						break;
					case 0x0c:
						printf("| LAN logical link control (ISO/IEC 8802-2)\n");
						break;
					default:
						printf("| Error\n");
						break;
				}
				break;
			case 3:
				ext = (octet[bit]&0x80) >> 7;
				printf("   |-----> | Ext: %x ", ext);
				printf("| Layer 3 ident ");
				user_info_lay_pro = (octet[bit]&0x1f);
				switch (user_info_lay_pro) {
					case 0x02:
						printf("| Recommendation Q.931\n");
						break;
					case 0x60:
						printf("| Recommendation X.25, packet layer\n");
						break;
					case 0x0c:
						printf("| ISO/IEC TR 9577\n");
						break;
					default:
						printf("| Error\n");
						break;
				}
				if (user_info_lay_pro == 0x0c) {
					if ((bit-statbit) < len) {
						bit++;
						ext = (octet[bit]&0x80) >> 7;
						printf("   |-----> | Ext: %x ", ext);
						spare_0 = (octet[bit]&0x70) >> 4;
						printf("| Spare: %x ", spare_0);
						int add_lay_3_pro = (octet[bit]&0x0f);
						printf("| Add_lay_3_pro: ");
						if (ext == 0) {
							switch (add_lay_3_pro) {
								case 15:
									printf("Internet Protocol (RFC 791)(ISO/IEC TR 9577)\n");
									break;
								case 12:
									printf("Point-to-point Protocol (RFC 1548)\n");
									break;
								default:
									printf("Error\n");
									break;
							}
						}
						else {
							switch (add_lay_3_pro) {
								case 12:
									printf("Internet Protocol (RFC 791)(ISO/IEC TR 9577)\n");
									break;
								case 15:
									printf("Point-to-point Protocol (RFC 1548)\n");
									break;
								default:
									printf("Error\n");
									break;
							}
						}
					}
				}
				break;
			default:
				break;
		}
	}
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
				printf("   |-----> Bearer capability (len= %d)\n", octet[bit]);
				_Bearer_capability(octet, bit);
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

void _Channel_identification(int octet[], int bit)
{
	int len = octet[bit];
	int statbit = bit;

	bit++;
	int ext = (octet[bit]&0x80) >> 7;
	printf("   |-----> | Ext: %x ", ext);
	int int_id = (octet[bit]&0x40) >> 6;
	printf("| Int_id: ");
	switch (int_id) {
		case 0:
			printf("Interface implicitly identified ");
			break;
		case 1:
			printf("Interface explicitly identified ");
			break;
		default:
			printf("Error ");
			break;
	}
	int int_type = (octet[bit]&0x20) >> 5;
	printf("| Int_type: ");
	switch (int_type) {
		case 0:
			printf("Basic interface ");
			break;
		case 1:
			printf("Other interface (primary rate) ");
			break;
		default:
			printf("Error ");
			break;
	}
	spare_0 = (octet[bit]&0x10) >> 4;
	printf("| spare_0: %x\n", spare_0);
	int pref_excl = (octet[bit]&0x08) >> 3;
	printf("           | Pref_excl: ");
	switch (pref_excl) {
		case 0:
			printf("Indicated channel is preferred ");
			break;
		case 1:
			printf("Exclusive ");
			break;
		default:
			printf("Error ");
			break;
	}
	int dchan_ind = (octet[bit]&0x04) >> 2;
	printf("| Dchan_ind: ");
	switch (dchan_ind) {
		case 0:
			printf("isn't D-channel ");
			break;
		case 1:
			printf("is D-channel ");
			break;
		default:
			printf("Error ");
			break;
	}
	int info_chan_selec = (octet[bit]&0x03);
	printf("| Info_chan_selec: ");
	switch (info_chan_selec) {
		case 0:
			if (int_type == 0) {
				printf("No channel\n");
			}
			else {
				printf("No channel\n");
			}
			break;
		case 1:
			if (int_type == 0) {
				printf("B1 channel\n");
			}
			else {
				printf("indicated in following\n");
			}
			break;
		case 2:
			if (int_type == 0) {
				printf("B2 channel\n");
			}
			else {
				printf("Reserved\n");
			}
			break;
		case 3:
			if (int_type == 0) {
				printf("Any channel\n");
			}
			else {
				printf("Any channel\n");
			}
		default:
			printf("Error\n");
			break;
	}
	if (int_id == 0) {
		if ((bit-statbit) < len) {
			bit++;
			ext = (octet[bit]&0x80) >> 7;
			printf("   |-----> | Ext: %x ", ext);
			int inter_id = (octet[bit]&0x7f);
			printf("| Inter_id: 0x%x \n", inter_id);
		}
	}
	if (int_type != 0) {
		if ((bit-statbit) < len) {
			bit++;
			ext = (octet[bit]&0x80) >> 7;
			printf("   |-----> | Ext: %x ", ext);
			int code_stand = (octet[bit]&0x60) >> 5;
			printf("| Code_stand: ");
			switch (code_stand) {
				case 0:
					printf("ITU-T standardized ");
					break;
				case 1:
					printf("ISO/IEC Standard ");
					break;
				case 2:
					printf("National standard ");
					break;
				case 3:
					printf("Standard defined for the network ");
					break;
				default:
					printf("Error ");
					break;
			}
			int num_map = (octet[bit]&0x10) >> 4;
			printf("| num_map: ");
			switch (num_map) {
				case 0:
					printf("indicated by the number ");
					break;
				case 1:
					printf("indicated by the slot map ");
					break;
				default:
					printf("Error ");
					break;
			}
			int chan_map_type = (octet[bit]&0x0f);
			printf("| chan_map_type: ");
			switch (chan_map_type) {
				case 3:
					printf("B-channel units ");
					break;
				case 6:
					printf("H0-channel units ");
					break;
				case 8:
					printf("H11-channel units ");
					break;
				case 9:
					printf("H12-channel units ");
					break;
				default:
					printf("%d(reserved) ", chan_map_type);
					break;
			}
			printf("\n");
		}
	}
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
			_Channel_identification(octet, bit);
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
