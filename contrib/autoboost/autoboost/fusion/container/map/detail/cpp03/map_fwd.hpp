/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_07212005_1105)
#define FUSION_MAP_FORWARD_07212005_1105

#include <autoboost/fusion/support/config.hpp>
#include <autoboost/fusion/container/map/detail/cpp03/limits.hpp>
#include <autoboost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(AUTOBOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <autoboost/fusion/container/map/detail/cpp03/preprocessed/map_fwd.hpp>
#else
#if defined(__WAVE__) && defined(AUTOBOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map" FUSION_MAX_MAP_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(AUTOBOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace autoboost { namespace fusion
{
    struct void_;
    struct map_tag;
    struct map_iterator_tag;

    template <
        AUTOBOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_MAP_SIZE, typename T, void_)
    >
    struct map;
}}

#if defined(__WAVE__) && defined(AUTOBOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // AUTOBOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
