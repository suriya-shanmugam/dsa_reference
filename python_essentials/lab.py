'''Input: nums = [100,4,200,1,3,2]
Output: 4'''
nums = []
nums_sorted = sorted(nums)
#[1,2,3,100,200]


# max_count = -1
# count = 1 
# for i in range(1,len(nums)):
#     if nums[i] - nums[i-1] ==  1 :
#         count += 1
#     else :
#         count = 1
#     max_count = max(count,max_count)

count = 1 
visited = set(nums)
for num in nums :
    if num-1 in visited :
        count +=1
    else :
        count = 1 
    max_count = max(count,max_count)