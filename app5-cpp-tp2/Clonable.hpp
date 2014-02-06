#ifndef CLONABLE_HPP
#define CLONABLE_HPP

#include <iostream>
#include <map>
#include <exception>
#include <string>

class Clonable
{
public:
	virtual Clonable* clone() const=0; 
	virtual std::string to_s() const { return "generic message for clonable stuff" ;} 
};

#endif