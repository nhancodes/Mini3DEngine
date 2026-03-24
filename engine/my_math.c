#include "my_math.h"
#include "math.h"
#include "raylib.h"

Coordinates screen_coordinates (const Screen* s, MyVector3* cp, MyVector3* dir, MyMatrix2x3* roll_angle){

  Coordinates out = {
    .c = {0}
  };
  for (int i = 0; i < 8; i++) {
      MyVector3 t3 = {0,0,2};

      MyVector3 rotate_vector = matrix_vector_mul(s->rotation_m_3x3, s->hexadron.model[i]);

      //view the scene through the cameria via the view matrix
      //get the view matrix

      //rolling
      //MyMatrix4x4 v_matrix = view_matrix(&(MyVector3){cos(roll_angle->v_x.x * (PI/180)),sin(roll_angle->v_x.y * (PI/180)),0}, &(MyVector3){cos((roll_angle->v_y.x + 90) * (PI/180)),sin((roll_angle->v_y.y + 90) * (PI/180)),0}, &(MyVector3){0,0,dir->z}, &(MyVector3){cp->x,cp->y,cp->z}); //right, up, direction, camera position
      MyVector3 v_x = {
        cos(roll_angle->v_x.x * (PI/180)),
        0, 
        sin(roll_angle->v_x.y * (PI/180))
      };

      MyVector3 v_z = {
        cos((roll_angle->v_y.x + 90) * (PI/180)),
        0,
        sin((roll_angle->v_y.y + 90) * (PI/180))
      };
      //yawing
      MyMatrix4x4 v_matrix = view_matrix(&v_x, &(MyVector3){0,1,0}, &v_z, &(MyVector3){cp->x,cp->y,cp->z}); //right, up, direction, camera position
      //MyVector3 translated_pos = matrix_vector_mul_4x4(&v_matrix, &s->hexadron.model[i]);
      MyVector3 translated_pos = matrix_vector_mul_4x4(&v_matrix, &rotate_vector);

      Vector2 projected_pos = project(translated_pos);
      
      Vector2 screen_pos = screen(projected_pos, s->width, s->height);
      out.c[i] = screen_pos;

     // DrawLine(0,0, cos(roll_angle->v_x.x * (PI/180)), sin(roll_angle->v_x.y * (PI/180)), GREEN);
      //DrawLine(0, 0, cos((roll_angle->v_y.x + 90) * (PI/180)),sin((roll_angle->v_y.y + 90) * (PI/180)), ORANGE);
  }
  return out; 
}

void screen_edges (Coordinates* c) {
  int vertix_map_1[12][2] = {
    {0, 4}, 
    {1, 0}, 
    {2, 6},
    {3, 2},
    {4, 5},
    {5, 1}, 
    {6, 7}, 
    {7, 3},
    {0, 2},
    {1, 3},
    {4, 6},
    {5, 7}     
   };
   for (int i = 0 ; i < 12; i++) {
      DrawLineV(c->c[vertix_map_1[i][0]], c->c[vertix_map_1[i][1]], RED );
   }
}

Vector2 screen (Vector2 vec2, int screenWidth, int screenHeight) {
  return (Vector2){ (vec2.x + 1)/2 * screenWidth, ( 1- (vec2.y + 1)/2) * screenHeight};
}

Vector2 project (MyVector3 vec3){
  return (Vector2){vec3.x/vec3.z, vec3.y/vec3.z};
}

