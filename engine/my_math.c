#include "my_math.h"
#include "math.h"
#include <stdio.h>

HexadronModel generate_hexahedron_model(MyVector3 vector)
{
  // create an arrays for points 1 to  8
  HexadronModel model = {
    {
      {vector.x, vector.y, vector.z},
      {-vector.x, vector.y, vector.z},
      {vector.x, -vector.y, vector.z},
      {-vector.x, -vector.y, vector.z},
      {vector.x, vector.y, -vector.z},
      {-vector.x, vector.y, -vector.z},
      {vector.x, -vector.y, -vector.z},
      {-vector.x, -vector.y, -vector.z},
    },
  };
  return model;
}

MyVector3 rotate_xz(MyVector3 vec3, float angle) {
  float c = cos(angle);
  float s = sin(angle);
  //printf("x = %f\n", c);
  //printf("y = %f\n", s);
  return (MyVector3){
    vec3.x * c - vec3.z * s,
    vec3.y,
    vec3.x * s + vec3.z * c
  };
}

/*MyVector3 rotate(MyVector3 vec3, MyVector3 axis, float angle) {
  Matrix3x3 K = {
    {0, -vec3.z, vec3.y},
    {vec3.z,0, -vec3.x},
    {-vec3.y, vec3.x, 0},
  };
  Matrix3x3 KCopy = {{0,0,0}, {0,0,0}, {0,0,0}};
  scalar_mul(K, sin(angle), KCopy);
  
  return (MyVector3){
  };
}*/

void scalar_mul(Matrix3x3 mat, float scalar, float scalar_d,  Matrix3x3 out) { // non working scalar type-> change to float

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      printf("scalar_f: %f scaler_d: %f product: %f\n", scalar, scalar_d,  mat[row][col]);
      
      out[row][col] = scalar * mat[row][col]; 
      printf("value: %f\n", (scalar * mat[row][col]));
    }
  }
}

void vector_mul(Matrix3x3 mat1, Matrix3x3 mat2, Matrix3x3 out) {
  for (int row = 0; row < 3; row++ ) {
      for ( int col = 0; col < 3; col++) {
      out[row][col] = (mat1[row][0] * mat2[0][col]) + (mat1[row][1] * mat2[1][col]) + (mat1[row][2] * mat2[2][col]);
      }
  }
}

MyVector3 translate(MyVector3 vec3, MyVector3 t3) {
  return (MyVector3){
    vec3.x + t3.x,
    vec3.y + t3.y,
    vec3.z + t3.z
  };
}