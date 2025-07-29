
#include<iostream>
#include<string>

bool ispalindrom( std::string str){

    if (str.size() <= 1){
        return true;
    }
    if (str[0] != str[str.size()-1]){
        return false;
    }
    
    return ispalindrom(str.substr(1,str.size()-2));

}

int main(){

    std::string str = "amma";
    std::cout << ispalindrom(str) << std::endl;


}