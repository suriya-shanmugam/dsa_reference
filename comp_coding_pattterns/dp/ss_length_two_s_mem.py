def lcs(s1,s2,i,j, cache):
    if i == len(s1) or j ==len(s2):
        return 0
    if cache[i][j] != -1 :
        return cache[i][j]

    if (s1[i] == s2[j]):
        cache[i][j] = 1 + lcs(s1,s2,i+1,j+1, cache)
    else:
        cache[i][j] = max(lcs(s1,s2,i+1,j, cache), lcs(s1,s2,i,j+1, cache))
    
    return cache[i][j]


s1 = "abc"
s2 = "ac"
cache = [[-1] * len(s2) for _ in range(len(s1))]
length = lcs(s1, s2, 0, 0, cache)

print(length)