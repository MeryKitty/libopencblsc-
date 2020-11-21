/*
 * algorithm.cpp
 *
 *  Created on: 20 Nov 2020
 *      Author: MeryKitty
 */

#include <cstring>
#include <memory>
#include <utility>

#include "basics/constant.h"
#include "model/expression.h"
#include "algorithm/solver.h"
#include "algorithm/algorithm.h"

extern "C" {
	void* get_int_solver(char* algorithm) {
		if (strcmp(algorithm, "simple hill climbing") == 0) {
			std::function<void(std::vector<std::raw_ptr<opencbls::var_t<int>>>&,
					std::vector<std::pair<int, std::unique_ptr<opencbls::constraint_t<int>>>>&)>
					_algo = opencbls::simple_hill_climbing<int>;
			return new opencbls::solver<int>(_algo);
		} else {
			return nullptr;
		}
	}

	void add_int_constraint(void* solver, void* constraint, int weight = 1) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		std::unique_ptr<opencbls::constraint_t<int>> _constraint((opencbls::constraint_t<int>*)constraint);
		_solver->add_constraint(std::move(_constraint), weight);
	}

	void* add_int_variable(void* solver, int min, int max) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		std::raw_ptr<opencbls::var_t<int>> _result = _solver->add_variable(min, max);
		return _result.get();
	}

	void* add_int_constant(int value) {
		return new opencbls::expr_t<int>(opencbls::const_t<int>(value));
	}

	void solve_int(void* solver) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		_solver->solve();
	}

	void* get_int_variable(void* var) {
		return new opencbls::expr_t<int>(std::raw_ptr<opencbls::var_t<int>>((opencbls::var_t<int>*) var));
	}

	int get_int_variable_value(void* var) {
		opencbls::var_t<int>* _var = (opencbls::var_t<int>*) var;
		return _var->value();
	}
}
