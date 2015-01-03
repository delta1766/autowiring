// Copyright (C) 2001-2003
// William E. Kempf
// Copyright (C) 2011-2013 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef AUTOBOOST_THREAD_CONFIG_WEK01032003_HPP
#define AUTOBOOST_THREAD_CONFIG_WEK01032003_HPP

#include <autoboost/config.hpp>
#include <autoboost/detail/workaround.hpp>
#include <autoboost/thread/detail/platform.hpp>

//#define AUTOBOOST_THREAD_DONT_PROVIDE_INTERRUPTIONS
// ATTRIBUTE_MAY_ALIAS

#if defined(__GNUC__) && !defined(__INTEL_COMPILER)

  // GCC since 3.3 has may_alias attribute that helps to alleviate optimizer issues with
  // regard to violation of the strict aliasing rules.

  #define AUTOBOOST_THREAD_DETAIL_USE_ATTRIBUTE_MAY_ALIAS
  #define AUTOBOOST_THREAD_ATTRIBUTE_MAY_ALIAS __attribute__((__may_alias__))
#else
  #define AUTOBOOST_THREAD_ATTRIBUTE_MAY_ALIAS
#endif


#if defined AUTOBOOST_THREAD_THROW_IF_PRECONDITION_NOT_SATISFIED
#define AUTOBOOST_THREAD_ASSERT_PRECONDITION(EXPR, EX) \
        if (EXPR) {} else autoboost::throw_exception(EX)
#define AUTOBOOST_THREAD_VERIFY_PRECONDITION(EXPR, EX) \
        if (EXPR) {} else autoboost::throw_exception(EX)
#define AUTOBOOST_THREAD_THROW_ELSE_RETURN(EX, RET) \
        autoboost::throw_exception(EX)
#else
#define AUTOBOOST_THREAD_ASSERT_PRECONDITION(EXPR, EX)
#define AUTOBOOST_THREAD_VERIFY_PRECONDITION(EXPR, EX) \
        (void)(EXPR)
#define AUTOBOOST_THREAD_THROW_ELSE_RETURN(EX, RET) \
        return (RET)
#endif

// This compiler doesn't support Boost.Chrono
#if defined __IBMCPP__ && (__IBMCPP__ < 1100) \
  && ! defined AUTOBOOST_THREAD_DONT_USE_CHRONO
#define AUTOBOOST_THREAD_DONT_USE_CHRONO
#if ! defined AUTOBOOST_THREAD_USES_DATETIME
#define AUTOBOOST_THREAD_USES_DATETIME
#endif
#endif

// This compiler doesn't support Boost.Move
#if AUTOBOOST_WORKAROUND(__SUNPRO_CC, < 0x5100) \
  && ! defined AUTOBOOST_THREAD_DONT_USE_MOVE
#define AUTOBOOST_THREAD_DONT_USE_MOVE
#endif

// This compiler doesn't support Boost.Container Allocators files
#if defined __SUNPRO_CC \
  && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_CTOR_ALLOCATORS
#define AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_CTOR_ALLOCATORS
#endif

#if defined _WIN32_WCE && _WIN32_WCE==0x501 \
  && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_CTOR_ALLOCATORS
#define AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_CTOR_ALLOCATORS
#endif


#if defined AUTOBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX || defined AUTOBOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define AUTOBOOST_THREAD_NO_CXX11_HDR_INITIALIZER_LIST
#define AUTOBOOST_THREAD_NO_MAKE_LOCK_GUARD
#define AUTOBOOST_THREAD_NO_MAKE_STRICT_LOCK
#define AUTOBOOST_THREAD_NO_MAKE_NESTED_STRICT_LOCK
#endif

#if defined(AUTOBOOST_NO_CXX11_HDR_TUPLE) || defined(AUTOBOOST_NO_CXX11_RVALUE_REFERENCES)
#define AUTOBOOST_THREAD_NO_MAKE_UNIQUE_LOCKS
#define AUTOBOOST_THREAD_NO_SYNCHRONIZE
#elif defined _MSC_VER && _MSC_VER <= 1600
// C++ features supported by VC++ 10 (aka 2010)
#define AUTOBOOST_THREAD_NO_MAKE_UNIQUE_LOCKS
#define AUTOBOOST_THREAD_NO_SYNCHRONIZE
#endif

/// BASIC_THREAD_ID
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_BASIC_THREAD_ID \
 && ! defined AUTOBOOST_THREAD_PROVIDES_BASIC_THREAD_ID
