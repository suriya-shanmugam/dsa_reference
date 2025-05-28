#include<iostream>
#include<unordered_map>
#include<string>

struct Node {
	bool is_word = false;
	std::unordered_map<char, Node*> children;
};

class Trie {
	public :
		Trie(){
			head = new Node{false, {}};
		}

		void add(std::string word){
			Node* current_node = head;
			for (const char& ch : word ){
				if ( current_node->children.find(ch) != current_node->children.end()){
					current_node = current_node->children[ch];
				}else {
					current_node->children[ch] = new Node{false,{}};
					current_node = current_node->children[ch];
				}
			}
			current_node->is_word = true;
		}

		bool is_word_found(std::string word){
			Node* current_node = head;
			for (const char&ch : word){
				if(current_node->children.find(ch) != current_node->children.end()){
					current_node = current_node->children[ch];
				}else{
					return false;
				}
			}
			return  current_node->is_word; 
		}
	
	private:
		Node* head;
};

int main(){
	Trie trie;
	std::string word = "cat";
	trie.add(word);
	std::cout << "Is the word `cat` found" << trie.is_word_found(word) << std::endl;
	std::cout << "Is the word `Lat` found" << trie.is_word_found("ate") << std::endl;
	return 0;
}
