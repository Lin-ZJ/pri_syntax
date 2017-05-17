#ifndef _PRI_MAIN_H_
#define _PRI_MAIN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <uuid/uuid.h>

#define log_path "modify.log"
#define U_MAX 200

#define _frame_flag	0x03

typedef struct{
	unsigned int SAPI:6;
	unsigned int C_R:1;
	unsigned int EA_0:1;
	unsigned int TEI:7;
	unsigned int EA_1:1;
	unsigned int N_S:7;
	unsigned int ZERO:1;
	unsigned int N_R:7;
	unsigned int P:1;
	unsigned int Pr_di:8;
	unsigned int L_c_ref:4;
	unsigned int flag:1;
	unsigned int Mes_Typ:7;
}_q931;

#define ALERTING			1
#define CALL_PROCEEDING		2
#define CONNECT				7
#define CONNECT_ACKNOWLEDGE 15
#define PROGRESS			3
#define SETUP				5
#define SETUP_ACKNOWLEDGE	13
#define RESUME				38
#define RESUME_ACKNOWLEDGE	46
#define RESUME_REJECT		34
#define SUSPEND				37
#define SUSPEND_ACKNOWLEDGE	45
#define SUSPEND_REJECT		33
#define USER_INFORMATION	32
#define DISCONNECT			69
#define RELEASE				77
#define RELEASE_COMPLETE	90
#define RESTART				70
#define RESTART_ACKNOWLEDGE	78
#define SEGMENT				96
#define CONGESTION_CONTROL	121
#define INFORMATION			123
#define NOTIFY				110
#define STATUS				125
#define	STATUS_ENQUIRY		117

#define Sen_com				0xa1
#define Rep_ind				0x50
#define Net_spe_fac			0x20
#define Key_fac				0x2c
#define Cag_par_num			0x6c
#define Cag_par_sub			0x6d
#define Cad_par_num			0x70
#define Cad_par_sub			0x71
#define Tra_net_sel			0x78
#define Dat_tim				0x29
#define Pro_ind				0x1e
#define Sig					0x34
#define Cau					0x08
#define Cha_ide				0x18
#define	Dis					0x28
#define Res_ind				0x79
#define Bea_cap				0x04
#define Low_lay_com			0x7c
#define Hig_lay_com			0x7d

#define Bea_cap_max			12
#define Cau_max				32
#define Key_fac_max			34
#define Cag_par_sub_max		23
#define Cad_par_sub_max		23
#define Dat_tim_max			8
#define Pro_ind_max			4
#define Sig_max				3
#define Dis_max				82
#define Res_ind_max			3
#define Low_lay_com_max		18
#define Hig_lay_com_max		5

#include "pri_func.h"
#include "pri_q931.h"
#include "pri_q921.h"
#include "pri_syntax.h"

#endif
