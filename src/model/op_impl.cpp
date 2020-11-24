#include <cassert>
#include <memory>
#include <experimental/memory>
#include <utility>
#include <variant>
#include <vector>

#include "basics/utility.h"
#include "basics/raw_ptr.h"
#include "model/op_impl.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
	op_add<T>::op_add(expr_t<T> operand1, expr_t<T> operand2) :
			op_t<T>::op_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_add<T>::value() {
		return this->_operand1.value() + this->_operand2.value();
	}

	template <class T>
	T op_add<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		return this->_operand1.delta(var, value) + this->_operand2.delta(var, value);
	}

	template <class T>
	op_sub<T>::op_sub(expr_t<T> operand1, expr_t<T> operand2) :
			op_t<T>::op_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_sub<T>::value() {
		return this->_operand1.value() - this->_operand2.value();
	}

	template <class T>
	T op_sub<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		return this->_operand1.delta(var, value) - this->_operand2.delta(var, value);
	}

	template <class T>
	op_mul<T>::op_mul(expr_t<T> operand1, expr_t<T> operand2) :
			op_t<T>::op_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_mul<T>::value() {
		return this->_operand1.value() * this->_operand2.value();
	}

	template <class T>
	T op_mul<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _delta1 = this->_operand1.delta(var, value);
		T _delta2 = this->_operand2.delta(var, value);
		T _value1 = this->_operand1.value();
		T _value2 = this->_operand2.value();
		return _delta1 * _value2 + _delta2 * _value1 + _delta1 * _delta2;
	}

	template <class T>
	op_div<T>::op_div(expr_t<T> operand1, expr_t<T> operand2) :
			op_t<T>::op_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T op_div<T>::value() {
		return this->_operand1.value() / this->_operand2.value();
	}

	template <class T>
	T op_div<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _delta1 = this->_operand1.delta(var, value);
		T _delta2 = this->_operand2.delta(var, value);
		T _value1 = this->_operand1.value();
		T _value2 = this->_operand2.value();
		return (_delta1 * _value2 - _delta2 * _value1) / (_value2 * (_value2 + _delta2));
	}

	template <class T>
	op_sum<T>::op_sum(std::vector<expr_t<T>> operands) :
			op_t<T>::op_t(std::vector<bool>()),
			_operands(std::move(operands)) {
		for (auto&& _operand : this->_operands) {
			this->_related_var = this->_related_var || _operand.related_var();
		}
	}

	template <class T>
	T op_sum<T>::value() {
		T _sum = 0;
		for (auto&& _operand : this->_operands) {
			_sum += _operand.value();
		}
		return _sum;
	}

	template <class T>
	T op_sum<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _sum = 0;
		for (auto&& _operand : this->_operands) {
			_sum += _operand.delta(var, value);
		}
		return _sum;
	}

    template <class T>
    op_user_defined<T>::op_user_defined(std::function<T(std::vector<T>&)> op, std::function<T(std::vector<T>&, std::vector<T>&)> delta, std::vector<expr_t<T>> operands) :
			op_t<T>::op_t(std::vector<bool>()),
			_op(std::move(op)),
			_delta(std::move(delta)),
			_operands(std::move(operands)) {
    	for (auto&& _operand : this->_operands) {
    		this->_related_var = this->_related_var || _operand.related_var();
    	}
    }

    template <class T>
    T op_user_defined<T>::value() {
    	std::size_t _size = this->_operands.size();
        std::vector<T> _operand_values(_size);
        for (std::size_t i = 0; i < _size; i++) {
            _operand_values[i] = this->_operands[i].value();
        }
        return this->_op(_operand_values);
    }

    template <class T>
    T op_user_defined<T>::delta_helper(std::raw_ptr<var_t<T>> var, T value) {
    	std::size_t _size = this->_operands.size();
    	std::vector<T> _operand_values(_size);
    	std::vector<T> _operand_deltas(_size);
    	for (std::size_t i = 0; i < _size; i++) {
    		_operand_values[i] = this->_operands[i].value();
    		_operand_deltas[i] = this->_operands[i].delta(var, value);
    	}
    	return this->_delta(_operand_values, _operand_deltas);
    }

    template class op_add<int>;
    template class op_sub<int>;
    template class op_mul<int>;
    template class op_div<int>;
    template class op_sum<int>;
    template class op_user_defined<int>;
}
