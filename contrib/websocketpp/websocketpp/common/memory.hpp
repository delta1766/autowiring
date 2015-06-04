/*
 * Copyright (c) 2013, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef WEBSOCKETPP_COMMON_MEMORY_HPP
#define WEBSOCKETPP_COMMON_MEMORY_HPP

#if defined _WEBSOCKETPP_CPP11_STL_ && !defined _WEBSOCKETPP_NO_CPP11_MEMORY_
    #ifndef _WEBSOCKETPP_CPP11_MEMORY_
        #define _WEBSOCKETPP_CPP11_MEMORY_
    #endif
#endif

#ifdef _WEBSOCKETPP_CPP11_MEMORY_
    #include <memory>
#else
    #include <autoboost/shared_ptr.hpp>
    #include <autoboost/scoped_array.hpp>
    #include <autoboost/enable_shared_from_this.hpp>
    #include <autoboost/pointer_cast.hpp>
#endif

namespace websocketpp {
namespace lib {

#ifdef _WEBSOCKETPP_CPP11_MEMORY_
    using std::shared_ptr;
    using std::weak_ptr;
    using std::enable_shared_from_this;
    using std::static_pointer_cast;

    typedef std::unique_ptr<unsigned char[]> unique_ptr_uchar_array;
#else
    using autoboost::shared_ptr;
    using autoboost::weak_ptr;
    using autoboost::enable_shared_from_this;
    using autoboost::static_pointer_cast;

    typedef autoboost::scoped_array<unsigned char> unique_ptr_uchar_array;
#endif

} // namespace lib
} // namespace websocketpp

#endif // WEBSOCKETPP_COMMON_MEMORY_HPP