
# 1. Object-Oriented Programming (OOP)

## Explanation

OOP is a programming paradigm where software is designed using **objects and classes**.

Main idea:

```
Model real-world entities as objects
```

Java follows **4 core OOP principles**.

---

## The 4 Pillars of OOP

### 1. Encapsulation

Hide internal state and expose only controlled access.

```java
class Car {

    private int speed;

    public int getSpeed(){
        return speed;
    }

    public void setSpeed(int s){
        speed = s;
    }
}
```

---

### 2. Inheritance

Allows a class to **reuse properties of another class**.

```java
class Vehicle {

    void start(){
        System.out.println("Vehicle starting");
    }
}

class Car extends Vehicle{

}
```

Usage:

```java
Car c = new Car();
c.start();
```

---

### 3. Polymorphism

Same method behaves **differently depending on object**.

Two types:

```
Compile-time polymorphism (Method Overloading)
Runtime polymorphism (Method Overriding)
```

Example:

```java
class Animal {

    void sound(){
        System.out.println("Animal sound");
    }
}

class Dog extends Animal{

    @Override
    void sound(){
        System.out.println("Bark");
    }
}
```

---

### 4. Abstraction

Expose **only essential behavior**.

Hide implementation details.

Achieved using:

```
Abstract classes
Interfaces
```

---

## Important Notes

Method overriding rules:

```
same method name
same parameters
same or covariant return type
```

---

## Caution

Always use `@Override`.

It prevents accidental bugs.

---

# 2. Interfaces

## Explanation

Interface defines **a contract**.

It specifies **what a class must implement**.

---

## Key Concepts

Interfaces contain:

```
abstract methods
default methods
static methods
constants
```

By default:

```
methods → public abstract
variables → public static final
```

---

## Basic Syntax

```java
interface Animal{

    void sound();

}
```

Implementing class:

```java
class Dog implements Animal{

    public void sound(){
        System.out.println("Bark");
    }
}
```

---

## Default Methods

Java 8 introduced default methods.

```java
interface Animal{

    default void sleep(){
        System.out.println("Sleeping");
    }
}
```

---

## Static Methods

```java
interface MathUtil{

    static int add(int a, int b){
        return a + b;
    }
}
```

Usage:

```java
MathUtil.add(3,5);
```

---

## Important Notes

A class can implement **multiple interfaces**.

```java
class Robot implements Runnable, AutoCloseable
```

---

## Caution

Interface variables are always:

```
public static final
```

So this is invalid:

```java
int x;   // ❌ must initialize
```

---

# 3. Abstract Classes

## Explanation

Abstract class is a **partially implemented class**.

It can contain:

```
abstract methods
concrete methods
fields
constructors
```

---

## Syntax

```java
abstract class Animal{

    abstract void sound();

    void sleep(){
        System.out.println("Sleeping");
    }
}
```

Subclass:

```java
class Dog extends Animal{

    void sound(){
        System.out.println("Bark");
    }
}
```

---

## Important Notes

Abstract class **cannot be instantiated**.

```java
Animal a = new Animal(); // ❌
```

But reference allowed:

```java
Animal a = new Dog();
```

---

## When to Use

Use abstract class when:

```
classes share common code
base behavior exists
```

---

## Caution

Abstract class can have **constructors**.

---

# 4. Interface vs Abstract Class

| Feature              | Interface          | Abstract Class       |
| -------------------- | ------------------ | -------------------- |
| Multiple inheritance | Yes                | No                   |
| Methods              | Abstract + default | Abstract + concrete  |
| Variables            | Constants only     | Any type             |
| Constructors         | ❌                  | ✔                    |
| Use case             | Contract           | Shared base behavior |

---

# 5. Generics

## Explanation

Generics allow **type-safe reusable code**.

Without generics:

```java
ArrayList list = new ArrayList();
```

With generics:

```java
ArrayList<Integer> list = new ArrayList<>();
```

---

## Benefits

```
Type safety
No casting
Reusable code
Compile-time checks
```

---

## Generic Class

```java
class Box<T>{

    T value;

    void set(T val){
        value = val;
    }

    T get(){
        return value;
    }
}
```

Usage:

```java
Box<Integer> box = new Box<>();
box.set(10);
```

---

## Generic Methods

```java
public static <T> void printArray(T[] arr){

    for(T val : arr)
        System.out.println(val);
}
```

---

## Wildcards

### Unbounded

```java
List<?> list
```

### Upper Bound

```java
List<? extends Number>
```

### Lower Bound

```java
List<? super Integer>
```

---

## Important Notes

Generics work only with **objects**.

Invalid:

```java
List<int>  // ❌
```

Correct:

```java
List<Integer>
```

---

## Caution

Due to **type erasure**, generic type info removed at runtime.

---

# 6. Exception Handling

## Explanation

Exception handling manages **runtime errors gracefully**.

---

## Exception Hierarchy

```
Throwable
   |
   +-- Error
   |
   +-- Exception
         |
         +-- Checked
         +-- Unchecked
```

---

## Checked Exceptions

Must be handled at compile time.

Examples:

```
IOException
SQLException
```

---

## Unchecked Exceptions

Runtime exceptions.

Examples:

```
NullPointerException
ArrayIndexOutOfBoundsException
ArithmeticException
```

---

## Try-Catch

```java
try{

    int x = 10/0;

}catch(ArithmeticException e){

    System.out.println("Error");

}
```

---

## Multiple Catch

```java
try{

}
catch(IOException e){

}
catch(Exception e){

}
```

---

## Finally

Always executes.

```java
try{

}
catch(Exception e){

}
finally{

}
```

---

## Throw

Used to manually throw exception.

```java
throw new IllegalArgumentException("Invalid value");
```

---

## Throws

Declares exceptions in method.

```java
void readFile() throws IOException{

}
```

---

## Custom Exception

```java
class MyException extends Exception{

    MyException(String msg){
        super(msg);
    }
}
```

---

## Important Notes

Unchecked exceptions extend:

```
RuntimeException
```

---

## Caution

Avoid catching generic exception unless necessary.

Bad:

```java
catch(Exception e)
```

Prefer:

```java
catch(IOException e)
```

---