#define AUTOBOOST_THREAD_PROVIDES_BASIC_THREAD_ID
#endif

/// RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR
//#if defined AUTOBOOST_NO_CXX11_RVALUE_REFERENCES || defined AUTOBOOST_MSVC
#define AUTOBOOST_THREAD_RVALUE_REFERENCES_DONT_MATCH_FUNTION_PTR
//#endif

// Default version
#if !defined AUTOBOOST_THREAD_VERSION
#define AUTOBOOST_THREAD_VERSION 2
#else
#if AUTOBOOST_THREAD_VERSION!=2  && AUTOBOOST_THREAD_VERSION!=3 && AUTOBOOST_THREAD_VERSION!=4
#error "AUTOBOOST_THREAD_VERSION must be 2, 3 or 4"
#endif
#endif

// CHRONO
// Uses Boost.Chrono by default if not stated the opposite defining AUTOBOOST_THREAD_DONT_USE_CHRONO
#if ! defined AUTOBOOST_THREAD_DONT_USE_CHRONO \
  && ! defined AUTOBOOST_THREAD_USES_CHRONO
#define AUTOBOOST_THREAD_USES_CHRONO
#endif

#if ! defined AUTOBOOST_THREAD_DONT_USE_ATOMIC \
  && ! defined AUTOBOOST_THREAD_USES_ATOMIC
#define AUTOBOOST_THREAD_USES_ATOMIC
//#define AUTOBOOST_THREAD_DONT_USE_ATOMIC
#endif

#if defined AUTOBOOST_THREAD_USES_ATOMIC
// Andrey Semashev
#define AUTOBOOST_THREAD_ONCE_ATOMIC
#else
//#elif ! defined AUTOBOOST_NO_CXX11_THREAD_LOCAL && ! defined AUTOBOOST_NO_THREAD_LOCAL && ! defined AUTOBOOST_THREAD_NO_UINT32_PSEUDO_ATOMIC
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2444.html#Appendix
#define AUTOBOOST_THREAD_ONCE_FAST_EPOCH
#endif
#if AUTOBOOST_THREAD_VERSION==2

// PROVIDE_PROMISE_LAZY
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_PROMISE_LAZY \
  && ! defined AUTOBOOST_THREAD_PROVIDES_PROMISE_LAZY
#define AUTOBOOST_THREAD_PROVIDES_PROMISE_LAZY
#endif

// PROVIDE_THREAD_EQ
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_THREAD_EQ \
  && ! defined AUTOBOOST_THREAD_PROVIDES_THREAD_EQ
#define AUTOBOOST_THREAD_PROVIDES_THREAD_EQ
#endif

#endif

#if AUTOBOOST_THREAD_VERSION>=3

// ONCE_CXX11
// fixme AUTOBOOST_THREAD_PROVIDES_ONCE_CXX11 doesn't works when thread.cpp is compiled AUTOBOOST_THREAD_VERSION 3
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_ONCE_CXX11 \
 && ! defined AUTOBOOST_THREAD_PROVIDES_ONCE_CXX11
#define AUTOBOOST_THREAD_DONT_PROVIDE_ONCE_CXX11
#endif

// THREAD_DESTRUCTOR_CALLS_TERMINATE_IF_JOINABLE
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_THREAD_DESTRUCTOR_CALLS_TERMINATE_IF_JOINABLE \
 && ! defined AUTOBOOST_THREAD_PROVIDES_THREAD_DESTRUCTOR_CALLS_TERMINATE_IF_JOINABLE
#define AUTOBOOST_THREAD_PROVIDES_THREAD_DESTRUCTOR_CALLS_TERMINATE_IF_JOINABLE
#endif

// THREAD_MOVE_ASSIGN_CALLS_TERMINATE_IF_JOINABLE
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_THREAD_MOVE_ASSIGN_CALLS_TERMINATE_IF_JOINABLE \
 && ! defined AUTOBOOST_THREAD_PROVIDES_THREAD_MOVE_ASSIGN_CALLS_TERMINATE_IF_JOINABLE
#define AUTOBOOST_THREAD_PROVIDES_THREAD_MOVE_ASSIGN_CALLS_TERMINATE_IF_JOINABLE
#endif

// PROVIDE_FUTURE
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE \
 && ! defined AUTOBOOST_THREAD_PROVIDES_FUTURE
#define AUTOBOOST_THREAD_PROVIDES_FUTURE
#endif

// FUTURE_CTOR_ALLOCATORS
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_CTOR_ALLOCATORS \
 && ! defined AUTOBOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
