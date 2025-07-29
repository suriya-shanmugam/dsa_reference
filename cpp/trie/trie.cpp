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

		bool is_starts_with(std::string letters){
			Node* current_node = head;
			for(const char& ch : letters){
				if(current_node->children.find(ch) == current_node->children.end()){
					return false;
				}
				current_node = current_node->children[ch];
			}
			return true;
		}

		bool search_with_dot(std::string chars){
			return dfs_search(head, 0, chars);
		}
	
	private:
		Node* head;

		bool dfs_search (Node* current_node, int index, std::string& chars){
			
			for (int i=index; i < chars.size(); i++){
				char c = chars[i];
				if(c == '.'){
					
					for (auto& [_, child] : current_node->children ) {
						
						if(dfs_search(child, i+1, chars)){
							return true;
						}
					}
					return false;
				}
				else{
					if (current_node->children.find(c) == current_node->children.end()){
						return false;
					}
					current_node = current_node->children[c];
				}
			}
			if(current_node->is_word == true){
				return true;
			}
			return false;

		}

};

int main(){
	Trie trie;
	
	std::string word = "cat";
	std::string word2 = "catalina";
	trie.add(word);
	trie.add(word2);
	
	std::cout << "Is the word `cat` found" << trie.is_word_found(word) << std::endl;
	std::cout << "Is the word `Lat` found" << trie.is_word_found("ate") << std::endl;
	std::cout << "Is the word `catalina` found" << trie.is_word_found("catalina") << std::endl;


	std::cout << "Is there a word starts with `ca` " << trie.is_starts_with("ca") << std::endl;
	std::cout << "Is there a word starts with `ac` " << trie.is_starts_with("ac") << std::endl;
        
	//std::cout << "Search for pattern `c.t` " << trie.search_with_dot("c.t") << std::endl;
        //std::cout << "Search for pattern `c.ta` " << trie.search_with_dot("c.ta") << std::endl;
	std::cout << "Search for pattern `c.tali..` " << trie.search_with_dot("c.tali..") << std::endl;

	return 0;
}
