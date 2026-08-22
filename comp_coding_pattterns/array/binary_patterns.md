
## Rule of thumb

There are two common binary search templates:

Interval |	Initial | right | Loop |	When going left|
| --- | --- | --- |
[left, right) (half-open)	len(nums)	while left < right	right = mid
[left, right] (inclusive)	len(nums) - 1	while left <= right	right = mid - 1


## Lower bound 
```
while left < right :
    if mid is lesser than target :
        #right portion
        l = mid + 1
    else :
        #left portion
        r = m # inclusive of mid because mid might be inclusive of target

    return left     
```

## Upper Bound 
```
while left < right :
    if mid is < = target :
        #right portion
        l = mid + 1
    else :
        #left portion
        r = mid
return left - 1    
```