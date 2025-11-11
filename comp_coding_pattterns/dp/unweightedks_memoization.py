# Memoization

def dfs(i, p, w, cache, c):
    if i >= len(w) or c == 0:
        return 0
    
    if cache[i][c] != -1:
        return cache[i][c]
    
    cache[i][c] = dfs(i+1, p, w, cache, c)

    if c >= w[i]:
        with_i = p[i] + dfs(i, p, w, cache, c-w[i])
        cache[i][c] = max(cache[i][c], with_i)
    
    return cache[i][c]



p = [4,4,7,1]
w = [5,2,3,1]
c = 8
cache = [ [-1] * (c+1) for _ in range(len(p))]
#print(cache)

profit = dfs(0,p,w, cache, c)
print(profit)
