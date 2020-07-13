// Copyright Larry Evans 2020
// Distributed under the Boost Software License, Version 1.0.
// (See license copy at http://boost.org/LICENSE_1_0.txt)
#ifndef PAIR_INDEX_TYPE_HPP_INCLUDED
#define PAIR_INDEX_TYPE_HPP_INCLUDED
//Purpose:
//  pair of index and type.  No data.
#include <cstdlib>
namespace composite_storage
{
    template<std::size_t Index, typename Type>
    struct pair_index_type
    {
    };
}//exit composite_storage namespace
#endif
