from opencbls import solver, constraint

def queenmain():
    n = int(input())
<<<<<<< HEAD
    _solver = solver.IntSolver('simple hill climbing')
    # vars: list[solver.IntVar]
=======
    _solver = solver.IntSolver(solver.Algorithm.SIMPLE_HILL_CLIMBING)
    vars: list[solver.IntVar]
>>>>>>> aa61356a8da617cf5f3c3182094342ca8db26d90
    vars = []
    for i in range(n):
        vars.append(_solver.add_variable(0, n))

    first_constraint = constraint.IntAllNotEqual(vars)
    _solver.add_constraint(first_constraint)

    # second_constraint_operands: list[solver.IntExpression]
    second_constraint_operands = []
    for i, var in enumerate(vars):
        second_constraint_operands.append(i + var)
    second_constraint = constraint.IntAllNotEqual(second_constraint_operands)
    _solver.add_constraint(second_constraint)

    # third_constraint_operands: list[solver.IntExpression]
    third_constraint_operands = []
    for i, var in enumerate(vars):
        third_constraint_operands.append(i - var)
    third_constraint = constraint.IntAllNotEqual(third_constraint_operands)
    _solver.add_constraint(third_constraint)
    _solver.solve()

    for i in range(n):
        print(vars[i].value())

def inequation():
    _solver = solver.IntSolver(solver.Algorithm.SIMPLE_HILL_CLIMBING)
    s = _solver.add_variable(30, 2000)
    p = _solver.add_variable(20, 1500)
    _solver.add_constraint(s // 5 + p * 3 // 10 <= 400)
    _solver.solve()
    print(s.value())
    print(p.value())

if __name__ == "__main__":
    queenmain()
