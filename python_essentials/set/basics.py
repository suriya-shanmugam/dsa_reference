#creation
# supports hashble (immuatble??)
s = set()
s = {1,2,3}

s = set([1,4,5,2,1])
fs = frozenset({1,2,3}) #immutable
print(s)

s = set()
s.add("suriya")
s.add("suriya")

s.update(["jesu"])

#s.remove("tharun")  #key_error on missing

s.discard("tharun")

print(s)

# returns random element
ele = s.pop()
print(ele)

#clears the set
s.clear()
print(s)
