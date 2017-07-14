//Purpose:
//  See if a map can be implemented similar to a tuple
//  implemented as a multiply inherited pairs where
//  first element in the pair is a std::size_t key.
//  The difference w.r.t. the proposed map being
//  the first element of the pair(the key) is a type
//  instead of a std::size_t.
//
  template
  < typename Key
  , typename Val
  >
  struct 
key_val_tpl
  //This is, essentially, element<std::size_t Key,Val>
  //here:
  //  https://github.com/ldionne/hana/blob/master/include/boost/hana/detail/closure.hpp#L20
  //except instead of typename Key, std::size_t Key is used.
  {
    Val get;
  };
  template
  < typename... KeyVal
  >
  struct 
map
  ;
  template
  < typename... Key
  , typename... Val
  >
  struct 
map
  < key_val_tpl<Key,Val>...
  >
  : key_val_tpl<Key,Val>...
    //This is, essentially, how tuple is implemented, but with
    //std::size_t's instead of Key.
    //See:
    //  https://github.com/ldionne/hana/blob/master/include/boost/hana/detail/closure.hpp#L20
    //  https://github.com/ldionne/hana/blob/master/include/boost/hana/detail/closure.hpp#L26
    //  
  {
  };
  
//{ gets:
//  the following get's were based on those
//  here:
/*
https://github.com/ldionne/hana/blob/master/include/boost/hana/detail/closure.hpp#L89
 */
//  but adapted to keys being types instead of unsigned int's.
//
 
template <typename Key, typename Xn>
static constexpr Xn const&
get(key_val_tpl<Key, Xn> const& x)
{ return x.get; }

template <typename Key, typename Xn>
static constexpr Xn&
get(key_val_tpl<Key, Xn>& x)
{ return x.get; }

template <typename Key, typename Xn>
static constexpr Xn&&
get(key_val_tpl<Key, Xn>&& x)
{ return static_cast<key_val_tpl<Key, Xn>&&>(x).get; }
//} gets:

//********test it*****************
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
#include <boost/hana/fwd/integral_constant.hpp>
using namespace boost::hana;

int main()
{
      map
      < key_val_tpl<_uint<1>, data_val<1> >
      , key_val_tpl<_uint<2>, data_val<2> >
      , key_val_tpl<_uint<3>, data_val<3> >
      , key_val_tpl<_uint<4>, data_val<4> >
      >
    mud
      ;
    std::cout
      <<get<_uint<1>>(mud)<<"\n"
      <<get<_uint<2>>(mud)<<"\n"
      <<get<_uint<3>>(mud)<<"\n"
      <<get<_uint<4>>(mud)<<"\n"
      ;
    return 0;
}    
