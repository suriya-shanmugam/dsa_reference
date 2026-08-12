from collections import deque
from typing import Any

import unittest

class DeDuplicator :
    def __init__(self, window_size) :
        self.window_size = window_size
        self.unique_id = set()
        self.queue = deque()
    
    def process (self, event_id : Any) -> bool :
        
        if event_id in self.unique_id :
            return False
        
        self.queue.append(event_id)
        self.unique_id.add(event_id)

        if len(self.queue) > self.window_size :
            item = self.queue.popleft()
            self.unique_id.remove(item)

        return True

class TestDeDuplicator(unittest.TestCase):

    def test_simple_duplicate(self):
        d = DeDuplicator(2)
        self.assertEqual(d.process(1), True)
        self.assertEqual(d.process(1), False)
    
    def test_insert_after_window(self):
        d = DeDuplicator(2)
        self.assertEqual(d.process(1), True)
        self.assertEqual(d.process(2), True)
        self.assertEqual(d.process(3), True)
        self.assertEqual(d.process(1), True)


if __name__ == "__main__" :
    unittest.main()

