#include "pch.h"
#include "gltext.h"

//HDC ��һ��ָ����Щ��ͼ��Դ�Ͳ����ľ����ͨ�������������������ָ�����豸�Ͻ��л�ͼ����
//����height ������ĸ߶�
void GL::Font::Build(int height)
{
	//����һ��Windows�ض��ĺ�������ȡ��ǰ���豸������ (Device Context, DC)��
	hdc = wglGetCurrentDC();

	//����96����������ʾ�б���Щ�б����ڴ洢��ASCII��32��127���ַ���
	base = glGenLists(96);

	//ʹ�� CreateFontA ��������һ�������������ָ��������ĸ߶Ⱥ��������ԣ�ʹ�õ���"Consolas"���塣
	HFONT hFont = CreateFontA(-height,0,0,0,FW_MEDIUM,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FF_DONTCARE| DEFAULT_PITCH, "Consolas");
	
	//ѡ���´�������������豸�������У�������֮ǰ���������
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	//ʹ�� wglUseFontBitmaps �������ɴ�ASCII��32��127���ַ���λͼ��������洢��֮ǰ���ɵ���ʾ�б��С�
	wglUseFontBitmaps(hdc, 32, 96, base);

	//�ָ�֮ǰ����������豸�������С�
	SelectObject(hdc, hOldFont);

	// ɾ���´��������������Ϊ���Ѿ�������Ҫ��
	DeleteObject(hFont);

	bBuilt = true;
}

void GL::Font::Print(float x, float y, const unsigned char color[3], const char* format, ...)
{
	//������ɫ:
	glColor3ub(color[0], color[1], color[2]);

	//�����������ı����Ƶ�λ�ã�x �� y ���ı�����ʼ���ꡣ
	glRasterPos2f(x, y);
	//��Щ�������ڴ���ɱ����������ʽ�����ı��洢�� text �����С�vsprintf_s ���ڽ���ʽ�����ַ���д�� text �У�va_list ���ڴ���䳤������
	char text[100];
	va_list args;
	va_start(args, format);
	vsprintf_s(text, 100, format, args);
	va_end(args);

	//�ⲿ�ִ��뱣���˵�ǰ������״̬����������ʾ�б�Ļ���ַ����ʹ�� glCallLists �����ı���base ���ַ���ʾ�б����ʼ������-32 ��Ϊ�˵�������ַ��
	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
}

//�����ı��ڸ������������ڵ�����λ��
vec3 GL::Font::centerText(float x, float y, float width, float height, float textWidth, float textHeight)
{
	vec3 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}

//���������Ŀ���Ǽ����ı���һ���ض���������ڵ�ˮƽ����λ�á����ص����ı�����ʼ x ���꣬��ʹ�ı���������ˮƽ���С�
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