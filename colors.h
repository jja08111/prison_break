#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

#define HEX_DEFAULT_COLOR	0x00aabbcc

#define BLACK		0  

#define RED2		12 
#define MAGENTA2	13 
#define YELLOW2		14 
#define GREEN		2
#define DARK_GRAY   8

#define GREY      7
#define WHITE1		15 

#define BACKGROUND_COLOR	WHITE1	// �Ͼ�
#define ON_BACKGROUND_COLOR BLACK	// ����

#define SURFACE_COLOR		GREY	// ȸ��
#define ON_SURFACE_COLOR	BLACK	// ����

#define DIALOG_COLOR		WHITE1	// �Ͼ�
#define ON_DIALOG_COLOR		BLACK	// ����

#define PRIMARY_COLOR		MAGENTA2// ����
#define SECONDARY_COLOR		YELLOW2 // ���
#define ACCENT_COLOR		RED2	// ����

#define MOB_VISION_COLOR	YELLOW2	// ���

// ������ (foreground, background) ���� ����
void textcolor(int color, int bgcolor);

#endif