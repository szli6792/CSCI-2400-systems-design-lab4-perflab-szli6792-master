//-*-c++-*-
#ifndef _Filter_h_
#define _Filter_h_

using namespace std;

class Filter {
  unsigned int divisor;
  unsigned int dim;
  int *data;

public:
  Filter(unsigned int _dim);
  int get(unsigned int r);
  void set(unsigned int r, int value);

  unsigned int getDivisor();
  void setDivisor(unsigned int value);

  unsigned int getSize();
};

#endif
