from __future__ import annotations
from abc import abstractmethod
from ctypes import c_void_p, c_int32, c_char_p

from .api import lib

class IntExpression:
    @abstractmethod
    def get(self) -> c_void_p:
        return c_void_p(0)

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

    def get(self) -> c_void_p:
        return lib.int_add_constant(self._value)

class IntVar(IntExpression):
    _internal: c_void_p

    def __init__(self, internal: c_void_p) -> None:
        self._internal = internal

    def get(self) -> c_void_p:
        return lib.int_get_variable_expression(c_void_p(self._internal))

    def value(self) -> int:
        return lib.int_get_variable_value(c_void_p(self._internal))

class IntOperation(IntExpression):
    pass

class IntConstraint:
    @abstractmethod
    def get(self) -> c_void_p:
        return c_void_p(0)

class IntSolver:
    _internal: c_void_p

    def __init__(self, algo_name: str) -> None:
        self._internal = lib.int_get_solver(c_char_p(algo_name.encode('utf8')))

    def add_variable(self, min: int, max: int) -> IntVar:
        return IntVar(lib.int_add_variable(c_void_p(self._internal), c_int32(min), c_int32(max)))

    def add_constraint(self, constraint: IntConstraint) -> None:
        lib.int_add_constraint(c_void_p(self._internal), c_void_p(constraint.get()))

    def solve(self) -> None:
        lib.int_solve(c_void_p(self._internal))
        lib.print_violation(c_void_p(self._internal))
