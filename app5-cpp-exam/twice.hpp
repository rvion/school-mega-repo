#ifndef TWICE_INCLUDED_HPP
#define TWICE_INCLUDED_HPP

#include <iterator>
// https://db.tt/G9lzDGwq

template<typename BaseIterator>
struct twice_iterator
{
  typedef std::iterator_traits<BaseIterator> category_t;

  typedef typename category_t::value_type       value_type;
  typedef typename category_t::value_type       reference;
  typedef typename category_t::pointer          pointer;
  typedef typename category_t::difference_type  difference_type;
  typedef typename category_t::iterator_category iterator_category;

  twice_iterator( BaseIterator i) : base_(i)
  { 
  }

  twice_iterator operator++(int)
  {
    twice_iterator i = *this;
    base_++;
    return i;
  }

  twice_iterator& operator++()
  {
    base_++;
    return *this;
  }

  reference operator*()
  {
    return 2 * *base_;
  }

  pointer operator->()
  {
    return base_.operator->();
  }

  bool operator==(twice_iterator const& rhs)
  {
    return base_ == rhs.base_;
  }

  bool operator!=(twice_iterator const& rhs)
  {
    return base_ != rhs.base_;
  }

  private:
  BaseIterator  base_;
};

#endif