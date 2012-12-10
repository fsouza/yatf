/*
 * Copyright 2012 Francisco Souza. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include "yactf.h"

static registry_t *r = NULL;

void *
emalloc(size_t size)
{
	void *p;
	p = malloc(size);
	if(p == NULL) {
		fprintf(stderr, "FATAL: can't allocate memory.\n");
		exit(1);
	}
	return p;
}

void
_register_test(char *name, void (*fn)(test_t *t))
{
	test_t *t;
	t = (test_t *)emalloc(sizeof(test_t));
	t->name = name;
	t->failed = 0;
	t->failures = NULL;
	t->fn = fn;
	registry_t *p = (registry_t *)emalloc(sizeof(registry_t));
	p->item = t;
	p->next = r;
	r = p;
}

void
free_test(test_t *t)
{
	failure_t *f;
	while(t->failures != NULL) {
		f = t->failures;
		t->failures = t->failures->next;
		free(f);
	}
}

void
free_suite()
{
	registry_t *p;
	while(r != NULL) {
		p = r;
		r = r->next;
		free_test(p->item);
		free(p->item);
		free(p);
	}
}

void
test_fail(test_t *t, char* reason)
{
	t->failed = 1;
	failure_t *failure;
	failure = (failure_t *)emalloc(sizeof(failure_t));
	failure->reason = reason;
	failure->next = t->failures;
	t->failures = failure;
}

int
run_tests()
{
	int ran, failed, plural;
	ran = failed = 0;
	if(r == NULL) {
		printf("Warning: no tests to run.\n");
		return 0;
	}
	registry_t *p = r;
	while(p != NULL) {
		p->item->fn(p->item);
		ran++;
		if(p->item->failed) {
			printf("FAIL: %s\n", p->item->name);
			failure_t *f;
			f = p->item->failures;
			while(f != NULL) {
				printf("      %s\n", f->reason);
				f = f->next;
			}
			printf("\n");
			failed++;
		}
		p = p->next;
	}
	free_suite();
	plural = ran > 1 ? 's' : '\0';
	printf("Ran %d test%c. Failures: %d.\n", ran, plural, failed);
	return failed > 0;
}
