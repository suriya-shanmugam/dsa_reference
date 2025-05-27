#include<iostream>

struct Node{
	int value;
	Node* left;
	Node* right;
};

class BinarySearchTree {
	public :
		Node* head;
		
		// FFT - Constructor accepting the copy of the param to avoid maintaining the life cycle
		BinarySearchTree(int value){
			head = new Node{value,nullptr,nullptr};
		}
		
		void append(int value){
			head = _append(head, value);
		}
		
		void inorder(){
			_inorder(head); 
		}
		
		void remove(int value){
			_remove(head, value);
		}
	
	private:	
		
		Node* _append(Node* node, int value){
			if (node == nullptr){
				return new Node{value,nullptr,nullptr};
			}
			if (value < node->value ){
				node->left = _append(node->left, value);
			}else{
				node->right = _append(node->right, value);
			}
			return node;
		}

		void _inorder(Node* node){
			if(node == nullptr){
				return;
			}
			_inorder(node->left);
			std::cout << node->value << std::endl;
			_inorder(node->right);

		}

		Node* _remove(Node* node, int value){
			if (value < node->value){
				node->left = _remove(node->left, value); 
			}else if(value > node->value){
				node->right = _remove(node->right, value);
			}else{
				if (node->left == nullptr ){
					return node->right;
				}else if (node->right == nullptr){
					return node->left;
				}else{
					Node* max_left = node->left;
					while(max_left != nullptr){
						max_left = node->right; 
					}
					node->value = max_left->value;
					node->left = _remove(node->left, max_left->value);
				}
			}
			return node;
		}
};

int main(){
	BinarySearchTree tree(10);
	tree.append(11);
	tree.append(12);
	tree.append(9);
	tree.append(3);
	tree.append(7);
	tree.append(6);
	tree.append(4);
	tree.append(5);
	tree.inorder();
	tree.remove(7);
	tree.inorder();
	//std::cout << "Head value" << tree.head->value << "Right value " << tree.head->right->value ;
	return 0;
}
