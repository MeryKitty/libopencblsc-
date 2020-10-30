	/*
 * utility.h
 *
 *  Created on: 28 Oct 2020
 *      Author: MeryKitty
 */
#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <memory>
#include <experimental/memory>
#include <utility>
#include <variant>
#include <vector>

namespace std {
	template <class T>
	using raw_ptr = experimental::observer_ptr<T>;
}

namespace opencbls {
	template <class T> class const_t;
	template <class T> class var_t;
	template <class T> class op_t;
	template <class T> class p_expr_t;

	template <class T>
	class const_t {
	private:
		T value;
	public:
		const_t();
		const_t(T value);

		const_t* operator-> ();
		T eval();
	};

	template <class T>
	class var_t {
	private:
		T min;
		T max;
		T value;

	public:
		var_t(T min, T max);

		T eval();
	};

	template <class T>
	class p_expr_t {
	private:
		std::variant<std::unique_ptr<op_t<T>>, std::raw_ptr<var_t<T>>, const_t<T>> expr;

	public:
		p_expr_t(p_expr_t<T>&& in);
		p_expr_t<T>& operator= (p_expr_t<T>&& in);

		p_expr_t(std::unique_ptr<op_t<T>> op);
		p_expr_t(std::raw_ptr<var_t<T>> var);
		p_expr_t(const_t<T> cst);

		T eval();
	};

	template <class T>
	class op_t {
	public:
		virtual T eval() = 0;
		virtual ~op_t() = 0;
	};
}

#endif // EXPRESSION_H_INCLUDED
