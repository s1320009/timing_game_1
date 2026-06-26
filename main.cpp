#include "raylib.h"
#include "Ball.h"
#include "Box.h"


#define GAME_TITLE u8"なんか動くやつ"
#define GAME_TIME 10.0f

int main(void)
{
	// 画面の初期化
	const int screenWidth = 800;
	const int screenHeight = 450;
	const char* gameTitle = (const char*)GAME_TITLE;

	InitWindow(screenWidth, screenHeight, gameTitle);
	InitAudioDevice(); // PCのサウンド機能をオンにする
	SetTargetFPS(60);

	//circleの位置を保持する構造体
	Ball ball = CreateBall(Vector2{200, 200}, Vector2{5, 5}, 50, RED);
	Box box = CreateBox(300, 300, 100, 100, BLUE);
	float gameTime = GAME_TIME; // ゲームの制限時間（秒）

	//ロード
	Sound finishSound = LoadSound("resources/finish.wav");

	// ゲーム終了フラグ
	bool isGameFinished = false; 

	while (!WindowShouldClose())
	{
		// ゲームの更新処理
		UpdateBall(&ball, screenWidth, screenHeight);
		UpdateBox(&box, ball.position, ball.radius);

		if (gameTime > 0) {
			gameTime -= GetFrameTime(); // 制限時間を減らす

			if (gameTime < 0) {
				gameTime = 0; // 制限時間が-にならないようにする
			}
		}

		// 🔔 【音を鳴らす更新
		if (gameTime <= 0 && !isGameFinished) {
			PlaySound(finishSound);
			isGameFinished = true;
		}

		// ...
		// 描画処理
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, Raylib!", 190, 200, 20, LIGHTGRAY);
		DrawBox(box);
		DrawBall(ball);
		DrawText(TextFormat("TIME: %.2f", gameTime), 650, 15, 25, GREEN);
		EndDrawing();
	}

	// 🔔 【メモリ解放】ループを抜けたら、使った音のメモリを開放する
	UnloadSound(finishSound);

	CloseAudioDevice(); // サウンド機能をオフにする

	CloseWindow();                    

	return 0;
}