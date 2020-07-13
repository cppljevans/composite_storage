// Copyright Larry Evans 2020
// Distributed under the Boost Software License, Version 1.0.
// (See license copy at http://boost.org/LICENSE_1_0.txt)
#ifndef MAP_INDEX_TYPE_HPP_INCLUDED
#define MAP_INDEX_TYPE_HPP_INCLUDED
//Purpose:
//  map of index to type;  type_at_index; index_at_type. No data.
#include <utility>
#include <type_traits>
#include "pair_index_type.hpp"
namespace composite_storage
{
    namespace detail
    {
        template
        < typename Indices
        , typename... Type
        >
      struct map_index_type
      ;
        template
        < std::size_t... Indices
        , typename... Type
        >
      struct map_index_type
        < std::integer_sequence<std::size_t, Indices...>
        , Type...
        >
      : pair_index_type<Indices,Type>...
      {};
    }
    
    template<typename... Type>
    using map_index_type
      = detail::map_index_type
        < std::make_index_sequence<sizeof...(Type)>
        , Type...
        >;
    
    template <std::size_t Index, typename Type>
    static Type
    type_at_index(pair_index_type<Index,Type>const&)
    ;
    template <typename Type, std::size_t Index>
    static std::integral_constant<std::size_t,Index>
    index_at_type(pair_index_type<Index,Type>const&)
    ;
}//exit composite_storage namespace
#endif//MAP_INDEX_TYPE_HPP_INCLUDED
