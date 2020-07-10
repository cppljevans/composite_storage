#ifndef NDX_DATA_VAL_INCLUDED
#define NDX_DATA_VAL_INCLUDED
#include <type_traits>
#include <iostream>
#include <stdexcept>

template<std::size_t Index>
using ndx_t=std::integral_constant<std::size_t,Index>;

template<unsigned TagVal>
struct data_val
//Represents some arbitrary data value.
{
  using val_t=unsigned;
  val_t val;
  data_val(val_t val=TagVal)
    : val(val)
    {
        std::cout<<"data_val<"<<TagVal<<">::(val_t=TagVal):val="<<val<<"\n";
    }
  data_val(data_val const& x)
    : val(x.val)
    {  
        std::cout<<"data_val<"<<TagVal<<">::(data_val const&):val="<<val<<"\n";
        if(val!=TagVal) throw std::runtime_error( "data_val(data_val const&)" );
    }
};

  template<unsigned TagVal>
  std::ostream&
operator<<
  ( std::ostream&sout
  , data_val<TagVal>const&x
  )
  {
    
      sout
        <<"data_val<"
        <<TagVal
        <<">:val="
        <<x.val;
      return sout;
  }
#endif//NDX_DATA_VAL_INCLUDED
