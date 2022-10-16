

#include <stdio.h>
#include "relic/relic.h"
#include "relic/relic_pc.h"
//#include "relic_bn.h"
//#include "relic_epx.h"
//#include "relic_fp.h"

//#include "relic_fpx.h"
/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (C) 2007-2019 RELIC Authors
 *
 * This file is part of RELIC. RELIC is legal property of its developers,
 * whose names are not listed here. Please refer to the COPYRIGHT file
 * for contact information.
 *
 * RELIC is free software; you can redistribute it and/or modify it under the
 * terms of the version 2.1 (or later) of the GNU Lesser General Public License
 * as published by the Free Software Foundation; or version 2.0 of the Apache
 * License as published by the Apache Software Foundation. See the LICENSE files
 * for more details.
 *
 * RELIC is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the LICENSE files for more details.
 *
 * You should have received a copy of the GNU Lesser General Public or the
 * Apache License along with RELIC. If not, see <https://www.gnu.org/licenses/>
 * or <https://www.apache.org/licenses/>.
 */

/**
 * @file
 *
 * Implementation of the pairings over prime curves.
 *
 * @ingroup pp
 */
#define X0		"2ABD462165DD51FE6C04FEDB34B5B10D73358C3E6402D59226DEF4DA1C7A1240C5C46C7C79500F"
#define X1      "58946AEB5E1C2537196E12B1765C7A3113BD577823FD7BDC56F9DB711CA3071C1676367F9491D"
#define X2		"29F4B088795B1C89F223B6CB69A7D699B1B06C4831DF540108A72F612095F79FC2170431EE3E69"
#define X3		"14B1E0C6C9C1C25B19A313FC5503CFCA12293A903C36BCBE545BB96BFE0E5E1EAC156DFC8FC5A6"
#define X4		"25FC28559B2C0D5A7F8DA3A7E081E42B6F4E126BC023D999ABB28695BC42C27492398390DCDD6D"
#define X5		"17AFB2B6F679FEA9EEB2B2ABF66E205F4CB2A23C160453DEA9EED5DDA437477D1C4609F4B07C4"
#define X6		"2D9AE5033103D87112FA4594003FC3BA449EF5E1FE4FDFC29A51C09B131B195BD82D46B88ACC8D"
#define X7		"1D2F2B5D02287C93BF737D5AE3AC431B113E69150F0E788A1D868E2A251AEE42D11D4DB347487A"
#define X8		"2D77538DB67FA0DABFDA27C95DD55880D0E8E77118AE732729A5250819CE9BA058B5A51620FECD"
#define X9		"4B0CCBA27BF29FDD864E99D111E2EAD803F973EB1A684508065785BF2EA3D8F2221518BA86E10"
#define X10		"8FAEBB1566640E9BEF4F12DFE21FF2137162BFE08EC3A814F2238000409EC355F3063C60C4B2E"
#define X11		"1B3C57505E53D39BFBF1DE9B8307D152E423CF9FA7B66209E44324654C3FD658EBC57CCA6FFFF3"
#define X12		"1F125EE2D5157BFEFE8571CAFFC2AE4E1062CB6526A87E3E9050D5375AB0F37ADE307C536E728F"

#define Y0		"31DDFA3A93A3B02CB8B13D1F6C7D24A3877CF2600513DD4EF5DE6410724E987EB847F17D6BE89"
#define Y1		"1107F6C78373AB0B5B36E458F3FA92641E8EA054E056C844B7493571D2F70CFCC13CBE2ADC17DE"
#define Y2		"16533C0ADDEA6C2D79D6139696336D7E94FEE4798B56134955A29FD15F287FB334718989AE0EF6"
#define Y3		"3DEC8837133A2F65C891E5886D034F6369D2FAFFC1BA67B0A4BFDDFEA4797593EC7B4ACBDDD1F"
#define Y4		"6430620153331E78E27176AFE8D23B90AFDA73D62EC5F9BC9747EA4AFBD8814F6F2B3687CD3FF"
#define Y5		"4D4FA058C308CCD65102F10E4B8E4FAE3ED106527359305BCFBEF66A350CD00F22F5D144DB215"
#define Y6		"189652E6C505DEC2A21626A5ED529B898C89707A1557F765E548FA515CE2E947F37DFC9B4521D1"
#define Y7		"B29DF623A04DB6DC7BB54036443E39153AD0ADD037050B1CA5C3BDAFFCA822A1A68C10D1DF72F"
#define Y8		"33A0B68997C7577CD6114004D1ED3359661C49EEDDF0F8E55F631562E7AEE519E8E24CDDF28056"
#define Y9		"1AAE620E614F63A1E5FB36D7ECDAFE0BAEF6F99E9C4B9DAD12CF00238C3B714E9C54E44153233C"
#define Y10		"15B621B7135EC055E9ACC6981EF2105C75AB67AE8DB83CCD355E85082DEBC51028C38B79EE9576"
#define Y11		"353D8EB9295630CD0CA815C0C76F7E3EE24AE4CBB0AA8B8652C3F617C88E71B9973D51432CA8D5"
#define Y12		"17D1816D1D1DB07DE35570400B8CA6CABA2C01A50CF2B159CC1D1DC1B2A8302D052FB890006B12"

