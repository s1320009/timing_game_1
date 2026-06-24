//ヘッダファイルには構造体と関数の宣言を書く

#pragma once    //絶対残せ

#include "raylib.h"

//構造体には位置やその他の必要な情報を書く
typedef struct {
	Vector2 position;   // 位置
	Vector2 speed;      // 速度
	float radius;		// 半径
	Color color;		// 色
} Ball;

//関数は初期化と更新と描画はほぼ必ずあって、そこに機能の関数を作っていく

Ball CreateBall(Vector2 position, Vector2 speed, float radius, Color color);

void UpdateBall(Ball* ball, float screenWidth, float screenHeight);

void DrawBall(const Ball ball);
