# Bruteforce

def dfs(i, p, w, c):
    if i >= len(w) or c == 0:
        return 0
    
    max_profit = dfs(i+1, p, w, c)

    if c >= w[i]:
        with_i = p[i] + dfs(i, p, w, c-w[i])
        max_profit = max(max_profit, with_i)
    
    return max_profit



p = [4,4,7,1]
w = [5,2,3,1]
c = 8

profit = dfs(0,p,w,c)
print(profit)
