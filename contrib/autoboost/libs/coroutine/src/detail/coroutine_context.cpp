
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/coroutine/detail/coroutine_context.hpp"

#ifdef AUTOBOOST_HAS_ABI_HEADERS
#  include AUTOBOOST_ABI_PREFIX
#endif

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable:4355)
#endif

#if defined(AUTOBOOST_USE_SEGMENTED_STACKS)
extern "C" {

void __splitstack_getcontext( void * [AUTOBOOST_COROUTINES_SEGMENTS]);

void __splitstack_setcontext( void * [AUTOBOOST_COROUTINES_SEGMENTS]);

}
#endif

namespace autoboost {
namespace coroutines {
namespace detail {

coroutine_context::coroutine_context() :
    stack_ctx_(),
    ctx_( 0)
{
#if defined(AUTOBOOST_USE_SEGMENTED_STACKS)
    __splitstack_getcontext( stack_ctx_.segments_ctx);
#endif
}

coroutine_context::coroutine_context( ctx_fn fn, stack_context const& stack_ctx) :
    stack_ctx_( stack_ctx),
    ctx_( context::make_fcontext( stack_ctx_.sp, stack_ctx_.size, fn) )
{}

coroutine_context::coroutine_context( coroutine_context const& other) :
    stack_ctx_( other.stack_ctx_),
    ctx_( other.ctx_)
{}

coroutine_context &
coroutine_context::operator=( coroutine_context const& other)
{
    if ( this == & other) return * this;

    stack_ctx_ = other.stack_ctx_;
    ctx_ = other.ctx_;

    return * this;
}

intptr_t
coroutine_context::jump( coroutine_context & other, intptr_t param, bool preserve_fpu)
{
#if defined(AUTOBOOST_USE_SEGMENTED_STACKS)
    __splitstack_getcontext( stack_ctx_.segments_ctx);
    __splitstack_setcontext( other.stack_ctx_.segments_ctx);

    intptr_t ret = context::jump_fcontext( & ctx_, other.ctx_, param, preserve_fpu);

    __splitstack_setcontext( stack_ctx_.segments_ctx);

    return ret;
#else
    return context::jump_fcontext( & ctx_, other.ctx_, param, preserve_fpu);
#endif
}

}}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#ifdef AUTOBOOST_HAS_ABI_HEADERS
#  include AUTOBOOST_ABI_SUFFIX
#endif