#define AUTOBOOST_THREAD_PROVIDES_FUTURE_CTOR_ALLOCATORS
#endif

// SHARED_MUTEX_UPWARDS_CONVERSIONS
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_SHARED_MUTEX_UPWARDS_CONVERSIONS \
 && ! defined AUTOBOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS
#define AUTOBOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS
#endif

// PROVIDE_EXPLICIT_LOCK_CONVERSION
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_EXPLICIT_LOCK_CONVERSION \
 && ! defined AUTOBOOST_THREAD_PROVIDES_EXPLICIT_LOCK_CONVERSION
#define AUTOBOOST_THREAD_PROVIDES_EXPLICIT_LOCK_CONVERSION
#endif

// GENERIC_SHARED_MUTEX_ON_WIN
#if ! defined AUTOBOOST_THREAD_DONT_PROVIDE_GENERIC_SHARED_MUTEX_ON_WIN \
 && ! defined AUTOBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN
#define AUTOBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN
#endif

// USE_MOVE
#if ! defined AUTOBOOST_THREAD_DONT_USE_MOVE \
 && ! defined AUTOBOOST_THREAD_USES_MOVE
#define AUTOBOOST_THREAD_USES_MOVE
#endif

#endif

// deprecated since version 4
#if AUTOBOOST_THREAD_VERSION < 4

// NESTED_LOCKS
#if ! defined AUTOBOOST_THREAD_PROVIDES_NESTED_LOCKS \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_NESTED_LOCKS
#define AUTOBOOST_THREAD_PROVIDES_NESTED_LOCKS
#endif

// CONDITION
#if ! defined AUTOBOOST_THREAD_PROVIDES_CONDITION \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_CONDITION
#define AUTOBOOST_THREAD_PROVIDES_CONDITION
#endif

// USE_DATETIME
#if ! defined AUTOBOOST_THREAD_DONT_USE_DATETIME \
 && ! defined AUTOBOOST_THREAD_USES_DATETIME
#define AUTOBOOST_THREAD_USES_DATETIME
#endif
#endif

#if AUTOBOOST_THREAD_VERSION>=4

// SIGNATURE_PACKAGED_TASK
#if ! defined AUTOBOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_SIGNATURE_PACKAGED_TASK
#define AUTOBOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK
#endif

// VARIADIC_THREAD
#if ! defined AUTOBOOST_THREAD_PROVIDES_VARIADIC_THREAD \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_VARIADIC_THREAD

#if ! defined(AUTOBOOST_NO_SFINAE_EXPR) && \
    ! defined(AUTOBOOST_NO_CXX11_VARIADIC_TEMPLATES) && \
    ! defined(AUTOBOOST_NO_CXX11_DECLTYPE) && \
    ! defined(AUTOBOOST_NO_CXX11_DECLTYPE_N3276) && \
    ! defined(AUTOBOOST_NO_CXX11_TRAILING_RESULT_TYPES) && \
    ! defined(AUTOBOOST_NO_CXX11_RVALUE_REFERENCES) && \
    ! defined(AUTOBOOST_NO_CXX11_HDR_TUPLE)

#define AUTOBOOST_THREAD_PROVIDES_VARIADIC_THREAD
#endif
#endif

#if ! defined AUTOBOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_WHEN_ALL_WHEN_ANY

#if ! defined(AUTOBOOST_NO_CXX11_VARIADIC_TEMPLATES) && \
    ! defined(AUTOBOOST_NO_CXX11_HDR_TUPLE)

#define AUTOBOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY
#endif
#endif

//    ! defined(AUTOBOOST_NO_SFINAE_EXPR) &&
//    ! defined(AUTOBOOST_NO_CXX11_RVALUE_REFERENCES) &&
//    ! defined(AUTOBOOST_NO_CXX11_AUTO) &&
//    ! defined(AUTOBOOST_NO_CXX11_DECLTYPE) &&
//    ! defined(AUTOBOOST_NO_CXX11_DECLTYPE_N3276) &&


// MAKE_READY_AT_THREAD_EXIT
#if ! defined AUTOBOOST_THREAD_PROVIDES_MAKE_READY_AT_THREAD_EXIT \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_MAKE_READY_AT_THREAD_EXIT

//#if defined AUTOBOOST_THREAD_PROVIDES_SIGNATURE_PACKAGED_TASK && defined(AUTOBOOST_THREAD_PROVIDES_VARIADIC_THREAD)
#define AUTOBOOST_THREAD_PROVIDES_MAKE_READY_AT_THREAD_EXIT
//#endif
#endif

