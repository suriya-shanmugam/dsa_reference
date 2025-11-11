
l = [1,2,3]

for i in range(len(l)):
    for j in range(i,len(l)) :
        if j == 1 :
            break
    print(j)