
#ifndef AUTOBOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define AUTOBOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <autoboost/mpl/aux_/config/typeof.hpp>
#include <autoboost/mpl/aux_/nttp_decl.hpp>

namespace autoboost { namespace mpl { namespace aux {

struct v_iter_tag;

#if defined(AUTOBOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
struct vector_tag;
#else
template< AUTOBOOST_MPL_AUX_NTTP_DECL(long, N) > struct vector_tag;
#endif

}}}

#endif // AUTOBOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
