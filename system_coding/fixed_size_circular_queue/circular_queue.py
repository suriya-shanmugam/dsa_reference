'''
1 
F - 0
R - 0

[]
F = -1
R = -1

1 
F - 0
R - 0

1, 2
F - 0
R - 1


2

F - 1
R - 1

2, 3

F - 1
R - 2

'''

class CircularQueue :
    def __init__(self, size):
        self.front = -1
        self.rear = -1
        self.container = [None] * size
        self.buffer_size = size
    
    def enqueue(self, value : int) -> bool:
        
        if self.front != 0 and (self.right - self.left + 1 == self.buffer_size) :
            raise BufferError("size exceeded")
        
        self.rear = self.rear + 1 % self.buffer_size
        self.container[self.rear] = value
        
    def dequeue() -> int :
        
        if self.front == self.rear and self.front != 0 :
            raise IndexError("Queue is Empty")
        elif self.front == self.rear and self.front == 0 :

        current = self.container[self.front]
        self.front = self.front + 1 % self.buffer_size
        return current

    def front() -> int :
        pass

    def back() -> int :
        pass

    def is_empty() -> bool :
        pass
    
    def is_full() -> bool :
        pass