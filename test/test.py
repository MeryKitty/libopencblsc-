import sys
sys.path.append('./src/api')

from pyopencbls import solver, constraint

def main():
    n = int(input())
    _solver = solver.IntSolver('simple hill climbing')
    vars: list[solver.IntVar]
    vars = []
    for i in range(n):
        vars.append(_solver.add_variable(0, n))

    first_constraint = constraint.IntAllNotEqual(vars)
    _solver.add_constraint(first_constraint)

    second_constraint_operands: list[solver.IntExpression]
    second_constraint_operands = []
    for i, var in enumerate(vars):
        second_constraint_operands.append(var + solver.IntConstant(i))
    second_constraint = constraint.IntAllNotEqual(second_constraint_operands)
    _solver.add_constraint(second_constraint)

    third_constraint_operands: list[solver.IntExpression]
    third_constraint_operands = []
    for i, var in enumerate(vars):
        third_constraint_operands.append(var - solver.IntConstant(i))
    third_constraint = constraint.IntAllNotEqual(second_constraint_operands)
    _solver.add_constraint(third_constraint)

    _solver.solve()

    for i in range(n):
        print(vars[i].value())


if __name__ == "__main__":
    main()