/*
 * combinatorial_constraint.h
 *
 *  Created on: 13 Nov 2020
 *      Author: MeryKitty
 */

#ifndef MODEL_COMBINATORIAL_CONSTRAINT_H_INCLUDED
#define MODEL_COMBINATORIAL_CONSTRAINT_H_INCLUDED

#include <vector>
#include "basics/constant.h"
#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	class constraint_all_not_equal : public constraint_t<T> {
	private:
		std::vector<expr_t<T>> _operands;
	protected:
		T violation_delta_helper(std::raw_ptr<var_t<T>> var, T value);
	public:
		constraint_all_not_equal(std::vector<expr_t<T>> operands);

		T violation();
	};
}



#endif /* SRC_MODEL_COMBINATORIAL_CONSTRAINT_H_INCLUDED */
