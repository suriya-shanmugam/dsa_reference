# Core Java — OOP Foundations

---

# 1. Class

## Explanation

A **class** is a blueprint for creating objects.

It defines:

```
fields (variables)
methods (functions)
constructors
```

Example analogy:

```
Class → Blueprint of house
Object → Actual house
```

---

## Basic Syntax

```java
class Car {

    String name;
    int speed;

    void start(){
        System.out.println(name + " started");
    }

}
```

---

## Creating Object

```java
Car c = new Car();

c.name = "Tesla";
c.speed = 100;

c.start();
```

---

## Important Notes

Access members using:

```
object.member
```

Example:

```
c.speed
c.start()
```

---

## Caution

Every Java program must have **at least one class**.

---

# 2. Object

## Explanation

An **object** is an instance of a class.

It contains:

```
state (fields)
behavior (methods)
```

Example:

```java
Car c = new Car();
```

Here:

```
Car → class
c → object reference
new Car() → object creation
```

---

## Object Creation Steps

```
1 allocate memory
2 call constructor
3 return reference
```

Example:

```java
Car c = new Car();
```

---

## Important Notes

Multiple objects share **same class definition** but have **different states**.

Example:

```java
Car c1 = new Car();
Car c2 = new Car();
```

---

# 3. Constructors

## Explanation

A **constructor** initializes objects.

Rules:

```
same name as class
no return type
called automatically
```

---

## Default Constructor

Java provides one automatically.

```java
class Car {

}
```

Equivalent to:

```java
Car(){
}
```

---

## Parameterized Constructor

```java
class Car {

    String name;

    Car(String name){
        this.name = name;
    }

}
```

Usage:

```java
Car c = new Car("Tesla");
```

---

## Important Concepts

### `this` Keyword

Refers to **current object**.

```java
this.name = name;
```

---

## Constructor Overloading

```java
class Car {

    String name;
    int speed;

    Car(){}

    Car(String name){
        this.name = name;
    }

    Car(String name, int speed){
        this.name = name;
        this.speed = speed;
    }
}
```

---

## Caution

Constructors **cannot be inherited**.

---

# 4. Encapsulation

## Explanation

Encapsulation means **hiding internal state** and exposing controlled access.

Usually done with:

```
private variables
public getters/setters
```

---

## Example

```java
class BankAccount {

    private int balance;

    public int getBalance(){
        return balance;
    }

    public void deposit(int amount){
        balance += amount;
    }
}
```

---

## Benefits

```
data protection
controlled modification
clean API
```

---

# 5. Inheritance

## Explanation

Allows one class to **inherit properties from another class**.

Keyword:

```
extends
```

---

## Example

```java
class Vehicle {

    void start(){
        System.out.println("Vehicle starting");
    }
}

class Car extends Vehicle {

}
```

Usage:

```java
Car c = new Car();
c.start();
```

---

## Important Notes

Java supports:

```
single inheritance
multilevel inheritance
hierarchical inheritance
```

Java **does NOT support multiple inheritance with classes**.

---

## Method Overriding

```java
class Animal {

    void sound(){
        System.out.println("Animal sound");
    }
}

class Dog extends Animal {

    @Override
    void sound(){
        System.out.println("Bark");
    }
}
```

---

# 6. Polymorphism

## Explanation

Polymorphism means **same method behaves differently**.

Two types:

```
Compile-time polymorphism
Runtime polymorphism
```

---

## Method Overloading

Same method name with different parameters.

```java
class MathUtil {

    int add(int a, int b){
        return a + b;
    }

    int add(int a, int b, int c){
        return a + b + c;
    }
}
```

---

## Method Overriding

Occurs in inheritance.

```java
class Dog extends Animal {

    @Override
    void sound(){
        System.out.println("Bark");
    }
}
```

---

# 7. Abstraction

## Explanation

Abstraction hides **implementation details** and exposes **essential behavior**.

Two ways:

```
abstract class
interface
```

---

# 8. Abstract Classes

## Explanation

Abstract class provides **partial implementation**.

It may contain:

```
abstract methods
normal methods
fields
constructors
```

---

## Example

```java
abstract class Animal {

    abstract void sound();

    void sleep(){
        System.out.println("Sleeping");
    }
}
```

Subclass:

```java
class Dog extends Animal {

    void sound(){
        System.out.println("Bark");
    }
}
```

---

## Important Notes

Cannot instantiate:

```java
Animal a = new Animal(); // ❌
```

Valid:

```java
Animal a = new Dog();
```

---

# 9. Interfaces

## Explanation

An interface defines a **contract**.

Classes must implement all methods.

---

## Syntax

```java
interface Animal {

    void sound();

}
```

Implementation:

```java
class Dog implements Animal {

    public void sound(){
        System.out.println("Bark");
    }
}
```

---

## Default Methods

```java
interface Animal {

    default void sleep(){
        System.out.println("Sleeping");
    }
}
```

---

## Static Methods

```java
interface Util {

    static int add(int a,int b){
        return a+b;
    }
}
```

Usage:

```java
Util.add(3,4);
```

---

# 10. Interface vs Abstract Class

| Feature              | Interface          | Abstract Class      |
| -------------------- | ------------------ | ------------------- |
| Multiple inheritance | ✔                  | ❌                   |
| Constructors         | ❌                  | ✔                   |
| Fields               | constants only     | any                 |
| Methods              | abstract + default | abstract + concrete |

---

# Important Interview Concepts

### 1. `super` Keyword

Used to call parent methods.

```java
super.start();
```

---

### 2. Object Equality

Override `equals()`.

Example from your code:

```java
@Override
public boolean equals(Object o){

    if(this == o) return true;

    if(!(o instanceof Car)) return false;

    Car c = (Car) o;

    return name.equals(c.name);
}
```

---

### 3. `instanceof`

Check object type.

```java
if(obj instanceof Car)
```

---
