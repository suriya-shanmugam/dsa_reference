import time
import unittest
import threading

class TokenRateLimiter :
    def __init__(self, capacity, rateps):
        self.capacity = capacity
        self.rateps = rateps
        self.tokens = capacity
        self.last_refill = time.time()

        self.lock = threading.Lock()
    
    def _refill(self):
       
        elasped = time.time() - self.last_refill
        
        refill_tokens = elasped * self.rateps
        
        if refill_tokens > 0 :
            self.tokens = min(
                self.capacity, 
                self.tokens + refill_tokens
            )
            self.last_refill = time.time()
        

    def allow(self):
        with self.lock:
            self._refill()
            
            if self.tokens > 0 :
                self.tokens -= 1
                return True
            
            return False

class TestTokenRateLimiter(unittest.TestCase):
    def test_base_case(self):
        trl = TokenRateLimiter(5, 1)
        
        def worker(worker_id):

            if trl.allow():
                print(worker_id, "allowed")
            else:
                print(worker_id, "blocked")
        
        threads_list = [
            threading.Thread(target=worker, args=(i,))
            for i in range(10)
        ]

        for i in range(10):
            threads_list[i].start()
        
        for i in range(10):
            threads_list[i].join()


if __name__ == '__main__':
    unittest.main()
