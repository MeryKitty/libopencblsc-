/*
 * main.cpp
 *
 *  Created on: 27 Oct 2020
 *      Author: MeryKitty
 */

#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "basics/constant.h"
#include "model/expression.h"
#include "model/op_impl.h"
#include "model/combinatoric_constraint.h"
#include "algorithm/solver.h"
#include "algorithm/algorithm.h"

void queen_set_up(opencbls::solver<int>& solver, int n);

int cppmain() {
	int N;
	std::cin >> N;
	std::function<void(std::vector<std::raw_ptr<opencbls::var_t<int>>>&,
			std::vector<std::pair<int, std::unique_ptr<opencbls::constraint_t<int>>>>&,
			std::any)> _algo = opencbls::simple_hill_climbing<int>;
	opencbls::solver<int> _solver(_algo, std::any());
	queen_set_up(_solver, N);
	_solver.solve();
	std::vector<int> result = _solver.value();
	for (int i : result) {
		std::cout << i << std::endl;
	}
	return 0;
}

void queen_set_up(opencbls::solver<int>& solver, int n) {
	std::vector<std::raw_ptr<opencbls::var_t<int>>> _variables;
	for (std::size_t i = 0; i < n; i++) {
		_variables.emplace_back(solver.add_variable(0, n));
	}

	std::vector<opencbls::expr_t<int>> _first_constraint;
	for (std::size_t i = 0; i < n; i++) {
		_first_constraint.emplace_back(opencbls::expr_t<int>(_variables[i]));
	}
	solver.add_constraint(std::make_unique<opencbls::constraint_all_not_equal<int>>(std::move(_first_constraint)));

	std::vector<opencbls::expr_t<int>> _second_constraint;
	for (std::size_t i = 0; i < n; i++) {
		_second_constraint.emplace_back(opencbls::expr_t<int>(std::make_unique<opencbls::op_add<int>>(opencbls::expr_t<int>(_variables[i]), opencbls::expr_t<int>(opencbls::const_t<int>(i)))));
	}
	solver.add_constraint(std::make_unique<opencbls::constraint_all_not_equal<int>>(std::move(_second_constraint)));

	std::vector<opencbls::expr_t<int>> _third_constraint;
	for (std::size_t i = 0; i < n; i++) {
		_third_constraint.emplace_back(opencbls::expr_t<int>(std::make_unique<opencbls::op_sub<int>>(opencbls::expr_t<int>(_variables[i]), opencbls::expr_t<int>(opencbls::const_t<int>(i)))));
	}
	solver.add_constraint(std::make_unique<opencbls::constraint_all_not_equal<int>>(std::move(_third_constraint)));
}
