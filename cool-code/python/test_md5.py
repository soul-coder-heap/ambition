#!/usr/bin/env python
# coding=utf-8

class RBNode(object):
    "node"
    def __init__ (self, data, left_child = None, right_child = None, color = 'red'):
        self._data = data
        self._parent = None
        self._left_child = left_child
        self._right_child = right_child
        self._color = color

class RBBinaryTree(object):
    "red black tree"
    def __init__ (self):
        self._root = None
        self._prefix_branch = '├'
        self._prefix_trunk = '|'
        self._prefix_leaf = '└'
        self._prefix_empty = ''
        self._prefix_left = '─L─'
        self._prefix_right = '─R─'

def main():
    import keyword
    print(keyword.kwlist)
    print(RBBinaryTree)
if "__main__":
    print("this.main")
    main()
