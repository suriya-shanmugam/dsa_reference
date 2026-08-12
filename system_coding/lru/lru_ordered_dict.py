from collections import OrderedDict

import unittest

class LRUCache:
    def __init__(self, capacity):
        self.cache = OrderedDict()
        self.capacity = capacity

    def get(self, key):
        if key not in self.cache:
            raise KeyError("Key not found")

        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key, value):
        self.cache[key] = value
        self.cache.move_to_end(key)

        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False)

class TestLRUCache(unittest.TestCase):
    def test_simple_eviction(self):
        cache = LRUCache(2)
        cache.put("A", 100)
        cache.put("B", 200)
        cache.put("C", 500)
        self.assertEqual(len(cache.cache), 2)
        self.assertEqual(cache.get("B"), 200)
        self.assertEqual(cache.get("C"), 500)
        with self.assertRaises(KeyError):
            self.assertEqual(cache.get("A"), 100)
    
    def test_lru_eviction(self):

        cache = LRUCache(2)
        cache.put("A", 100)
        cache.put("B", 200)
        cache.get("A")
        cache.put("C", 500)
        self.assertEqual(len(cache.cache), 2)
        self.assertEqual(cache.get("A"), 100)
        self.assertEqual(cache.get("C"), 500)
        with self.assertRaises(KeyError):
            self.assertEqual(cache.get("B"), 200)

if __name__ == '__main__':
    unittest.main()
