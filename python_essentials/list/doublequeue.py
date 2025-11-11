from collections import deque

q = deque(["Intro","experience","project","skills"])
q.popleft()
print(q)
q.appendleft("summary")
print(q)

q.rotate(1) # positive right rotate
# q.rotate(-1) # negative left rotate
print(q)
