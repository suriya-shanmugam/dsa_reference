s1 = "abc"
s2 = "ac"
M = len(s1)
N = len(s2)
table = [[0] * (N+1) for _ in range(M+1)]

for i in range(1,M):
    for j in range(1,N):
        if s1[i] == s2[j]:
            table[i+1][j+1] = 1 + table[i][j]
        else :
            table[i+1][j+1] = max(table[i][j+1],table[i+1][j])

print(table[M][N])

