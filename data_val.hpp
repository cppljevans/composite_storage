#ifndef DATA_VAL_HPP_INCLUDED
#define DATA_VAL_HPP_INCLUDED
#include <iostream>
template<unsigned TagVal>
struct data_val
//Represents some arbitrary data value.
{
};

  template<unsigned TagVal>
  std::ostream&
operator<<
  ( std::ostream&sout
  , data_val<TagVal>const&
  )
  {
    
    sout
      <<"data_val<"
      <<TagVal
      <<">";
    return sout;
  }
#endif//DATA_VAL_HPP_INCLUDED
