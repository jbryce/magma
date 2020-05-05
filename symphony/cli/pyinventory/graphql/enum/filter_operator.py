#!/usr/bin/env python3
# @generated AUTOGENERATED file. Do not Change!

from enum import Enum

class FilterOperator(Enum):
    IS = "IS"
    CONTAINS = "CONTAINS"
    IS_ONE_OF = "IS_ONE_OF"
    IS_NOT_ONE_OF = "IS_NOT_ONE_OF"
    DATE_GREATER_THAN = "DATE_GREATER_THAN"
    DATE_LESS_THAN = "DATE_LESS_THAN"
    MISSING_ENUM = ""

    @classmethod
    def _missing_(cls, value: str) -> "FilterOperator":
        return cls.MISSING_ENUM