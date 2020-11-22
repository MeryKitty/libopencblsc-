/*
 * model.cpp
 *
 *  Created on: 21 Nov 2020
 *      Author: MeryKitty
 */

#include "model/expression.h"
#include "model/op_impl.h"
#include "model/constraint.h"
#include "model/numeric_constraint.h"
#include "model/combinatoric_constraint.h"

extern "C" {
	void* int_op_add(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::expr_t<int>(std::make_unique<opencbls::op_add<int>>(
				std::move(*_operand1), std::move(*_operand2)));
	}

	void* int_op_sub(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::expr_t<int>(std::make_unique<opencbls::op_sub<int>>(
				std::move(*_operand1), std::move(*_operand2)));
	}

	void* int_op_mul(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::expr_t<int>(std::make_unique<opencbls::op_mul<int>>(
				std::move(*_operand1), std::move(*_operand2)));
	}

	void* int_op_div(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::expr_t<int>(std::make_unique<opencbls::op_div<int>>(
				std::move(*_operand1), std::move(*_operand2)));
	}

	void* int_constraint_and(void* operand1, void* operand2) {
		std::unique_ptr<opencbls::constraint_t<int>> _operand1((opencbls::constraint_t<int>*) operand1);
		std::unique_ptr<opencbls::constraint_t<int>> _operand2((opencbls::constraint_t<int>*) operand2);
		return new opencbls::constraint_and<int>(
				std::move(_operand1), std::move(_operand2));
	}	

	void* int_constraint_or(void* operand1, void* operand2) {
		std::unique_ptr<opencbls::constraint_t<int>> _operand1((opencbls::constraint_t<int>*) operand1);
		std::unique_ptr<opencbls::constraint_t<int>> _operand2((opencbls::constraint_t<int>*) operand2);
		return new opencbls::constraint_or<int>(
				std::move(_operand1), std::move(_operand2));
	}

	void* int_constraint_xor(void* operand1, void* operand2) {
		std::unique_ptr<opencbls::constraint_t<int>> _operand1((opencbls::constraint_t<int>*) operand1);
		std::unique_ptr<opencbls::constraint_t<int>> _operand2((opencbls::constraint_t<int>*) operand2);
		return new opencbls::constraint_xor<int>(
				std::move(_operand1), std::move(_operand2));
	}

	void* int_constraint_not(void* operand) {
		std::unique_ptr<opencbls::constraint_t<int>> _operand((opencbls::constraint_t<int>*) operand);
		return new opencbls::constraint_not<int>(
				std::move(_operand));
	}

	void* int_constraint_equal(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::constraint_equal<int>(std::move(*_operand1), std::move(*_operand2));
	}

	void* int_constraint_not_equal(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::constraint_not_equal<int>(std::move(*_operand1), std::move(*_operand2));
	}

	void* int_constraint_less_than(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::constraint_less_than<int>(std::move(*_operand1), std::move(*_operand2));
	}

	void* int_constraint_more_than(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::constraint_more_than<int>(std::move(*_operand1), std::move(*_operand2));
	}

	void* int_constraint_not_less_than(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::constraint_not_less_than<int>(std::move(*_operand1), std::move(*_operand2));
	}

	void* int_constraint_not_more_than(void* operand1, void* operand2) {
		opencbls::expr_t<int>* _operand1 = (opencbls::expr_t<int>*) operand1;
		opencbls::expr_t<int>* _operand2 = (opencbls::expr_t<int>*) operand2;
		return new opencbls::constraint_not_more_than<int>(std::move(*_operand1), std::move(*_operand2));
	}

	void* int_constraint_all_not_equal(int operand_num, void* operands) {
		void** poperands = (void**) operands;
		std::vector<opencbls::expr_t<int>> _operands;
		for (std::size_t i = 0; i < operand_num; i++) {
			opencbls::expr_t<int>* _operand = (opencbls::expr_t<int>*) poperands[i];
			_operands.emplace_back(std::move(*_operand));
		}
		return new opencbls::constraint_all_not_equal<int>(std::move(_operands));
	}
}

