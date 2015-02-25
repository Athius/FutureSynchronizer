/**
 * The MIT License (MIT)
 *
 * Copyright (c) <2015> <Romain LEGUAY romain.leguay@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
**/
/*
 * FutureSynchronyzer.hxx
 *
 *  Created on: 24 févr. 2015
 *      Author: rleguay
 */

#ifndef FUTURESYNCHRONYZER_HXX_
#define FUTURESYNCHRONYZER_HXX_

#include "../policy/ResultPolicy.hxx"
#include "../factory/FutureFactory.hxx"

#include <vector>

namespace thread
{
  template<class ResultPolicy=policy::NoResultPolicy,
      class FutureFactory=factory::AsyncFutureFactory,
      typename OutputResult=void>
  /**
   * This class permits to add functions and it's arguments and launch
   * them with a limit number of threads defined at the onbject's construction.
   * All the function added must returned the same type of argument.
   */
  class FutureSynchronyzer : public ResultPolicy, public FutureFactory
  {
  private:
    std::vector<std::future<OutputResult>> m_futures;
    std::vector<std::function<OutputResult()>> m_functions;
    size_t m_numThreads;
    OutputResult * m_outputResult;

  public:

    /**
     * Construct the Future Synchronizer.
     * @param outputResult the return result (optional);
     * @param numThreads the max number of threads. By default, the number of
     * concurrent threads supported if detected or 1.
     */
    FutureSynchronyzer(OutputResult * outputResult = NULL,
                       size_t numThreads =
                           std::thread::hardware_concurrency() > 0 ?
                           std::thread::hardware_concurrency() : 1) :
       m_numThreads(numThreads),
       m_outputResult(outputResult)
    {
      if (m_numThreads == 0)
      {
        m_numThreads = 1;
      }
    }

    virtual ~FutureSynchronyzer()
    {
    }

    /**
     * Add the function and its arguments to the list of function
     * @param function
     * @param args all arguments
     */
    template<typename Fn, typename... Args>
    void addFunction(Fn && function, Args&&... args)
    {
      std::function<OutputResult()> func = std::bind(function,args...);
      m_functions.push_back(std::move(func));
    }

    /**
     * Launch all functions
     */
    void launch()
    {
      //Initialize parts
      size_t size = m_numThreads < m_functions.size() ?
          m_numThreads : m_functions.size();
      for (size_t i = 0; i < size; ++i)
      {
        std::function<OutputResult()> f = getNextFunction();
        std::future<OutputResult> future =
            FutureFactory::template createFuture<OutputResult>(f);
        m_futures.push_back(std::move(future));
      }

      //While all functions are not launched;
      while(!m_functions.empty())
      {
        for (size_t numThread = 0; numThread < m_numThreads; ++numThread)
        {
          std::future_status status =
              m_futures[numThread].wait_for(std::chrono::microseconds(0));
          //If the current future is ready
          if (status == std::future_status::ready)
          {
            //Then, we calculate the result (if necessary)
            applyResult(m_futures[numThread]);
            //And we create a new future.
            std::function<OutputResult()> f = getNextFunction();
            std::future<OutputResult> future =
                FutureFactory::template createFuture<OutputResult>(f);
            m_futures[numThread] = std::move(future);
          }
        }
      }
    }

    /**
     * Wait all functions to be finished.
     */
    void wait()
    {
      for (std::future<OutputResult> & future : m_futures)
      {
        future.wait();
        applyResult(future);
      }

      m_futures.clear();
    }

    /**
     * Launch all the functions and wait them to be finished.
     */
    void launchAndWait()
    {
      launch();
      wait();
    }

    OutputResult * outputResult() const
    {
      return m_outputResult;
    }

    size_t numThreads() const
    {
      return m_numThreads;
    }

  private:

    /**
     * @return the next function to be treated.
     */
    std::function<OutputResult()> getNextFunction()
    {
      std::function<OutputResult()> f = m_functions.back();
      m_functions.pop_back();
      return f;
    }

    /**
     * Launch the result operation.
     * This method is used if OutputResult is not void and
     * ResultPolicy is not ResultPolicy.
     * @param f the finished future with the result
     */
    template<typename Output = OutputResult, typename Policy = ResultPolicy>
    typename std::enable_if<!(std::is_same<Output, void>::value) && !(std::is_same<Policy, policy::NoResultPolicy>::value), void>::type
    applyResult(std::future<Output> & f)
    {
      Output futureOutput = f.get();
      ResultPolicy::applyResult(m_outputResult, &futureOutput);
    }

    /**
     * Launch the result operation.
     * This method is used if OutputResult is void or
     * ResultPolicy is ResultPolicy.
     * @param f the finished future with the result
     */
    template<typename Output = OutputResult, typename Policy = ResultPolicy>
    typename std::enable_if<(std::is_same<Output, void>::value) || (std::is_same<Policy, policy::NoResultPolicy>::value), void>::type
    applyResult(std::future<Output> & f)
    {
    }

  };
} // namespace thread

#endif /* FUTURESYNCHRONYZER_HXX_ */
