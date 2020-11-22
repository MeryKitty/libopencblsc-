from ctypes import CDLL, c_void_p, c_int32

so_file = "./build/libopencblscpp.so"

lib = CDLL(so_file)
lib.int_get_solver.restype = c_void_p
lib.int_add_variable.restype = c_void_p
lib.int_add_constant.restype = c_void_p
lib.int_get_variable_expression.restype = c_void_p
lib.int_get_variable_value.restype = c_int32

lib.int_op_add.restype = c_void_p
lib.int_op_sub.restype = c_void_p
lib.int_constraint_all_not_equal.restype = c_void_p