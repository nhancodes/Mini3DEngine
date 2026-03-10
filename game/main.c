#include "raylib.h"
#include "engine.h"
#include "my_math.h"
//#include <math.h>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
typedef Matrix3x3 tests [1][2];

bool is_equal_matrix(Matrix3x3 actual_result, Matrix3x3 expected_result) {
    // iterate through the actual_result and check the expected_result
    // loop through the rows 
    for (int row = 0; row < 3; row++) {
    //loop through the value
        for (int col = 0; col < 3; col++) {
        // if not equal to expected_result return false
            if (actual_result[row][col] != expected_result[row][col]){
                return false;
            }
        }
    }
    return true;
}

void print_matrix(Matrix3x3 matrix) {
    // iterate through the actual_result and check the expected_result
    // loop through the rows 
    for (int row = 0; row < 3; row++) {
    //loop through the value
        for (int col = 0; col < 3; col++) {
        // if not equal to expected_result return false
            printf("row: %d col: %d value: %d\n", row, col, matrix[row][col]);
        }
    }
}

int main(void)
{
    //TEST 
    //[[actual, expected ], [actual, expected]]
    Matrix3x3 mat1 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 mat2 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}};
    
    Matrix3x3 expected_result = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}};
    //get the actual_result
    Matrix3x3 actual_result = {{0,0,0}, {0,0,0},{0,0,0}};
    vector_mul(mat1, mat2, actual_result);
    
    // bool is_equal(actual_result, expected result)
    bool result = is_equal_matrix(actual_result, expected_result);
    printf("result %s\n", result ? "true" : "false");

    Matrix3x3 mat3 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 mat4 = {{0, 0, 1} , {0, 0, 1}, {0, 0, 1}};
    
    Matrix3x3 expected_result_1 = {{0, 2, 1} , {0, 0, 1}, {0, 0, 1}};
    //get the actual_result
    Matrix3x3 actual_result_1 = {{0,0,0}, {0,0,0},{0,0,0}};
    vector_mul(mat1, mat2, actual_result);
    
    // bool is_equal(actual_result, expected result)
    bool result_1 = is_equal_matrix(actual_result_1, expected_result_1);
    printf("result %s\n", result_1 ? "true" : "false");

    Matrix3x3 mat5 = {{1, 0, 0} , {0, 1, 0}, {0, 0, 1}};
    print_matrix(mat5);

    Matrix3x3 expected_result_2 = {{2, 0, 0} , {0, 2, 0}, {0, 0, 2}};

    //get the actual_result
    Matrix3x3 actual_result_2 = {{0,0,0}, {0,0,0},{0,0,0}};
    scalar_mul(mat5, 2.0, actual_result_2);

    printf("_________________");
    print_matrix(actual_result_2);
    // bool is_equal(actual_result, expected result)
    bool result_2 = is_equal_matrix(actual_result_2, expected_result_2);
    printf("result %s\n", result_2 ? "true" : "false");

    //return 0;
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
    float angle = 0;
    Vector2 origin_pos = {0,0};
    //float dz = 1; 
    // Main game loop
    int f = 0;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        float dt = 1.f/targetFPS;
        //dz += 1 * dt;
        angle += .5 * PI *dt;
        f++;
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 screen_origin_pos = screen(origin_pos, screenWidth, screenWidth);
        DrawLine(0,screen_origin_pos.y, 800, screen_origin_pos.y, BLUE);
        DrawLine(screen_origin_pos.x, 0, screen_origin_pos.x, 800, BLUE);
        for (int i = 0; i < 8; i++) {
            //DrawCircleV(screen(project(hexadron_model.HexadronModel[i]), screenWidth, screenHeight), 5, RED);
            //DrawCircleV(screen(project(rotate_xz(hexadron_model.HexadronModel[i], angle)), screenWidth, screenHeight), 5, RED);
            MyVector3 rotated_pos = rotate_xz(hexadron_model.HexadronModel[i], angle);
            MyVector3 t3 = {0,0,1.5};
            MyVector3 translated_pos = translate(rotated_pos,t3);
            Vector2 projected_pos = project(translated_pos);
            Vector2 screen_pos = screen(projected_pos, screenWidth, screenHeight);
            DrawText(TextFormat("%d", i), screen_pos.x, screen_pos.y, 24, RED);
            if (i == 0 && f % 10 == 0) {
                printf("point 0 = %f\n %f\n", screen_pos.x, screen_pos.y);
            }
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}