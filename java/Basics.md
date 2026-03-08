Great. Let’s build this like a **real interview handbook**, not random notes.
We’ll structure it so you can **revise Java for interviews in ~30 minutes**.

I’ll organize it into **4 layers**:

1️⃣ Java Language Core
2️⃣ Collections Framework
3️⃣ Utility Classes (Arrays, String, Math, etc.)
4️⃣ Interview Coding Patterns

Each topic will follow your structure:

```
Explanation
Basic Methods
Code Snippets
Important Notes
Caution / Traps
```

---

# Java DSA Interview Handbook

---

# 1. Variables & Data Types

## Explanation

Java has **two main categories of data types**:

### Primitive Types

Stored directly in memory.

```
byte
short
int
long
float
double
char
boolean
```

Example:

```java
int a = 10;
double pi = 3.14;
char letter = 'A';
boolean flag = true;
```

---

### Reference Types

Objects stored in **heap memory**.

Examples:

```
String
Array
ArrayList
HashMap
Custom objects
```

---

## Important Notes

Primitive → stored in **stack**

Objects → reference in stack, data in **heap**

---

## Caution

Wrapper classes allow primitives to behave like objects.

```
int → Integer
double → Double
```

---

# 2. Wrapper Classes

## Explanation

Wrapper classes convert **primitive values into objects**.

Used because **Collections require objects**.

Example wrappers:

```
Integer
Double
Character
Boolean
Long
```

---

## Important Methods

```java
Integer.parseInt("123")

Integer.valueOf("123")

Double.isNaN(value)

Character.isDigit('7')

Character.isLetter('a')
```

---

## Example

```java
Integer x = 100;      // autoboxing
int y = x;            // unboxing

Integer num = Integer.parseInt("123");
```

---

## Important Notes

Autoboxing

```
int → Integer automatically
```

Unboxing

```
Integer → int automatically
```

---

## Caution

Never compare wrappers using `==`.

```java
Integer a = 128;
Integer b = 128;

System.out.println(a == b);      // false
System.out.println(a.equals(b)); // true
```

---

# 3. Control Flow

## Explanation

Control statements manage **execution flow**.

Types:

```
if
switch
loops
break
continue
ternary
```

---

## Basic Syntax

### If

```java
if(value > 0){
    System.out.println("Positive");
}
else if(value < 0){
}
else{
}
```

---

### Switch

```java
switch(day){

    case 1:
        System.out.println("Monday");
        break;

    default:
        System.out.println("Other");
}
```

---

### Ternary Operator

```java
String result = (num > 0) ? "Positive" : "Negative";
```

---

## Loops

### For Loop

```java
for(int i=0;i<5;i++){
    System.out.println(i);
}
```

### While

```java
while(index < 5){
    index++;
}
```

### Do While

```java
do{
    j++;
}while(j < 5);
```

---

## Important Notes

Enhanced for loop:

```java
for(int n : arr)
```

Works for

```
arrays
collections
```

---

## Caution

```
break → exits loop
continue → skips iteration
```

---

# 4. Arrays

## Explanation

Arrays store **fixed-size ordered elements**.

Properties:

```
contiguous memory
constant-time access
fixed size
```

---

## Important Methods

```java
Arrays.sort(arr)

Arrays.binarySearch(arr, key)

Arrays.fill(arr, value)

Arrays.copyOf(arr, length)

Arrays.toString(arr)
```

---

## Example

```java
int[] arr = {5,2,9,1};

Arrays.sort(arr);

System.out.println(Arrays.toString(arr));

int idx = Arrays.binarySearch(arr,5);
```

---

## Important Notes

Binary search requires **sorted array**.

```
Time Complexity = O(log n)
```

---

## Caution

Array size is fixed.

```
arr.length
```

NOT

```
arr.length()
```

---

# 5. Strings

## Explanation

Java strings are **immutable**.

Every modification creates **new object**.

---

## Important Methods

```java
length()

charAt(i)

substring(a,b)

contains()

indexOf()

replace()

split()

toCharArray()
```

---

## Example

```java
String s = "hello";

s.length();

s.charAt(1);

s.substring(1,4);

s.contains("ell");

s.indexOf("l");

s.replace("l","x");
```

---

## Important Notes

```
substring(start,end)
```

`end` is **exclusive**

---

## Caution

Avoid modifying strings in loops.

Bad:

```java
s = s + "a";
```

Good:

```
StringBuilder
```

---

# 6. StringBuilder

## Explanation

Mutable string.

Much faster for **repeated modifications**.

---

## Important Methods

