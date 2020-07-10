#ifndef MAPASTUPLE_HPP_INCLUDED_2017_09_03
#define MAPASTUPLE_HPP_INCLUDED_2017_09_03
//Purpose:
//  See if a map can be implemented similar to a tuple
//  implemented as a multiply inherited pairs where
//  first element in the pair is a std::size_t key.
//  The difference w.r.t. the proposed map being
//  the first element of the pair(the key) is a type
//  instead of a std::size_t.
//Alternatives:
//  Based on the hana map documentation here:
//    http://www.boost.org/doc/libs/1_65_0/libs/hana/doc/html/index.html#tutorial-containers-elements
//  the hana::map does essentially the same thing.  The only difference between
//  here and there is that here:
//    key_val_tpl<Key,Val>
//  is used, whereas there:
//    hana::pair<type<Key>,Val>
//  is used.
//===================
  template
  < typename Key
  , typename Val
  >
  struct 
key_val_tpl
  //Purpose:
  //  Key Value pair for map-like container similar to a tuple.
  //  However, instead of an numerical index, a type, Key,
  //  is the index.
  //References:
  //  This is, essentially, element<std::size_t Key,Val>
  //  here:
  //    https://github.com/ldionne/hana/blob/master/include/boost/hana/detail/closure.hpp#L20
  //  except instead of typename Key, std::size_t Key is used.
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
    constexpr map()
      {}
    constexpr map
      ( key_val_tpl<Key,Val>const&... vals
      )
      : key_val_tpl<Key,Val>
        ( vals
        )...
      {}
  };
  
  template
  < typename... Key
  , typename... Val
  >
  constexpr auto
make_map
  (  key_val_tpl<Key,Val>const&... vals
  )
  {
    return map<key_val_tpl<Key,Val>...>(vals...);
  }    
//{ gets:
//  the following get's were based on those
//  here:
/*
https://github.com/ldionne/hana/blob/master/include/boost/hana/detail/closure.hpp#L89
 */
//  but adapted to keys being types instead of unsigned int's.
//
 
template <typename Key, typename Val>
static constexpr Val const&
get_val(key_val_tpl<Key, Val> const& x)
{ return x.get; }

template <typename Key, typename Val>
static constexpr Val&
get_val(key_val_tpl<Key, Val>& x)
{ return x.get; }

template <typename Key, typename Val>
static constexpr Val&&
get_val(key_val_tpl<Key, Val>&& x)
{ return static_cast<key_val_tpl<Key, Val>&&>(x).get; }

template <typename Key, typename Val>
static constexpr auto const&
get_key_val(key_val_tpl<Key, Val> const& x)
{ return x; }

template <typename Key, typename Val>
static constexpr auto&
get_key_val(key_val_tpl<Key, Val>& x)
{ return x; }

template <typename Key, typename Val>
static constexpr auto&&
get_key_val(key_val_tpl<Key, Val>&& x)
{ return static_cast<key_val_tpl<Key, Val>&&>(x); }
//} gets:

#endif//MAPASTUPLE_HPP_INCLUDED_2017_09_03
