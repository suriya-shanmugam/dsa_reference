The `typing` module in Python provides **type hints**, allowing you to specify the expected types of variables, function parameters, and return values. Type hints improve code readability, enable better IDE support, and allow static type checkers like **mypy**, **Pyright**, or **PyCharm** to detect bugs before runtime.

> **Important:** Python remains **dynamically typed**. Type hints are not enforced at runtime unless additional libraries are used.

---

# 1. Basic Type Hints

## Variables

```python
name: str = "Alice"
age: int = 25
salary: float = 50000.5
is_active: bool = True
```

Without type hints:

```python
name = "Alice"
```

---

## Function Annotations

```python
def add(a: int, b: int) -> int:
    return a + b
```

Example

```python
result = add(10, 20)
```

The `-> int` specifies the return type.

---

# 2. Built-in Collection Types (Python 3.9+)

Instead of importing from `typing`, use built-in generics.

```python
numbers: list[int] = [1, 2, 3]

names: set[str] = {"Alice", "Bob"}

mapping: dict[str, int] = {
    "Alice": 90,
    "Bob": 80
}

coordinates: tuple[int, int] = (10, 20)
```

Older versions (<3.9)

```python
from typing import List, Dict, Set, Tuple

numbers: List[int]
```

Interview Tip:

> Python 3.9 introduced built-in generic types like `list[int]`.

---

# 3. Union

Represents multiple possible types.

```python
from typing import Union

def process(x: Union[int, str]):
    print(x)
```

Python 3.10+

```python
def process(x: int | str):
    print(x)
```

Example

```python
process(10)
process("hello")
```

Interview favorite:
Difference between

```python
int | str
```

and

```python
Union[int, str]
```

Answer:
They are equivalent in Python 3.10+.

---

# 4. Optional

Represents a value or `None`.

```python
from typing import Optional

def greet(name: Optional[str]) -> None:
    print(name)
```

Equivalent to

```python
str | None
```

Example

```python
greet(None)
greet("Alice")
```

Interview question:
Is `Optional[T]` optional parameter?

No.

This

```python
def f(x: Optional[int]):
```

means

```python
x: int | None
```

It does **not** make the argument optional.

Optional argument means

```python
def f(x: int = 0):
```

---

# 5. Any

```python
from typing import Any

def process(data: Any):
    pass
```

Accepts everything.

```python
process(10)
process("abc")
process([])
```

Use sparingly because static type checking becomes ineffective.

---

# 6. Type Alias

```python
UserId = int

def get_user(id: UserId):
    pass
```

More complex

```python
Vector = list[float]
```

Interview use:
Improves readability.

---

# 7. Literal

Restricts values.

```python
from typing import Literal

def set_mode(mode: Literal["read", "write"]):
    pass
```

Allowed

```python
set_mode("read")
```

Static checker error

```python
set_mode("delete")
```

---

# 8. Final

Prevent reassignment.

```python
from typing import Final

PI: Final = 3.14159
```

Static checkers complain if reassigned.

```python
PI = 5
```

---

# 9. ClassVar

Class variables.

```python
from typing import ClassVar

class Student:
    school: ClassVar[str] = "ABC School"

    def __init__(self):
        self.name: str = ""
```

Without `ClassVar`, static checkers assume it is an instance attribute.

---

# 10. Annotated

Attach metadata.

```python
from typing import Annotated

age: Annotated[int, "Must be positive"]
```

Frameworks like FastAPI and Pydantic use this heavily.

Example

```python
from typing import Annotated

x: Annotated[int, "greater than zero"]
```

---

# 11. Sequence vs List

```python
from typing import Sequence

def total(nums: Sequence[int]):
    return sum(nums)
```

Accepts

```python
[1,2,3]
(1,2,3)
range(10)
```

Better than

```python
list[int]
```

because it is more flexible.

Interview Tip

Use the least restrictive type possible.

---

# 12. Iterable

```python
from typing import Iterable

def print_all(items: Iterable[int]):
    for x in items:
        print(x)
```

Accepts

* list
* tuple
* set
* generators

---

# 13. Iterator

```python
from typing import Iterator

def counter() -> Iterator[int]:
    yield 1
    yield 2
```

Difference

Iterable

```python
for x in iterable
```

Iterator

```python
next(iterator)
```

Interview favorite.

---

# 14. Generator

```python
from typing import Generator

def numbers() -> Generator[int, None, None]:
    yield 1
    yield 2
```

Generator

```python
Generator[YieldType, SendType, ReturnType]
```

Example

```python
Generator[int, str, bool]
```

means

* yields int
* accepts str via send()
* returns bool

---

# 15. Callable

Function types.

```python
from typing import Callable

def operate(func: Callable[[int, int], int]):
    print(func(2, 3))
```

