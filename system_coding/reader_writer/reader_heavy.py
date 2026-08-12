import threading
import unittest
import time

class ReaderWriterLock() :
    def __init__(self):
        self.active_readers = 0
        self.writer_active = False
        self.lock = threading.Lock()
        self.cv = threading.Condition(self.lock)
        
    
    def acquire_readlock(self):
        with self.cv :
            while self.writer_active :
                self.cv.wait()
            
            self.active_readers += 1


    def release_readlock(self):
        with self.cv:
            self.active_readers -= 1

            if self.active_readers == 0 :
                self.cv.notify_all()


    def acquire_writelock(self):
        with self.cv :
            while self.writer_active or self.active_readers > 0 :
                self.cv.wait()
            
            self.writer_active = True

    
    def release_writelock(self):
        with self.cv :
            self.writer_active = False
            self.cv.notify_all()


class Cache :
    def __init__(self):
        self.cache = {}
        self.rw_lock = ReaderWriterLock()
        
    def get(self, key):        
            self.rw_lock.acquire_readlock()
            try :
                if key in self.cache :
                    return self.cache[key]
                raise KeyError
            finally :
                self.rw_lock.release_readlock()
    
    def set(self, key, value):
        
        self.rw_lock.acquire_writelock()
        # time.sleep(1)
        try :
            self.cache[key] = value
            return True
        finally :
            self.rw_lock.release_writelock()


class TestReadHeavy(unittest.TestCase):
    def test_simple_set_get(self):
        rhcache = Cache()
        rhcache.set(1, "Apple")
        self.assertEqual(rhcache.get(1), "Apple")
    
    def test_get_missing_key(self):
        cache = Cache()

        with self.assertRaises(KeyError):
            cache.get(100)
    
    def test_multiple_readers_together(self):
        cache = Cache()
        cache.set(1, "Apple")

        result = []
        def readers():
            result.append(cache.get(1))
        threads = [
            threading.Thread(target=readers)
            for _ in range(10)
        ]
        
        for t in threads:
            t.start()
        for t in threads:
            t.join()
        self.assertEqual(len(result), 10)
    
    # def test_writer_blocks_reader(self):
    #     cache = Cache()
    #     writer_started = threading.Event()
    #     reader_finished = threading.Event()

    #     def writer():
    #         writer_started.set()
    #         cache.set(1, "Apple")


    #     def reader():
    #         writer_started.wait()
    #         cache.get(1)
    #         reader_finished.set()
        
    #     t1 = threading.Thread(target=writer)
    #     t2 = threading.Thread(target=reader)

    #     t1.start()
    #     t2.start()

    #     self.assertFalse(reader_finished.wait(timeout=0.2))

    #     t1.join()
    #     t2.join()

            


if __name__ == '__main__':
    unittest.main()

