/*
 * algorithm.h
 *
 *  Created on: 20 Nov 2020
 *      Author: MeryKitty
 */

#ifndef API_ALGORITHM_H_INCLUDED
#define API_ALGORITHM_H_INCLUDED

extern "C" {
	void* get_int_solver(char* algorithm);
	void add_int_constraint(void* solver, void* constraint, int weight = 1);
	void* add_int_variable(void* solver, int min, int max);
	void* add_int_constant(int value);
	void solve_int(void* solver);
	void* get_int_variable(void* var);
	int get_int_variable_value(void* var);
}

#endif /* API_ALGORITHM_H_INCLUDED */
