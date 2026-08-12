'''
states needs to be maintained
front - for dequeue constant time Operation
rear - for enqueue constant time Operation
length - to avoid o(N) calculation
'''
from typing import Any

class Node :
    def __init__(self, value):
        self.value = value
        self.next = None 

class Queue :
    def __init__(self) :
        self.front  = None
        self.rear = None
        self.length = 0   

    def enqueue(self, value) -> bool :
        node = Node(value)
        if self.rear is None :
            self.front = node
            self.rear = node
        else :    
            self.rear.next = node
            self.rear = node
        self.length += 1
       
        return True
    
    def dequeue(self) -> Any :
        if self.front is None :
            raise IndexError("Queue is Empty")
        
        node = self.front
        self.front = self.front.next
        
        if self.front is None :
            self.rear = None
        
        self.length -= 1
        
        return node.value


    def peek(self) -> int :
        if self.front is None :
            raise IndexError("Queue is Empty")
        return self.front.value

    def size(self) -> int :
        return self.length

    def is_empty(self) -> int :
        return self.length == 0 

queue  = Queue()

queue.enqueue(2)
assert queue.peek() == 2
assert queue.size() == 1

queue.enqueue(3)
assert queue.peek() == 2
assert queue.size() == 2

queue.dequeue()
assert queue.peek() == 3
assert queue.size() == 1
 
