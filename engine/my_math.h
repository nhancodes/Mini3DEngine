#ifndef MY_MATH_H
#define MY_MATH_H

#include <my_math.h>
#include "raylib.h"


typedef struct {
 int a;
 int b;
} Int2;
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
typedef struct {
  MyVector3* v;
  int v_count;
  Int2* indices_mapping;
  int i_count;
} Base;

typedef struct
{
  float x;
  float y;
  float z;
  float w;
} MyVector4;
typedef struct {
  MyVector3 model[8];
} Hexahedron;

typedef struct {
  float m_3x3[3][3];
} MyMatrix3x3;

typedef struct {
  MyVector3 v_x;
  MyVector3 v_y;
} MyMatrix2x3;

typedef struct {
  float m_4x4[4][4];
} MyMatrix4x4;
typedef struct {
  MyVector3 c[8];
} Coordinates;
typedef struct {
  int width; 
  int height; 
  MyMatrix3x3 rotation_m_3x3;
  Vector3 v;
} Screen;

typedef struct {
  MyVector3 axis;
  float angle;
} RotationInput;

MyVector3 matrix_vector_mul_4x4(MyMatrix4x4* v4_m, MyVector3* v3);

MyMatrix4x4 view_matrix (MyVector3* right, MyVector3* up, MyVector3* direction, MyVector3* cam_position);

Hexahedron generate_hexahedron_model(MyVector3 vector);

MyMatrix3x3 axis_angle_rotate( MyVector3 axis, float angle);

MyVector3 rotate_xz(MyVector3 vec3, float angle);

MyVector3 translate(MyVector3 vec3, MyVector3 t3);

MyMatrix3x3 matrix_mul(MyMatrix3x3 mat1, MyMatrix3x3 mat2);

MyMatrix4x4 matrix_mul_4x4 (MyMatrix4x4 mat1, MyMatrix4x4 mat2);

MyVector3 matrix_vector_mul(MyMatrix3x3 mat1, MyVector3 vec2);

MyMatrix3x3 scalar_mul(MyMatrix3x3 mat, float scalar);

MyMatrix3x3 matrix_add(MyMatrix3x3 mat1, MyMatrix3x3 mat2);

void print_matrix(MyMatrix3x3 matrix, char *name);

MyVector3 normalize_vector (MyVector3 v);

MyVector3 generate_screen(MyVector3 vec3, int screenWidth, int screenHeight);

MyVector3 generate_projection(MyVector3 vec3);

MyVector3 generate_view(MyVector3 v_3, MyVector3* cp, MyVector3* dir, MyMatrix2x3* roll_angle);

MyMatrix4x4 generate_model (MyVector3 s_matrix_input, RotationInput* rot_input, MyVector3 t_matrix_input);

Vector2 convert_3D_to_2D (MyVector3 vec3);

void draw_model ( Base b, MyMatrix3x3 r_matrix,  MyVector3* cp, MyVector3* dir, MyMatrix2x3* roll_angle, int width, int height, Color* color, MyVector3 s_matrix_input, RotationInput* rot_input, MyVector3 t_matrix_input);

#endif;