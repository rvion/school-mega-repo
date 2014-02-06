#ifndef RANGE_NTH_INCLUDED_HPP
#define RANGE_NTH_INCLUDED_HPP

#include "nth.hpp"
#include <iterator>

template<class BaseIterator, int n>
struct every_nth_range 
{
  typedef every_nth_iterator<BaseIterator, n> nth;

  every_nth_range(const BaseIterator & begin, const BaseIterator & end) :
    _cache(0), _nth1(begin)
  {
      BaseIterator it(begin);
      BaseIterator last_correct(begin);
      while(it != end)
      {
          _cache++; 
          if(_cache % n == 0)
              last_correct = it;
          ++it;
      }
      _nth2 = nth(++last_correct);
  }

  nth begin(){return _nth1;}
  nth end(){return _nth2;}
  bool empty(){return _nth1 == _nth2;}
  bool size(){return _cache;}
    
  private:
    nth _nth1;
    nth _nth2;
    
    int _cache;
};

#endif