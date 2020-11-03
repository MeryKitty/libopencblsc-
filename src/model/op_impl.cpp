#include <cassert>
#include <memory>
#include <experimental/memory>
#include <utility>
#include <variant>
#include <vector>

#include "basics/utility.h"
#include "model/op_impl.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
	op_add<T>::op_add(expr_t<T> operand1, expr_t<T> operand2) :
			_related_var(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_add<T>::eval() {
		return this->operand1.eval() + this->operand2.eval();
	}

	template <class T>
	T op_add<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		return this->_operand1.delta(var, value) + this->_operand2.delta(var, value);
	}

	template <class T>
	op_sub<T>::op_sub(expr_t<T> operand1, expr_t<T> operand2) :
			_related_var(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_sub<T>::eval() {
		return this->operand1.eval() - this->operand2.eval();
	}

	template <class T>
	T op_sub<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		return this->_operand1.delta(var, value) - this->_operand2.delta(var, value);
	}

	template <class T>
	op_mul<T>::op_mul(expr_t<T> operand1, expr_t<T> operand2) :
			_related_var(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_mul<T>::eval() {
		return this->operand1.eval() * this->operand2.eval();
	}

	template <class T>
	T op_mul<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _delta1 = this->_operand1.delta(var, value);
		T _delta2 = this->_operand2.delta(var, value);
		T _value1 = this->_operand1.eval();
		T _value2 = this->_operand2.eval();
		return _delta1 * _value2 + _delta2 * _value1 + _delta1 * _delta2;
	}

	template <class T>
	op_div<T>::op_div(expr_t<T> operand1, expr_t<T> operand2) :
			_related_var(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_div<T>::eval() {
		return this->operand1.eval() / this->operand2.eval();
	}

	template <class T>
	T op_div<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _delta1 = this->_operand1.delta(var, value);
		T _delta2 = this->_operand2.delta(var, value);
		T _value1 = this->_operand1.eval();
		T _value2 = this->_operand2.eval();
		return (_delta1 * _value2 - _delta2 * _value1) / (_value2 * (_value2 + _delta2));
	}

	template <class T>
	op_sum<T>::op_sum(std::vector<expr_t<T>> operands) :
			_related_var(std::vector<bool>()),
			_operands(std::move(operands)) {}

	template <class T>
	T op_sum<T>::eval() {
		T _sum = 0;
		for (auto&& _operand : this->operands) {
			_sum += _operand.eval();
		}
		return _sum;
	}

	template <class T>
	T op_sum<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _sum = 0;
		for (auto&& _operand : this->operands) {
			_sum += _operand.delta(var, value);
		}
		return _sum;
	}

    template <class T>
    op_user_defined<T>::op_user_defined(std::function<T(std::vector<T>&)> op, std::function<T(std::vector<T>&, std::vector<T>&)> delta, std::vector<expr_t<T>> operands) :
			_op(std::move(op)),
			_delta(delta),
			_operands(std::move(operands)) {}

    template <class T>
    T op_user_defined<T>::eval() {
        std::vector<T> _operand_values(this->operands.size());
        for (auto&& _operand : this->_operands) {
            _operand_values[i] = _operand.eval();
        }
        return this->_op(_operands_value);
    }

    template <class T>
    T op_user_defined<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
    	std::vector<T> _operand_values(this->_operands.size());
    	std::vector<T> _operand_deltas(this->_operands.size());
    	for (auto&& _operand : this->_operands) {
    		_operand_values[i] = _operand.eval();
    		_operand_deltas[i] = _operand.delta(var, value);
    	}
    	return this->_delta(_operand_values, _operand_deltas);
    }
}
