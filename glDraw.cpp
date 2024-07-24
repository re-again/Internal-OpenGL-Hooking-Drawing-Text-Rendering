#include "pch.h"
#include "glDraw.h"

//Setup ����    ������������ͶӰ����
void GL::SetupOrtho()
{
	//���浱ǰ������״̬��������������λ����ȷ�����ں���ִ����Ϻ󣬿��Իָ�֮ǰ��״̬��
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//����ǰ�����ջ���ľ����Ʋ����͵���ջ�ϡ���Ҫ���ڱ��浱ǰ��ͶӰ����״̬��
	glPushMatrix();

	//����һ���������洢�ӿڵ��ĸ�������
	GLint viewport[4];

	//��ȡ��ǰ���ӿڲ�����������洢�� viewport �����С�viewport[0] �� viewport[1] �ֱ����ӿڵ����½�λ�ã�viewport[2] �� viewport[3] �ֱ����ӿڵĿ�Ⱥ͸߶ȡ�
	glGetIntegerv(GL_VIEWPORT, viewport);

	//�����ӿڣ�ָ�����ڵĿɻ���������������Ϊ�������ڡ�
	glViewport(0, 0, viewport[2], viewport[3]);

	//�л���ͶӰ����ģʽ���������ľ��������Ӱ��ͶӰ����
	glMatrixMode(GL_PROJECTION);

	//����ǰ��ͶӰ��������Ϊ��λ����
	glLoadIdentity();

	/*
	��������ͶӰ���󡣲���������һ��2DͶӰ�ı߽磺
	��߽磺0
		�ұ߽磺�ӿڿ��
		�±߽磺�ӿڸ߶�
		�ϱ߽磺0
		���ü�ƽ�棺 - 1
		Զ�ü�ƽ�棺1
	*/
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

	//�л���ģ����ͼ����ģʽ���������ľ��������Ӱ��ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);

	//����ǰ��ģ����ͼ��������Ϊ��λ����
	glLoadIdentity();

	// ������Ȳ��ԡ�����2D��Ⱦ��ͨ������Ҫ��Ȳ��ԡ�
	glDisable(GL_DEPTH_TEST);
}


//�ָ�֮ǰ�����OpenGL״̬��ȷ�������ص�֮ǰ�����ã�׼������������Ⱦ������
void GL::RestoreGL()
{
	//�Ӿ����ջ�е���֮ǰ����ľ��󣬲�����ָ�Ϊ��ǰ�������� glPushMatrix() ���ʹ�ã����ڻָ�֮ǰ�����ͶӰ����״̬��
	glPopMatrix();

	//�ָ�֮ǰ�������������״̬������ glPushAttrib(GL_ALL_ATTRIB_BITS) ���ʹ�ã����ڻָ�֮ǰ�����OpenGL״̬��
	glPopAttrib();
}


/*
float x���������½ǵ�x���ꡣ
float y���������½ǵ�y���ꡣ
float width�����εĿ�ȡ�
float height�����εĸ߶ȡ�
const GLubyte color[3]��һ������RGB��ɫ���������飬����ָ�����ε���ɫ��
*/
void GL::DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	//���õ�ǰ��ɫΪָ����RGBֵ
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);

	//���ﶨ����4������
	glVertex2f(x, y);
	glVertex2f(x+width, y);
	glVertex2f(x+width, y+height);
	glVertex2f(x, y+height);

	//����
	glEnd();
}

//���ڻ���һ�����ε�����
void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	//�������Ϊָ���� lineWidth��
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	//��ɫ
	glColor3ub(color[0], color[1], color[2]);


	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);

	//��������㣬�ص���㣬��������պϡ�
	glVertex2f(x - 0.5f, y - 0.5f);


	glEnd();
}
