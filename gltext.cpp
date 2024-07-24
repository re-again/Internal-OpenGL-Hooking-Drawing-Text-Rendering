#include "pch.h"
#include "gltext.h"

//HDC 是一个指向这些绘图资源和参数的句柄，通过这个句柄，程序可以在指定的设备上进行绘图操作
//参数height 是字体的高度
void GL::Font::Build(int height)
{
	//这是一个Windows特定的函数，获取当前的设备上下文 (Device Context, DC)。
	hdc = wglGetCurrentDC();

	//创建96个连续的显示列表，这些列表将用于存储从ASCII码32到127的字符。
	base = glGenLists(96);

	//使用 CreateFontA 函数创建一个字体对象，这里指定了字体的高度和其他属性，使用的是"Consolas"字体。
	HFONT hFont = CreateFontA(-height,0,0,0,FW_MEDIUM,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FF_DONTCARE| DEFAULT_PITCH, "Consolas");
	
	//选择新创建的字体对象到设备上下文中，并保存之前的字体对象。
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	//使用 wglUseFontBitmaps 函数生成从ASCII码32到127的字符的位图，并将其存储在之前生成的显示列表中。
	wglUseFontBitmaps(hdc, 32, 96, base);

	//恢复之前的字体对象到设备上下文中。
	SelectObject(hdc, hOldFont);

	// 删除新创建的字体对象，因为它已经不再需要。
	DeleteObject(hFont);

	bBuilt = true;
}

void GL::Font::Print(float x, float y, const unsigned char color[3], const char* format, ...)
{
	//设置颜色:
	glColor3ub(color[0], color[1], color[2]);

	//这里设置了文本绘制的位置，x 和 y 是文本的起始坐标。
	glRasterPos2f(x, y);
	//这些代码用于处理可变参数，将格式化的文本存储到 text 数组中。vsprintf_s 用于将格式化的字符串写入 text 中，va_list 用于处理变长参数。
	char text[100];
	va_list args;
	va_start(args, format);
	vsprintf_s(text, 100, format, args);
	va_end(args);

	//这部分代码保存了当前的属性状态，设置了显示列表的基地址，并使用 glCallLists 绘制文本。base 是字符显示列表的起始索引，-32 是为了调整基地址。
	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
}

//计算文本在给定矩形区域内的中心位置
vec3 GL::Font::centerText(float x, float y, float width, float height, float textWidth, float textHeight)
{
	vec3 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}

//这个函数的目的是计算文本在一个特定宽度区域内的水平居中位置。返回的是文本的起始 x 坐标，以使文本在区域内水平居中。
float GL::Font::centerText(float x, float width, float textWidth)
{
	if (width > textWidth)
	{
		float difference = width - textWidth;
		return (x + (difference / 2));
	}
	else
	{
		float difference = textWidth - width;
		return (x - (difference / 2));
	}
}