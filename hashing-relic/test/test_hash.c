/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (c) 2009 RELIC Authors
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
 * Tests for prime field arithmetic.
 *
 * @ingroup test
 */

#include <stdio.h>
#include "relic.h"
#include "relic_ep.h"
#include "relic_epx.h"
#include "relic_pc.h"
#include "relic_test.h"
static int hash(void) {
	int code = RLC_ERR;
	uint8_t msg[5];
	ep13_t p, q;
	
	ep13_null(p);
	ep13_null(q);
	RLC_TRY {
		ep13_new(p);
		ep13_new(q);

		TEST_CASE("hashing to G2 using method I"){
		rand_bytes(msg, 5);
		ep13_map(p, msg, 5);
		ep13_cof_fuentes(q, p);		
		TEST_ASSERT(g2_is_valid_bw13(q), end);
		}
		TEST_END;

		TEST_CASE("hashing to G2 using method II"){
		rand_bytes(msg, 5);
		ep13_map(p, msg, 5);
		ep13_cof(q, p);		
		TEST_ASSERT(g2_is_valid_bw13(q), end);
		}
		TEST_END;

	}

	RLC_CATCH_ANY {
		RLC_ERROR(end);
	}
	code = RLC_OK;
  end:
	ep13_free(p);
	fp_free(q);
	return code;
}

int main(void) {
	if (core_init() != RLC_OK) {
		core_clean();
		return 1;
	}

	util_banner("Tests for hashing to G2 on BW13-P310", 0);

	RLC_TRY {
		ep_param_set_any();
		ep_param_print();
	} RLC_CATCH_ANY {
		core_clean();
		return 0;
	}
	
	if (hash() != RLC_OK) {
		core_clean();
		return 1;
	}

	util_banner("All tests have passed.\n", 0);

	core_clean();
	return 0;
}
