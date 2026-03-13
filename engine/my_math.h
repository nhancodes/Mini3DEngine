#ifndef MY_MATH_H
#define MY_MATH_H

typedef struct
{
  float x;
  float y;
} MyVector2;

typedef struct
{
  float x;
  float y;
  float z;
} MyVector3;

typedef struct
{
  MyVector3 HexadronModel[8];
} HexadronModel;

typedef float Matrix3x3[3][3];

HexadronModel generate_hexahedron_model(MyVector3 vector);

void axis_angle_rotate( MyVector3 axis, float angle, Matrix3x3 out);

MyVector3 rotate_xz(MyVector3 vec3, float angle);

MyVector3 translate(MyVector3 vec3, MyVector3 t3);

void matrix_mul(Matrix3x3 mat1, Matrix3x3 mat2, Matrix3x3 out);

MyVector3 matrix_vector_mul(Matrix3x3 mat1, MyVector3 vec2);

void scalar_mul(Matrix3x3 mat, float scalar, Matrix3x3 out);

void matrix_add(Matrix3x3 mat1, Matrix3x3 mat2, Matrix3x3 out);

void print_matrix(Matrix3x3 matrix, char *name);

#endif