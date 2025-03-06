
// Recurssion pass by Value

#include <iostream>
#include <string>

std::string reverse(std::string str){

    if (str.size() == 0){
        return str ;
    }
    return reverse(str.substr(1,str.size()-1)) + str[0];
}


int main(){

    std::string res = "Hello";
    std::cout << res  << std::endl;
    
    std::cout << reverse(res) <<  std::endl;   

}