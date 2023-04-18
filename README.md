# Custom AVL Tree

This project was made for Data Structures and Algorithms

Binary Search Trees (BST) can often be an efficient and useful way to store and retrieve sorted data. However, the efficiency of these data trees relies heavily on how balanced a BST is. For example, searching through the BST on the left is much more efficient than searching through the BST on the right, despite both figures showing valid BST with the exact same elements.

To avoid inefficient binary search trees, we use balanced Binary Search Trees. A balanced BST has a balance factor of less than ±threshold, where the balance factor is the difference in heights of the left and right subtrees at any given tree node. One such balanced tree is an AVL tree that maintains a threshold of 1. As soon as a node in an AVL tree has a balance factor of +2/-2, “tree rotations” are performed to maintain balance in the tree.

# Methods built in the AVL Tree:

insert    	     ->   Add a Student object into the tree with the specified name, number ID. The ID must be unique.
remove	         ->   Find and remove the account with the specified ID from the tree.
removeInorder	   ->   Remove the Nth ID from the inorder traversal of the tree (N = 0 for the first item, etc).
search	         ->   Search for the student with the specified ID or name from the tree.
printInorder	   ->   Print the tree using inOrder traversal.
printPreorder	   ->   Print the tree using preOrder traversal.
printPostorder	 ->   Print the tree using postOrder traversal.
printLevelCount	 ->   Print the tree using levelOrder traversal.

# Example User Input

8 
insert "Brandon" 45679999 
insert "Brian" 35459999 
insert "Briana" 87879999 
insert "Bella" 95469999 
printInorder 
remove 45679999 
removeInorder 2 
printInorder

# Example User Output

successful 
successful 
successful 
successful 
Brian, Brandon, Briana, Bella 
successful 
successful 
Brian, Briana
