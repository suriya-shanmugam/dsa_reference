import unittest
def max_zero_sum_subarray_length(arr):
    pref_sum_to_idx = {}
    max_len = -1
    cur_sum = 0

    pref_sum_to_idx[0] = -1

    for i in range(len(arr)):
        cur_sum += arr[i]
        if cur_sum in pref_sum_to_idx :
            length = i - pref_sum_to_idx[cur_sum] 
            max_len = max(length, max_len)
        else :
            pref_sum_to_idx[cur_sum] = i
    return max_len

class TestMaxZeroSumSubarray(unittest.TestCase):

    def test_given_example(self):
        arr = [15, -2, 2, -8, 1, 7, 10, 23]
        self.assertEqual(max_zero_sum_subarray_length(arr), 5)

    def test_no_zero_sum(self):
        arr = [1, 2, 3]
        self.assertEqual(max_zero_sum_subarray_length(arr), -1)

    def test_entire_array_zero_sum(self):
        arr = [1, -1, 2, -2]
        self.assertEqual(max_zero_sum_subarray_length(arr), 4)

    def test_empty_array(self):
        arr = []
        self.assertEqual(max_zero_sum_subarray_length(arr), -1)

    def test_single_zero(self):
        arr = [0]
        self.assertEqual(max_zero_sum_subarray_length(arr), 1)

if __name__ == "__main__":
    unittest.main()