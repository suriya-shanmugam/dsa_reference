#include <iostream>
#include <map>
#include <vector>
#include <list>


int main(){

   
    
    std::map<int, std::vector<std::string>> directed_neighbors;
    std::vector<std::string> address_0 = {"127.0.0.1:50052"};
    std::vector<std::string> address_1 = {"127.0.0.1:50053","127.0.0.1:50054"};
    std::vector<std::string> address_2 = {"127.0.0.1:50055"};
    std::vector<std::string> address_3 = {};
    std::vector<std::string> address_4 = {};
    directed_neighbors[0] = address_0;
    directed_neighbors[1] = address_1;
    directed_neighbors[2] = address_2;
    directed_neighbors[3] = address_3;
    directed_neighbors[4] = address_4;

    for (const auto& pair : directed_neighbors){
        std::cout << pair.first << std::endl;

        for (const auto& server_address : pair.second){

            std::cout << server_address <<  " " ;

        }
        std::cout << std::endl ;
    }
    
    return 0;
}