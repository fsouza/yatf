/*
 * Copyright 2012 Francisco Souza. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

/* Output: Ran 1 test. Failures: 0. */

#include <stdio.h>
#include <stdlib.h>
#include <yatf.h>

int
sum(int x, int y)
{
	return x + y;
}

void
test_sum(test_t *t)
{
	int i;
	static struct
	{
		int x, y;
		int expected;
	} input[] = {
		{2, 4, 6},
		{2, 3, 5},
		{50, -1, 49},
		{20, 32, 52},
		{0, 0, 0},
	};
	for(i = 0; input[i].x != 0; i++) {
		int got = sum(input[i].x, input[i].y);
		if(got != input[i].expected) {
			char *reason = (char *)malloc(100 * sizeof(char));
			sprintf(reason, "Fail: sum(%d, %d). Want %d. Got %d.",
			          input[i].x, input[i].y, input[i].expected, got);
			test_fail(t, reason);
		}
	}
}

int
main(void)
{
	register_test(test_sum);
	return run_tests();
}
