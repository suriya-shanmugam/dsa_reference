# sorting is in-place and stable in python
nums = [5,6,8,0]
nums.sort() 
print(nums)

weighted_text = [("title",2),("description",3), ("skills", 1)]
# sort based on length of the string
# pass any function to 	`key` param - function is applied to each element and comparison is done
weighted_text.sort(key=lambda x : len(x[0]))
print("sort based on len of strings ", weighted_text) 

#sort alphatically
weighted_text.sort(key=lambda x : x[0])
print("sort based on alpha ",  weighted_text)

#sort based on weight
weighted_text.sort(key=lambda x : x[1])
print("sort based on ", weighted_text)

#reversing - inplace
l = [1,2,3,4]
l.reverse()
print(l)

# reverse copy use slice
l.reverse()
lc = l[::-1]
print(lc)

# rotation
l = [1,2,3,4,5]
r = 3
# right rotate creates copy
res = l[-r:] + l[:-r]
print("rotated list ", res)

# left rotate
l = [1,2,3,4,5]
r = 3
res = l[r:]+l[:r]
print("rotated list ", res)


