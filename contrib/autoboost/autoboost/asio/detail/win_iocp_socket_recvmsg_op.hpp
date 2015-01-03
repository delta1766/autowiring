//
// detail/win_iocp_socket_recvmsg_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef AUTOBOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
#define AUTOBOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <autoboost/asio/detail/config.hpp>

#if defined(AUTOBOOST_ASIO_HAS_IOCP)

#include <autoboost/asio/detail/addressof.hpp>
#include <autoboost/asio/detail/bind_handler.hpp>
#include <autoboost/asio/detail/buffer_sequence_adapter.hpp>
#include <autoboost/asio/detail/fenced_block.hpp>
#include <autoboost/asio/detail/handler_alloc_helpers.hpp>
#include <autoboost/asio/detail/handler_invoke_helpers.hpp>
#include <autoboost/asio/detail/operation.hpp>
#include <autoboost/asio/detail/socket_ops.hpp>
#include <autoboost/asio/error.hpp>
#include <autoboost/asio/socket_base.hpp>

#include <autoboost/asio/detail/push_options.hpp>

namespace autoboost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler>
class win_iocp_socket_recvmsg_op : public operation
{
public:
  AUTOBOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_socket_recvmsg_op);

  win_iocp_socket_recvmsg_op(
      socket_ops::weak_cancel_token_type cancel_token,
      const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags, Handler& handler)
    : operation(&win_iocp_socket_recvmsg_op::do_complete),
      cancel_token_(cancel_token),
      buffers_(buffers),
      out_flags_(out_flags),
      handler_(AUTOBOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  static void do_complete(io_service_impl* owner, operation* base,
      const autoboost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    autoboost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_socket_recvmsg_op* o(
        static_cast<win_iocp_socket_recvmsg_op*>(base));
    ptr p = { autoboost::asio::detail::addressof(o->handler_), o, o };

    AUTOBOOST_ASIO_HANDLER_COMPLETION((o));

#if defined(AUTOBOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<autoboost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(AUTOBOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    socket_ops::complete_iocp_recvmsg(o->cancel_token_, ec);
    o->out_flags_ = 0;

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, autoboost::system::error_code, std::size_t>
      handler(o->handler_, ec, bytes_transferred);
    p.h = autoboost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      AUTOBOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      autoboost_asio_handler_invoke_helpers::invoke(handler, handler.handler_);
      AUTOBOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  socket_ops::weak_cancel_token_type cancel_token_;
  MutableBufferSequence buffers_;
  socket_base::message_flags& out_flags_;
  Handler handler_;
};

} // namespace detail
} // namespace asio
} // namespace autoboost

#include <autoboost/asio/detail/pop_options.hpp>

#endif // defined(AUTOBOOST_ASIO_HAS_IOCP)

#endif // AUTOBOOST_ASIO_DETAIL_WIN_IOCP_SOCKET_RECVMSG_OP_HPP
