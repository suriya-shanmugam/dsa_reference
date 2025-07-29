'''
Basics of how data structure is serialized

This is the fundamental for storing the data strutures into files eg : B-Tree index etc

'''


class Node :
    def __init__(self,value):
        self.value = value
        self.left = None
        self.right = None
class Tree :
    
    def __init__(self) :
        self.head = None

    def dfs(self, root) :
        if root == None :
            return
        
        print(root.value)
        self.dfs(root.left)
        self.dfs(root.right)

    @staticmethod
    
    def _serialize(node, arraylist):
        if node == None :
            return
        
        arraylist.append(node.value)
        Tree._serialize(node.left, arraylist)
        Tree._serialize(node.right, arraylist)

    def serialize(self) :
        self.result = []
        Tree._serialize(self.head, self.result)
        


def main() :
    
    t = Tree()
    root = Node(3)
    left = Node(4)
    right = Node(5)

    root.left = left
    root.right = right
    
    t.head = root
    t.dfs(t.head)

    t.serialize()
    
    for num in t.result :
        print (num)


if __name__ == "__main__" :
    main()

    
