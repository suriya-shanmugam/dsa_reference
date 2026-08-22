# Counting, Permutations, and Combinations — Reference Notes

## 1. Basic Counting Principle (Multiplication Rule)

The foundation of all counting problems is the **Multiplication Principle**.

> If one task can be done in **m** ways and another independent task can be done in **n** ways, then both tasks together can be done in:

\[
m \times n
\]

### Example

You have:

- 3 shirts
- 2 pants

Number of outfits:

\[
3 \times 2 = 6
\]

Reason:

- Shirt: 3 choices
- Pant: 2 choices

Total:

```
3 × 2 = 6
```

---

## 2. Factorial

Factorial counts the number of ways to arrange all distinct objects.

Definition:

\[
n! = n(n-1)(n-2)...3\times2\times1
\]

Examples:

\[
5! = 120
\]

\[
4! = 24
\]

\[
3! = 6
\]

Special case:

\[
0! = 1
\]

### Why factorial?

Arrange 4 people:

```
Position 1 → 4 choices
Position 2 → 3 choices
Position 3 → 2 choices
Position 4 → 1 choice
```

Multiply:

\[
4\times3\times2\times1=4!
\]

So factorial naturally counts **all possible arrangements**.

---

# 3. Permutations

A **Permutation** is an **ordered arrangement**.

**Order matters.**

Examples:

- Seating arrangements
- Race rankings
- Passwords
- Captain and Vice Captain

---

## Example

Arrange

```
A B C
```

Possible arrangements:

```
ABC
ACB
BAC
BCA
CAB
CBA
```

Total:

\[
3!=6
\]

---

## Derivation of the Permutation Formula

Suppose there are:

- n people
- r positions

Fill the positions one by one.

### Position 1

Choices:

```
n
```

### Position 2

One person already chosen.

Choices:

```
n−1
```

### Position 3

Choices:

```
n−2
```

Continue until r positions are filled.

Total arrangements:

\[
n(n-1)(n-2)...(n-r+1)
\]

---

## Writing the Product Using Factorials

Example:

\[
8\times7\times6
\]

Notice

\[
8!=8\times7\times6\times5!
\]

Divide by

\[
5!
\]

Result:

\[
\frac{8!}{5!}=8\times7\times6
\]

General formula:

\[
^nP_r=\frac{n!}{(n-r)!}
\]

---

## Example

Choose Captain and Vice Captain from 5 students.

```
Captain → 5 choices

Vice Captain → 4 choices
```

Total:

```
5×4=20
```

Formula:

\[
^5P_2=\frac{5!}{3!}=20
\]

---

# 4. Combinations

A **Combination** is a **selection**.

**Order does NOT matter.**

Examples:

- Choosing a committee
- Selecting a team
- Picking lottery numbers

---

## Example

Choose 2 students from

```
A B C
```

Possible groups:

```
AB
AC
BC
```

Notice

```
AB = BA
```

because only the members matter.

Total:

3 groups.

---

# Why Does Combination Divide by r!?

This is the most important idea.

Suppose the chosen group is

```
A B C
```

Permutation counts:

```
ABC
ACB
BAC
BCA
CAB
CBA
```

There are

\[
3!=6
\]

arrangements.

But they all represent the **same group**:

```
{A,B,C}
```

Permutation counts one group **6 times**.

Therefore:

```
Combination
=
Permutation ÷ 6
```

Since

\[
6=3!
\]

we divide by

\[
r!
\]

---

## General Proof

Permutation counts

\[
^nP_r
\]

ordered arrangements.

Each selected group can be internally rearranged in

\[
r!
\]

ways.

Therefore every group appears

\[
r!
\]

times.

So

\[
^nC_r
=
\frac{^nP_r}{r!}
\]

Substitute permutation formula:

\[
^nC_r
=
\frac{n!}{r!(n-r)!}
\]

---

# Understanding Why r! Appears

Suppose you select

```
A B C D
```

These four people can be arranged as

```
ABCD
ABDC
ACBD
...
```

Total arrangements:

\[
4!=24
\]

But every one of those arrangements represents exactly one group:

```
{A,B,C,D}
```

So permutation counts each group

24 times.

Therefore

```
Actual groups
=
Permutation ÷ 24
```

---

## Small Example

Choose 2 from

```
A B C
```

Permutation counts

```
AB
BA

AC
CA

BC
CB
```

There are

6 arrangements.

Groups are

```
AB

AC

BC
```

Each group appears

```
2!=2
```

times.

Therefore

```
6÷2=3
```

---

# Relationship Between Permutation and Combination

Permutation:

```
Choose
+
Arrange
```

Combination:

```
Choose only
```

Therefore

\[
^nP_r
=
^nC_r\times r!
\]

or

\[
^nC_r
=
\frac{^nP_r}{r!}
\]

---

# Example

Choose 3 from 5.

Permutation:

\[
5\times4\times3=60
\]

Each group appears

\[
3!=6
\]

times.

Therefore

\[
60÷6=10
\]

Formula:

\[
\frac{5!}{3!2!}=10
\]

Same answer.

---

# Understanding n(n−1)/2

The formula

\[
\frac{n(n-1)}{2}
\]

counts the number of **unique pairs** that can be formed from n distinct objects.

It is exactly

\[
\binom{n}{2}
=
\frac{n!}{2!(n-2)!}
\]

Since

\[
2!=2
\]

this simplifies to

\[
\frac{n(n-1)}{2}
\]

---

## Example

5 people shaking hands.

Each handshake involves exactly two people.

Number of handshakes:

\[
\frac{5\times4}{2}=10
\]

---

# Quick Decision Guide

| Situation | Formula |
|-----------|----------|
| Arrange books | Permutation |
| Race rankings | Permutation |
| Captain and Vice Captain | Permutation |
| Committee selection | Combination |
| Sports team | Combination |
| Handshakes | Combination (\(n(n-1)/2\)) |
| Shirt and Pant choices | Multiplication Principle |

---

# Summary

## Multiplication Principle

Multiply the number of choices available at each independent step.

---

## Factorial

Counts the number of arrangements of all objects.

\[
n!
\]

---

## Permutation

Ordered selection.

Order matters.

\[
^nP_r=\frac{n!}{(n-r)!}
\]

Derived by multiplying the available choices for each position.

---

## Combination

Unordered selection.

Order does not matter.

\[
^nC_r=\frac{n!}{r!(n-r)!}
\]

Derived by dividing permutations by the number of internal arrangements of the selected items.

---

## Why Divide by r!?

Because every selected group is counted exactly

\[
r!
\]

times in the permutation count.

Example:

```
Group:
A B C

Permutation counts:

ABC
ACB
BAC
BCA
CAB
CBA
```

All six arrangements represent the same group.

Therefore divide by

\[
3!
\]

to count the group only once.

---

# One-Line Memory Trick

- **Factorial (`n!`)** → Arrange all `n` items.
- **Permutation (`nPr`)** → Choose **and arrange** `r` items (order matters).
- **Combination (`nCr`)** → Choose `r` items only (order does not matter).
- **`r!` in combinations** → Removes duplicate orderings of the same selected group.
- **`n(n-1)/2`** → Counts unique pairs (e.g., handshakes, friendships, pairwise comparisons).