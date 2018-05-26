#ifndef NDX_DATA_VAL_INCLUDED
#define NDX_DATA_VAL_INCLUDED
#include <type_traits>
#include <iostream>

template<std::size_t Index>
using ndx_t=std::integral_constant<std::size_t,Index>;

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
#endif//NDX_DATA_VAL_INCLUDED
