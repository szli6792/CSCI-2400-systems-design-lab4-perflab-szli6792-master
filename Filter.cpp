#include "Filter.h"
#include <iostream>

Filter::Filter(unsigned int _dim)
{
  divisor = 1;
  dim = _dim;
  data = new int[dim * dim];
}

int Filter::get(unsigned int r)
{
  return data[r];
}

void Filter::set(unsigned int r, int value)
{
  data[r] = value;
}

unsigned int Filter::getDivisor()
{
  return divisor;
}

void Filter::setDivisor(unsigned int value)
{
  divisor = value;
}

unsigned int Filter::getSize()
{
  return dim;
}

