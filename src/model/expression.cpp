#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "model/expression.h"

namespace opencbls {
	template <class T>
	const_t<T>::const_t() : value(0) {};

	template <class T>
	const_t<T>::const_t(T value) : value(std::move(value)) {};

	template <class T>
	const_t* const_t<T>::operator-> () {
		return this;
	}

	template <class T>
	T const_t<T>::eval() {
		return this->value;
	}

    template <class T>
    var_t<T>::var_t(T min, T max) : min(min), max(max) {}

    template <class T>
    T var_t<T>::eval() {
        return this->value;
    }

    template <class T>
    p_expr_t<T>::p_expr_t(p_expr_t<T>&& in) {
    	this->expr.swap(in.expr);
    }

    template <class T>
    p_expr_t<T>& p_expr_t<T>::operator =(p_expr_t<T>&& in) {
    	this->expr.swap(in.expr);
    	return *this;
    }

    template <class T>
    p_expr_t<T>::p_expr_t(std::unique_ptr<op_t<T>> op) : expr(std::move(op)) {}

    template <class T>
    p_expr_t<T>::p_expr_t(std::raw_ptr<var_t<T>> var) : expr(std::move(var)) {}

    template <class T>
    p_expr_t<T>::p_expr_t(const_t<T> cst) : expr(std::move(cst)) {}

    template <class T>
    T p_expr_t<T>::eval() {
    	auto&& get_value = [](auto&& expr) {
    		return expr->eval();
    	};
    	return std::visit(get_value, this->expr);
    }
}
