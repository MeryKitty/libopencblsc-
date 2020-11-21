from __future__ import annotations
from abc import abstractmethod
import ctypes

from .api import lib

class Expression:
    @abstractmethod
    def get(self) -> ctypes.c_void_p:
        return ctypes.c_void_p(0)

    def __add__(self, other: Expression) -> Expression:
        from .operation import OpAdd
        return OpAdd(self, other)

    def __sub__(self, other: Expression) -> Expression:
        from .operation import OpSub
        return OpSub(self, other)

class Constant(Expression):
    _value: int

    def __init__(self, value: int) -> None:
        self._value = value

    def get(self) -> ctypes.c_void_p:
        return lib.add_int_constant(self._value)

class IntVar(Expression):
    _internal: ctypes.c_void_p

    def __init__(self, internal: ctypes.c_void_p) -> None:
        self._internal = internal

    def get(self) -> ctypes.c_void_p:
        return lib.get_int_variable(ctypes.c_void_p(self._internal))

    def value(self) -> int:
        return lib.get_int_variable_value(ctypes.c_void_p(self._internal))

class Operation(Expression):
    pass

class Constraint:
    @abstractmethod
    def get(self) -> ctypes.c_void_p:
        return ctypes.c_void_p(0)

class IntSolver:
    _internal: ctypes.c_void_p

    def __init__(self, algo_name: str) -> None:
        self._internal = lib.get_int_solver(ctypes.c_char_p(algo_name.encode('utf8')))

    def add_variable(self, min: int, max: int) -> IntVar:
        return IntVar(lib.add_int_variable(ctypes.c_void_p(self._internal), ctypes.c_int32(min), ctypes.c_int32(max)))

    def add_constraint(self, constraint: Constraint) -> None:
        lib.add_int_constraint(ctypes.c_void_p(self._internal), ctypes.c_void_p(constraint.get()))

    def solve(self) -> None:
        lib.solve_int(ctypes.c_void_p(self._internal))
