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

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

/**
 * Calulate the distance from a point to all the other points.
 * @param size        data's size
 * @param index       point to test
 * @param xIndex2     temp index
 * @param width       data's width
 * @param yIndex2     temp index
 * @param distByPoint return vector result
 * @param xIndex      x-coordinate point to test
 * @param yIndex      y-coordinate point to test
 */
void calcDistanceToPoint(unsigned int size, unsigned int index, int xIndex2,
    unsigned int width, int yIndex2, std::vector<float> & distByPoint,
    int xIndex, int yIndex)
{
  for (unsigned int index2 = 0; index2 < size; ++index2)
  {
    if (index2 != index)
    {
      xIndex2 = static_cast<int>(index2 % width);
      yIndex2 = static_cast<int>(index2 / width);
      distByPoint[index] += sqrtf(1.f*(xIndex2 - xIndex) * (xIndex2 - xIndex) +
                                  (yIndex2 - yIndex) * (yIndex2 - yIndex));
    }
  }
  distByPoint[index] /= size;
}

void distPointCalculation()
{
  unsigned int width = 200;
  unsigned int height = 200;
  unsigned int size = width * height;
  std::vector<float> distByPoint;
  distByPoint.resize(size);
  int xIndex, yIndex;
  int xIndex2, yIndex2;

  //Create a future synchronyzer with default value: no result policy,
  //create asynchrone future, and with the number of threads of the current
  //computer.
  thread::FutureSynchronyzer<> sync;

  //The loop to add all the functions;
  for (unsigned int index = 0; index < size; ++index)
  {
    xIndex = static_cast<int>(index % width);
    yIndex = static_cast<int>(index / height);
    sync.addFunction(calcDistanceToPoint, size, index, xIndex2, width, yIndex2,
        std::ref(distByPoint), xIndex, yIndex);
  }

  //Launch all the function and wait;
  sync.launchAndWait();

  std::ofstream ofs("test.csv");
  for (const float& dist : distByPoint)
  {
    ofs << dist << "\n";
  }
}

int main(int argc, char **argv)
{
  std::chrono::system_clock::time_point startPoint, endPoint;

  startPoint = std::chrono::system_clock::now();
  distPointCalculation();
  endPoint = std::chrono::system_clock::now();

  auto us = std::chrono::duration_cast<std::chrono::microseconds>(endPoint - startPoint).count();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint).count();
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(endPoint - startPoint).count();
  auto minutes = sec / 60;
  us = us - ms * 1000;
  ms = ms - sec * 1000;
  sec = sec - minutes * 60;
  std::cout << "Time: " << minutes << " min  " << sec << " s " << ms <<
      " ms " << us <<
      " us" << std::endl;

  return 0;
}
