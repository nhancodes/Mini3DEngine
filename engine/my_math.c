#include "my_math.h"
#include "math.h"
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

void axis_angle_rotate(MyVector3 axis, float angle, Matrix3x3 out) {
  Matrix3x3 identity = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };

  Matrix3x3 K = {
    {0, -axis.z, axis.y},
    {axis.z,0, -axis.x},
    {-axis.y, axis.x, 0},
  };

  Matrix3x3 b_result = {{0,0,0}, {0,0,0}, {0,0,0}};
  scalar_mul(K, sin(angle), b_result);
  print_matrix(b_result, "SIN(ANGLE) * K");

  Matrix3x3 a_result = {{0,0,0}, {0,0,0}, {0,0,0}};
  matrix_add(identity, b_result, a_result);
  print_matrix(a_result, "IDENTITY + SIN(ANGLE) * K");

  Matrix3x3 mul_k_result =  {{0,0,0}, {0,0,0}, {0,0,0}};
  matrix_mul(K,K, mul_k_result);
  print_matrix(mul_k_result, "K * K");

  float c_scalar = 1 - cos(angle);
  Matrix3x3 c_result = {{0,0,0}, {0,0,0}, {0,0,0}};
  scalar_mul(mul_k_result, c_scalar, c_result);
  print_matrix(c_result, " 1 - cos(angle) * K");

  matrix_add(a_result, c_result, out);
  print_matrix(out, "A_RESULT + C_RESULT");
}

void matrix_add(Matrix3x3 mat1, Matrix3x3 mat2, Matrix3x3 out) {
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 3; col++) {
      out[row][col] = mat1[row][col] + mat2[row][col];
    }
  }
}

void scalar_mul(Matrix3x3 mat, float scalar,  Matrix3x3 out) { // non working scalar type-> change to float
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      out[row][col] = scalar * mat[row][col]; 
    }
  }
}

MyVector3 matrix_vector_mul(Matrix3x3 mat1, MyVector3 vec3) {
    return (MyVector3){
      (mat1[0][0] * vec3.x) + (mat1[0][1] * vec3.y) + (mat1[0][2] * vec3.z),
      (mat1[1][0] * vec3.x) + (mat1[1][1] * vec3.y) + (mat1[1][2] * vec3.z),
      (mat1[2][0] * vec3.x) + (mat1[2][1] * vec3.y) + (mat1[2][2] * vec3.z)
  };
}

void matrix_mul(Matrix3x3 mat1, Matrix3x3 mat2, Matrix3x3 out) {
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

void print_matrix(Matrix3x3 matrix, char* name) {
    // iterate through the actual_result and check the expected_result
    // loop through the rows 
    printf("______%s______\n", name);
    for (int row = 0; row < 3; row++) {
    //loop through the value
        for (int col = 0; col < 3; col++) {
        // if not equal to expected_result return false
            printf("%f ", matrix[row][col]);
        }
        printf("\n");
    }
}