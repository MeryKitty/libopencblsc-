#include <cassert>
#include <memory>
#include <experimental/memory>
#include <utility>
#include <variant>
#include <vector>

#include "model/op_impl.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
	op_add<T>::op_add(p_expr_t<T> operand1, p_expr_t<T> operand2) :
			operand1(std::move(operand1)), operand2(std::move(operand2)) {}

	template <class T>
	T op_add<T>::eval() {
		return this->operand1.eval() + this->operand2.eval();
	}

	template <class T>
	op_sub<T>::op_sub(p_expr_t<T> operand1, p_expr_t<T> operand2) :
			operand1(std::move(operand1)), operand2(std::move(operand2)) {}

	template <class T>
	T op_sub<T>::eval() {
		return this->operand1.eval() - this->operand2.eval();
	}

	template <class T>
	op_mul<T>::op_mul(p_expr_t<T> operand1, p_expr_t<T> operand2) :
			operand1(std::move(operand1)), operand2(std::move(operand2)) {}

	template <class T>
	T op_mul<T>::eval() {
		return this->operand1.eval() * this->operand2.eval();
	}

	template <class T>
	op_div<T>::op_div(p_expr_t<T> operand1, p_expr_t<T> operand2) :
			operand1(std::move(operand1)), operand2(std::move(operand2)) {}

	template <class T>
	T op_div<T>::eval() {
		return this->operand1.eval() / this->operand2.eval();
	}

	template <class T>
	op_sum<T>::op_sum(std::vector<p_expr_t<T>> operands) : operands(std::move(operands)) {}

	template <class T>
	T op_sum<T>::eval() {
		T _sum = 0;
		for (auto&& _operand : this->operands) {
			_sum += _operand.eval();
		}
		return _sum;
	}

    template <class T>
    op_user_defined<T>::op_user_defined(std::function<T(std::vector<T>&)> op, std::vector<p_expr_t<T>> operands) :
			op(std::move(op)), operands(std::move(operands)) {}

    template <class T>
    T op_user_defined<T>::eval() {
        std::vector<T> _operand_values(this->operands.size());
        for (auto&& _operand : _operands) {
            T _temp_value = _operand.eval();
            _operand_values.push_back(_temp_value);
        }
        return this->op(_operands_value);
    }
}
