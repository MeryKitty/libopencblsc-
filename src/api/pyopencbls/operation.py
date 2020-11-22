from ctypes import c_void_p

from .api import lib
from .solver import IntExpression, IntOperation

class IntOpAdd(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def get(self) -> c_void_p:
        return lib.int_op_add(c_void_p(self._operand1.get()), c_void_p(self._operand2.get()))

class IntOpSub(IntOperation):
    _operand1: IntExpression
    _operand2: IntExpression

    def __init__(self, operand1: IntExpression, operand2: IntExpression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def get(self) -> c_void_p:
        return lib.int_op_sub(c_void_p(self._operand1.get()), c_void_p(self._operand2.get()))