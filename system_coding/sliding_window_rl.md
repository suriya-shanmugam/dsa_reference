Great approach. Before discussing **HashMap + Deque** or the implementation, it's important to understand **what problem a sliding-window rate limiter solves**.

---

# Problem Statement

Imagine you are designing the backend for an API.

You want to protect your servers from clients sending too many requests.

For example:

> **Policy:** A user can make **at most 5 requests in any 10-second window**.

Notice the wording carefully:

> **Any 10-second window**

This is different from saying:

> 5 requests every clock interval (00:00–00:10, 00:10–00:20...)

The limiter should work regardless of when requests arrive.

---

# Example 1

Suppose the limit is

```
Max Requests = 5
Window = 10 seconds
```

A user sends requests at

```
Time(s)

1
2
3
4
5
```

Current requests inside last 10 seconds:

```
[1,2,3,4,5]
```

Count = 5

The next request comes at

```
Time = 6
```

Window becomes

```
[-4,6]
```

Requests inside the window are

```
1
2
3
4
5
```

Still 5 requests.

Adding the request at 6 would make

```
1
2
3
4
5
6
```

Count = 6

So we reject it.

---

# Example 2

Now time advances.

Next request arrives at

```
Time = 12
```

Current window is

```
[2,12]
```

Which requests remain?

Request at time 1 is now outside the window.

Remaining:

```
2
3
4
5
```

Count = 4

So request at 12 is allowed.

Now stored timestamps become

```
2
3
4
5
12
```

---

# Example 3

Another request comes at

```
Time = 14
```

Window:

```
[4,14]
```

Old timestamps

```
2
3
```

expire.

Remaining

```
4
5
12
```

Count = 3

Request at 14 is accepted.

Now timestamps become

```
4
5
12
14
```

---

# Visual Timeline

```
Time →

0   2   4   6   8   10  12  14

1---2---3---4---5-----------12---14
```

When evaluating the request at **14**, we only care about

```
Window = [4,14]
```

Everything before 4 is irrelevant.

---

# Why Not Simply Keep a Counter?

Suppose we only store

```
User A

Count = 5
```

At time 12,

we need to know

> Which of those 5 requests are older than 10 seconds?

The counter alone cannot answer this.

Example:

Both users have

```
Count = 5
```

User 1

```
1
2
3
4
5
```

User 2

```
8
9
10
11
12
```

Both counts are 5.

But at time 13:

For User 1:

```
Window = [3,13]

Remaining requests:
3
4
5

Count = 3
```

A new request should be **allowed**.

For User 2:

```
Window = [3,13]

Remaining:
8
9
10
11
12

Count = 5
```

A new request should be **rejected**.

The same count produces different answers because the timestamps are different.

---

# What Information Do We Actually Need?

To decide whether to accept a request, we must know:

1. **When previous requests happened**.
2. **Which requests have expired** (fallen outside the sliding window).
3. **How many valid requests remain**.

That naturally suggests storing the **timestamps** of recent requests instead of just a count.

---

# Desired Operations

For every incoming request at time `t`:

1. Remove timestamps older than `t - window_size`.
2. Count how many timestamps remain.
3. If the count is less than the limit:

   * Accept the request.
   * Store timestamp `t`.
4. Otherwise:

   * Reject the request.

---

## Why This Leads to `HashMap + Deque`

If there are many users, each user needs their own collection of recent timestamps.

* **HashMap**

  * Key: `userId`
  * Value: that user's recent request timestamps

* **Deque (queue)**

  * Stores timestamps in chronological order.
  * The oldest request is always at the front, making expired requests easy to remove.
  * New requests are appended at the back.

This combination supports the required operations efficiently and achieves **amortized O(1)** time per request, which we'll explore next when discussing the implementation.
