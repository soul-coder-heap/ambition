def account():
    count = 0
    for i in range(1, 1001):
        list1 = []
        for j in range(1, i):
            if i % j == 0:
                list1.append(j)
        if sum(list1) == i:
            count += 1
    return count

print(account())
class TreeNode:
    def __init__(self,x):
        self.val = x
        self.left=None
        self.right =None

class Solution:
    def KthNode(self,pRoot,k):
        retList=[]

        def preOrder(pRoot):
            if pRoot==None:
                return None
            preOrder(pRoot.left)
            retList.append(pRoot)
            preOrder(pRoot.right)

        preOrder(pRoot)

        if len(retList)<k or k <1:
            return None

        return retList[k-1]