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
    // You should use the base conversion approach taught in class to avoid repeated calls to pow()
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        //Calculation of w
        std::vector<unsigned long long> w(5, 0);
        size_t wIdx = 4;
        std::vector<HASH_INDEX_T> a(6, 0);
        size_t aIdx = 5;
        size_t count = 0; //Substring size
        // Go backwards through the letters for ease of computation
        for(size_t i = 0; i < k.size(); i++){
            if(count == 6){ // Have a full 6
                //Calculate w[wIdx]
                unsigned long long mult = 1;
                for(size_t j = 0; j < 6; j++){
                    w[wIdx] += a[5-j]*mult;
                    mult *= 36;
                }
                //Modify variables
                wIdx--;
                count = 0;
                aIdx = 5;
            }
            a[aIdx] = letterDigitToNumber(k[k.size() - 1 - i]);

            aIdx--;
            count++;
        }
        if(count != 0){ //Don't have a full 6
            unsigned long long mult = 1;
                for(size_t j = 0; j < count; j++){
                    w[wIdx] += a[5-j]*mult;
                    mult *= 36;
                }
        }

        //Calculate return value
        unsigned long long retValue = 0;
        for(size_t i = 0; i < 5; i++){
            retValue += rValues[i]*w[i];
        }
        return retValue;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    // '0'-'9' = 48-57, 'A'-'Z' = 65-90, 'a'-'z' = 97-122
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter < 58) // Number
            return HASH_INDEX_T((letter - 48) + 26);
        else if(letter < 91) //Uppercase
            return HASH_INDEX_T(letter - 65);
        else //Lowercase
            return HASH_INDEX_T(letter - 97);
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
