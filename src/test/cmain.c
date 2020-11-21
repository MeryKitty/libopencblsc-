/*
 * cmain.c
 *
 *  Created on: 21 Nov 2020
 *      Author: MeryKitty
 */

#include <stdio.h>
#include <stdlib.h>
#include "capi/algorithm.h"
#include "capi/model.h"

int main() {
	int n;
	scanf("%d", &n);
	void* _solver = get_int_solver("simple hill climbing");
	void** _vars = (void**)malloc(sizeof(void*) * n);
	int i = 0;
	for (i = 0; i < n; i++) {
		_vars[i] = add_int_variable(_solver, 0, n);
	}

	void** _first_constraint_operands = (void**)malloc(sizeof(void*) * n);
	for (i = 0; i < n; i++) {
		_first_constraint_operands[i] = get_int_variable(_vars[i]);
	}
	void* _first_constraint = constraint_all_not_equal(n, _first_constraint_operands);
	add_int_constraint(_solver, _first_constraint);

	void** _second_constraint_operands = (void**)malloc(sizeof(void*) * n);
	for (i = 0; i < n; i++) {
		_second_constraint_operands[i] = op_add_int(get_int_variable(_vars[i]), add_int_constant(i));
	}
	void* _second_constraint = constraint_all_not_equal(n, _second_constraint_operands);
	add_int_constraint(_solver, _second_constraint);

	void** _third_constraint_operands = (void**)malloc(sizeof(void*) * n);
	for (i = 0; i < n; i++) {
		_third_constraint_operands[i] = op_sub_int(get_int_variable(_vars[i]), add_int_constant(i));
	}
	void* _third_constraint = constraint_all_not_equal(n, _third_constraint_operands);
	add_int_constraint(_solver, _third_constraint);

	solve_int(_solver);

	print_values(_solver);
}
