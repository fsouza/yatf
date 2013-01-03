// Copyright 2012 Francisco Souza. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yatf.h"

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
	registry_t *p;
	test_t *t;
	t = (test_t *)emalloc(sizeof(test_t));
	t->name = name;
	t->failed = 0;
	t->failures = NULL;
	t->fn = fn;
	p = (registry_t *)emalloc(sizeof(registry_t));
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
		free(f->reason);
		free(f);
	}
}

void
free_suite(void)
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
	failure_t *failure;
	failure = (failure_t *)emalloc(sizeof(failure_t));
	failure->reason = (char *)emalloc((strlen(reason) + 1) * sizeof(char));
	strcpy(failure->reason, reason);
	failure->next = t->failures;
	t->failures = failure;
	t->failed = 1;
}

int
run_tests(void)
{
	registry_t *p = r;
	failure_t *f;
	int ran, failed, plural;
	ran = failed = 0;
	if(r == NULL) {
		printf("Warning: no tests to run.\n");
		return 0;
	}
	while(p != NULL) {
		p->item->fn(p->item);
		ran++;
		if(p->item->failed) {
			printf("FAIL: %s\n", p->item->name);
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
	printf("Ran: %d test%c. Succeeded: %d. Failed: %d.\n", ran, plural, ran-failed, failed);
	return failed > 0;
}
