// Copyright (C) 2014 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// 2014/01 Vicente J. Botet Escriba
//    first implementation of a thread_executor.

#ifndef AUTOBOOST_THREAD_THREAD_EXECUTOR_HPP
#define AUTOBOOST_THREAD_THREAD_EXECUTOR_HPP

#include <autoboost/thread/detail/config.hpp>
#include <autoboost/thread/detail/delete.hpp>
#include <autoboost/thread/detail/move.hpp>
#include <autoboost/thread/executors/work.hpp>
#include <autoboost/thread/executors/executor.hpp>
#include <autoboost/thread/thread_only.hpp>

#include <autoboost/config/abi_prefix.hpp>

namespace autoboost
{
namespace executors
{
  class thread_executor
  {
  public:
    /// type-erasure to store the works to do
    typedef  executors::work work;
    bool closed_;
    /**
     * Effects: try to execute one task.
     * Returns: whether a task has been executed.
     * Throws: whatever the current task constructor throws or the task() throws.
     */
    bool try_executing_one()
    {
      return false;
    }

  public:
    /// thread_executor is not copyable.
    AUTOBOOST_THREAD_NO_COPYABLE(thread_executor)

    /**
     * \b Effects: creates a inline executor that runs closures immediately.
     *
     * \b Throws: Nothing.
     */
    thread_executor()
    : closed_(false)
    {
    }
    /**
     * \b Effects: Destroys the inline executor.
     *
     * \b Synchronization: The completion of all the closures happen before the completion of the \c thread_executor destructor.
     */
    ~thread_executor()
    {
      // signal to all the worker thread that there will be no more submissions.
      close();
    }

    /**
     * \b Effects: close the \c thread_executor for submissions.
     * The loop will work until there is no more closures to run.
     */
    void close()
    {
      closed_ = true;
    }

    /**
     * \b Returns: whether the pool is closed for submissions.
     */
    bool closed()
    {
      return closed_;
    }

    /**
     * \b Requires: \c Closure is a model of \c Callable(void()) and a model of \c CopyConstructible/MoveConstructible.
     *
     * \b Effects: The specified \c closure will be scheduled for execution at some point in the future.
     * If invoked closure throws an exception the \c thread_executor will call \c std::terminate, as is the case with threads.
     *
     * \b Synchronization: completion of \c closure on a particular thread happens before destruction of thread's thread local variables.
     *
     * \b Throws: \c sync_queue_is_closed if the thread pool is closed.
     * Whatever exception that can be throw while storing the closure.
     */

#if defined(AUTOBOOST_NO_CXX11_RVALUE_REFERENCES)
    template <typename Closure>
    void submit(Closure & closure)
    {
      if (closed()) return;
      thread th(closure);
      th.detach();
    }
#endif
    void submit(void (*closure)())
    {
      if (closed()) return;
      thread th(closure);
      th.detach();
    }

    template <typename Closure>
    void submit(AUTOBOOST_THREAD_FWD_REF(Closure) closure)
    {
      if (closed()) return;
      thread th(autoboost::forward<Closure>(closure));
      th.detach();
    }

    /**
     * \b Requires: This must be called from an scheduled task.
     *
     * \b Effects: reschedule functions until pred()
     */
    template <typename Pred>
    bool reschedule_until(Pred const&)
    {
      return false;
    }

  };
}
using executors::thread_executor;
}

#include <autoboost/config/abi_suffix.hpp>

#endif