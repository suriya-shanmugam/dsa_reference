p = [4,4,7,1]
w = [5,2,3,1]
c = 8

N = len(p)
M = c + 1
table = [[0]* M for _ in range(N)]

for i in range(M):
    if i >= w[0]:
        table[0][i] = p[0]


for i in range(1,N):
   for j in range(M):
       #without
       max_p = table[i-1][j]
       if j >= w[i] :
            with_self = p[i] + table[i][j-w[i]]
            max_p = max(max_p, with_self)
        
       table[i][j] = max_p
    
print(table)