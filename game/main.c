#include "raylib.h"
#include "../engine/engine.h"
#include "../engine/my_math.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h> 
#include "../test/test.h"
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
    
    MyVector3 a_6 = {1, 0, 0};
    float r_angle_6 = 0;
    MyMatrix3x3 r_6_actual = axis_angle_rotate( a_6, r_angle_6);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 1200;
    const int targetFPS = 120;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(targetFPS); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    MyVector3 v3 = {.25, .25, .25};
    Hexahedron hexadron_model = generate_hexahedron_model(v3);
    MyVector3 base_v [4] = {{0,0,0},{-1,0,0}, {0,-1,0}, {0,0,-1}};
    //float angle = 0;
    //MyVector3 origin_pos = {0,0,0};
    //float dz = 1; 
    MyVector3 camera_position = {-1, -1, 1.5};

    MyVector3 dir = {0, 0, 1};
    MyMatrix2x3 roll_angle = {
        .v_x = {0,0,0},
        .v_y = {0,0,0}
    };

    int f = 0;
    Int2 mapping_hex [12] = {
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

    Color map_hex_color [12] = {
        { 255, 255, 255, 255 },
        {  255, 255, 255, 255  },
        { 255, 255, 255, 255 },
        {  255, 255, 255, 255  },
        { 255, 255, 255, 255 },
        {  255, 255, 255, 255  },
        { 255, 255, 255, 255 },
        {  255, 255, 255, 255  },
        { 255, 255, 255, 255 },
        {  255, 255, 255, 255  },
        { 255, 255, 255, 255 },
        {  255, 255, 255, 255  },
    };

    Color map_base_color [3] = {
        { 230, 41, 55, 255 },
        { 0, 228, 48, 255 },
        {0, 121, 241, 255 },
    };

    Base hex = {
        .v = hexadron_model.model,
        .v_count = 8,
        .indices_mapping = mapping_hex,
        .i_count = 12
    };

    Int2 mapping_base [3] = {
        {0, 1}, 
        {0, 2}, 
        {0, 3}
    };

    Base base = {
        .v = base_v,
        .v_count = 4,
        .indices_mapping = mapping_base,
        .i_count = 3
    };

    RotationInput rotation_input_base = {
        .axis = {0,1,0},
        .angle = 0 
    };

    MyVector3 scale_input_base = {1,1,1};
    
    MyVector3 translation_input_base = {0,0,0};

    RotationInput rotation_input_hex = {
        .axis = {0,1,0},
        .angle = 0 
    };

    MyVector3 scale_input_hex = {1.5,1,1};
    
    MyVector3 translation_input_hex = {-.5,-.5,0};
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        float dt = 1.f/targetFPS;
        //dz += 1 * dt;
        f++;
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        //MyVector3 screen_origin_pos = generate_screen(origin_pos, screenWidth, screenHeight);
        //DrawLine(0,(int)screen_origin_pos.y, screenWidth, (int)screen_origin_pos.y, BLUE);
        //DrawLine((int)screen_origin_pos.x, 0, (int)screen_origin_pos.x, screenHeight, BLUE);

        draw_model(base, r_6_actual, &camera_position, &dir, &roll_angle, screenWidth, screenHeight, map_base_color, scale_input_base, &rotation_input_base, translation_input_base );

        draw_model(hex, r_5_actual, &camera_position, &dir, &roll_angle, screenWidth, screenHeight, map_hex_color, scale_input_hex, &rotation_input_hex, translation_input_hex);
        rotation_input_hex.angle += .5f * PI *dt;

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
        //r_5_actual = axis_angle_rotate( a_5, r_angle_5);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
