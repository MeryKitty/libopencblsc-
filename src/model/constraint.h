/*
 * constraint.h
 *
 *  Created on: 29 Oct 2020
 *      Author: MeryKitty
 */

#ifndef MODEL_CONSTRAINT_H_INCLUDED
#define MODEL_CONSTRAINT_H_INCLUDED

#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "basics/constant.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
	class constraint_t {
	protected:
		std::vector<bool> _related_var;
		virtual T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) = 0;
	public:
		constraint_t(std::vector<bool> related_var);

		virtual ~constraint_t();

		virtual T violation() = 0;
		std::vector<bool>& related_var();
		T violation_delta(std::raw_ptr<var_t<T>> var, T value);
	};

	template <class T>
	class constraint_and : public constraint_t<T> {
	private:
		std::unique_ptr<constraint_t<T>> _operand1;
		std::unique_ptr<constraint_t<T>> _operand2;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_and(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2);

		T violation();
	};

	template <class T>
	class constraint_or : public constraint_t<T> {
	private:
		std::unique_ptr<constraint_t<T>> _operand1;
		std::unique_ptr<constraint_t<T>> _operand2;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_or(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2);

		T violation();
	};

	template <class T>
	class constraint_not : public constraint_t<T> {
	private:
		std::unique_ptr<constraint_t<T>> _operand;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_not(std::unique_ptr<constraint_t<T>> operand);

		T violation();
	};

	template <class T>
	class constraint_xor : public constraint_t<T> {
	private:
		std::unique_ptr<constraint_t<T>> _operand1;
		std::unique_ptr<constraint_t<T>> _operand2;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_xor(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2);

		T violation();
	};


	template <class T>
	class constraint_multi_and : public constraint_t<T> {
	private:
		std::vector<std::unique_ptr<constraint_t<T>>> _operands;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_multi_and(std::vector<std::unique_ptr<constraint_t<T>>> operands);

		T violation();
	};

	template <class T>
	class constraint_multi_or : public constraint_t<T> {
	private:
		std::vector<std::unique_ptr<constraint_t<T>>> _operands;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_multi_or(std::vector<std::unique_ptr<constraint_t<T>>> operands);

		T violation();
	};
}


#endif // MODEL_CONSTRAINT_H_INCLUDED
