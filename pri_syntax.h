#ifndef _PRI_SYNTAX_
#define _PRI_SYNTAX_

#include "pri_main.h"

int Reserved(int octet[], int bit, int len, _q931 q931);

int Shift(int octet[], int bit, int len, _q931 q931);

int More_data(int octet[], int bit, int len, _q931 q931);

int Sending_complete(int octet[], int bit, int len, _q931 q931);

int Congestion_level(int octet[], int bit, int len, _q931 q931);

int Repeat_indicator(int octet[], int bit, int len, _q931 q931);

int Segmented_message(int octet[], int bit, int len, _q931 q931);

int Bearer_capability(int octet[], int bit, int len, _q931 q931);

int Cause(int octet[], int bit, int len, _q931 q931);

int Call_identity(int octet[], int bit, int len, _q931 q931);

int Call_state(int octet[], int bit, int len, _q931 q931);

int Channel_identification(int octet[], int bit, int len, _q931 q931);

int Progress_indicator(int octet[], int bit, int len, _q931 q931);

int Network_specific_facilities(int octet[], int bit, int len, _q931 q931);

int Notification_indicator(int octet[], int bit, int len, _q931 q931);

int Display(int octet[], int bit, int len, _q931 q931);

int Date_time(int octet[], int bit, int len, _q931 q931);

int Keypad_facility(int octet[], int bit, int len, _q931 q931);

int Signal(int octet[], int bit, int len, _q931 q931);

int Information_rate(int octet[], int bit, int len, _q931 q931);

int End_to_end_transit_delay(int octet[], int bit, int len, _q931 q931);

int Transit_delay_selection_and_indication(int octet[], int bit, int len, _q931 q931);

int Packet_layer_binary_parameters(int octet[], int bit, int len, _q931 q931);

int Packet_layer_window_size(int octet[], int bit, int len, _q931 q931);

int Packet_size(int octet[], int bit, int len, _q931 q931);

int Closed_user_group(int octet[], int bit, int len, _q931 q931);

int Reverse_charging_indication(int octet[], int bit, int len, _q931 q931);

int Calling_party_number(int octet[], int bit, int len, _q931 q931);

int Calling_party_subaddress(int octet[], int bit, int len, _q931 q931);

int Called_party_number(int octet[], int bit, int len, _q931 q931);

int Called_party_subaddress(int octet[], int bit, int len, _q931 q931);

int Redirecting_number(int octet[], int bit, int len, _q931 q931);

int Transit_network_selection(int octet[], int bit, int len, _q931 q931);

int Restart_indicator(int octet[], int bit, int len, _q931 q931);

int Low_layer_compatibility(int octet[], int bit, int len, _q931 q931);

int High_layer_compatibility(int octet[], int bit, int len, _q931 q931);

int User_user(int octet[], int bit, int len, _q931 q931);

int Escape_for_extension(int octet[], int bit, int len, _q931 q931);

/*
 * You can add a new status here.
 * But need to observe the following rules.
 *    int <status>(int <octet[]>, int <bit>, int <len>, _q931 <q931>);
 * And then goto pri_syntax.c in order to code new rules.
 */

#endif
