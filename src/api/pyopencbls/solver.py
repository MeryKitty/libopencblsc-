from __future__ import annotations
from abc import abstractmethod

from . import capi

class IntExpression:
    @abstractmethod
    def _get(self):
        return None

    def __add__(self, other: IntExpression) -> IntExpression:
        from .operation import IntAdd
        return IntAdd(self, other)

    def __sub__(self, other: IntExpression) -> IntExpression:
        from .operation import IntSub
        return IntSub(self, other)

class IntConstant(IntExpression):
    _value: int

    def __init__(self, value: int) -> None:
        self._value = value

    def _get(self):
        return capi.int_add_constant(self._value)

class IntVar(IntExpression):
    def __init__(self, internal) -> None:
        self._internal = internal

    def _get(self):
        return capi.int_get_variable_expression(self._internal)

    def value(self) -> int:
        return capi.int_get_variable_value(self._internal)

class IntOperation(IntExpression):
    pass

class IntConstraint:
    @abstractmethod
    def _get(self):
        return None

class IntSolver:
    def __init__(self, algo_name: str) -> None:
        self._internal = capi.int_get_solver(algo_name)

    def add_variable(self, min: int, max: int) -> IntVar:
        return IntVar(capi.int_add_variable(self._internal, min, max))

    def add_constraint(self, constraint: IntConstraint) -> None:
        capi.int_add_constraint(self._internal, constraint._get())

    def solve(self) -> None:
        capi.int_solve(self._internal)
        capi.print_violation(self._internal)

    def close(self) -> None:
        capi.int_close_solver(self._internal)
        self._internal = None

    def __enter__(self) -> IntSolver:
        return self

    def __exit__(self, type, value, traceback) -> None:
        self.close()