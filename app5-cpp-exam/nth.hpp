#ifndef NTH_INCLUDED_HPP
#define NTH_INCLUDED_HPP

#include <iterator>
// https://db.tt/G9lzDGwq

template<typename BaseIterator, int n>
struct every_nth_iterator
{
  typedef std::iterator_traits<BaseIterator> category_t;

  typedef typename category_t::value_type       value_type;
  typedef typename category_t::pointer          pointer;
  typedef typename category_t::difference_type  difference_type;
  typedef typename category_t::iterator_category iterator_category;
   
  typedef typename category_t::reference        reference;
  // typedef typename category_t::value_type    reference;
  

  every_nth_iterator() : base_(0)
  {
  }

  every_nth_iterator(BaseIterator i) : base_(i)
  {
  }

  every_nth_iterator(const every_nth_iterator & i)
  {
      base_ = i.base_;
  }

  every_nth_iterator operator++(int)
  {
    every_nth_iterator i = *this;
    base_+= n;
    return i;
  }

  every_nth_iterator& operator++()
  {
    base_+=n;
    return *this;
  }

  reference operator*()
  {
    return *base_;
  }

  pointer operator->()
  {
    return base_.operator->();
  }

  bool operator==(every_nth_iterator const& rhs)
  {
    return base_ == rhs.base_;
  }

  bool operator!=(every_nth_iterator const& rhs)
  {
    return base_ != rhs.base_;
  }

  private:
  BaseIterator  base_;
};

#endif