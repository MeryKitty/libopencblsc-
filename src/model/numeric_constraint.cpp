#include "basics/constant.h"
#include "basics/utility.h"
#include "basics/raw_ptr.h"
#include "model/expression.h"
#include "model/constraint.h"
#include "model/numeric_constraint.h"

namespace opencbls {
	template <class T>
	constraint_equal<T>::constraint_equal(expr_t<T> operand1, expr_t<T> operand2) :
			constraint_t<T>::constraint_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_equal<T>::violation() {
		T _value = this->_operand1.value() - this->_operand2.value();
		return _value > T(0) ? _value : -_value;
	}

	template <class T>
	T constraint_equal<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _before = this->_operand1.value() - this->_operand2.value();
		T _delta = this->_operand1.delta(var, value) - this->_operand2.delta(var, value);
		T _after = _before + _delta;
		_before = _before > T(0) ? _before : -_before;
		_after = _after > T(0) ? _after : -_after;
		return _after - _before;
	}

	template <class T>
	constraint_not_equal<T>::constraint_not_equal(expr_t<T> operand1, expr_t<T> operand2) :
			constraint_t<T>::constraint_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_not_equal<T>::violation() {
		T _value = this->_operand1.value() -  this->_operand2.value();
		_value = _value > T(0) ? _value : -_value;
		_value = constant::false_violation<T> - _value;
		return _value > T(0) ? _value : T(0);
	}

	template <class T>
	T constraint_not_equal<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _before = this->_operand1.value() - this->_operand2.value();
		T _delta = this->_operand1.delta(var, value) - this->_operand2.delta(var, value);
		T _after = _before + _delta;
		_before = _before > T(0) ? _before : -_before;
		_after = _after > T(0) ? _after : -_after;
		_before = constant::false_violation<T> - _before;
		_after = constant::false_violation<T> - _after;
		_before = _before > T(0) ? _before : -_before;
		_after = _after > T(0) ? _after : -_after;
		return _after - _before;
	}

	template <class T>
	constraint_less_than<T>::constraint_less_than(expr_t<T> operand1, expr_t<T> operand2) :
			constraint_t<T>::constraint_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_less_than<T>::violation() {
		T _value = this->_operand1.value() -  this->_operand2.value();
		return _value > T(0) ? _value : T(0);
	}

	template <class T>
	T constraint_less_than<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _before = this->_operand1.value() -  this->_operand2.value();
		T _delta = this->_operand1.delta(var, value) - this->_operand2.delta(var, value);
		T _after = _before + _delta;
		_before = _before > 0 ? _before : T(0);
		_after = _after > 0 ? _after : T(0);
		return _after - _before;
	}

	template <class T>
	constraint_more_than<T>::constraint_more_than(expr_t<T> operand1, expr_t<T> operand2) :
			constraint_t<T>::constraint_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_more_than<T>::violation() {
		T _value = this->_operand2.value() -  this->_operand1.value();
		return _value > T(0) ? _value : T(0);
	}

	template <class T>
	T constraint_more_than<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _before = this->_operand2.value() -  this->_operand1.value();
		T _delta = this->_operand2.delta(var, value) - this->_operand1.delta(var, value);
		T _after = _before + _delta;
		_before = _before > 0 ? _before : T(0);
		_after = _after > 0 ? _after : T(0);
		return _after - _before;
	}

	template <class T>
	constraint_not_more_than<T>::constraint_not_more_than(expr_t<T> operand1, expr_t<T> operand2) :
			constraint_t<T>::constraint_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_not_more_than<T>::violation() {
		T _value = this->_operand1.value() -  this->_operand2.value();
		_value = _value > T(0) ? _value : T(0);
		return _value < constant::tolerance<T> ? T(0) : _value;
	}

	template <class T>
	T constraint_not_more_than<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _before = this->_operand1.value() -  this->_operand2.value();
		T _delta = this->_operand1.delta(var, value) - this->_operand2.delta(var, value);
		T _after = _before + _delta;
		_before = _before > 0 ? _before : T(0);
		_after = _after > 0 ? _after : T(0);
		_before = _before < constant::tolerance<T> ? T(0) : _before;
		_after = _after < constant::tolerance<T> ? T(0) : _after;
		return _after - _before;
	}

	template <class T>
	constraint_not_less_than<T>::constraint_not_less_than(expr_t<T> operand1, expr_t<T> operand2) :
			constraint_t<T>::constraint_t(operand1.related_var() || operand2.related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_not_less_than<T>::violation() {
		T _value = this->_operand2.value() -  this->_operand1.value();
		_value = _value > T(0) ? _value : T(0);
		return _value < constant::tolerance<T> ? T(0) : _value;
	}

	template <class T>
	T constraint_not_less_than<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _before = this->_operand2.value() -  this->_operand1.value();
		T _delta = this->_operand2.delta(var, value) - this->_operand1.delta(var, value);
		T _after = _before + _delta;
		_before = _before > 0 ? _before : T(0);
		_after = _after > 0 ? _after : T(0);
		_before = _before < constant::tolerance<T> ? T(0) : _before;
		_after = _after < constant::tolerance<T> ? T(0) : _after;
		return _after - _before;
	}

	template class constraint_equal<int>;
	template class constraint_not_equal<int>;
	template class constraint_less_than<int>;
	template class constraint_more_than<int>;
	template class constraint_not_more_than<int>;
	template class constraint_not_less_than<int>;
}
