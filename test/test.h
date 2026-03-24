#pragma once
#include <math.h> 
#include "my_math.h"
#define  EPSILON_F 1e-6f

bool equal_relative(float a, float b) {
    float diff = fabsf(a - b);
    float larger = fmaxf(fabsf(a), fabsf(b));

    if (larger < EPSILON_F) {
       return diff < EPSILON_F ; 
    }
    return diff / larger < EPSILON_F;
}

bool is_equal_matrix(MyMatrix3x3 actual_result, MyMatrix3x3 expected_result) {
    // iterate through the actual_result and check the expected_result
    // loop through the rows 
    for (int row = 0; row < 3; row++) {
    //loop through the value
        for (int col = 0; col < 3; col++) {
        // if not equal to expected_result return false
           if (equal_relative(actual_result.m_3x3[row][col], expected_result.m_3x3[row][col]) == false) {
            return false;
           }
            /*if (actual_result[row][col] != expected_result[row][col]){
                return false;
            }*/
        }
    }
    return true;
}