import ctypes

from .api import lib
from .solver import Expression, Operation

class OpAdd(Operation):
    _operand1: Expression
    _operand2: Expression

    def __init__(self, operand1: Expression, operand2: Expression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def get(self) -> ctypes.c_void_p:
        return lib.op_add_int(ctypes.c_void_p(self._operand1.get()), ctypes.c_void_p(self._operand2.get()))

class OpSub(Operation):
    _operand1: Expression
    _operand2: Expression

    def __init__(self, operand1: Expression, operand2: Expression) -> None:
        self._operand1 = operand1
        self._operand2 = operand2

    def get(self) -> ctypes.c_void_p:
        return lib.op_sub_int(ctypes.c_void_p(self._operand1.get()), ctypes.c_void_p(self._operand2.get()))