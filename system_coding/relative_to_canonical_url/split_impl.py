
import unittest

def split_str(text : str, split_by: str) -> list:

    result = []
    curr = []

    for ch in text+split_by :
        if ch == split_by :
            prev = "".join(curr)
            if prev != "" :
                result.append("".join(curr))
            curr = []
        else :
            curr.append(ch)
    
    return result

assert split_str("/a/hello/b", '/') == ["a","hello","b"]

class TestSplit(unittest.TestCase):
    def test_simple_split(self) :
        self.assertEqual(split_str("/a/hello/b", '/'), ["a","hello","b"])

if __name__ == "__main__" :
    unittest.main()