## 🔹 1. What is a Dictionary?

A **dictionary** is an **unordered collection of key-value pairs**.

* **Keys** → unique and immutable (like strings, numbers, tuples)
* **Values** → can be any Python object (mutable or immutable)
* **Mutable** → you can add, update, or delete items

---

## 🔹 2. Creating Dictionaries

```python
# Using curly braces
person = {
    'name': 'Alice',
    'age': 25,
    'city': 'New York'
}
print(person)

# Using dict() constructor
person2 = dict(name='Bob', age=30)
print(person2)

# Empty dictionary
empty = {}
```

---

## 🔹 3. Accessing Values

```python
print(person['name'])  # Alice
print(person.get('age'))  # 25
print(person.get('country', 'USA'))  # USA (default value if key not found)
```

> `get()` is safer than `[]` because it won’t raise `KeyError`.

---

## 🔹 4. Adding & Updating Items

```python
person['email'] = 'alice@example.com'  # add new key
person['age'] = 26  # update existing key
print(person)
```

* Use `update()` to merge dictionaries:

```python
person.update({'city': 'Boston', 'phone': '123-456'})
print(person)
```

---

## 🔹 5. Removing Items

```python
del person['email']      # remove specific key
age = person.pop('age')  # remove key and get value
last_item = person.popitem()  # remove and return a random key-value pair
person.clear()           # remove all items
```

---

## 🔹 6. Dictionary Keys, Values, and Items

```python
person = {'name': 'Alice', 'age': 25, 'city': 'NY'}

print(person.keys())   # dict_keys(['name', 'age', 'city'])
print(person.values()) # dict_values(['Alice', 25, 'NY'])
print(person.items())  # dict_items([('name', 'Alice'), ('age', 25), ('city', 'NY')])
```

* Can iterate over keys, values, or key-value pairs:

```python
for key, value in person.items():
    print(key, value)
```

---

## 🔹 7. Membership Testing

```python
print('name' in person)   # True
print('email' not in person)  # True
```

* Checks **keys only**, not values.

---

## 🔹 8. Dictionary Comprehensions

Like list/set comprehensions:

```python
squares = {x: x**2 for x in range(5)}
print(squares)  # {0: 0, 1: 1, 2: 4, 3: 9, 4: 16}
```

---

## 🔹 9. Nested Dictionaries

Dictionaries can store other dictionaries:

```python
students = {
    'Alice': {'age': 25, 'grade': 'A'},
    'Bob': {'age': 22, 'grade': 'B'}
}

print(students['Alice']['grade'])  # A
```

---

## 🔹 10. Use Cases for Dictionaries

1. **Fast lookup by key**:

```python
phonebook = {'Alice': '123', 'Bob': '456'}
print(phonebook.get('Alice'))  # 123
```

2. **Counting / Frequency**:

```python
words = ['apple', 'banana', 'apple']
count = {}
for word in words:
    count[word] = count.get(word, 0) + 1
print(count)  # {'apple': 2, 'banana': 1}
```

3. **Mapping / Configuration**:

```python
config = {'host': 'localhost', 'port': 8080}
```

4. **Nested data storage** (JSON-like):

```python
data = {'users': [{'name': 'Alice'}, {'name': 'Bob'}]}
```

---

### 🔹 Summary of Key Dictionary Operations

| Operation             | Example                                   |
| --------------------- | ----------------------------------------- |
| Access                | `d[key]` or `d.get(key)`                  |
| Add/Update            | `d[key] = value`, `d.update({...})`       |
| Remove                | `del d[key]`, `d.pop(key)`, `d.popitem()` |
| Keys / Values / Items | `d.keys()`, `d.values()`, `d.items()`     |
| Membership            | `'key' in d`                              |
| Comprehension         | `{k: v for k, v in iterable}`             |

---
