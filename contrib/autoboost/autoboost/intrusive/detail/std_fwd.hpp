//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef AUTOBOOST_INTRUSIVE_DETAIL_STD_FWD_HPP
#define AUTOBOOST_INTRUSIVE_DETAIL_STD_FWD_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

#if defined(__clang__) && defined(_LIBCPP_VERSION)
   #define AUTOBOOST_INTRUSIVE_CLANG_INLINE_STD_NS
   #pragma GCC diagnostic push
   #pragma GCC diagnostic ignored "-Wc++11-extensions"
   #define AUTOBOOST_INTRUSIVE_STD_NS_BEG _LIBCPP_BEGIN_NAMESPACE_STD
   #define AUTOBOOST_INTRUSIVE_STD_NS_END _LIBCPP_END_NAMESPACE_STD
#else
   #define AUTOBOOST_INTRUSIVE_STD_NS_BEG namespace std{
   #define AUTOBOOST_INTRUSIVE_STD_NS_END }
#endif

AUTOBOOST_INTRUSIVE_STD_NS_BEG

template<class T>
struct less;

template<class T>
struct equal_to;

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

AUTOBOOST_INTRUSIVE_STD_NS_END

#ifdef AUTOBOOST_INTRUSIVE_CLANG_INLINE_STD_NS
   #pragma GCC diagnostic pop
   #undef AUTOBOOST_INTRUSIVE_CLANG_INLINE_STD_NS
#endif   //AUTOBOOST_INTRUSIVE_CLANG_INLINE_STD_NS

#endif //#ifndef AUTOBOOST_INTRUSIVE_DETAIL_STD_FWD_HPP

