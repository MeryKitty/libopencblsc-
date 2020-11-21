import ctypes

so_file = "./build/libopencblscpp.so"

lib = ctypes.CDLL(so_file)
lib.get_int_solver.restype = ctypes.c_void_p
lib.add_int_variable.restype = ctypes.c_void_p
lib.add_int_constant.restype = ctypes.c_void_p
lib.get_int_variable.restype = ctypes.c_void_p
lib.get_int_variable_value.restype = ctypes.c_int32

lib.op_add_int.restype = ctypes.c_void_p
lib.op_sub_int.restype = ctypes.c_void_p
lib.constraint_all_not_equal.restype = ctypes.c_void_p