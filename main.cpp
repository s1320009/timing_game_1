#include "raylib.h"
#include "Ball.h"
#include "Box.h"


#define GAME_TITLE u8"なんか動くやつ"
#define GAME_TIME 10.0f

// ゲームの状態を表す種類（シーン）
typedef enum {
	STATE_TITLE,    // タイトル画面
	STATE_GAMEPLAY, // ゲーム本番（10秒タイマー）
	STATE_GOOD_ENDING, // エンディング画面（ボックスを壊した）
	STATE_ENDING    // エンディング画面（タイムアップ）
} GameState;

int main(void)
{
	GameState currentState = STATE_TITLE; // 最初はタイトル画面からスタート

	// 画面の初期化
	const int screenWidth = 800;
	const int screenHeight = 450;
	const char* gameTitle = (const char*)GAME_TITLE;

	InitWindow(screenWidth, screenHeight, gameTitle);
	InitAudioDevice(); // PCのサウンド機能をオンにする
	SetTargetFPS(60);

	//ゲームの初期化
	Ball ball = CreateBall(Vector2{200, 200}, Vector2{5, 5}, 50, RED);
	Box box = CreateBox(300, 300, 100, 100, BLUE);
	float gameTime = GAME_TIME; // ゲームの制限時間（秒）

	//ロード
	Sound openingSound = LoadSound("resources/opening.wav"); 
	Sound finishSound = LoadSound("resources/finish.wav");
	Sound breakSound = LoadSound("resources/finalWin.wav");
	Texture2D ballTexture = LoadTexture("resources/ball.png");

	// ゲーム終了フラグ
	bool isOver = false; 
	bool isTitleSound = false; 

	while (!WindowShouldClose())
	{
		switch (currentState) {
		case STATE_TITLE:
			if (!isTitleSound) {
				PlaySound(openingSound);  // タイトル画面で音を鳴らす
				isTitleSound = true;
			}
			// 例えば「ENTERキーが押されたら状態を STATE_GAMEPLAY に変える」
			if (IsKeyPressed(KEY_ENTER)) {
				StopSound(openingSound); // タイトル画面の音を止める)
				currentState = STATE_GAMEPLAY;
			}
			break;

		case STATE_GAMEPLAY:
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
			if (gameTime <= 0 && !isOver) {
				PlaySound(finishSound);
				isOver = true;
				currentState = STATE_ENDING;
			}
			// もしBox.isActiveがfalseになったら、STATE_GOOD_ENDINGに遷移する
			if (!box.isActive) {
				PlaySound(breakSound);
				currentState = STATE_GOOD_ENDING;
			}
			break;

		case STATE_ENDING:
			// 例えば「ENTERキーが押されたら、ゲームをリセットしてタイトルに戻す
			if (IsKeyPressed(KEY_ENTER)) {
				// 🛠️ 【超重要】各種ステータスを初期値にリセット！
				gameTime = GAME_TIME;
				isOver = false; // 音をもう一度鳴らせるようにする
				isTitleSound = false; // タイトル音を再度鳴らせるようにする
				box = CreateBox(300, 300, 100, 100, BLUE); // ボックスを再生成（生存フラグもtrueに戻る）
				ball = CreateBall(Vector2{ 200, 200 }, Vector2{ 5, 5 }, 50, RED); // ボール位置もリセット
				StopSound(finishSound); //音を止める
				currentState = STATE_TITLE; // タイトルへ戻る
			}
			break;	

		case STATE_GOOD_ENDING:		//全部STATE_ENDINGとほぼ同じ
			
			if (IsKeyPressed(KEY_ENTER)) {
				// 🛠️ 【超重要】各種ステータスを初期値にリセット！
				gameTime = GAME_TIME;
				isTitleSound = false; // タイトル音を再度鳴らせるようにする
				box = CreateBox(300, 300, 100, 100, BLUE); // ボックスを再生成（生存フラグもtrueに戻る）
				ball = CreateBall(Vector2{ 200, 200 }, Vector2{ 5, 5 }, 50, RED); // ボール位置もリセット
				StopSound(breakSound); // 音を止める
				currentState = STATE_TITLE; // タイトルへ戻る
			}
			break;
		}

		// 描画処理
		BeginDrawing();
		ClearBackground(RAYWHITE);

		switch (currentState) {
		case STATE_TITLE:
			// タイトル画面の文字や画像を出す
			DrawText("TIMING GAME", 240, 150, 40, DARKGRAY);
			DrawText("PRESS ENTER TO START", 250, 260, 20, GRAY);
			break;

		case STATE_GAMEPLAY:
		{ // 💡 エラー対策：caseの中に変数宣言を置くために、中括弧 { } で小部屋を作る
			// ゲーム本番の描画
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
			break;
		} // 💡 小部屋の終わり

		case STATE_ENDING:
			// エンディング画面の描画
			DrawText("GAME OVER", 280, 150, 40, RED);
			DrawText("PRESS ENTER TO TITLE", 250, 260, 20, GRAY);
			break;

		case STATE_GOOD_ENDING:
			// エンディング画面の描画
			DrawText("YOU WIN!", 280, 150, 40, GREEN);
			DrawText("PRESS ENTER TO TITLE", 250, 260, 20, GRAY);
			break;
		}
		EndDrawing();
	}

	// 🔔 【メモリ解放】ループを抜けたら、使った音のメモリを開放する
	UnloadTexture(ballTexture);
	UnloadSound(openingSound);
	UnloadSound(finishSound);
	UnloadSound(breakSound);

	CloseAudioDevice(); // サウンド機能をオフにする
	CloseWindow();                    

	return 0;
}