from collections import defaultdict, deque
import time
import unittest

class RequestCounter:
    def __init__(self, time_window):
        self.requests = defaultdict(lambda : defaultdict(deque))
        self.time_window = time_window
    
    def record(self, ip, browser):
        now = time.time()
        
        attributes = {
            "ip" : ip,
            "browser" : browser
        }
        
        for groupname, groupvalue in attributes.items():
            timestamps = self.requests[groupname][groupvalue]
            self._clean_expired(timestamps, now)
            timestamps.append(time.time())
    
    def count(self, groupname, groupvalue):

        now = time.time()

        timestamps = self.requests[groupname][groupvalue]

        if timestamps is None :
            return 0
        
        self._clean_expired(timestamps, now)
        return len(timestamps)


    def _clean_expired(self, timestamps, now):

        cutoff = now - self.time_window

        while timestamps and timestamps[0] <= cutoff :
            timestamps.popleft()

class TestRequestCounter(unittest.TestCase):
    def test_simple_counter(self):
        rc = RequestCounter(10)
        rc.record("198.168.0.1","Edge")
        rc.record("198.168.0.1","Edge")
        time.sleep(3)
        self.assertEqual(rc.count("ip","198.168.0.1"), 2)
        time.sleep(7)
        self.assertEqual(rc.count("ip","198.168.0.1"), 0)

if __name__ == "__main__":
    unittest.main()



    




