#include "pch.h"
#include "glDraw.h"

//Setup 正交    用于设置正交投影矩阵
void GL::SetupOrtho()
{
	//保存当前的属性状态，包括所有属性位。这确保了在函数执行完毕后，可以恢复之前的状态。
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//将当前矩阵堆栈顶的矩阵复制并推送到堆栈上。主要用于保存当前的投影矩阵状态。
	glPushMatrix();

	//声明一个数组来存储视口的四个参数。
	GLint viewport[4];

	//获取当前的视口参数，并将其存储在 viewport 数组中。viewport[0] 和 viewport[1] 分别是视口的左下角位置，viewport[2] 和 viewport[3] 分别是视口的宽度和高度。
	glGetIntegerv(GL_VIEWPORT, viewport);

	//设置视口，指定窗口的可绘制区域。这里设置为整个窗口。
	glViewport(0, 0, viewport[2], viewport[3]);

	//切换到投影矩阵模式。接下来的矩阵操作将影响投影矩阵。
	glMatrixMode(GL_PROJECTION);

	//将当前的投影矩阵重置为单位矩阵。
	glLoadIdentity();

	/*
	设置正交投影矩阵。参数定义了一个2D投影的边界：
	左边界：0
		右边界：视口宽度
		下边界：视口高度
		上边界：0
		近裁剪平面： - 1
		远裁剪平面：1
	*/
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

	//切换回模型视图矩阵模式。接下来的矩阵操作将影响模型视图矩阵。
	glMatrixMode(GL_MODELVIEW);

	//将当前的模型视图矩阵重置为单位矩阵。
	glLoadIdentity();

	// 禁用深度测试。对于2D渲染，通常不需要深度测试。
	glDisable(GL_DEPTH_TEST);
}


//恢复之前保存的OpenGL状态，确保环境回到之前的配置，准备进行其他渲染操作。
void GL::RestoreGL()
{
	//从矩阵堆栈中弹出之前保存的矩阵，并将其恢复为当前矩阵。这与 glPushMatrix() 配对使用，用于恢复之前保存的投影矩阵状态。
	glPopMatrix();

	//恢复之前保存的所有属性状态。这与 glPushAttrib(GL_ALL_ATTRIB_BITS) 配对使用，用于恢复之前保存的OpenGL状态。
	glPopAttrib();
}


/*
float x：矩形左下角的x坐标。
float y：矩形左下角的y坐标。
float width：矩形的宽度。
float height：矩形的高度。
const GLubyte color[3]：一个包含RGB颜色分量的数组，用于指定矩形的颜色。
*/
void GL::DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	//设置当前颜色为指定的RGB值
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);

	//这里定义了4个顶点
	glVertex2f(x, y);
	glVertex2f(x+width, y);
	glVertex2f(x+width, y+height);
	glVertex2f(x, y+height);

	//结束
	glEnd();
}

//用于绘制一个矩形的轮廓
void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	//线条宽度为指定的 lineWidth。
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	//颜色
	glColor3ub(color[0], color[1], color[2]);


	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);

	//第五个顶点，回到起点，完成轮廓闭合。
	glVertex2f(x - 0.5f, y - 0.5f);


	glEnd();
}
