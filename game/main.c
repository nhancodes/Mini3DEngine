#include "raylib.h"
#include "engine.h"
#include "my_math.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h> 
#include "test.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //TEST 
    MyMatrix3x3 mat1 = {.m_3x3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}}};
    MyMatrix3x3 mat2 = {.m_3x3 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}}};
    MyMatrix3x3 expected_result = {.m_3x3 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}}};
    MyMatrix3x3 actual_result = matrix_mul(mat1, mat2);
    bool result = is_equal_matrix(actual_result, expected_result);
    printf("result %s\n", result ? "true" : "false");//true

    MyMatrix3x3 mat3 = {.m_3x3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}}};
    MyMatrix3x3 mat4 = {.m_3x3 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}}};
    MyMatrix3x3 expected_result_1 = {.m_3x3 = {{0, 2, 1} , {0, 0, 1}, {0, 0, 1}}};
    MyMatrix3x3 actual_result_1 =  matrix_mul(mat3, mat4);
    bool result_1 = is_equal_matrix(actual_result_1, expected_result_1);
    printf("result %s\n", result_1 ? "true" : "false"); //false

    MyMatrix3x3 mat5 = {.m_3x3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}}};
    MyMatrix3x3 expected_result_2 = {.m_3x3 = {{2, 0, 0} , {0, 2, 0}, {0, 0, 2}}};
    MyMatrix3x3 actual_result_2 = scalar_mul(mat5, 2);
    bool result_2 = is_equal_matrix(actual_result_2, expected_result_2);
    printf("result %s\n", result_2 ? "true" : "false"); //true
    
    MyMatrix3x3 mat6 = {.m_3x3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}}};
    MyMatrix3x3 mat7 = {.m_3x3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}}};
    MyMatrix3x3 expected_result_3 = {.m_3x3 = {{2, 0, 0} , {0, 2, 0}, {0, 0, 2}}};
    MyMatrix3x3 actual_result_3 = matrix_add(mat6, mat7);
    bool result_3 = is_equal_matrix(actual_result_3, expected_result_3);
    printf("result %s\n", result_3 ? "true" : "false"); //true

    MyVector3 a_1 = {1, 0, 0};
    float r_angle_1 = PI/2;
    MyMatrix3x3 r_1_expected =  {
        .m_3x3 = {
            {1,  0,  0},
            {0,  0, -1},
            {0,  1,  0}
        }
    };
    MyMatrix3x3 r_1_actual = axis_angle_rotate( a_1, r_angle_1);
    bool r_1_assert = is_equal_matrix(r_1_actual, r_1_expected);
    //print_matrix(r_1_actual, "ROTATION MATRIX");
    printf("r_1 %s\n", r_1_assert ? "true" : "false"); //true

    MyVector3 a_2 = {0, 1, 0};
    float r_angle_2 = PI/2;
    MyMatrix3x3 r_2_expected =  {
        .m_3x3 = {
            {0,  0,  1},
            {0,  1, 0 },
            {-1,  0, 0}
        }
    };
    MyMatrix3x3 r_2_actual = axis_angle_rotate( a_2, r_angle_2);
    bool r_2_assert = is_equal_matrix(r_2_actual, r_2_expected);
    //print_matrix(r_2_actual, "ROTATION MATRIX");
    printf("r_2 %s\n", r_2_assert ? "true" : "false"); //true

    MyVector3 a_3 = {0, 0, 1};
    float r_angle_3 = PI/2;
    MyMatrix3x3 r_3_expected =  {
        .m_3x3 = {
            {0,  -1,  0},
            {1,  0,  0},
            {0,  0, 1}
        }
    };

    MyMatrix3x3 r_3_actual = axis_angle_rotate( a_3, r_angle_3);
    bool r_3_assert = is_equal_matrix(r_3_actual, r_3_expected);
    //print_matrix(r_3_actual, "ROTATION MATRIX");
    printf("r_3 %s\n", r_3_assert ? "true" : "false"); //true

    MyVector3 a_4 = {0.57735027f, 0.57735027f, 0.57735027f};
    float r_angle_4 = PI/2;
    MyMatrix3x3 r_4_expected =  {
        .m_3x3 = {
            { 0.33333333f, -0.24401694f,  0.9106836f },
            { 0.9106836f ,  0.33333333f, -0.24401694f},
            {-0.24401694f,  0.9106836f ,  0.33333333f}
        }
    };
    MyMatrix3x3 r_4_actual = axis_angle_rotate( a_4, r_angle_4);
    bool r_4_assert = is_equal_matrix(r_4_actual, r_4_expected);
    //print_matrix(r_4_actual, "ROTATION MATRIX");
    printf("r_4 %s\n", r_4_assert ? "true" : "false"); //true
    
    //return 0;

    MyVector3 a_5 = {0, 1, 0};
    float r_angle_5 = 0;
    MyMatrix3x3 r_5_actual = axis_angle_rotate( a_5, r_angle_5);
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 1200;
    const int targetFPS = 120;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(targetFPS); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    MyVector3 v3 = {.5, .5, .5};
    Hexahedron hexadron_model = generate_hexahedron_model(v3);
    //float angle = 0;
    Vector2 origin_pos = {0,0};
    //float dz = 1; 
    MyVector3 camera_position = {0, 0, 1};
    MyVector3 dir = {0, 0, 1};
    MyMatrix2x3 roll_angle = {
        .v_x = {0,0,0},
        .v_y = {0,0,0}
    };

    int f = 0;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        float dt = 1.f/targetFPS;
        //dz += 1 * dt;
        r_angle_5 += .5f * PI *dt;
        f++;
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 screen_origin_pos = screen(origin_pos, screenWidth, screenHeight);
        DrawLine(0,(int)screen_origin_pos.y, screenWidth, (int)screen_origin_pos.y, BLUE);
        DrawLine((int)screen_origin_pos.x, 0, (int)screen_origin_pos.x, screenHeight, BLUE);
        Screen s = {
           .width = screenWidth,
           .height = screenHeight,
           .rotation_m_3x3 = r_5_actual,
           .hexadron = hexadron_model
        };
        Coordinates c = screen_coordinates(&s, &camera_position, &dir, &roll_angle);
        screen_edges(&c);
        if (IsKeyDown(KEY_DOWN)) {
            camera_position.z += .01f;
        }
        if (IsKeyDown(KEY_UP)) {
            camera_position.z -= .01f;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            camera_position.x += .01f;
        }
        if (IsKeyDown(KEY_LEFT)) {
            camera_position.x -= .01f;
        }
        if (IsKeyDown(KEY_W)) {
            camera_position.y += .01f;
        }
        if (IsKeyDown(KEY_S)) {
            camera_position.y -= .01f;
        }
        if (IsKeyDown(KEY_A)) {
            dir.z += .01f;
        }
        if (IsKeyDown(KEY_D)) {
            dir.z -= .01f;
        }
        if (IsKeyDown(KEY_Q)) {
            roll_angle.v_x.x += 1;
            roll_angle.v_x.y += 1;
            roll_angle.v_y.x += 1;
            roll_angle.v_y.y += 1;
        }
        if (IsKeyDown(KEY_R)) {
            roll_angle.v_x.x -= 1;
            roll_angle.v_x.y -= 1;
            roll_angle.v_y.x -= 1;
            roll_angle.v_y.y -= 1;
        }
        r_5_actual = axis_angle_rotate( a_5, r_angle_5);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}