/*
 * numeric_constraint.h
 *
 *  Created on: 30 Oct 2020
 *      Author: MeryKitty
 */

#ifndef MODEL_NUMERIC_CONSTRAINT_H_INCLUDED
#define MODEL_NUMERIC_CONSTRAINT_H_INCLUDED

#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	class constraint_equal : public constraint_t<T> {
	private:
		p_expr_t<T> operand1;
		p_expr_t<T> operand2;
	public:
		constraint_equal(p_expr_t<T> operand1, p_expr_t<T> operand2);

		T violation();
	};

	template <class T>
	class constraint_not_equal : public constraint_t<T> {
	private:
		p_expr_t<T> operand1;
		p_expr_t<T> operand2;
	public:
		constraint_not_equal(p_expr_t<T> operand1, p_expr_t<T> operand2);

		T violation();
	};
}

#endif /* MODEL_NUMERIC_CONSTRAINT_H_INCLUDED */
