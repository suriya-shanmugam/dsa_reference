import heapq
h = [10,9,12,1,2,3,4,5]
# by default python support min heap
heapq.heapify(h)
heapq.heappush(h, 0)
print(h)
print(heapq.heappop(h))
print(heapq.heappop(h))

print("5 largest elements ", heapq.nlargest(5,h))
print("5 smallest elements ", heapq.nsmallest(5,h))


# trick for max heap
h = [10,9,12,1,2,3,4,5]
h[:] = [-x for x in h]
heapq.heapify(h)
heapq.heappush(h, -20)
print(h)
print(-heapq.heappop(h))
print(-heapq.heappop(h))

# construct and get smallest and largest
h = [10,9,12,1,2,3,4,5]
print("5 largest elements ", heapq.nsmallest(5, h, key= lambda x : -x))
print("5 smallest elements ", heapq.nlargest(5, h, key= lambda x : -x))

