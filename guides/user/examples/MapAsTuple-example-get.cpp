#include "MapAsTuple.hpp"
#include "ndx_data_val.hpp"
int main()
{
  { std::cout<<"default CTOR\n";
    auto mud=
      make_map
      ( key_val_tpl<ndx_t<1>, data_val<1> >{}
      , key_val_tpl<ndx_t<2>, data_val<2> >{}
      , key_val_tpl<ndx_t<3>, data_val<3> >{}
      , key_val_tpl<ndx_t<4>, data_val<4> >{}
      )
      ;
    std::cout
      <<get_val<ndx_t<1>>(mud)<<"\n"
      <<get_val<ndx_t<2>>(mud)<<"\n"
      <<get_val<ndx_t<3>>(mud)<<"\n"
      <<get_val<ndx_t<4>>(mud)<<"\n"
      ;
  }
  { std::cout<<"fwd CTOR\n";
      map
      < key_val_tpl<ndx_t<1>, data_val<1> >
      , key_val_tpl<ndx_t<2>, data_val<2> >
      , key_val_tpl<ndx_t<3>, data_val<3> >
      , key_val_tpl<ndx_t<4>, data_val<4> >
      >
    mud
      ( key_val_tpl<ndx_t<1>, data_val<1> >{}
      , key_val_tpl<ndx_t<2>, data_val<2> >{}
      , key_val_tpl<ndx_t<3>, data_val<3> >{}
      , key_val_tpl<ndx_t<4>, data_val<4> >{}
      )
      ;
    std::cout
      <<get_val<ndx_t<1>>(mud)<<"\n"
      <<get_val<ndx_t<2>>(mud)<<"\n"
      <<get_val<ndx_t<3>>(mud)<<"\n"
      <<get_val<ndx_t<4>>(mud)<<"\n"
      ;
  }
    return 0;
}    
