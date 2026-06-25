#pragma once

#include "raylib.h"

typedef struct {
	Rectangle rect;	 // Box rectangle
	Color color;     // Box color
	bool isActive;   // 画面に存在しているか
} Box;

Box CreateBox(float x, float y, float width, float height, Color color);
void UpdateBox(Box* box, Vector2 ballPosition, float radius);
void DrawBox(Box box);