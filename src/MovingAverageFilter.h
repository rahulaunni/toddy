
#ifndef MovingAverageFilter_h
#define MovingAverageFilter_h

#define MAX_DATA_POINTS 20

class MovingAverageFilter {
public:
  //construct without coefs
explicit  MovingAverageFilter(unsigned int newDataPointsCount);

  float process(float in);

private:
  int k; // k stores the index of the current array read to create a circular memory through the array
  float out;
  int dataPointsCount;
  int i; // just a loop counter
   float values[MAX_DATA_POINTS];

};
#endif

