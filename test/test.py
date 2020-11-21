import ctypes

def main():
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

    n = int(input())
    solver = lib.get_int_solver(ctypes.c_char_p("simple hill climbing".encode('utf8')))

    vars = []
    for i in range(n):
        vars.append(lib.add_int_variable(ctypes.c_void_p(solver), ctypes.c_int32(0), ctypes.c_int32(n)))
    
    first_constraint_operand_list = []
    for i in range(n):
        first_constraint_operand_list.append(lib.get_int_variable(ctypes.c_void_p(vars[i])))
    first_constraint_operands = (ctypes.c_void_p * n)(*first_constraint_operand_list)
    first_constraint = lib.constraint_all_not_equal(n, first_constraint_operands)
    lib.add_int_constraint(ctypes.c_void_p(solver), ctypes.c_void_p(first_constraint))

    second_constraint_operand_list = []
    for i in range(n):
        second_constraint_operand_list.append(lib.op_add_int(
                ctypes.c_void_p(lib.get_int_variable(ctypes.c_void_p(vars[i]))),
                ctypes.c_void_p(lib.add_int_constant(i))))
    second_constraint_operands = (ctypes.c_void_p * n)(*second_constraint_operand_list)
    second_constraint = lib.constraint_all_not_equal(n, second_constraint_operands)
    lib.add_int_constraint(ctypes.c_void_p(solver), ctypes.c_void_p(second_constraint))

    third_constraint_operand_list = []
    for i in range(n):
        third_constraint_operand_list.append(lib.op_sub_int(
                ctypes.c_void_p(lib.get_int_variable(ctypes.c_void_p(vars[i]))),
                ctypes.c_void_p(lib.add_int_constant(i))))
    third_constraint_operands = (ctypes.c_void_p * n)(*third_constraint_operand_list)
    third_constraint = lib.constraint_all_not_equal(n, third_constraint_operands)
    lib.add_int_constraint(ctypes.c_void_p(solver), ctypes.c_void_p(third_constraint))

    lib.solve_int(ctypes.c_void_p(solver))

    for i in range(n):
        print(lib.get_int_variable_value(ctypes.c_void_p(vars[i])))

if __name__ == "__main__":
    main()