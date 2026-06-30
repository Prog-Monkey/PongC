#include "raylib.h"

// Define the structure
struct Ball
{
    Vector2 pos;
    Vector2 speed;
    float radius;
    Color color;
};

// Returns a new struct with reset values
struct Ball ResetBall(Vector2 center)
{
    struct Ball b;
    b.pos = center;
    // Randomly pick direction
    b.speed.x = (GetRandomValue(0, 1) == 0) ? 500 : -500;
    b.speed.y = (GetRandomValue(0, 1) == 0) ? 500 : -500;
    b.radius = 20;
    b.color = RED;
    return b;
}

int main()
{
    InitWindow(10, 10, "Pong in C by Suga");
    ToggleFullscreen();
    MaximizeWindow();
    Vector2 center = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    int p1Score = 0, p2Score = 0;

    Rectangle p1 = {20, center.y - 50, 30, 100};
    Rectangle p2 = {(float)GetScreenWidth() - 50, center.y - 50, 30, 100};

    // Initialize the ball
    struct Ball ball = ResetBall(center);
    float paddleSpeed = 600.0f;
    float maxSpeed = 1000.0f;
    while (!WindowShouldClose())
    {

        if (ball.speed.x > maxSpeed)
            ball.speed.x = maxSpeed;
        if (ball.speed.x < -maxSpeed)
            ball.speed.x = -maxSpeed;
        // --- Update ---
        ball.pos.x += ball.speed.x * GetFrameTime();
        ball.pos.y += ball.speed.y * GetFrameTime();

        // Wall Collision
        if (ball.pos.y <= ball.radius || ball.pos.y >= GetScreenHeight() - ball.radius)
            ball.speed.y *= -1.0f;

        // Scoring
        if (ball.pos.x < 0)
        {
            p2Score++;
            ball = ResetBall(center);
        }
        else if (ball.pos.x > GetScreenWidth())
        {
            p1Score++;
            ball = ResetBall(center);
        }

        // Paddle Collision (Check before movement to prevent sticking)
        if (CheckCollisionCircleRec(ball.pos, ball.radius, p1) ||
            CheckCollisionCircleRec(ball.pos, ball.radius, p2))
        {
            ball.speed.x *= -1.1f;
        }

        // Movement
        if (IsKeyDown(KEY_W) && p1.y > 0)
            p1.y -= paddleSpeed * GetFrameTime();
        if (IsKeyDown(KEY_S) && p1.y < GetScreenHeight() - p1.height)
            p1.y += paddleSpeed * GetFrameTime();
        if (IsKeyDown(KEY_UP) && p2.y > 0)
            p2.y -= paddleSpeed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN) && p2.y < GetScreenHeight() - p2.height)
            p2.y += paddleSpeed * GetFrameTime();

        // --- Draw ---
        BeginDrawing();
        ClearBackground(BLUE);
        DrawRectangleRec(p1, GREEN);
        DrawRectangleRec(p2, GREEN);
        DrawCircleV(ball.pos, ball.radius, ball.color);
        DrawText(TextFormat("P1: %i", p1Score), 100, 20, 40, WHITE);
        DrawText(TextFormat("P2: %i", p2Score), GetScreenWidth() - 200, 20, 40, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}