# Built-in generics
numbers :list[int] = []
names : set[str] = []
mapping : dict[str, int] = {
    1 : "Bob",
    2 : "Alice"
}
coordinates : tuple[int,int] = (1, 2)

# Union
x : str | int = 6

# Optional
x : str | None = None


# Older version
from typing import List, Dict, Set, Tuple
from typing import Union
from typing import Optional

# Used sparingly
from typing import Any

# Restricts values
from typing import Literal
mode: Literal["read", "write"] = "read"

# Final
from typing import Final

# iterable
from typing import Iterable

def print_all(items: Iterable[int]):
    for x in items:
        print(x)
