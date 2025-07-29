

#include<string>
#ifndef PROFILE_H
#define PROFILE_H


class Profile {

	public:
		
		
		std::string name;
		int age;

		Profile(const std::string &name, int age);

		std::string  getName() const;
		int getAge() const;
};


#endif
