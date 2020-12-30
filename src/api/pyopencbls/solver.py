from __future__ import annotations
import enum
from abc import abstractmethod

from . import capi

class Algorithm(enum.Enum):
    SIMPLE_HILL_CLIMBING = 'simple hill climbing'
    TABU_SEARCH = 'tabu search'

class IntConstraint:
    @abstractmethod
    def _get(self):
        return None

class IntExpression:
    @abstractmethod
    def _get(self):
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

    def _get(self):
        return capi.int_add_constant(self._value)

    def value(self) -> int:
        return self._value

class IntVar(IntExpression):
    def __init__(self, internal) -> None:
        self._internal = internal

    def _get(self):
        return capi.int_get_variable_expression(self._internal)

    def value(self) -> int:
        return capi.int_get_variable_value(self._internal)

class IntOperation(IntExpression):
    pass

class IntSolver:
    def __init__(self, algo_name: Algorithm) -> None:
        self._internal = capi.int_get_solver(algo_name.value)

    def add_variable(self, min: int, max: int) -> IntVar:
        return IntVar(capi.int_add_variable(self._internal, min, max))

    def add_constraint(self, constraint: IntConstraint) -> None:
        capi.int_add_constraint(self._internal, constraint._get())

    def solve(self) -> None:
        capi.int_solve(self._internal)
        # capi.print_violation(self._internal)

    def close(self) -> None:
        capi.int_close_solver(self._internal)
        self._internal = None

    def __enter__(self) -> IntSolver:
        return self

    def __exit__(self, type, value, traceback) -> None:
        self.close()