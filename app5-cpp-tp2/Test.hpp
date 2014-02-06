#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <map>
#include <exception>
#include <string>

#include "Clonable.hpp"


class Test : public Clonable
{
	public:
		virtual Test* clone () const {
			return (new Test());
		} 
		virtual std::string to_s() const {
			return "I'm a test";
		}

		Test() :_a(0) {}
		Test(std::string const & s) {if (s == "super") {_a=0;} else {_a=1;}}
		~Test() {}
	
	private:
		int _a;
};

#endif