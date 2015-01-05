
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef AUTOBOOST_TT_IS_FUNDAMENTAL_HPP_INCLUDED
#define AUTOBOOST_TT_IS_FUNDAMENTAL_HPP_INCLUDED

#include <autoboost/type_traits/is_arithmetic.hpp>
#include <autoboost/type_traits/is_void.hpp>
#include <autoboost/type_traits/detail/ice_or.hpp>

// should be the last #include
#include <autoboost/type_traits/detail/bool_trait_def.hpp>

namespace autoboost {

namespace detail {

template <typename T> 
struct is_fundamental_impl
    : public ::autoboost::type_traits::ice_or< 
          ::autoboost::is_arithmetic<T>::value
        , ::autoboost::is_void<T>::value
        >
{ 
};

} // namespace detail

//* is a type T a fundamental type described in the standard (3.9.1)
#if defined( __CODEGEARC__ )
AUTOBOOST_TT_AUX_BOOL_TRAIT_DEF1(is_fundamental,T,__is_fundamental(T))
#else
AUTOBOOST_TT_AUX_BOOL_TRAIT_DEF1(is_fundamental,T,::autoboost::detail::is_fundamental_impl<T>::value)
#endif

} // namespace autoboost

#include <autoboost/type_traits/detail/bool_trait_undef.hpp>

#endif // AUTOBOOST_TT_IS_FUNDAMENTAL_HPP_INCLUDED
