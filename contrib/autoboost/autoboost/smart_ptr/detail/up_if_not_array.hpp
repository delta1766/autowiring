/*
 * Copyright (c) 2014 Glen Joseph Fernandes 
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License, 
 * Version 1.0. (See accompanying file LICENSE_1_0.txt 
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#ifndef AUTOBOOST_SMART_PTR_DETAIL_UP_IF_NOT_ARRAY_HPP
#define AUTOBOOST_SMART_PTR_DETAIL_UP_IF_NOT_ARRAY_HPP

#include <memory>

namespace autoboost {
    namespace detail {
        template<class T> 
        struct up_if_not_array {
            typedef std::unique_ptr<T> type;
        };

        template<class T>
        struct up_if_not_array<T[]> {
        };

        template<class T, std::size_t N>
        struct up_if_not_array<T[N]> {
        };
    }
}

#endif
