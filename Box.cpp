#include "Box.h"
#include "raylib.h"

Box CreateBox(float x, float y, float width, float height, Color color) {
	Box box;
	box.rect.x = x;
	box.rect.y = y;
	box.rect.width = width;
	box.rect.height = height;
	box.color = color;
	box.isActive = true;
	return box;
}

void UpdateBox(Box* box, Vector2 ballPosition, float radius) {
	if (box->isActive == true) {
		// Check for collision with the ball
		if (CheckCollisionCircleRec(ballPosition, radius, box->rect)) {		//CheckCollisionCircleRecは四角形の一番近い辺または角が円の中心からどれくらい離れているか計算し、それの2乗が円の半径の2乗より小さいかどうかを比較する
			box->isActive = false; // Deactivate the box if collision occurs
		}
	}
} 

void DrawBox(Box box) {
	if (box.isActive == true) {
		DrawRectangleRec(box.rect, box.color); // Draw the box if it is active
	}
}