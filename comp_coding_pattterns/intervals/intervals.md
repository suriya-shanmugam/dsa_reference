
## Merge Interval

- Use res array 
- Sort the array
- Last element in res array is the reference 
- Two action - Add interval or Update the END of last interval in res
```
if res[-1][END] < interval [START]:
    res.add(interval)
else :
    res[-1][END] = max(res[-1][END], interval[END])
```



## Insert Interval
- Use additional result array
- Use while loop for each because number iterations are can't be pre determined.
- Each time insert into result on following while loop
- Insert **untill** no merge required  [ intervals[i][END] < newInterval[START]]
- Merge **untill** they share boundary and update it as new interval -> then insert once (this handles the prepend if case no merge)
```
interval[i][START] <= newInterval[END]
newInterval[0] = min(newInterval[0], intervals[i][0])
newInterval[1] = max(newInterval[1], intervals[i][1])
```
- Insert the rest

Method 2 ;
- insert at right position
- Do ##Merge Interval


## Non overlapping interval
- Sort by end time [greedy idea is to always keep the interval that ends earliest so longer range gets removed]
```
if lastEnd <= intervals[i][0] :
    lastEnd = intervals[i][1]
    continue
else :
    count += 1
```  


## Meeting room 2

- Use min heap to check lastest completed room. If room available use it else add it to the heap(like slots)
- So result heap size is number of room required


## Minimum Interval to Include Each Query

- sort both queries and intervals
- for each query add intervals after this and delete ends before this
- works fine for next iteration since the queries list is sorted