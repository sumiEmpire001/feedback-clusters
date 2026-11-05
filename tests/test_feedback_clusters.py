import unittest
from feedback_clusters import cluster
class Tests(unittest.TestCase):
    def test_match(self):
        self.assertEqual(cluster(["app is slow"],{"speed":["slow"]})["counts"]["speed"],1)
    def test_unmatched(self):
        self.assertEqual(cluster(["hello"],{"speed":["slow"]})["counts"]["unmatched"],1)
    def test_multilabel(self):
        result=cluster(["slow and crashes"],{"speed":["slow"],"stability":["crashes"]})
        self.assertEqual(result["counts"]["stability"],1)
        self.assertEqual(result["counts"]["speed"],1)
    def test_case_insensitive(self):
        self.assertEqual(cluster(["SLOW"],{"speed":["slow"]})["counts"]["speed"],1)
    def test_bad_schema(self):
        with self.assertRaises(ValueError): cluster(["ok"],{"topic":"word"})
if __name__=="__main__": unittest.main()
