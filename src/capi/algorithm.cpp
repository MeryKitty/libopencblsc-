#include <cstring>
#include <memory>
#include <utility>

#include "basics/constant.h"
#include "model/expression.h"
#include "algorithm/solver.h"
#include "algorithm/algorithm.h"

extern "C" {
	void* int_get_solver(char* algorithm) {
		if (strcmp(algorithm, "simple hill climbing") == 0) {
			std::function<void(std::vector<std::raw_ptr<opencbls::var_t<int>>>&,
					std::vector<std::pair<int, std::unique_ptr<opencbls::constraint_t<int>>>>&)>
					_algo = opencbls::simple_hill_climbing<int>;
			return new opencbls::solver<int>(_algo);
		} else {
			return nullptr;
		}
	}

	void int_close_solver(void* solver) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		delete _solver;
	}

	void int_add_weighted_constraint(void* solver, void* constraint, int weight) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		std::unique_ptr<opencbls::constraint_t<int>> _constraint((opencbls::constraint_t<int>*)constraint);
		_solver->add_constraint(std::move(_constraint), weight);
	}

	void int_add_constraint(void* solver, void* constraint) {
		int_add_weighted_constraint(solver, constraint, 1);
	}

	void* int_add_variable(void* solver, int min, int max) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		std::raw_ptr<opencbls::var_t<int>> _result = _solver->add_variable(min, max);
		return _result.get();
	}

	void* int_add_constant(int value) {
		return new opencbls::expr_t<int>(opencbls::const_t<int>(value));
	}

	void int_solve(void* solver) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		_solver->solve();
	}

	void* int_get_variable_expression(void* var) {
		return new opencbls::expr_t<int>(std::raw_ptr<opencbls::var_t<int>>((opencbls::var_t<int>*) var));
	}

	int int_get_variable_value(void* var) {
		opencbls::var_t<int>* _var = (opencbls::var_t<int>*) var;
		return _var->value();
	}

	void print_values(void* solver) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		_solver->print_value();
	}

	void print_violation(void* solver) {
		opencbls::solver<int>* _solver = (opencbls::solver<int>*) solver;
		_solver->print_violation();
	}
}
