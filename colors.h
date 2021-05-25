#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

#define BLACK		0  

#define RED			12 
#define MAGENTA		13 
#define YELLOW		14 
#define GREEN		2
#define DARK_GRAY   8

#define GRAY		7
#define WHITE		15 

#define BACKGROUND_COLOR	WHITE	// �Ͼ�
#define ON_BACKGROUND_COLOR BLACK	// ����

#define SURFACE_COLOR		GRAY	// ȸ��
#define ON_SURFACE_COLOR	BLACK	// ����

#define DIALOG_COLOR		WHITE	// �Ͼ�
#define ON_DIALOG_COLOR		BLACK	// ����

#define PRIMARY_COLOR		MAGENTA	// ����
#define SECONDARY_COLOR		YELLOW	// ���
#define ACCENT_COLOR		RED		// ����

#define MOB_VISION_COLOR	YELLOW	// ���

// ������ (foreground, background) ���� ����
void textcolor(int color, int bgcolor);

#endif