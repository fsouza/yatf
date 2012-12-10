/*
 * Copyright 2012 Francisco Souza. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#define register_test(fn) _register_test(#fn, fn)
#define test_fatal(t, reason) test_fail(t, reason); return

struct failure_t
{
	char             *reason;
	struct failure_t *next;
};

struct test_t
{
	char             *name;
	struct failure_t *failures;
	int              failed;
	void (*fn)(struct test_t *t);
};

struct test_list_t
{
	struct test_t      *item;
	struct test_list_t *next;
};

typedef struct failure_t failure_t;
typedef struct test_t test_t;
typedef struct test_list_t registry_t;

void test_fail(test_t *t, char *reason);
void _register_test(char *name, void (*fn)(test_t *t));
void free_test(test_t *t);
void free_registry();
int run_tests();
