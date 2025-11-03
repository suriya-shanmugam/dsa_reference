

def lcs(s1,s2,i,j):
    if i == len(s1) or j ==len(s2):
        return 0
    if (s1[i] == s2[j]):
        return 1 + lcs(s1,s2,i+1,j+1)
    else:
        return max(lcs(s1,s2,i+1,j), lcs(s1,s2,i,j+1))


s1 = "abc"
s2 = "abc"
length = lcs(s1, s2, 0, 0)

print(length)