#define ASSIGN()   \
    RLC_GET(str,X0, sizeof(X0));	                       \
    fp_read_str(g->x[0], str, strlen(str), 16);                  \
	RLC_GET(str,X1, sizeof(X1));              						\
	fp_read_str(g->x[1], str, strlen(str), 16);	                 \
	RLC_GET(str,X2, sizeof(X2));	           						\
	fp_read_str(g->x[2], str, strlen(str), 16);								\
	RLC_GET(str,X3, sizeof(X3));							\
	fp_read_str(g->x[3], str, strlen(str), 16);							\
    RLC_GET(str,X4, sizeof(X4));							\
    fp_read_str(g->x[4], str, strlen(str), 16);								\
	RLC_GET(str,X5, sizeof(X5));\
    fp_read_str(g->x[5], str, strlen(str), 16);	\
    RLC_GET(str,X6, sizeof(X6));							\
	fp_read_str(g->x[6], str, strlen(str), 16);	\
	RLC_GET(str,X7, sizeof(X7));			\
	fp_read_str(g->x[7], str, strlen(str), 16);                     \
	RLC_GET(str,X8, sizeof(X8));				\
	fp_read_str(g->x[8], str, strlen(str), 16);				\
	RLC_GET(str,X9, sizeof(X9));				\
	fp_read_str(g->x[9], str, strlen(str), 16);				\
	RLC_GET(str,X10, sizeof(X10));				\
	fp_read_str(g->x[10], str, strlen(str), 16);				\
	RLC_GET(str,X11, sizeof(X11));				\
	fp_read_str(g->x[11], str, strlen(str), 16);				\
	RLC_GET(str,X12, sizeof(X12));				\
	fp_read_str(g->x[12], str, strlen(str), 16);				\
	RLC_GET(str,Y0, sizeof(Y0));				\
	fp_read_str(g->y[0], str, strlen(str), 16);			\
	RLC_GET(str,Y1, sizeof(Y1));				\
	fp_read_str(g->y[1], str, strlen(str), 16);			\
	RLC_GET(str,Y2, sizeof(Y2));			\
	fp_read_str(g->y[2], str, strlen(str), 16);			   \
    RLC_GET(str,Y3, sizeof(Y3));			\
	fp_read_str(g->y[3], str, strlen(str), 16);				\
	RLC_GET(str,Y4, sizeof(Y4));				\
	fp_read_str(g->y[4], str, strlen(str), 16);			             \
	RLC_GET(str,Y5, sizeof(Y5));						\
	fp_read_str(g->y[5], str, strlen(str), 16);                                              \
	RLC_GET(str,Y6, sizeof(Y6));					        \
	fp_read_str(g->y[6], str, strlen(str), 16);				\
	RLC_GET(str,Y7, sizeof(Y7));                                                             \
	fp_read_str(g->y[7], str, strlen(str), 16);                                                 \
 	RLC_GET(str,Y8, sizeof(Y8));	                                      \
 	fp_read_str(g->y[8], str, strlen(str), 16);	                                            \
 	RLC_GET(str,Y9, sizeof(Y9));                         \
	fp_read_str(g->y[9], str, strlen(str), 16);	             				\
	RLC_GET(str,Y10, sizeof(Y10));	               					\
	fp_read_str(g->y[10], str, strlen(str), 16);	       \
	RLC_GET(str,Y11, sizeof(Y11));	               					\
	fp_read_str(g->y[11], str, strlen(str), 16);\
	RLC_GET(str,Y12, sizeof(Y12));	               					\
	fp_read_str(g->y[12], str, strlen(str), 16);  

	
int main(void) {
	core_init(); 
	ctx_t *ctx = core_get();
	ep_param_set_any_pairf();
	char str[2 * RLC_FP_BYTES + 1];
	ep13_t g, r;
	fp13_t s,e;fp_t p;
	ep13_null(g);
	ep13_new(g);
	ep13_null(r);
	ep13_new(r);
 	ep13_set_infty(r);
	ASSIGN();
	fp13_zero(g->z);
	fp_set_dig(g->z[0], 1);
	printf("****************************mapping g to G2 using method I**************\n");
	ep13_cof_fuentes(r,g);

	printf("****************************mapping g to G2 using method II**************\n");
    ep13_cof(r, g);

	if(g2_is_valid_bw13(r) == 1){
		printf("	hashing to G2 is correct\n");
		}
	else{
		printf("	hashing to G2 is NOT correct\n");
		}
	return 0;
}


