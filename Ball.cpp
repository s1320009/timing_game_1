//クラスには関数の中身を書く

#include "Ball.h"

Ball CreateBall(Vector2 position, Vector2 speed, float radius, Color color) {
	Ball ball;
	ball.position = position;
	ball.speed = speed;
	ball.radius = radius;
	ball.color = color;
	return ball;
}

void UpdateBall(Ball* ball, float screenWidth, float screenHeight) {
	// 入力されたら
	if (IsKeyDown(KEY_RIGHT)) {
		ball->position.x += ball->speed.x;
	}
	if (IsKeyDown(KEY_LEFT)) {
		ball->position.x -= ball->speed.x;
	}
	if (IsKeyDown(KEY_UP)) {
		ball->position.y -= ball->speed.y;
	}
	if (IsKeyDown(KEY_DOWN)) {
		ball->position.y += ball->speed.y;
	}
	// 画面端での反射処理
	if (ball->position.x - ball->radius < 0) {
		ball->position.x = ball->radius; // 左端に衝突した場合、ボールの位置を左端に設定
	}
	if (ball->position.x + ball->radius > screenWidth) {
		ball->position.x = screenWidth - ball->radius; // 右端に衝突した場合、ボールの位置を右端に設定
	}
	if (ball->position.y - ball->radius < 0) {
		ball->position.y = ball->radius; // 上端に衝突した場合、ボールの位置を上端に設定
	}
	if (ball->position.y + ball->radius > screenHeight) {
		ball->position.y = screenHeight - ball->radius; // 下端に衝突した場合、ボールの位置を下端に設定
	}
}

void DrawBall(const Ball ball) {
	DrawCircleV(ball.position, ball.radius, ball.color);
}
