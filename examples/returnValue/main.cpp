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
 * main.cpp
 *
 *  Created on: 21 févr. 2015
 *      Author: rleguay
 */

#include <thread/FutureSynchronyzer.hxx>

#include <iostream>
#include <chrono>

size_t cumul(const size_t & start, const size_t & end)
{
  size_t res = 0;
  for (size_t i = start; i < end; ++i)
  {
    res += i;
  }
  return res;
}

int main(int argc, char **argv)
{
  std::chrono::system_clock::time_point startPoint, endPoint;

  startPoint = std::chrono::system_clock::now();
  size_t end = 500000000;
  size_t step = 5000000;

  size_t res = 0;
  thread::FutureSynchronyzer<policy::AddNumberResultPolicy, factory::AsyncFutureFactory, size_t> sync(&res, 4);

  for (size_t i = 0; i < end; i += step)
  {
    sync.addFunction(cumul, i, i+step-1);
  }

  sync.launchAndWait();

  endPoint = std::chrono::system_clock::now();

  std::cout << *(sync.outputResult()) << std::endl;
  std::cout << res << std::endl;

  auto us = std::chrono::duration_cast<std::chrono::microseconds>(endPoint - startPoint).count();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint).count();
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(endPoint - startPoint).count();
  auto minutes = sec / 60;
  us = us - ms * 1000;
  ms = ms - sec * 1000;
  sec = sec - minutes * 60;
  std::cout << "Time: " << minutes << " min  " << sec << " s " << ms <<
      " ms " << us <<
      " us; Num Threads: " << sync.numThreads() << std::endl;

  return 0;
}


