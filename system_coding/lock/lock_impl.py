from threading import Lock,Thread
import time

counter = 0
lock = Lock()

def increment ():
    global counter
    for _ in range(100):
        time.sleep(0)
        counter += 1

threads = [
    Thread(target=increment)
    for _ in range(4)
]

for t in threads:
    t.start()

for t in threads:
    t.join()

print(counter)

