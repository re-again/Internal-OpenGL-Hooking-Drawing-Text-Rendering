#include "glDraw.h"
#include "mem.h"
#include "gltext.h"
#include "hook.h"
#include <iostream>

uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"ac_client.exe");

bool bHealth = false, bAmmo = false, bRecoil = false;

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
twglSwapBuffers owglSwapBuffers;
twglSwapBuffers wglSwapBuffersGateway;

GL::Font glFont;
//字体的高度
const int FONT_HEIGHT = 15;
//字体的宽度
const int FONT_WIDTH = 9;

const char* example = "BITCH 刘力嘉";
const char* example2 = "I am your father";


void Draw()
{
	HDC currentHDC = wglGetCurrentDC();
	if (!glFont.bBuilt || currentHDC != glFont.hdc)
	{
		glFont.Build(FONT_HEIGHT);
	}

	//设置正交投影矩阵
	GL::SetupOrtho();

	//用于绘制一个矩形的轮廓
	GL::DrawOutline(300, 300, 200, 200, 2.0f, rgb::red);


	float textPointX = glFont.centerText(300, 200, strlen(example) * FONT_WIDTH);
	float textPointY = 300 - FONT_HEIGHT / 2;
	glFont.Print(textPointX, textPointY, rgb::green, "%s", example);

	vec3 insideTextPoint = glFont.centerText(300, 300 + 100, 200, 200, strlen(example2) * FONT_WIDTH, FONT_HEIGHT);
	glFont.Print(insideTextPoint.x, insideTextPoint.y, rgb::green, "%s", example2);

	GL::RestoreGL();
}

BOOL __stdcall hkwglSwapBuffers(HDC hDc)
{
	std::cout << "BITCH" << std::endl;
	if (GetKeyState(VK_NUMPAD0) & 1)
	{
		Draw();
	}
	return wglSwapBuffersGateway(hDc);
}