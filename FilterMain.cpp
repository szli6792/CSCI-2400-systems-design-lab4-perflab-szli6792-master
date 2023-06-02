#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    unsigned int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    unsigned int div;
    input >> div;
    filter -> setDivisor(div);
    for (unsigned int i=0; i < size*size; i++) {
        int value;
        input >> value;
        filter -> set(i, value);
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;
  
  int red;
  int green;
  int blue;
    
    int filterPixel1 = filter -> get(0);
    int filterPixel2 = filter -> get(1);
    int filterPixel3 = filter -> get(2);
    int filterPixel4 = filter -> get(3);
    int filterPixel5 = filter -> get(4);
    int filterPixel6 = filter -> get(5);
    int filterPixel7 = filter -> get(6);
    int filterPixel8 = filter -> get(7);
    int filterPixel9 = filter -> get(8);
    
    int screenPixelR1;
    int screenPixelR2;
    int screenPixelR3;
    int screenPixelR4;
    int screenPixelR5;
    int screenPixelR6;
    int screenPixelR7;
    int screenPixelR8;
    int screenPixelR9;
    int screenPixelG1;
    int screenPixelG2;
    int screenPixelG3;
    int screenPixelG4;
    int screenPixelG5;
    int screenPixelG6;
    int screenPixelG7;
    int screenPixelG8;
    int screenPixelG9;
    int screenPixelB1;
    int screenPixelB2;
    int screenPixelB3;
    int screenPixelB4;
    int screenPixelB5;
    int screenPixelB6;
    int screenPixelB7;
    int screenPixelB8;
    int screenPixelB9;
    
    
    unsigned int rowHeight = (input -> height) - 1;
    unsigned int colWidth = (input -> width) - 1;
    unsigned int divisor = filter -> getDivisor();
    
    /*
    int matrix[colWidth*rowHeight*3];
    for(int col = 1; col < colWidth; col = col + 1) {
        matrix[() 
    */
    
    for(unsigned int row = 1; row < rowHeight; row = row + 1) {
      for(unsigned int col = 1; col < colWidth; col = col + 1) {
    
        screenPixelR1 =  input -> color[row -1][col-1][0];
        screenPixelG1 =  input -> color[row -1][col-1][1];
        screenPixelB1 =  input -> color[row -1][col-1][2];
          
        screenPixelR2 =  input -> color[row -1][col][0];
        screenPixelG2 =  input -> color[row -1][col][1];          
        screenPixelB2 =  input -> color[row -1][col][2];          
        
        screenPixelR3 =  input -> color[row -1][col+1][0];
        screenPixelG3 =  input -> color[row -1][col+1][1];
        screenPixelB3 =  input -> color[row -1][col+1][2];          
          
        screenPixelR4 =  input -> color[row][col-1][0];
        screenPixelG4 =  input -> color[row][col-1][1];
        screenPixelB4 =  input -> color[row][col-1][2];
          
        screenPixelR5 =  input -> color[row][col][0];
        screenPixelG5 =  input -> color[row][col][1];          
        screenPixelB5 =  input -> color[row][col][2];
          
        screenPixelR6 =  input -> color[row][col+1][0];
        screenPixelG6 =  input -> color[row][col+1][1];
        screenPixelB6 =  input -> color[row][col+1][2];          
          
        screenPixelR7 =  input -> color[row +1][col-1][0];
        screenPixelG7 =  input -> color[row +1][col-1][1];          
        screenPixelB7 =  input -> color[row +1][col-1][2];
          
        screenPixelR8 =  input -> color[row +1][col][0];
        screenPixelG8 =  input -> color[row +1][col][1];          
        screenPixelB8 =  input -> color[row +1][col][2];
          
        screenPixelR9 =  input -> color[row +1][col+1][0];
        screenPixelG9 =  input -> color[row +1][col+1][1];
        screenPixelB9 =  input -> color[row +1][col+1][2];
        
        red = (screenPixelR1 * filterPixel1);
        red += (screenPixelR2 * filterPixel2);
        red += (screenPixelR3 * filterPixel3);
        red += (screenPixelR4 * filterPixel4);
        red += (screenPixelR5 * filterPixel5);
        red += (screenPixelR6 * filterPixel6);
        red += (screenPixelR7 * filterPixel7);
        red += (screenPixelR8 * filterPixel8);
        red += (screenPixelR9 * filterPixel9);
        
        red = red/divisor;
        red = max(0, min(red,255)); //renormalize
        output -> color[row][col][0] = red;
        
        green = (screenPixelG1 * filterPixel1);
        green += (screenPixelG2 * filterPixel2);
        green+= (screenPixelG3 * filterPixel3);
        green += (screenPixelG4 * filterPixel4);
        green += (screenPixelG5 * filterPixel5);
        green += (screenPixelG6 * filterPixel6);
        green += (screenPixelG7 * filterPixel7);
        green += (screenPixelG8 * filterPixel8);
        green += (screenPixelG9 * filterPixel9);
        
        green = green/divisor;
        green = max(0, min(green,255)); //renormalize
        output -> color[row][col][1] = green;
          
        blue = (screenPixelB1 * filterPixel1);
        blue += (screenPixelB2 * filterPixel2);
        blue += (screenPixelB3 * filterPixel3);
        blue += (screenPixelB4 * filterPixel4);
        blue += (screenPixelB5 * filterPixel5);
        blue += (screenPixelB6 * filterPixel6);
        blue += (screenPixelB7 * filterPixel7);
        blue += (screenPixelB8 * filterPixel8);
        blue += (screenPixelB9 * filterPixel9);
        
        blue = blue/divisor;
        blue = max(0, min(blue,255)); //renormalize
        output -> color[row][col][2] = blue;      
    }
  }
    
    
  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}