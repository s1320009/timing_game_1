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
	Texture2D ballTexture = LoadTexture("resources/ball.png");

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

		//画像のどの部分を使うか(全部)
		Rectangle sourceRect = { 0, 0, (float)ballTexture.width, (float)ballTexture.height };
		//画像の大きさを指定
		Rectangle destRect = {
			ball.position.x - ball.radius,		// 画像の中心をボールの位置に合わせるために半径分引く
			ball.position.y - ball.radius,		// 画像の中心をボールの位置に合わせるために半径分引く
			ball.radius * 2,					// 画像の大きさをボールの半径に合わせるために半径の2倍にする
			ball.radius * 2						// 画像の大きさをボールの半径に合わせるために半径の2倍にする
		};
		//引数はそれぞれ: テクスチャ, ソース切り抜き, 位置と大きさ, 回転中心, 回転角度, 色
		DrawTexturePro(ballTexture, sourceRect, destRect, Vector2{ 0, 0 }, 0, WHITE);
		DrawText(TextFormat("TIME: %.2f", gameTime), 650, 15, 25, GREEN);
		EndDrawing();
	}

	// 🔔 【メモリ解放】ループを抜けたら、使った音のメモリを開放する
	UnloadTexture(ballTexture);
	UnloadSound(finishSound);

	CloseAudioDevice(); // サウンド機能をオフにする

	CloseWindow();                    

	return 0;
}