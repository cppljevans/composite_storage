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

#include "./data_val.hpp"
template<std::size_t Index>
using ndx_t=std::integral_constant<std::size_t,Index>;

//********test it*****************

int main()
{
      map
      < key_val_tpl<ndx_t<1>, data_val<1> >
      , key_val_tpl<ndx_t<2>, data_val<2> >
      , key_val_tpl<ndx_t<3>, data_val<3> >
      , key_val_tpl<ndx_t<4>, data_val<4> >
      >
    mud
      ;
    std::cout
      <<get<ndx_t<1>>(mud)<<"\n"
      <<get<ndx_t<2>>(mud)<<"\n"
      <<get<ndx_t<3>>(mud)<<"\n"
      <<get<ndx_t<4>>(mud)<<"\n"
      ;
    return 0;
}    
