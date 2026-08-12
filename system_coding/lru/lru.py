'''
1 2 3
3 1 2
'''
import unittest

class Node :
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next  = None
        self.prev = None

class LRU :
    def __init__(self, capacity):
        self.capacity = capacity
        self.nodes_by_key = {}
        self.dummy_head = Node(-1, None)
        self.dummy_tail = Node(-1, None)
        self.dummy_head.next = self.dummy_tail
        self.dummy_tail.prev = self.dummy_head

    def get(self, key):
        
        if key not in self.nodes_by_key :
            raise KeyError("Key does not exist")

        node = self.nodes_by_key[key]
        self._remove(node)
        self._append(node)
        
        return node.value
        
    def put(self, key, value):
        
        if key in self.nodes_by_key :
            node = self.nodes_by_key[key]
            node.value = value
            self._remove(node)
            self._append(node)
            return True

        
        node = Node(key, value)
        self._append(node)
        self.nodes_by_key[key] = node

        if len(self.nodes_by_key) > self.capacity :
            self._remove_lru()
        
        return True

    def _remove(self, node) :
        
        next_node = node.next
        prev_node = node.prev

        prev_node.next = next_node
        next_node.prev = prev_node

        node.prev = None
        node.next = None
    
    def _append(self, node) :
        
        last_node = self.dummy_tail.prev
        
        last_node.next = node
        node.prev = last_node

        node.next = self.dummy_tail
        self.dummy_tail.prev = node
    

    def _remove_lru(self):
        target_node = self.dummy_head.next
        self._remove(target_node)
        del self.nodes_by_key[target_node.key] 
        
class TestCases(unittest.TestCase):
    def test_simple_put(self):
        lru = LRU(2)
        self.assertEqual(lru.put(1, "Apple"), True)
        self.assertEqual(lru.get(1), "Apple")
    
    def test_simple_eviction(self):
        lru = LRU(2)
        self.assertEqual(lru.put(1, "Apple"), True)
        self.assertEqual(lru.put(2, "Bannana"), True)
        self.assertEqual(lru.put(3, "Orange"), True)

        self.assertEqual(len(lru.nodes_by_key), 2)
        with self.assertRaises(KeyError) :
            lru.get(1)
    
    def test_simple_eviction_put_update(self):
        lru = LRU(2)
        self.assertEqual(lru.put(1, "Apple"), True)
        self.assertEqual(lru.put(2, "Bannana"), True)
        self.assertEqual(lru.put(1, "apple"), True)
        self.assertEqual(lru.put(3, "Oranges"), True)
        
        self.assertEqual(len(lru.nodes_by_key), 2)
        self.assertEqual(lru.get(1), "apple")
        with self.assertRaises(KeyError) :
            lru.get(2)
        

if __name__ == '__main__' :
    unittest.main()
        


       

        
       
    
   
        
            