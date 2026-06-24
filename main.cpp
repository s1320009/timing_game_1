#include "raylib.h"


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
	Vector2 circlePos = { 200, 200 };
	Vector2 circleSpeed = { 5, 5 };
	

	while (!WindowShouldClose())
	{
		// ゲームの更新処理
		if(IsKeyDown(KEY_RIGHT)) circlePos.x += circleSpeed.x;    //キーが押されたらX座標にspeedを足す
		if(IsKeyDown(KEY_LEFT)) circlePos.x -= circleSpeed.x;     //キーが押されたらX座標にspeedを引く
		if(IsKeyDown(KEY_UP)) circlePos.y -= circleSpeed.y;       //キーが押されたらY座標にspeedを引く
		if(IsKeyDown(KEY_DOWN)) circlePos.y += circleSpeed.y;     //キーが押されたらY座標にspeedを足す

		
		// ...
		// 描画処理
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
		DrawRectangle(300, 300, 100, 100, BLUE);
		DrawCircleV(circlePos, 100, RED);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}