import unittest
import heapq

class Node:
    def __init__(self, id, key, value, expiration):
        self.key = key
        self.value = value
        self.exp = expiration
        self.next = None
        self.prev = None
        self.id = id


class TTLCache :
    def __init__(self, capacity):
        self.cache = {}
        self.capacity = capacity
        self.heap = []
        self.counter = 0

        self.dummy_head = Node(None, -1, -1, None)
        self.dummy_tail = Node(None, -1, -1, None)

        self.dummy_head.next = self.dummy_tail
        self.dummy_tail.prev = self.dummy_head
    
    def get(self, key, now):
        self._clean_expired(now)
        
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._append(node)
            return node.value
        
        raise KeyError("Key Not Found")
    
    def set(self, key, value, ttl, now):
        self._clean_expired(now)
        
        if key in self.cache :
            node = self.cache[key]
            node.value = value
            expiry = now + ttl
            node.ttl = expiry
            self._remove(node)
            self._append(node)
            heapq.heappush(self.heap, [expiry, node.id, node])
            return True
        
        # Key does not exist
        expiry = ttl + now
        self.counter = self.counter + 1
        node = Node (id = self.counter,
                    key=key,
                    value=value,
                    expiration=expiry)
        self.cache[key] = node
        self._append(node)
        
        heapq.heappush(self.heap, [expiry, node.id, node])
        
        if len(self.cache) > self.capacity :
            self._removelru()

        return True

    def _remove(self, node):
        next_node = node.next
        prev_node = node.prev

        prev_node.next = next_node
        next_node.prev = prev_node

        node.next = None
        node.prev = None
    
    def _append(self, node):
        cur_tail = self.dummy_tail.prev
        self.dummy_tail.prev = node
        cur_tail.next = node
        node.next = self.dummy_tail
        node.prev = cur_tail

    def _removelru(self):
        
        current_head = self.dummy_head.next
        current_head_next = current_head.next
        
        self.dummy_head.next = current_head_next
        current_head_next.prev = self.dummy_head

        self._remove(current_head)
        del self.cache[current_head.key]
    
    def _clean_expired(self, now):
        
        while self.heap and self.heap[0][0] <= now :
            id, expiry, node = heapq.heappop(self.heap)
            key = node.key
            if node is self.cache[key] :
                self._remove(node)
                del self.cache[key]
        
class TestExpirationCache( unittest.TestCase):
    def test_base_eviction(self):
        ttlcache = TTLCache(2)
        ttlcache.set(
            key=1, 
            value="Apple",
            ttl=10,
            now=5)
        self.assertEqual(ttlcache.get(1, now=10), "Apple")
        with self.assertRaises(KeyError):
            self.assertEqual(ttlcache.get(1, now=16), "Apple")
        ttlcache.set(
            key=2, 
            value="Orange",
            ttl=10,
            now=17)
        ttlcache.set(
            key=3, 
            value="Mango",
            ttl=10,
            now=17)
        ttlcache.set(
            key=4, 
            value="Kiwi",
            ttl=10,
            now=17)
        with self.assertRaises(KeyError):
            self.assertEqual(ttlcache.get(2, now=17), "Orange")
        self.assertEqual(ttlcache.get(4, now=17), "Kiwi")
    
    def test_lru(self):
        ttlcache = TTLCache(2)
        ttlcache.set(
            key=1, 
            value="Apple",
            ttl=10,
            now=5)
        ttlcache.set(
            key=2, 
            value="Orange",
            ttl=10,
            now=5)
        ttlcache.set(
            key=3, 
            value="Mango",
            ttl=10,
            now=14)
        self.assertEqual(len(ttlcache.cache), 2)
        self.assertEqual(3 in ttlcache.cache, True)
        self.assertEqual(2 in ttlcache.cache, True)


if __name__ == '__main__':
    unittest.main()