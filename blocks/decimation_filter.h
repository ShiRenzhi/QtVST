/**
 * \filter decimation_filter.h
 */

#ifndef DECIMATION_FILTER
#define DECIMATION_FILTER

#include <boost/scoped_array.hpp>

namespace DSP
{

template<class LowPassFilter, class DataType>
class DecimationFilter
{
  LowPassFilter filter;

  boost::scoped_array<DataType> temp_array;
  int temp_size;
public:
  DecimationFilter()
  :temp_size(0)
  {
  }

  LowPassFilter& get_filter()
  {
    return filter;
  }

  template<class DataTypeIn>
  void process(const DataTypeIn* in, DataType* out, long size)
  {
    if (size > temp_size)
    {
      temp_array.reset(new DataType[size]);
      temp_size = size;
    }

    filter.process(in, temp_array.get(), size);

    for(int i = 0; i < size / 2; ++i)
    {
      out[i] = temp_array[2 * i];
    }
  }
};

}

#endif