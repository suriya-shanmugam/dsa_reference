import unittest
class Node :
    def __init__(self, key, value):
        self.key  = key
        self.value = value
        self.freq = 1
        self.next = None
        self.prev = None

class LRU :
    def __init__(self):
        self.dummy_head = Node(-1, -1)
        self.dummy_tail = Node(-1, -1)
        self.dummy_head.next = self.dummy_tail
        self.dummy_tail.prev = self.dummy_head

class LFU :    
    def __init__(self, capacity : int) : 
        self.nodes_by_key = {}
        self.capacity = capacity
        self.node_list_by_freq : dict[int, LRU] = {} # dict freq and Nodeptr

    def get(self, key) :

        if key not in self.nodes_by_key :
            raise KeyError("Key not found")
        
        node = self.nodes_by_key[key]
        
        node_prev_freq = node.freq
        self._remove(node_prev_freq, node)
        
        node.freq = node_prev_freq + 1
        self._append(node_prev_freq + 1, node)

        return node.value

    def set(self, key, value):

        if key in self.nodes_by_key :
            node = self.nodes_by_key[key]
            node.value = value
            
            prev_freq = node.freq
            self._remove(prev_freq, node)

            node.freq = prev_freq + 1
            self._append(prev_freq + 1, node) 
            return True

        node = Node(key, value)
        self._append(1, node)
        self.nodes_by_key[key] = node

        if len(self.nodes_by_key) > self.capacity :
            self._remove_lfu()
            print("removed")
        
        return True

    def _remove(self, freq, node) :
        
        if freq not in self.node_list_by_freq :
            raise KeyError("Freq Key is not found")

        if freq in self.node_list_by_freq :
            next_node = node.next
            prev_node = node.prev

            prev_node.next = next_node
            next_node.prev = prev_node

            node.next = None
            node.prev = None
    
    def _append(self, freq, node):

        if freq not in self.node_list_by_freq :
            self.node_list_by_freq[freq] = LRU()
        
        lru = self.node_list_by_freq[freq]
        
        prev_tail_node = lru.dummy_tail.prev
        
        lru.dummy_tail.prev = node
        node.next = lru.dummy_tail

        prev_tail_node.next = node
        node.prev = prev_tail_node

        print(node.key, node.value, node.freq)
        print(lru.dummy_tail.prev.key, lru.dummy_tail.prev.value, lru.dummy_tail.prev.freq)

    def  _remove_lfu(self):
        
        for i in range(10000):
            if i in self.node_list_by_freq :
                lru = self.node_list_by_freq[i]
                if lru.dummy_head.next == lru.dummy_tail :
                    continue
                
                # Deleting head node
                prev_head = lru.dummy_head.next
                
                lru.dummy_head.next = prev_head.next
                prev_head.next.prev = lru.dummy_head

                prev_head.next = None
                prev_head.prev = None

                del self.nodes_by_key[prev_head.key]
                return
                
                
class TestLFU(unittest.TestCase):
    def test_simple_set(self):
        lfu = LFU(2)
        self.assertEqual(lfu.set(1, "Apple"), True)
        #self.assertEqual(lfu.get(1), "Apple")
        self.assertEqual(len(lfu.nodes_by_key), 1)
        self.assertEqual(lfu.nodes_by_key[1].freq, 1)
        
        # self.assertEqual(lfu.node_list_by_freq[2].dummy_tail.prev.value, "Apple")
    def test_freq_update(self):
        lfu = LFU(2)
        self.assertEqual(lfu.set(1, "Apple"), True)
        self.assertEqual(lfu.get(1), "Apple")
        self.assertEqual(len(lfu.nodes_by_key), 1)
        self.assertEqual(lfu.nodes_by_key[1].freq, 2)
        self.assertEqual(lfu.node_list_by_freq[2].dummy_tail.prev.value, "Apple")
    
    def test_simple_lfu_eviction(self):
        
        lfu = LFU(2)
        self.assertEqual(lfu.set(1, "Apple"), True)
        self.assertEqual(lfu.get(1), "Apple")
        self.assertEqual(lfu.set(2, "Orange"), True)
        self.assertEqual(len(lfu.nodes_by_key), 2)
        self.assertEqual(lfu.nodes_by_key[1].freq, 2)

        self.assertEqual(lfu.set(3, "Mango"), True)
        self.assertEqual(len(lfu.nodes_by_key), 2)
        self.assertEqual(lfu.get(1), "Apple")
        self.assertEqual(lfu.get(3), "Mango")
    
    def test_simple_lru_eviction(self):
        
        lfu = LFU(2)
        self.assertEqual(lfu.set(1, "Apple"), True)
        self.assertEqual(lfu.set(2, "Orange"), True)
        self.assertEqual(len(lfu.nodes_by_key), 2)
        self.assertEqual(lfu.nodes_by_key[1].freq, 1)

        self.assertEqual(lfu.set(3, "Mango"), True)
        self.assertEqual(len(lfu.nodes_by_key), 2)
        self.assertEqual(lfu.get(2), "Orange")
        self.assertEqual(lfu.get(3), "Mango")
        with self.assertRaises(KeyError):
            self.assertEqual(lfu.get(1), "Apple")

if __name__ == "__main__":
    unittest.main()

            

        
        
        
        