```java
append()

insert()

delete()

deleteCharAt()

reverse()

toString()
```

---

## Example

```java
StringBuilder sb = new StringBuilder("hello");

sb.append(" world");

sb.insert(0,"Say ");

sb.deleteCharAt(2);

String result = sb.toString();
```

---

## Important Notes

Operations are **O(1) amortized**.

---

# 7. ArrayList

## Explanation

Dynamic array.

Internally resizes automatically.

---

## Important Methods

```java
add()

add(index,val)

get()

set()

remove()

contains()

size()

clear()

isEmpty()
```

---

## Example

```java
ArrayList<String> list = new ArrayList<>();

list.add("Apple");

list.add(0,"Orange");

list.get(1);

list.set(0,"Banana");

list.remove(1);
```

---

## Important Notes

Access:

```
O(1)
```

Insertion:

```
O(n)
```

---

## Caution

Removing during enhanced loop causes exception.

Wrong:

```java
for(Integer n : list){
    list.remove(n);
}
```

Correct:

```java
Iterator<Integer> it = list.iterator();
while(it.hasNext()){
    it.next();
    it.remove();
}
```

---

# 8. HashSet

## Explanation

Stores **unique values**.

Internally backed by **HashMap**.

---

## Important Methods

```java
add()

remove()

contains()

size()

clear()
```

---

## Example

```java
HashSet<String> set = new HashSet<>();

set.add("Apple");

set.add("Banana");

set.contains("Apple");
```

---

## Common Pattern — Duplicate Detection

```java
HashSet<String> seen = new HashSet<>();

for(String s : arr){
    if(!seen.add(s)){
        System.out.println("duplicate");
    }
}
```

---

# 9. HashMap

## Explanation

Stores **key-value pairs**.

Implemented using **hash table**.

---

## Important Methods

```java
put()

get()

containsKey()

getOrDefault()

remove()

keySet()

values()

entrySet()
```

---

## Example

```java
HashMap<String,Integer> map = new HashMap<>();

map.put("Apple",10);

map.get("Apple");

map.containsKey("Apple");
```

---

## Frequency Counting Pattern

```java
map.put(c, map.getOrDefault(c,0) + 1);
```

---

## Best Iteration

```java
for(Map.Entry<String,Integer> e : map.entrySet()){
    String key = e.getKey();
    Integer val = e.getValue();
}
```

---

# 10. Queue

## Explanation

FIFO structure.

---

## Important Methods

```java
offer()

poll()

peek()
```

---

## Example

```java
Queue<Integer> q = new LinkedList<>();

q.offer(1);

q.poll();

q.peek();
```

---

# 11. Deque (Stack + Queue)

## Explanation

Double-ended queue.

Better replacement for **Stack class**.

---

## Important Methods

Stack:

```
push
pop
peek
```

Queue:

```
addFirst
addLast
pollFirst
pollLast
```

---

## Example

```java
Deque<Integer> dq = new ArrayDeque<>();

dq.push(10);

dq.pop();

dq.peek();
```

---

# 12. PriorityQueue (Heap)

## Explanation

Heap-based priority structure.

Default = **Min Heap**

---

## Important Methods

```java
add()

offer()

peek()

poll()
```

---

## Min Heap

```java
PriorityQueue<Integer> pq = new PriorityQueue<>();
```

---

## Max Heap

```java
PriorityQueue<Integer> pq =
    new PriorityQueue<>(Collections.reverseOrder());
```

---

# 13. Sorting

## Explanation

Sorting arrays or collections.

---

## Important Methods

```java
Arrays.sort(arr)

Collections.sort(list)
```

---

## Custom Sorting

```java
nums.sort((a,b) -> a-b);

nums.sort((a,b) -> b-a);
```

---

# 14. Comparator vs Comparable

## Comparable

Defined inside class.

```java
class Car implements Comparable<Car>{

    public int compareTo(Car other){
        return this.name.compareTo(other.name);
    }
}
```

---

## Comparator

External comparison rule.

```java
students.sort((a,b) -> a.age - b.age);
```

---

# 15. Big-O Mental Model

| Structure     | Access    | Insert       | Delete        |
| ------------- | --------- | ------------ | ------------- |
| ArrayList     | O(1)      | O(n)         | O(n)          |
| LinkedList    | O(n)      | O(1)         | O(1)          |
| HashMap       | O(1)      | O(1)         | O(1)          |
| TreeMap       | O(log n)  | O(log n)     | O(log n)      |
| PriorityQueue | peek O(1) | add O(log n) | poll O(log n) |

---
