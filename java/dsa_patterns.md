# Java DSA Coding Patterns

---

# 1. Two Pointers

## Explanation

Two pointers traverse a structure **from two positions**.

Usually used in:

```
sorted arrays
palindrome checks
pair problems
```

---

## When to Use

Use when problem asks:

```
pair sum
palindrome
remove duplicates
merge sorted arrays
```

---

## Core Template

```java
int left = 0;
int right = arr.length - 1;

while(left < right){

    if(condition){
        left++;
    }
    else{
        right--;
    }
}
```

---

## Example — Two Sum (Sorted Array)

```java
int left = 0;
int right = nums.length - 1;

while(left < right){

    int sum = nums[left] + nums[right];

    if(sum == target)
        return new int[]{left,right};

    if(sum < target)
        left++;
    else
        right--;
}
```

---

## Important Notes

Time Complexity

```
O(n)
```

Much better than

```
O(n²)
```

---

## Common Mistake

For **unsorted arrays**, use **HashMap instead**.

---

# 2. Sliding Window

## Explanation

Used when working with **subarrays or substrings**.

Instead of recomputing every window, we **slide the window**.

---

## When to Use

Look for keywords:

```
substring
subarray
longest
minimum window
```

---

## Core Template

```java
int left = 0;

for(int right = 0; right < arr.length; right++){

    // expand window

    while(window invalid){
        left++;
    }

}
```

---

## Example — Longest Substring Without Repeating Characters

```java
Set<Character> set = new HashSet<>();

int left = 0;
int max = 0;

for(int right=0; right<s.length(); right++){

    while(set.contains(s.charAt(right))){
        set.remove(s.charAt(left));
        left++;
    }

    set.add(s.charAt(right));
    max = Math.max(max, right-left+1);
}
```

---

## Important Notes

Time Complexity

```
O(n)
```

Because each element is processed **at most twice**.

---

## Common Mistake

Forgetting:

```
right-left+1
```

---

# 3. Fast & Slow Pointers (Cycle Detection)

## Explanation

Two pointers move at **different speeds**.

Used to detect **cycles in linked lists**.

Also used for **middle of list problems**.

---

## When to Use

```
linked list cycle
find middle node
happy number
```

---

## Core Template

```java
ListNode slow = head;
ListNode fast = head;

while(fast != null && fast.next != null){

    slow = slow.next;
    fast = fast.next.next;

    if(slow == fast)
        return true;
}
```

---

## Example — Find Middle Node

```java
ListNode slow = head;
ListNode fast = head;

while(fast != null && fast.next != null){
    slow = slow.next;
    fast = fast.next.next;
}

return slow;
```

---

## Important Notes

Fast pointer moves **2 steps**.

Slow pointer moves **1 step**.

---

# 4. Binary Search Pattern

## Explanation

Binary search reduces search space **by half**.

Works only on **sorted structures**.

---

## When to Use

Look for keywords:

```
sorted
minimum
maximum
search
```

---

## Core Template

```java
int left = 0;
int right = arr.length - 1;

while(left <= right){

    int mid = left + (right-left)/2;

    if(arr[mid] == target)
        return mid;

    else if(arr[mid] < target)
        left = mid + 1;

    else
        right = mid - 1;
}
```

---

## Important Notes

Always compute mid as:

```java
mid = left + (right-left)/2
```

Prevents **integer overflow**.

---

# 5. Prefix Sum

## Explanation

Precompute cumulative sums to answer queries **in O(1)**.

---

## When to Use

Look for:

```
range sum
subarray sum
continuous sum
```

---

## Core Template

```java
int[] prefix = new int[n];

prefix[0] = arr[0];

for(int i=1;i<n;i++){
    prefix[i] = prefix[i-1] + arr[i];
}
```

Range sum:

```java
sum = prefix[r] - prefix[l-1];
```

---

## Example

```java
int sum = prefix[right] - prefix[left-1];
```

---

## Important Notes

Time

```
Precompute O(n)
Query O(1)
```

---

# 6. HashMap Frequency Pattern

## Explanation

Count occurrences using HashMap.

---

## When to Use

```
frequency
duplicates
anagram
majority element
```

---

## Core Template

```java
Map<Integer,Integer> map = new HashMap<>();

for(int n : nums){

    map.put(n, map.getOrDefault(n,0)+1);

}
```

---

## Example — Two Sum

```java
Map<Integer,Integer> map = new HashMap<>();

for(int i=0;i<nums.length;i++){

    int complement = target - nums[i];

    if(map.containsKey(complement))
        return new int[]{map.get(complement), i};

    map.put(nums[i],i);
}
```

---

# 7. Monotonic Stack

## Explanation

Stack that maintains **increasing or decreasing order**.

Used for **next greater element problems**.

---

## When to Use

Keywords:

```
next greater
next smaller
daily temperatures
histogram
```

---

## Core Template

```java
Stack<Integer> stack = new Stack<>();

for(int i=0;i<n;i++){

    while(!stack.isEmpty() && arr[i] > arr[stack.peek()]){
        stack.pop();
    }

    stack.push(i);
}
```

---

## Example — Next Greater Element

```java
Stack<Integer> stack = new Stack<>();

for(int i=0;i<nums.length;i++){

    while(!stack.isEmpty() && nums[i] > nums[stack.peek()]){
        int idx = stack.pop();
    }

    stack.push(i);
}
```

---

# 8. BFS (Breadth First Search)

## Explanation

Level-by-level traversal using **queue**.

---

## When to Use

```
shortest path
tree level traversal
matrix traversal
```

---

## Core Template

```java
Queue<Node> q = new LinkedList<>();

q.offer(start);

while(!q.isEmpty()){

    Node node = q.poll();

    for(Node neigh : node.neighbors){
        q.offer(neigh);
    }
}
```

---

# 9. DFS (Depth First Search)

## Explanation

Explore branch deeply before backtracking.

---

## Recursive Template

```java
void dfs(Node node){

    if(node == null)
        return;

    dfs(node.left);
    dfs(node.right);
}
```

---

# 10. Backtracking

## Explanation

Try possibilities and **undo choices**.

Used for **permutation and combination problems**.

---

## When to Use

```
permutations
subsets
n-queens
combinations
```

---

## Core Template

```java
void backtrack(List<Integer> temp){

    if(condition){
        result.add(new ArrayList<>(temp));
        return;
    }

    for(int i=0;i<n;i++){

        temp.add(nums[i]);

        backtrack(temp);

        temp.remove(temp.size()-1);
    }
}
```

---

# 11. Heap (Top K Elements)

## Explanation

Use heap when asked:

```
top k
k largest
k smallest
```

---

## Template

```java
PriorityQueue<Integer> pq = new PriorityQueue<>();

for(int n : nums){

    pq.offer(n);

    if(pq.size() > k)
        pq.poll();
}
```

---

## Important Notes

Min Heap keeps **largest k elements**.

---

# 12. Union Find (Disjoint Set)

## Explanation

Tracks connected components.

---

## Template

```java
int find(int x){
    if(parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void union(int a, int b){

    int pa = find(a);
    int pb = find(b);

    if(pa != pb)
        parent[pa] = pb;
}
```

---

# The 12 Patterns 

```
Two Pointer
Sliding Window
Fast Slow Pointer
Binary Search
Prefix Sum
HashMap Frequency
Monotonic Stack
BFS
DFS
Backtracking
Heap / Top K
Union Find
```
