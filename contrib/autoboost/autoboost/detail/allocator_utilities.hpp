/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See Boost website at http://www.boost.org/
 */

#ifndef AUTOBOOST_DETAIL_ALLOCATOR_UTILITIES_HPP
#define AUTOBOOST_DETAIL_ALLOCATOR_UTILITIES_HPP

#include <autoboost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <autoboost/detail/workaround.hpp>
#include <autoboost/mpl/eval_if.hpp>
#include <autoboost/type_traits/is_same.hpp>
#include <cstddef>
#include <memory>
#include <new>

namespace autoboost{

namespace detail{

/* Allocator adaption layer. Some stdlibs provide allocators without rebind
 * and template ctors. These facilities are simulated with the external
 * template class rebind_to and the aid of partial_std_allocator_wrapper.
 */

namespace allocator{

/* partial_std_allocator_wrapper inherits the functionality of a std
 * allocator while providing a templatized ctor and other bits missing
 * in some stdlib implementation or another.
 */

template<typename Type>
class partial_std_allocator_wrapper:public std::allocator<Type>
{
public:
  /* Oddly enough, STLport does not define std::allocator<void>::value_type
   * when configured to work without partial template specialization.
   * No harm in supplying the definition here unconditionally.
   */

  typedef Type value_type;

  partial_std_allocator_wrapper(){};

  template<typename Other>
  partial_std_allocator_wrapper(const partial_std_allocator_wrapper<Other>&){}

  partial_std_allocator_wrapper(const std::allocator<Type>& x):
    std::allocator<Type>(x)
  {
  };

#if defined(AUTOBOOST_DINKUMWARE_STDLIB)
  /* Dinkumware guys didn't provide a means to call allocate() without
   * supplying a hint, in disagreement with the standard.
   */

  Type* allocate(std::size_t n,const void* hint=0)
  {
    std::allocator<Type>& a=*this;
    return a.allocate(n,hint);
  }
#endif

};

/* Detects whether a given allocator belongs to a defective stdlib not
 * having the required member templates.
 * Note that it does not suffice to check the Boost.Config stdlib
 * macros, as the user might have passed a custom, compliant allocator.
 * The checks also considers partial_std_allocator_wrapper to be
 * a standard defective allocator.
 */

#if defined(AUTOBOOST_NO_STD_ALLOCATOR)&&\
  (defined(AUTOBOOST_HAS_PARTIAL_STD_ALLOCATOR)||defined(AUTOBOOST_DINKUMWARE_STDLIB))

template<typename Allocator>
struct is_partial_std_allocator
{
  AUTOBOOST_STATIC_CONSTANT(bool,
    value=
      (is_same<
        std::allocator<AUTOBOOST_DEDUCED_TYPENAME Allocator::value_type>,
        Allocator
      >::value)||
      (is_same<
        partial_std_allocator_wrapper<
          AUTOBOOST_DEDUCED_TYPENAME Allocator::value_type>,
        Allocator
      >::value));
};

#else

template<typename Allocator>
struct is_partial_std_allocator
{
  AUTOBOOST_STATIC_CONSTANT(bool,value=false);
};

#endif

/* rebind operations for defective std allocators */

template<typename Allocator,typename Type>
struct partial_std_allocator_rebind_to
{
  typedef partial_std_allocator_wrapper<Type> type;
};

/* rebind operation in all other cases */

template<typename Allocator>
struct rebinder
{
  template<typename Type>
  struct result
  {
      typedef typename Allocator::AUTOBOOST_NESTED_TEMPLATE
          rebind<Type>::other other;
  };
};

template<typename Allocator,typename Type>
struct compliant_allocator_rebind_to
{
  typedef typename rebinder<Allocator>::
      AUTOBOOST_NESTED_TEMPLATE result<Type>::other type;
};

/* rebind front-end */

template<typename Allocator,typename Type>
struct rebind_to:
  mpl::eval_if_c<
    is_partial_std_allocator<Allocator>::value,
    partial_std_allocator_rebind_to<Allocator,Type>,
    compliant_allocator_rebind_to<Allocator,Type>
  >
{
};

/* allocator-independent versions of construct and destroy */

template<typename Type>
void construct(void* p,const Type& t)
{
  new (p) Type(t);
}

#if AUTOBOOST_WORKAROUND(AUTOBOOST_MSVC,AUTOBOOST_TESTED_AT(1500))
/* MSVC++ issues spurious warnings about unreferencend formal parameters
 * in destroy<Type> when Type is a class with trivial dtor.
 */

#pragma warning(push)
#pragma warning(disable:4100)
#endif

template<typename Type>
void destroy(const Type* p)
{

#if AUTOBOOST_WORKAROUND(__SUNPRO_CC,AUTOBOOST_TESTED_AT(0x590))
  const_cast<Type*>(p)->~Type();
#else
  p->~Type();
#endif

}

#if AUTOBOOST_WORKAROUND(AUTOBOOST_MSVC,AUTOBOOST_TESTED_AT(1500))
#pragma warning(pop)
#endif

} /* namespace autoboost::detail::allocator */

} /* namespace autoboost::detail */

} /* namespace autoboost */

#endif
