	/*
 * utility.h
 *
 *  Created on: 28 Oct 2020
 *      Author: MeryKitty
 */
#ifndef MODEL_EXPRESSION_H_INCLUDED
#define MODEL_EXPRESSION_H_INCLUDED

#include <memory>
#include <experimental/memory>
#include <utility>
#include <variant>
#include <vector>

#include "basics/constant.h"

namespace opencbls {
	template <class T> class const_t;
	template <class T> class var_t;
	template <class T> class op_t;
	template <class T> class expr_t;

	template <class T>
	class const_t {
	private:
		static std::vector<bool> _dummy();

		T _value;
	public:
		const_t();
		const_t(T value);

		T eval();
		const std::vector<bool>& dummy_vector();
	};

	template <class T>
	class var_t {
	private:
		std::size_t _id;
		T _min;
		T _max;
		T _value;
		std::vector<bool> _onehot;
	public:
		var_t(std::size_t id, T min, T max);

		std::size_t id();
		T eval();
		const std::vector<bool>& id_onehot();
	};

	template <class T>
	class expr_t {
	private:
		std::variant<std::unique_ptr<op_t<T>>, std::raw_ptr<var_t<T>>, const_t<T>> _expr;

	public:
		expr_t(expr_t<T>&& in);
		expr_t<T>& operator= (expr_t<T>&& in);

		expr_t(std::unique_ptr<op_t<T>> op);
		expr_t(std::raw_ptr<var_t<T>> var);
		expr_t(const_t<T> cst);

		T eval();
		T delta(std::raw_ptr<var_t<T>> var, T value);
		const std::vector<bool>& related_var();
	};

	template <class T>
	class op_t {
	protected:
		std::vector<bool> _related_var;

		bool relate(std::raw_ptr<var_t<T>> var) noexcept;

		virtual T delta_helper(std::raw_ptr<var_t<T>> var, T value) = 0;
	public:
		T delta(std::raw_ptr<var_t<T>> var, T value);
		const std::vector<bool>& related_var();

		virtual T eval() = 0;
		virtual ~op_t() = 0;
	};
}

#endif // MODEL_EXPRESSION_H_INCLUDED
