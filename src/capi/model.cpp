/*
 * model.cpp
 *
 *  Created on: 21 Nov 2020
 *      Author: MeryKitty
 */

#include "model/expression.h"
#include "model/op_impl.h"
#include "model/constraint.h"
#include "model/combinatoric_constraint.h"

extern "C" {
	void* op_add_int(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::expr_t<int>(std::make_unique<opencbls::op_add<int>>(
				std::move(*_operand1), std::move(*_operand2)));
	}

	void* op_sub_int(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::expr_t<int>(std::make_unique<opencbls::op_sub<int>>(
				std::move(*_operand1), std::move(*_operand2)));
	}



	void* constraint_all_not_equal(int operand_num, void** operands) {
		std::vector<opencbls::expr_t<int>> _operands;
		for (std::size_t i = 0; i < operand_num; i++) {
			opencbls::expr_t<int>* _operand = (opencbls::expr_t<int>*) operands[i];
			_operands.emplace_back(std::move(*_operand));
		}
		return new opencbls::constraint_all_not_equal<int>(std::move(_operands));
	}
}