Hexahedron generate_hexahedron_model(MyVector3 vector)
{
  // create an arrays for points 1 to  8
  Hexahedron model = {
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

MyVector3 normalize_vector (MyVector3 v) {
  float v_length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
  return (MyVector3){
    v.x / v_length,
    v.y / v_length,
    v.z / v_length
  };
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

MyMatrix3x3 axis_angle_rotate(MyVector3 axis, float angle) {
  MyMatrix3x3 identity = {
    .m_3x3 = {
      {1, 0, 0},
      {0, 1, 0},
      {0, 0, 1}
    }
  };

  axis = normalize_vector(axis);

  MyMatrix3x3 K = {
    .m_3x3 = {
      {0, -axis.z, axis.y},
      {axis.z,0, -axis.x},
      {-axis.y, axis.x, 0},
    }
  };

  //Matrix b_result = {{0,0,0}, {0,0,0}, {0,0,0}};
  MyMatrix3x3 b_result = scalar_mul(K, sin(angle));
  //print_matrix(b_result, "SIN(ANGLE) * K");

  //Matrix3x3 a_result = {{0,0,0}, {0,0,0}, {0,0,0}};
  MyMatrix3x3 a_result = matrix_add(identity, b_result);
  //print_matrix(a_result, "IDENTITY + SIN(ANGLE) * K");

  //Matrix3x3 mul_k_result =  {{0,0,0}, {0,0,0}, {0,0,0}};
  MyMatrix3x3 mul_k_result = matrix_mul(K,K);
  //print_matrix(mul_k_result, "K * K");

  float c_scalar = 1 - cos(angle);
  //Matrix3x3 c_result = {{0,0,0}, {0,0,0}, {0,0,0}};
  MyMatrix3x3 c_result = scalar_mul(mul_k_result, c_scalar);
  //print_matrix(c_result, " 1 - cos(angle) * K");

  MyMatrix3x3 result = matrix_add(a_result, c_result);
  return result;
  //print_matrix(out, "A_RESULT + C_RESULT");
}

MyMatrix3x3 matrix_add(MyMatrix3x3 mat1, MyMatrix3x3 mat2) {
  MyMatrix3x3 result = {0};
  for(int row = 0; row < 3; row++) {
    for(int col = 0; col < 3; col++) {
      result.m_3x3[row][col] = mat1.m_3x3[row][col] + mat2.m_3x3[row][col];
    }
  }
  return result;
}

MyMatrix3x3 scalar_mul(MyMatrix3x3 mat, float scalar) { // non working scalar type-> change to float
  MyMatrix3x3 result = {0};
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      result.m_3x3[row][col] = scalar * mat.m_3x3[row][col]; 
    }
  }
  return result;
}

MyVector3 matrix_vector_mul(MyMatrix3x3 mat1, MyVector3 vec3) {
  return (MyVector3){
    (mat1.m_3x3[0][0] * vec3.x) + (mat1.m_3x3[0][1] * vec3.y) + (mat1.m_3x3[0][2] * vec3.z),
    (mat1.m_3x3[1][0] * vec3.x) + (mat1.m_3x3[1][1] * vec3.y) + (mat1.m_3x3[1][2] * vec3.z),
    (mat1.m_3x3[2][0] * vec3.x) + (mat1.m_3x3[2][1] * vec3.y) + (mat1.m_3x3[2][2] * vec3.z)
  };
}

MyVector3 matrix_vector_mul_4x4(MyMatrix4x4* v4_m, MyVector3* v3) {
    MyVector4 v4 =  {
      v3->x,
      v3->y,
      v3->z,
      1
    };
    MyVector4 result = {0};
    result.x = 
    (v4_m->m_4x4[0][0] * v4.x) + 
    (v4_m->m_4x4[0][1] * v4.y)+
    (v4_m->m_4x4[0][2] * v4.z) + 
    (v4_m->m_4x4[0][3] * v4.w);

    result.y = 
    (v4_m->m_4x4[1][0] * v4.x) + 
    (v4_m->m_4x4[1][1] * v4.y)+
    (v4_m->m_4x4[1][2] * v4.z) +
    (v4_m->m_4x4[1][3] * v4.w);

    result.z = 
    (v4_m->m_4x4[2][0] * v4.x) + 
    (v4_m->m_4x4[2][1] * v4.y)+
    (v4_m->m_4x4[2][2] * v4.z) +
    (v4_m->m_4x4[2][3] * v4.w);

    result.w = 
    (v4_m->m_4x4[3][0] * v4.x) + 
    (v4_m->m_4x4[3][1] * v4.y)+
    (v4_m->m_4x4[3][2] * v4.z) +
    (v4_m->m_4x4[3][3] * v4.w);
    return (MyVector3) {
      result.x,
      result.y,
      result.z
    };
}

MyMatrix4x4 view_matrix (MyVector3* right, MyVector3* up, MyVector3* direction, MyVector3* cam_position) {
    MyMatrix4x4 rot = {
      .m_4x4 = {
        //{ right->x, right->y, right->z, 0 },
        { right->x, right->y, right->z, 0 },
        { up->x, up->y, up->z, 0 },
        { direction->x, direction->y, direction->z, 0 },
        { 0, 0, 0, 1 },
      }
    };
    
    MyMatrix4x4 trans = {
      .m_4x4 = {
        {1, 0, 0, -cam_position->x},
        {0, 1, 0, -cam_position->y},
        {0, 0, 1, -cam_position->z},
        {0, 0, 0, 1}
      }
    };

    MyMatrix4x4 result = {.m_4x4 = {0}};

    for (int row = 0; row < 4; row += 1) {
      for (int col = 0; col < 4; col += 1) {
        result.m_4x4[row][col] = 
        ( rot.m_4x4[row][0] * trans.m_4x4[0][col]) + 
        ( rot.m_4x4[row][1] * trans.m_4x4[1][col]) + 
        ( rot.m_4x4[row][2] * trans.m_4x4[2][col]) + 
        ( rot.m_4x4[row][3] * trans.m_4x4[3][col]);
      }
    }
   return result;
}

MyMatrix3x3 matrix_mul(MyMatrix3x3 mat1, MyMatrix3x3 mat2) {
  MyMatrix3x3 result = {0};
  for (int row = 0; row < 3; row++ ) {
    for ( int col = 0; col < 3; col++) { 
      result.m_3x3[row][col] = 
      (mat1.m_3x3[row][0] * mat2.m_3x3[0][col]) +
      (mat1.m_3x3[row][1] * mat2.m_3x3[1][col]) + 
      (mat1.m_3x3[row][2] * mat2.m_3x3[2][col]);
    }
  }
  return result;
}

MyVector3 translate(MyVector3 vec3, MyVector3 t3) {
  return (MyVector3){
    vec3.x + t3.x,
    vec3.y + t3.y,
    vec3.z + t3.z
  };
}

void print_matrix(MyMatrix3x3 matrix, char* name) {
    // iterate through the actual_result and check the expected_result
    // loop through the rows 
    printf("______%s______\n", name);
    for (int row = 0; row < 3; row++) {
    //loop through the value
        for (int col = 0; col < 3; col++) {
        // if not equal to expected_result return false
            printf("%f ", matrix.m_3x3[row][col]);
        }
        printf("\n");
    }
}