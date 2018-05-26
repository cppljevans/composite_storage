//Purpose:
//  See if a variant can be implemented as close as
//  possible to a tuple.
#include <algorithm> //for std::max
#include "./map_index_type.hpp"

namespace composite_storage
{

  template <typename Key, typename Val>
struct key_val_var
  //Purpose:
  //  Key Value pair for map-like container similar to a variant.
  //  However, instead of an numerical index, a type, Key,
  //  is the index.
  //Design:
  //  It differs from key_val_tpl by *not* containing:
  //    Val get;
  //  because the container, of which this is a superclass,
  //  can only hold 1 of a number of types; hence, the storage
  //  for the value is passed up from the container to the
  //  *protected* construct, destruct methods.
  {
  public:
      using key=Key;
  protected:
        template<typename... Args>
          static
        void 
      construct
        ( void*storage
        , Args&&... args
        )
        {
          new (storage) Val(std::forward<Args>(args)...);
        }
          static
        void 
      destruct
        ( void*storage
        )
        {
          auto p=static_cast<Val*>(storage);
          p->~Val();
        }
          static
        Val*
      get_val_ptr
        ( void*storage
        )
        {
          auto p=static_cast<Val*>(storage);
          return p;
        }
          static
        Val const*
      get_val_ptr
        ( void const*storage
        )
        {
          auto p=static_cast<Val const*>(storage);
          return p;
        }
  };

  template<typename... KeyVals>
struct map;
    
  template
  < typename... Keys
  , typename... Vals
  >
struct map
  < key_val_var<Keys, Vals>...
  >
  : key_val_var<Keys, Vals>...
  {
        static constexpr std::size_t
      our_size_value
        =std::max({sizeof(Vals)...});
  private:
        typename std::aligned_union<our_size_value,Vals...>::type
      my_storage;
        std::size_t
      my_which;
        void*
      storage()
        { return static_cast<void*>(std::addressof(my_storage));
        }
        void const*
      storage()const
        { return static_cast<void*>(std::addressof(my_storage));
        }
        using
      our_map_index_type=map_index_type<Keys...>
        ;
        template
        < typename SomeKey
        , typename SomeVal
        , typename... Args
        >
        void
      construct_at_key
        ( key_val_var<SomeKey, SomeVal>&
        , Args&&... args
        )
        { 
          key_val_var<SomeKey, SomeVal>::
            construct
            ( storage()
            , std::forward<Args>(args)...
            );
          using index_t=
            decltype
            ( index_at_type<SomeKey>
              ( std::declval<our_map_index_type>()
              )
            );
          my_which=index_t::value;
        }
        template
        < typename SomeKey
        , typename SomeVal
        >
        SomeVal*
      get_at_key
        ( key_val_var<SomeKey, SomeVal>&
        )
        { 
            using 
          index_t=
            decltype
            ( index_at_type<SomeKey>
              ( std::declval<our_map_index_type>()
              )
            );
          if(my_which==index_t::value)
          {
            return key_val_var<SomeKey, SomeVal>::
              get_val_ptr
              ( storage()
              );
          }
          else
          {
            return static_cast<SomeVal*>(0);
          }
        }
        template
        < typename SomeKey
        , typename SomeVal
        >
        SomeVal const*
      get_at_key
        ( key_val_var<SomeKey, SomeVal>const&
        )const
        { 
            using 
          index_t=
            decltype
            ( index_at_type<SomeKey>
              ( std::declval<our_map_index_type>()
              )
            );
          if(my_which==index_t::value)
          {
            return key_val_var<SomeKey, SomeVal>::
              get_val_ptr
              ( storage()
              );
          }
          else
          {
            return static_cast<SomeVal const*>(0);
          }
        }
        void
      destroy_which()
        {
          typedef void(*destructor_t)(void*);
          destructor_t destructors[]={key_val_var<Keys, Vals>::destruct...} ;
          destructors[my_which](storage());
        }
  public:
        std::size_t
      which()const
        { return my_which;
        }
        template
        < typename SomeKey
        >
      map
        ( SomeKey
        )
        { 
          construct_at_key<SomeKey>(*this);
        }
        template
        < typename SomeKey
        , typename SomeVal
        >
        void
      put
        ( SomeVal const& a_val
        )
        { 
          destroy_which();
          construct_at_key<SomeKey>(*this,a_val);
        }
        template
        < typename SomeKey
        >
        auto
      get_ptr
        ( void
        )
        { 
          return get_at_key<SomeKey>(*this);
        }
        template
        < typename SomeKey
        >
        auto
      get_ptr
        ( void
        )const
        { 
          return get_at_key<SomeKey>(*this);
        }
  };

}//exit composite_storage namespace

using namespace composite_storage;

#include "./data_val.hpp"
template<std::size_t Index>
using ndx_t=std::integral_constant<std::size_t,Index>;

//********test it*****************
    
int main(int argc, const char * argv[])
{
      map
      < key_val_var<ndx_t<0>,data_val<0>>
      , key_val_var<ndx_t<1>,data_val<1>>
      , key_val_var<ndx_t<2>,data_val<2>>
      >
    cs_v(ndx_t<1>{});
    std::cout<<":which@val<1>="<<cs_v.which()<<"\n";
    std::cout<<":val<1>="<<*(cs_v.get_ptr<ndx_t<1>>())<<"\n";
    std::cout<<":val<0>*="<<cs_v.get_ptr<ndx_t<0>>()<<"\n";
    cs_v.put<ndx_t<2>>(data_val<2>{});
    std::cout<<":which@val<2>="<<cs_v.which()<<"\n";
    std::cout<<":val<2>="<<*(cs_v.get_ptr<ndx_t<2>>())<<"\n";
    return 0;
}
