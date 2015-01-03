//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef AUTOBOOST_MOVE_MOVE_TRAITS_HPP
#define AUTOBOOST_MOVE_MOVE_TRAITS_HPP

#include <autoboost/move/detail/config_begin.hpp>
#include <autoboost/type_traits/has_trivial_destructor.hpp>
#include <autoboost/type_traits/is_nothrow_move_constructible.hpp>
#include <autoboost/type_traits/is_nothrow_move_assignable.hpp>
#include <autoboost/type_traits/is_copy_constructible.hpp>
#include <autoboost/move/detail/meta_utils.hpp>

#ifndef AUTOBOOST_NO_CXX11_RVALUE_REFERENCES
#include <autoboost/move/core.hpp>
#endif

namespace autoboost {

//! If this trait yields to true
//! (<i>has_trivial_destructor_after_move &lt;T&gt;::value == true</i>)
//! means that if T is used as argument of a move construction/assignment,
//! there is no need to call T's destructor.
//! This optimization tipically is used to improve containers' performance.
//!
//! By default this trait is true if the type has trivial destructor,
//! every class should specialize this trait if it wants to improve performance
//! when inserted in containers.
template <class T>
struct has_trivial_destructor_after_move
   : ::autoboost::has_trivial_destructor<T>
{};

//! By default this traits returns
//! <pre>autoboost::is_nothrow_move_constructible<T>::value && autoboost::is_nothrow_move_assignable<T>::value </pre>.
//! Classes with non-throwing move constructor
//! and assignment can specialize this trait to obtain some performance improvements.
template <class T>
struct has_nothrow_move
{
   static const bool value = autoboost::is_nothrow_move_constructible<T>::value &&
                             autoboost::is_nothrow_move_assignable<T>::value;
};

namespace move_detail {

template <class T>
struct is_nothrow_move_constructible_or_uncopyable
{
   //The standard requires is_nothrow_move_constructible for move_if_noexcept
   //but a user (usually in C++03) might specialize has_nothrow_move which includes it
   static const bool value = autoboost::is_nothrow_move_constructible<T>::value ||
                             has_nothrow_move<T>::value ||
                            !autoboost::is_copy_constructible<T>::value;
};

}  //move_detail {
}  //namespace autoboost {

#include <autoboost/move/detail/config_end.hpp>

#endif //#ifndef AUTOBOOST_MOVE_MOVE_TRAITS_HPP
