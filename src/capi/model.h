/*
 * model.h
 *
 *  Created on: 20 Nov 2020
 *      Author: MeryKitty
 */

#ifndef API_MODEL_H_INCLUDED
#define API_MODEL_H_INCLUDED

extern "C" {
	void* op_add_int(void* operand1, void* operand2);
	void* op_sub_int(void* operand1, void* operand2);

	void* constraint_all_not_equal(int operand_num, void** operands);
}

#endif /* API_MODEL_H_INCLUDED */
