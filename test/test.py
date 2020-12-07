from opencbls import solver, constraint

def queenmain():
    n = int(input())
    _solver = solver.IntSolver(solver.Algorithm.SIMPLE_HILL_CLIMBING)
    vars: list[solver.IntVar]
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

def sudoku():
    _solver = solver.IntSolver(solver.Algorithm.TABU_SEARCH)
    vars: list[list[solver.IntExpression]]
    vars = list()
    for i in range(9):
        vars.append(list())
        line = input().split()
        known = [int(_var) for _var in line]
        for j in range(9):
            temp = known[j]
            if temp == 0:
                vars[i].append(_solver.add_variable(0, 9))
            else:
                vars[i].append(solver.IntConstant(temp - 1))

    for i in range(9):
        _solver.add_constraint(constraint.IntAllNotEqual(vars[i]))
        _solver.add_constraint(constraint.IntAllNotEqual([vars[j][i] for j in range(9)]))
    
    for i in range(3):
        for j in range(3):
            operands: list[solver.IntExpression]
            operands = list()
            for k in range(3):
                for l in range(3):
                    operands.append(vars[i * 3 + k][j * 3 + l])
            _solver.add_constraint(constraint.IntAllNotEqual(operands))

    _solver.solve()

    for i in range(9):
        print()
        for j in range(9):
            print(str(vars[i][j].value()) + ' ', end = '')

if __name__ == "__main__":
    sudoku()
