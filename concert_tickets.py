# MAGIC CODEFORCES PYTHON FAST IO
import atexit
import io
import sys

_INPUT_LINES = sys.stdin.read().splitlines()
input = iter(_INPUT_LINES).__next__
_OUTPUT_BUFFER = io.StringIO()
sys.stdout = _OUTPUT_BUFFER

@atexit.register
def write():
    sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())
# END OF MAGIC CODEFORCES PYTHON FAST IO

import random

NOT_FOUND = (-1,-1)

class EmptyNode(object):
    def insert(self, val):
        return BSTNode(val)
    def findAndRemove(self, upper):
        return self, NOT_FOUND
    def merge(self, right):
        return right
    def empty(self):
        return True
    def depth(self):
        return 0

# Notar que no necesitamos balancear porque tenemos todos los datos que insertamos al comienzo:
# basta un random_shuffle al comienzo para tener un arbol balanceado.
# NOTA: Asumiendo que no hay repetidos!!! Por eso tuve un WA, y hubo que desempatar cosas.
class BSTNode(object):
    def __init__(self, val):
        self.left  = EmptyNode()
        self.right = EmptyNode()
        self.val   = val
    def empty(self):
        return False
    def insert(self, val):
        if val <= self.val:
            self.left = self.left.insert(val)
        else:
            self.right = self.right.insert(val)
        return self
    # Sabemos que todo el arbol right es mayor estricto que todo nuestro arbol
    def merge(self, right):
        parent, largest = None, self
        while not largest.right.empty():
            parent , largest = largest, largest.right
        if parent is not None:
            parent.right = largest.left
            largest.left = self
        largest.right = right
        return largest
        
    def findAndRemove(self, upper):
        if upper >= self.val:
            self.right, ret = self.right.findAndRemove(upper)
            if ret == NOT_FOUND:
                return self.left.merge(self.right), self.val
            else:
                return self, ret
        else:
            self.left , ret = self.left.findAndRemove(upper)
            return self, ret
    def depth(self):
        return 1+max(self.left.depth(), self.right.depth())
    
class BinarySearchTree(object):
    def __init__(self):
        self.root = EmptyNode()
    def insert(self, val):
        self.root = self.root.insert(val)
    def insertAll(self, values):
        for val in values:
            self.insert(val)
    def findAndRemove(self, upper):
        self.root, ret = self.root.findAndRemove(upper)
        return ret
    
def readLineInts():
    return map(int,input().split())

n,m = readLineInts()
h = [(x,i) for i,x in enumerate(readLineInts())]
random.shuffle(h)
bst = BinarySearchTree()
bst.insertAll(h)
print(bst.root.depth(), file=sys.stderr)
t = readLineInts()
for customer in t:
    val, index = bst.findAndRemove((customer, n))
    print(val)
