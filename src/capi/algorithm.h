/*
 * algorithm.h
 *
 *  Created on: 20 Nov 2020
 *      Author: MeryKitty
 */

#ifndef API_ALGORITHM_H_INCLUDED
#define API_ALGORITHM_H_INCLUDED

extern "C" {
	void* int_get_solver(char* algorithm);
	void int_add_weighted_constraint(void* solver, void* constraint, int weight);
	void int_add_constraint(void* solver, void* constraint);
	void* int_add_variable(void* solver, int min, int max);
	void* int_add_constant(int value);
	void int_solve(void* solver);
	void* int_get_variable_expression(void* var);
	int int_get_variable_value(void* var);
	void print_values(void* solver);
	void print_violation(void* solver);
}

#endif /* API_ALGORITHM_H_INCLUDED */