// FUTURE_CONTINUATION
#if ! defined AUTOBOOST_THREAD_PROVIDES_FUTURE_CONTINUATION \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_CONTINUATION
#define AUTOBOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#endif

#if ! defined AUTOBOOST_THREAD_PROVIDES_FUTURE_UNWRAP \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_UNWRAP
#define AUTOBOOST_THREAD_PROVIDES_FUTURE_UNWRAP
#endif

// FUTURE_INVALID_AFTER_GET
#if ! defined AUTOBOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_FUTURE_INVALID_AFTER_GET
#define AUTOBOOST_THREAD_PROVIDES_FUTURE_INVALID_AFTER_GET
#endif

// NESTED_LOCKS
#if ! defined AUTOBOOST_THREAD_PROVIDES_NESTED_LOCKS \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_NESTED_LOCKS
#define AUTOBOOST_THREAD_DONT_PROVIDE_NESTED_LOCKS
#endif

// CONDITION
#if ! defined AUTOBOOST_THREAD_PROVIDES_CONDITION \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_CONDITION
#define AUTOBOOST_THREAD_DONT_PROVIDE_CONDITION
#endif

#endif // AUTOBOOST_THREAD_VERSION>=4

// INTERRUPTIONS
#if ! defined AUTOBOOST_THREAD_PROVIDES_INTERRUPTIONS \
 && ! defined AUTOBOOST_THREAD_DONT_PROVIDE_INTERRUPTIONS
#define AUTOBOOST_THREAD_PROVIDES_INTERRUPTIONS
#endif

// CORRELATIONS

// EXPLICIT_LOCK_CONVERSION.
#if defined AUTOBOOST_THREAD_PROVIDES_EXPLICIT_LOCK_CONVERSION
#define AUTOBOOST_THREAD_EXPLICIT_LOCK_CONVERSION explicit
#else
#define AUTOBOOST_THREAD_EXPLICIT_LOCK_CONVERSION
#endif

// AUTOBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN is defined if AUTOBOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS
#if defined AUTOBOOST_THREAD_PROVIDES_SHARED_MUTEX_UPWARDS_CONVERSIONS \
&& ! defined AUTOBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN
#define AUTOBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN
#endif

// For C++11 call_once interface the compiler MUST support constexpr.
// Otherwise once_flag would be initialized during dynamic initialization stage, which is not thread-safe.
#if defined(AUTOBOOST_THREAD_PROVIDES_ONCE_CXX11)
#if defined(AUTOBOOST_NO_CXX11_CONSTEXPR)
#undef AUTOBOOST_THREAD_PROVIDES_ONCE_CXX11
#endif
#endif

#if defined(AUTOBOOST_THREAD_PLATFORM_WIN32) && defined AUTOBOOST_THREAD_DONT_USE_DATETIME
#undef AUTOBOOST_THREAD_DONT_USE_DATETIME
#define AUTOBOOST_THREAD_USES_DATETIME
#endif

#if defined(AUTOBOOST_THREAD_PLATFORM_WIN32) && defined AUTOBOOST_THREAD_DONT_USE_CHRONO
#undef AUTOBOOST_THREAD_DONT_USE_CHRONO
#define AUTOBOOST_THREAD_USES_CHRONO
#endif

// AUTOBOOST_THREAD_PROVIDES_DEPRECATED_FEATURES_SINCE_V3_0_0 defined by default up to Boost 1.55
// AUTOBOOST_THREAD_DONT_PROVIDE_DEPRECATED_FEATURES_SINCE_V3_0_0 defined by default up to Boost 1.55
#if defined AUTOBOOST_THREAD_PROVIDES_DEPRECATED_FEATURES_SINCE_V3_0_0

#if  ! defined AUTOBOOST_THREAD_PROVIDES_THREAD_EQ
#define AUTOBOOST_THREAD_PROVIDES_THREAD_EQ
#endif

#endif


//#if ! defined AUTOBOOST_NO_CXX11_RVALUE_REFERENCES || defined AUTOBOOST_THREAD_USES_MOVE
#if ! defined AUTOBOOST_NO_CXX11_RVALUE_REFERENCES
#define AUTOBOOST_THREAD_FUTURE_USES_OPTIONAL
#endif

#if AUTOBOOST_WORKAROUND(__BORLANDC__, < 0x600)
#  pragma warn -8008 // Condition always true/false
#  pragma warn -8080 // Identifier declared but never used
#  pragma warn -8057 // Parameter never used
#  pragma warn -8066 // Unreachable code
#endif