Example

```python
operate(lambda a, b: a + b)
```

Interview question

Difference

```python
Callable[..., int]
```

vs

```python
Callable[[int], int]
```

---

# 16. TypeVar (Generics)

Most important interview topic.

```python
from typing import TypeVar

T = TypeVar("T")
```

Generic function

```python
def first(items: list[T]) -> T:
    return items[0]
```

Usage

```python
first([1,2,3])
first(["A","B"])
```

---

Generic class

```python
from typing import Generic

T = TypeVar("T")

class Stack(Generic[T]):
    def __init__(self):
        self.items: list[T] = []

    def push(self, item: T):
        self.items.append(item)

    def pop(self) -> T:
        return self.items.pop()
```

---

# 17. Protocol (Structural Typing)

Very common interview question.

```python
from typing import Protocol

class Drawable(Protocol):
    def draw(self) -> None:
        ...
```

Any class with

```python
draw()
```

matches the protocol.

```python
class Circle:
    def draw(self):
        print("circle")
```

No inheritance needed.

This is called **duck typing with static checking**.

---

# 18. TypedDict

Dictionary with fixed keys.

```python
from typing import TypedDict

class Employee(TypedDict):
    name: str
    age: int
```

Usage

```python
emp: Employee = {
    "name": "Alice",
    "age": 30
}
```

Better than

```python
dict[str, Any]
```

---

# 19. NamedTuple

```python
from typing import NamedTuple

class Point(NamedTuple):
    x: int
    y: int
```

Usage

```python
p = Point(10,20)

print(p.x)
```

Immutable.

---

# 20. NewType

Creates distinct logical types.

```python
from typing import NewType

UserId = NewType("UserId", int)

OrderId = NewType("OrderId", int)
```

Even though both are integers, type checkers treat them as different.

---

# 21. Overload

Useful when a function has multiple valid signatures.

```python
from typing import overload

@overload
def func(x: int) -> int: ...

@overload
def func(x: str) -> str: ...

def func(x):
    return x
```

Type checkers infer the correct return type based on the input.

---

# 22. Self (Python 3.11+)

```python
from typing import Self

class Builder:
    def set_name(self) -> Self:
        return self
```

Supports fluent APIs.

---

# 23. Never / NoReturn

Function never returns.

```python
from typing import Never

def fail() -> Never:
    raise Exception()
```

Older versions

```python
NoReturn
```

---

# 24. TypeGuard

Useful for custom type narrowing.

```python
from typing import TypeGuard

def is_str(x: object) -> TypeGuard[str]:
    return isinstance(x, str)
```

Usage

```python
if is_str(value):
    value.upper()
```

---

# 25. Casting

```python
from typing import cast

value = cast(str, obj)
```

Only affects static type checking.

---

# Frequently Asked Interview Questions

| Question                                                 | Answer                                                                                                                |        |
| -------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------- | ------ |
| Is Python statically typed?                              | No, it is dynamically typed; type hints are optional and mainly for static analysis.                                  |        |
| Do type hints affect runtime?                            | No, not by themselves.                                                                                                |        |
| Difference between `Any` and `object`?                   | `Any` disables type checking; `object` is the common base type, and operations require explicit narrowing or casting. |        |
| Difference between `list[int]` and `Sequence[int]`?      | `list[int]` requires a list; `Sequence[int]` accepts any read-only sequence such as lists, tuples, or ranges.         |        |
| Difference between `Iterable` and `Iterator`?            | An `Iterable` can produce an iterator; an `Iterator` is stateful and supports `next()`.                               |        |
| Difference between `Union` and `Optional`?               | `Optional[T]` is shorthand for `Union[T, None]` or `T                                                                 | None`. |
| Difference between `TypedDict` and `dict`?               | `TypedDict` specifies expected keys and value types for better static checking.                                       |        |
| Difference between `Protocol` and abstract base classes? | `Protocol` uses structural typing (matching by methods), while abstract base classes require inheritance.             |        |
| What is `TypeVar`?                                       | A way to write generic functions and classes while preserving type information.                                       |        |
| What is `NewType`?                                       | Creates distinct logical types for static checking without runtime overhead.                                          |        |

## High-Priority Topics for Technical Interviews

If you're preparing for Python interviews (especially at product companies), prioritize these concepts:

1. Basic type hints (`int`, `str`, `list[int]`, `dict[str, int]`)
2. `Union` (`|`) and `Optional`
3. `Any` vs `object`
4. `Sequence`, `Iterable`, and `Iterator`
5. `Callable`
6. `TypeVar` and generic classes/functions
7. `Protocol` (structural typing)
8. `TypedDict`
9. `Literal`
10. `cast`, `TypeGuard`, and `Self` (common in modern Python codebases)
