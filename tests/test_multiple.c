// Copyright 2012 Francisco Souza. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// Output: Ran 3 tests. Failures: 0.

#include <stdio.h>
#include <yatf.h>

int
sum(int x, int y)
{
	return x + y;
}

void
test_sum_1_and_3(test_t *t)
{
	int got = sum(1, 3);
	if(got != 4) {
		test_fail(t, "1 + 3 should be 4!");
	}
}

void
test_sum_1_and_4(test_t *t)
{
	int got = sum(1, 4);
	if(got != 5) {
		test_fail(t, "1 + 4 should be 5!");
	}
}

void
test_sum_2_and_3(test_t *t)
{
	int got = sum(2, 3);
	if(got != 5) {
		test_fail(t, "2 + 3 should be 5!");
	}
}

int
main(void)
{
	register_test(test_sum_1_and_3);
	register_test(test_sum_1_and_4);
	register_test(test_sum_2_and_3);
	return run_tests();
}
