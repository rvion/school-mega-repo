#ifndef FACTORY_HPP
#define FACTORY_HPP


#include <iostream>
#include <map>
#include <exception>
#include <string>

#include "Test.hpp"

template <typename T>
class Factory
{
	public:

		struct TypeNotFound : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "TypeNotFound";
			}
		};
		typedef std::map<std::string, T*> _T;
		static void setup() {
			add("test", new Test());
		}

		static void add(std::string const & k, T* v) {
			factoryStorage()[k]=v;
		}

		T* make(std::string const & k) {
			if(auto kk = factoryStorage()[k]){
				return kk->clone();				
			}
			throw TypeNotFound();
		}
	  
	  static _T& factoryStorage()
	  {
	    static _T products;
	    return products;
	  }

		Factory() {setup();}
		virtual ~Factory(){}

	private:
		static std::map<std::string, T*> _map;
};

#endif