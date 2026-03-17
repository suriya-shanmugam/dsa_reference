ROWS  = 3
COLS = 4
zeroMatrix = [[0 for  _ in range(COLS)] for _ in range(ROWS)]
print(zeroMatrix)

# legacy way
zeroMat_legacy = []
for i in range(ROWS):
    col = []
    for j in range(COLS):
        col.append(False)
    zeroMat_legacy.append(col)
print(zeroMat_legacy)

# list comprehension with condition
matrix = [[1 if i == j else 0 for j in range(COLS)] for i in range(ROWS)]
print(matrix)

# has performance bottleneck as it iterates through the string every time
inputStr = "banana"
freqCountHandy = {ch: inputStr.count(ch) for ch in set(inputStr)}
print(freqCountHandy)

# legacy way but more efficient as it iterates through the string only once
freqCount = {}
for ch in inputStr:
    # if ch in freqCount:
    #     freqCount[ch] += 1
    # else:
    #     freqCount[ch] = 1
    freqCount[ch] = freqCount.get(ch, 0) + 1

print(freqCount)

from collections import Counter
import heapq
freqCountHandy2 = Counter(inputStr)
print(freqCountHandy2)

# tranformations

inputList = [1, 2, 3, 4, 5]
squaredList = [x**2 for x in inputList]
print(squaredList)
negatedList_withCycle = [(-x, 0) for x in inputList]
print(negatedList_withCycle)

import heapq
heapq.heapify(negatedList_withCycle)
print(negatedList_withCycle)


# tranformation and sorting
sortByFreq = sorted(freqCountHandy2.items(), key=lambda x: x[1], reverse=True)
print(sortByFreq)


inputStr = "1 2 3 4 5"
inputList = list(map(int, inputStr.split()))
print(inputList)


# legacy way
inputList_legacy = []
for num in inputStr.split():
    inputList_legacy.append(int(num))
print(inputList_legacy)


# square map
chList_map = {x : str(x) for x in inputList}
print(chList_map)

# matrix transpose
matrix = [
    [1, 2, 3],
    [4, 5, 6]
]

legacyTranspose = []
for i in range (len(matrix[0])):
    col = []
    for j in range(len(matrix)):
        col.append(matrix[j][i])
    legacyTranspose.append(col)
print(legacyTranspose)

transpose = [[matrix[j][i] for j in range(len(matrix))] for i in range(len(matrix[0]))]
print(transpose)




names = ["Alice", "Bob", "Charlie"]
names.sort(key=lambda x: len(x))
print(names)