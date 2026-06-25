#include "raylib.h"
#include "Ball.h"
#include "Box.h"


#define GAME_TITLE u8"なんか動くやつ"

int main(void)
{
	// 画面の初期化
	const int screenWidth = 800;
	const int screenHeight = 450;
	const char* gameTitle = (const char*)GAME_TITLE;

	InitWindow(screenWidth, screenHeight, gameTitle);
	SetTargetFPS(60);

	//circleの位置を保持する構造体
	Ball ball = CreateBall(Vector2{200, 200}, Vector2{5, 5}, 50, RED);
	Box box = CreateBox(300, 300, 100, 100, BLUE);

	while (!WindowShouldClose())
	{
		// ゲームの更新処理
		UpdateBall(&ball, screenWidth, screenHeight);
		UpdateBox(&box, ball.position, ball.radius);

		
		// ...
		// 描画処理
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
		DrawBox(box);
		DrawBall(ball);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}