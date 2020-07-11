#include "MapAsVariant.hpp"
using namespace composite_storage;

#include "./ndx_data_val.hpp"

//********test it*****************
    
int main(int argc, const char * argv[])
{
  {
    std::cout<<"contruct default.\n";
      map
      < key_val_var<ndx_t<0>,data_val<0>>
      , key_val_var<ndx_t<1>,data_val<1>>
      , key_val_var<ndx_t<2>,data_val<2>>
      >
    cs_v;
    std::cout<<":empty="<<cs_v.is_empty()<<"\n";
    std::cout<<":which="<<cs_v.which()<<"\n";
    std::cout<<":val<0>*="<<cs_v.get_ptr<ndx_t<0>>()<<"\n";
    std::cout<<":val<1>*="<<cs_v.get_ptr<ndx_t<1>>()<<"\n";
    std::cout<<":val<2>*="<<cs_v.get_ptr<ndx_t<2>>()<<"\n";
    cs_v.put<ndx_t<2>>(data_val<2>{});
    std::cout<<":which@val<2>="<<cs_v.which()<<"\n";
    std::cout<<":val<2>="<<*(cs_v.get_ptr<ndx_t<2>>())<<"\n";
  }
  {
    std::cout<<"contruct with ndx_t<1>.\n";
      map
      < key_val_var<ndx_t<0>,data_val<0>>
      , key_val_var<ndx_t<1>,data_val<1>>
      , key_val_var<ndx_t<2>,data_val<2>>
      >
    cs_v(ndx_t<1>{});
    std::cout<<":empty@val<1>="<<cs_v.is_empty()<<"\n";
    std::cout<<":which@val<1>="<<cs_v.which()<<"\n";
    std::cout<<":val<1>="<<*(cs_v.get_ptr<ndx_t<1>>())<<"\n";
    std::cout<<":val<0>*="<<cs_v.get_ptr<ndx_t<0>>()<<"\n";
    cs_v.put<ndx_t<2>>(data_val<2>{});
    std::cout<<":which@val<2>="<<cs_v.which()<<"\n";
    std::cout<<":val<2>="<<*(cs_v.get_ptr<ndx_t<2>>())<<"\n";
  }
  return 0;
}
