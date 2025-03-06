
// Recurssion pass by Reference

#include <iostream>
#include <string>



void reverse(std::string& str){

    if (str.size() == 0){
        std::cout << "Base case" << std::endl;
        return ;
    }
    char first_letter = str[0];
    std::cout << "Before call - "<< first_letter << std::endl;
    str.erase(0,1);
    
    reverse(str);
    str.push_back(first_letter);
    std::cout << "after call " << first_letter << std::endl;
    
}


int main(){

    std::string res = "Hello";
    std::cout << res << std::endl;
    reverse(res);
    std::cout << res <<  std::endl;   

}