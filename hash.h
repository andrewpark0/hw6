#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      unsigned long long w[5] = {0, 0, 0, 0, 0};
      int length = k.length();
      int segSize = 6;
      int numSegments = (length + segSize - 1) / segSize; //calculate # of segs

      for(int i = 0; i < numSegments; ++i){
        int start = length - segSize * (i+1);
        int end = length - segSize * i;
        
        if(start < 0){
          start = 0;
        }
        
        w[4 - i] = computeSegmentValue(k, start, end);
      }

      unsigned long long hash = 0;
      for(int i = 0; i < 5; ++i){
        hash += rValues[i] * w[i];
        std::cout << "w[" << i << "] = " << w[i] << std::endl;
      }

      return hash;
    }

    //helper
    unsigned long long computeSegmentValue(const std::string& str, int start, int end) const{
      unsigned long long value = 0;
      unsigned long long base = 1;

      for(int i = end - 1; i >= start; --i){
        value += letterDigitToNumber(str[i]) * base;
        base *= 36;
      }
      return value;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      if(isdigit(letter)){
        return 26 + (letter - '0');
      }
      else{
        return std::tolower(letter) - 'a';
      }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
