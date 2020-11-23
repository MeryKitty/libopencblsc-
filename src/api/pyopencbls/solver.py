from __future__ import annotations
import enum
from abc import abstractmethod
from ctypes import c_void_p, c_int32, c_char_p

from .api import lib

class Algorithm(enum.Enum):
    SIMPLE_HILL_CLIMBING = 'simple hill climbing'

class IntConstraint:
    @abstractmethod
    def _get(self) -> c_void_p:
        return None

class IntExpression:
    @abstractmethod
    def _get(self) -> c_void_p:
        return None

    def __add__(self, other) -> IntExpression:
        from .operation import IntAdd
        if isinstance(other, IntExpression):
            return IntAdd(self, other)
        elif isinstance(other, int):
            return IntAdd(self, IntConstant(other))
        else:
            return NotImplemented

    def __radd__(self, other) -> IntExpression:
        from .operation import IntAdd
        if isinstance(other, int):
            return IntAdd(IntConstant(other), self)
        elif isinstance(other, IntExpression):
            raise AssertionError()
        else:
            return NotImplemented

    def __sub__(self, other) -> IntExpression:
        from .operation import IntSub
        if isinstance(other, IntExpression):
            return IntSub(self, other)
        elif isinstance(other, int):
            return IntSub(self, IntConstant(other))
        else:
            return NotImplemented

    def __rsub__(self, other) -> IntExpression:
        from .operation import IntSub
        if isinstance(other, int):
            return IntSub(IntConstant(other), self)
        elif isinstance(other, IntExpression):
            raise AssertionError()
        else:
            return NotImplemented

    def __mul__(self, other) -> IntExpression:
        from .operation import IntMul
        if isinstance(other, IntExpression):
            return IntMul(self, other)
        elif isinstance(other, int):
            return IntMul(self, IntConstant(other))
        else:
            return NotImplemented

    def __rmul__(self, other) -> IntExpression:
        from .operation import IntMul
        if isinstance(other, int):
            return IntMul(IntConstant(other), self)
        elif isinstance(other, IntExpression):
            raise AssertionError()
        else:
            return NotImplemented

    def __floordiv__(self, other) -> IntExpression:
        from .operation import IntDiv
        if isinstance(other, IntExpression):
            return IntDiv(self, other)
        elif isinstance(other, int):
            return IntDiv(self, IntConstant(other))
        else:
            return NotImplemented

    def __rfloordiv__(self, other) -> IntExpression:
        from .operation import IntDiv
        if isinstance(other, int):
            return IntDiv(IntConstant(other), self)
        elif isinstance(other, IntExpression):
            raise AssertionError()
        else:
            return NotImplemented

    def __eq__(self, other) -> IntConstraint:
        from .constraint import IntEqual
        if isinstance(other, IntExpression):
            return IntEqual(self, other)
        elif isinstance(other, int):
            return IntEqual(self, IntConstant(other))
        else:
            return NotImplemented

    def __ne__(self, other) -> IntConstraint:
        from .constraint import IntNotEqual
        if isinstance(other, IntExpression):
            return IntNotEqual(self, other)
        elif isinstance(other, int):
            return IntNotEqual(self, IntConstant(other))
        else:
            return NotImplemented

    def __lt__(self, other) -> IntConstraint:
        from .constraint import IntLessThan
        if isinstance(other, IntExpression):
            return IntLessThan(self, other)
        elif isinstance(other, int):
            return IntLessThan(self, IntConstant(other))
        else:
            return NotImplemented

    def __gt__(self, other) -> IntConstraint:
        from .constraint import IntMoreThan
        if isinstance(other, IntExpression):
            return IntMoreThan(self, other)
        elif isinstance(other, int):
            return IntMoreThan(self, IntConstant(other))
        else:
            return NotImplemented

    def __le__(self, other) -> IntConstraint:
        from .constraint import IntNotMoreThan
        if isinstance(other, IntExpression):
            return IntNotMoreThan(self, other)
        elif isinstance(other, int):
            return IntNotMoreThan(self, IntConstant(other))
        else:
            return NotImplemented

    def __ge__(self, other) -> IntConstraint:
        from .constraint import IntNotLessThan
        if isinstance(other, IntExpression):
            return IntNotLessThan(self, other)
        elif isinstance(other, int):
            return IntNotLessThan(self, IntConstant(other))
        else:
            return NotImplemented

class IntConstant(IntExpression):
    _value: int

    def __init__(self, value: int) -> None:
        self._value = value

    def _get(self) -> c_void_p:
        return lib.int_add_constant(c_int32(self._value))

class IntVar(IntExpression):
    _internal: c_void_p

    def __init__(self, internal: c_void_p) -> None:
        self._internal = internal

    def _get(self) -> c_void_p:
        return lib.int_get_variable_expression(c_void_p(self._internal))

    def value(self) -> int:
        return lib.int_get_variable_value(c_void_p(self._internal))

class IntOperation(IntExpression):
    pass

class IntSolver:
    _internal: c_void_p

    def __init__(self, algo_name: Algorithm) -> None:
        self._internal = lib.int_get_solver(c_char_p(algo_name.value.encode('utf8')))

    def add_variable(self, min: int, max: int) -> IntVar:
        return IntVar(lib.int_add_variable(c_void_p(self._internal), c_int32(min), c_int32(max)))

    def add_constraint(self, constraint: IntConstraint) -> None:
        lib.int_add_constraint(c_void_p(self._internal), c_void_p(constraint._get()))

    def solve(self) -> None:
        lib.int_solve(c_void_p(self._internal))

    def close(self) -> None:
        lib.int_close_solver(c_void_p(self._internal))
        self._internal = None

    def __enter__(self) -> IntSolver:
        return self

    def __exit__(self, type, value, traceback) -> None:
        self.close()