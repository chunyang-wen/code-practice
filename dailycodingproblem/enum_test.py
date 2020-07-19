from enum import Enum
from enum import auto, unique


@unique
class Access(Enum):
    Read = auto()
    Write = auto()


print(Access.Read.value)
print(Access.Write.value)
