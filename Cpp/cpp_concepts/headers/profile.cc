#include "profile.h"


Profile::Profile(const std::string &name, int age){
 	this->name = name;
	this->age = age;
}

std::string Profile::getName() const {
	return this->name;

}

int Profile::getAge() const{
	return this->age;
}

