import threading
from collections import deque
import time

q = []
not_empty = threading.Condition()
done = False
def producer():
   
    global done
    for i in range(10):
        with not_empty:
            q.append(i)
            not_empty.notify()
    
    with not_empty :
        done = True
        not_empty.notify_all()
    print("Finished")
    
def consumer():
    global done
    while True :
        with not_empty :
            native_id = threading.get_native_id()
            while not q and not done:
                not_empty.wait()
            
            if not q and done :
                break             
            
            item = q.pop(0)
            print("Thread Id -" , native_id,"Consumed - ", item)
            time.sleep(1)

consumers = [
    threading.Thread(target=consumer)
    for _ in range(2)
]

producers = [threading.Thread(target=producer)]

for ct in consumers:
    ct.start()

for pt in producers:
    pt.start()

for ct in consumers:
    ct.join()

for pt in producers:
    pt.join()