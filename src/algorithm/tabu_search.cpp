#include <any>
#include <iostream>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

#include "basics/constant.h"
#include "model/expression.h"
#include "model/constraint.h"
#include "algorithm/algorithm.h"

namespace opencbls {
    template <class T>
    void tabu_search(std::vector<std::raw_ptr<var_t<T>>>& variables,
			std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>& constraints,
            std::any parameters) {
        tabu_parameters<T> _parameters = std::any_cast<tabu_parameters<T>>(parameters);
        bool _intensify_phase = false;
        std::vector<T> _pivot(variables.size());
        auto violation = [&variables, &constraints]() {
			T _violation = T(0);
			for (auto&& constraint : constraints) {
				_violation += constraint.first * constraint.second->violation();
			}
			return _violation;
		};

        auto delta = [&variables, &constraints](std::raw_ptr<var_t<T>> var, T value) {
			T _delta = T(0);
			for (auto&& constraint : constraints) {
				_delta += constraint.first * constraint.second->violation_delta(var, value);
			}
			return _delta;
		};

        auto modified_delta = [&variables, &constraints, &_parameters, &_pivot, &delta, &_intensify_phase](std::raw_ptr<var_t<T>> var, T value) {
            T _base = delta(var, value);
            std::size_t _index;
            for (std::size_t i = 0; i < variables.size(); i++) {
                if (variables[i] == var) {
                    _index = i;
                    break;
                }
            }
            T _ori_diff = variables[_index]->value() - _pivot[_index];
            _ori_diff = _ori_diff > 0 ? _ori_diff : -_ori_diff;
            T _new_diff = value - _pivot[_index];
            _new_diff = _new_diff > 0 ? _new_diff : -_new_diff;
            T _diff = _new_diff - _ori_diff;
            if (_intensify_phase) {
                return _base + _parameters.intensify_weight * _diff;
            } else {
                return _base - _parameters.diversify_weight * _diff;
            }
        };

        T _best_violation = violation();
        std::vector<T> _best_vars(variables.size());
        for (std::size_t i = 0; i < variables.size(); i++) {
            _best_vars[i] = variables[i]->value();
        }
        std::size_t _period = _parameters.intensify_period + _parameters.diversify_period;
        T _current = _best_violation;
        for (std::size_t _iter = 0, _stale_iter = 0; _iter < _parameters.limit_iter; _iter++) {
            std::size_t _phase = _iter % _period;
            if (_phase == 0 || _phase == _parameters.intensify_period) {
                for (std::size_t i = 0; i < variables.size(); i++) {
                    _pivot[i] = variables[i]->value();
                }
                if (_phase == 0) {
                    _intensify_phase = true;
                } else {
                    _intensify_phase = false;
                }
            }
            T _best_mod_delta = std::numeric_limits<T>::max() - 1;
            std::raw_ptr<var_t<T>> _best_mod_var;
            T _best_mod_value;
            for (auto&& _var : variables) {
                for (T _value = _var->min(); _value < _var->max(); _value += constant::tolerance<T>) {
					T _mod_delta = modified_delta(_var, _value);
					if (_mod_delta < _best_mod_delta) {
						_best_mod_delta = _mod_delta;
                        _best_mod_var = _var;
                        _best_mod_value = _value;
					}
				}
            }
            T _delta = delta(_best_mod_var, _best_mod_value);
            _current += _delta;
            std::cout << "Violation: " << _current << std::endl;
            _best_mod_var->assign(_best_mod_value);
            if (_current < _best_violation) {
                _best_violation = _current;
                _stale_iter = 0;
                for (std::size_t i = 0; i < variables.size(); i++) {
                    _best_vars[i] = variables[i]->value();
                }
                if (_current == 0) {
                    break;
                }
            } else {
                _stale_iter++;
                if (_stale_iter > _parameters.stale_iter) {
                    break;
                }
            }
        }
        for (std::size_t i = 0; i < variables.size(); i++) {
            variables[i]->assign(_best_vars[i]);
        }
    }

    template void tabu_search<int>(std::vector<std::raw_ptr<var_t<int>>>& variables,
			std::vector<std::pair<int, std::unique_ptr<constraint_t<int>>>>& constraints,
            std::any parameters);
}