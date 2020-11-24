#ifndef API_MODEL_H_INCLUDED
#define API_MODEL_H_INCLUDED

extern "C" {
	void* int_op_add(void* operand1, void* operand2);
	void* int_op_sub(void* operand1, void* operand2);
	void* int_op_mul(void* operand1, void* operand2);
	void* int_op_div(void* operand1, void* operand2);

	void* int_constraint_and(void* operand1, void* operand2);
	void* int_constraint_or(void* operand1, void* operand2);
	void* int_constraint_xor(void* operand1, void* operand2);
	void* int_constraint_not(void* operand);

	void* int_constraint_equal(void* operand1, void* operand2);
	void* int_constraint_not_equal(void* operand1, void* operand2);
	void* int_constraint_less_than(void* operand1, void* operand2);
	void* int_constraint_more_than(void* operand1, void* operand2);
	void* int_constraint_not_more_than(void* operand1, void* operand2);
	void* int_constraint_not_less_than(void* operand1, void* operand2);

	void* int_constraint_all_not_equal(int operand_num, void* operands);
}

#endif /* API_MODEL_H_INCLUDED */
