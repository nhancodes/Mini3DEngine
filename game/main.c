#include "raylib.h"
#include "engine.h"
#include "my_math.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h> 
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
#define  EPSILON_F 1e-6f

bool equal_relative(float a, float b) {
    float diff = fabsf(a - b);
    float larger = fmaxf(fabsf(a), fabsf(b));

    if (larger < EPSILON_F) {
       return diff < EPSILON_F ; 
    }
    return diff / larger < EPSILON_F;
}

bool is_equal_matrix(Matrix3x3 actual_result, Matrix3x3 expected_result) {
    // iterate through the actual_result and check the expected_result
    // loop through the rows 
    for (int row = 0; row < 3; row++) {
    //loop through the value
        for (int col = 0; col < 3; col++) {
        // if not equal to expected_result return false
           if (equal_relative(actual_result[row][col], expected_result[row][col]) == false) {
            return false;
           }
            /*if (actual_result[row][col] != expected_result[row][col]){
                return false;
            }*/
        }
    }
    return true;
}


int main(void)
{
    //TEST 
    float x = 0.2f;
    float y = 0.1f;
    printf("%f", x + y);
    Matrix3x3 mat1 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 mat2 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}};
    Matrix3x3 expected_result = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}};
    Matrix3x3 actual_result = {{0,0,0}, {0,0,0},{0,0,0}};
    matrix_mul(mat1, mat2, actual_result);
    bool result = is_equal_matrix(actual_result, expected_result);
    printf("result %s\n", result ? "true" : "false");//true

    Matrix3x3 mat3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 mat4 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}};
    Matrix3x3 expected_result_1 = {{0, 2, 1} , {0, 0, 1}, {0, 0, 1}};
    Matrix3x3 actual_result_1 = {{0,0,0}, {0,0,0},{0,0,0}};
    matrix_mul(mat3, mat4, actual_result_1);
    bool result_1 = is_equal_matrix(actual_result_1, expected_result_1);
    printf("result %s\n", result_1 ? "true" : "false"); //false

    Matrix3x3 mat5 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 expected_result_2 = {{2, 0, 0} , {0, 2, 0}, {0, 0, 2}};
    Matrix3x3 actual_result_2 = {{0,0,0}, {0,0,0},{0,0,0}};
    scalar_mul(mat5, 2, actual_result_2);
    bool result_2 = is_equal_matrix(actual_result_2, expected_result_2);
    printf("result %s\n", result_2 ? "true" : "false"); //true
    
    Matrix3x3 mat6 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 mat7 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 expected_result_3 = {{2, 0, 0} , {0, 2, 0}, {0, 0, 2}};
    Matrix3x3 actual_result_3 = {{0,0,0}, {0,0,0},{0,0,0}};
    matrix_add(mat6, mat7, actual_result_3);
    bool result_3 = is_equal_matrix(actual_result_3, expected_result_3);
    printf("result %s\n", result_3 ? "true" : "false"); //true

    MyVector3 a_1 = {1, 0, 0};
    float r_angle_1 = PI/2;
    Matrix3x3 r_1_expected =  {
        {1,  0,  0},
        {0,  0, -1},
        {0,  1,  0}
    };
    Matrix3x3 r_1_actual = {{0, 0, 0} , {0, 0, 0}, {0, 0, 0}};
    axis_angle_rotate( a_1, r_angle_1, r_1_actual);
    bool r_1_assert = is_equal_matrix(r_1_actual, r_1_expected);
    print_matrix(r_1_actual, "ROTATION MATRIX");
    printf("r_1 %s\n", r_1_assert ? "true" : "false"); //true

    MyVector3 a_2 = {0, 1, 0};
    float r_angle_2 = PI/2;
    Matrix3x3 r_2_expected =  {
        {0,  0,  1},
        {0,  1, 0 },
        {-1,  0, 0}
    };
    Matrix3x3 r_2_actual = {{0, 0, 0} , {0, 0, 0}, {0, 0, 0}};
    axis_angle_rotate( a_2, r_angle_2, r_2_actual);
    bool r_2_assert = is_equal_matrix(r_2_actual, r_2_expected);
    print_matrix(r_2_actual, "ROTATION MATRIX");
    printf("r_2 %s\n", r_2_assert ? "true" : "false"); //true

    MyVector3 a_3 = {0, 0, 1};
    float r_angle_3 = PI/2;
    Matrix3x3 r_3_expected =  {
        {0,  -1,  0},
        {1,  0,  0},
        {0,  0, 1}
    };
    Matrix3x3 r_3_actual = {{0, 0, 0} , {0, 0, 0}, {0, 0, 0}};
    axis_angle_rotate( a_3, r_angle_3, r_3_actual);
    bool r_3_assert = is_equal_matrix(r_3_actual, r_3_expected);
    print_matrix(r_3_actual, "ROTATION MATRIX");
    printf("r_3 %s\n", r_3_assert ? "true" : "false"); //true

    MyVector3 a_4 = {0.57735027f, 0.57735027f, 0.57735027f};
    float r_angle_4 = PI/2;
    Matrix3x3 r_4_expected =  {
        { 0.33333333f, -0.24401694f,  0.9106836f },
        { 0.9106836f ,  0.33333333f, -0.24401694f},
        {-0.24401694f,  0.9106836f ,  0.33333333f}
    };
    Matrix3x3 r_4_actual = {{0, 0, 0} , {0, 0, 0}, {0, 0, 0}};
    axis_angle_rotate( a_4, r_angle_4, r_4_actual);
    bool r_4_assert = is_equal_matrix(r_4_actual, r_4_expected);
    print_matrix(r_4_actual, "ROTATION MATRIX");
    printf("r_4 %s\n", r_4_assert ? "true" : "false"); //true
    
    return 0;
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int targetFPS = 120;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(targetFPS); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    MyVector3 v3 = {.25, .25, .25};
    HexadronModel hexadron_model = generate_hexahedron_model(v3);
    //float angle = 0;
    Vector2 origin_pos = {0,0};
    //float dz = 1; 
    // Main game loop
    r_angle_1 = 0;
    int f = 0;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        float dt = 1.f/targetFPS;
        //dz += 1 * dt;
        r_angle_1 += .5 * PI *dt;
        f++;
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 screen_origin_pos = screen(origin_pos, screenWidth, screenWidth);
        DrawLine(0,(int)screen_origin_pos.y, 800, (int)screen_origin_pos.y, BLUE);
        DrawLine((int)screen_origin_pos.x, 0, (int)screen_origin_pos.x, 800, BLUE);
        for (int i = 0; i < 8; i++) {
            //DrawCircleV(screen(project(hexadron_model.HexadronModel[i]), screenWidth, screenHeight), 5, RED);
            //DrawCircleV(screen(project(rotate_xz(hexadron_model.HexadronModel[i], angle)), screenWidth, screenHeight), 5, RED);
           // MyVector3 rotated_pos = rotate_xz(hexadron_model.HexadronModel[i], angle);
            MyVector3 t3 = {0,0,1};
            MyVector3 rotate_90_vector = matrix_vector_mul(r_1_actual, hexadron_model.HexadronModel[i]);
            MyVector3 translated_pos = translate(rotate_90_vector,t3);
            //MyVector3 translated_pos = translate( hexadron_model.HexadronModel[i],t3);
            Vector2 projected_pos = project(translated_pos);
            Vector2 screen_pos = screen(projected_pos, screenWidth, screenHeight);
            DrawText(TextFormat("%d", i), (int)screen_pos.x, (int)screen_pos.y, 24, RED);
            if (i == 0 && f % 10 == 0) {
                printf("point 0 = %f\n %f\n", screen_pos.x, screen_pos.y);
            }
        }
        axis_angle_rotate( a_1, r_angle_1, r_1_actual);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}