#include <autoboost/thread/detail/platform.hpp>

#if defined(AUTOBOOST_THREAD_PLATFORM_WIN32)
#else
  #   if defined(AUTOBOOST_HAS_PTHREAD_DELAY_NP) || defined(AUTOBOOST_HAS_NANOSLEEP)
  #     define AUTOBOOST_THREAD_SLEEP_FOR_IS_STEADY
  #   endif
#endif

// provided for backwards compatibility, since this
// macro was used for several releases by mistake.
#if defined(AUTOBOOST_THREAD_DYN_DLL) && ! defined AUTOBOOST_THREAD_DYN_LINK
# define AUTOBOOST_THREAD_DYN_LINK
#endif

// compatibility with the rest of Boost's auto-linking code:
#if defined(AUTOBOOST_THREAD_DYN_LINK) || defined(AUTOBOOST_ALL_DYN_LINK)
# undef  AUTOBOOST_THREAD_USE_LIB
# if !defined(AUTOBOOST_THREAD_USE_DLL)
#  define AUTOBOOST_THREAD_USE_DLL
# endif
#endif

#if defined(AUTOBOOST_THREAD_BUILD_DLL)   //Build dll
#elif defined(AUTOBOOST_THREAD_BUILD_LIB) //Build lib
#elif defined(AUTOBOOST_THREAD_USE_DLL)   //Use dll
#elif defined(AUTOBOOST_THREAD_USE_LIB)   //Use lib
#else //Use default
#   if defined(AUTOBOOST_THREAD_PLATFORM_WIN32)
#       if defined(AUTOBOOST_MSVC) || defined(AUTOBOOST_INTEL_WIN) \
      || defined(__MINGW32__) || defined(MINGW32) || defined(AUTOBOOST_MINGW32)
      //For compilers supporting auto-tss cleanup
            //with Boost.Threads lib, use Boost.Threads lib
#           define AUTOBOOST_THREAD_USE_LIB
#       else
            //For compilers not yet supporting auto-tss cleanup
            //with Boost.Threads lib, use Boost.Threads dll
#           define AUTOBOOST_THREAD_USE_DLL
#       endif
#   else
#       define AUTOBOOST_THREAD_USE_LIB
#   endif
#endif

#if defined(AUTOBOOST_HAS_DECLSPEC)
#   if defined(AUTOBOOST_THREAD_BUILD_DLL) //Build dll
#       define AUTOBOOST_THREAD_DECL AUTOBOOST_SYMBOL_EXPORT
//#       define AUTOBOOST_THREAD_DECL __declspec(dllexport)

#   elif defined(AUTOBOOST_THREAD_USE_DLL) //Use dll
#       define AUTOBOOST_THREAD_DECL AUTOBOOST_SYMBOL_IMPORT
//#       define AUTOBOOST_THREAD_DECL __declspec(dllimport)
#   else
#       define AUTOBOOST_THREAD_DECL
#   endif
#elif (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  define AUTOBOOST_THREAD_DECL AUTOBOOST_SYMBOL_VISIBLE

#else
#   define AUTOBOOST_THREAD_DECL
#endif // AUTOBOOST_HAS_DECLSPEC

//
// Automatically link to the correct build variant where possible.
//
#if !defined(AUTOBOOST_ALL_NO_LIB) && !defined(AUTOBOOST_THREAD_NO_LIB) && !defined(AUTOBOOST_THREAD_BUILD_DLL) && !defined(AUTOBOOST_THREAD_BUILD_LIB)
//
// Tell the autolink to link dynamically, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#if defined(AUTOBOOST_THREAD_USE_DLL)
#   define AUTOBOOST_DYN_LINK
#endif
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#if defined(AUTOBOOST_THREAD_LIB_NAME)
#    define AUTOBOOST_LIB_NAME AUTOBOOST_THREAD_LIB_NAME
#else
#    define AUTOBOOST_LIB_NAME autoboost_thread
#endif
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
// And include the header that does the work:
//
#include <autoboost/config/auto_link.hpp>
#endif  // auto-linking disabled

#endif // AUTOBOOST_THREAD_CONFIG_WEK1032003_HPP

// Change Log:
//   22 Jan 05 Roland Schwarz (speedsnail)
//      Usage of AUTOBOOST_HAS_DECLSPEC macro.
//      Default again is static lib usage.
//      AUTOBOOST_DYN_LINK only defined when autolink included.
