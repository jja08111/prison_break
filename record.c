#include "record.h"
#include "utils.h"
#include "constants.h"
#include "render.h"
#include "colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define MAX_COUNT 256

#define HEADER_X_POS (SCREEN_WIDTH / 2 - 19)
#define HEADER_Y_POS 2

#define BODY_HORIZONTAL_PADDING 10
#define BODY_Y_POS				9

// 점수 기준으로 내림차순 정렬 비교
static int compareRecord(const Record* a, const Record* b)
{
	if (a->totalScore == b->totalScore)
	{
		if (a->reachedStageLevel == b->reachedStageLevel)
		{
			if (a->killingCount == b->killingCount)
				return strcmp(a->name, b->name); // 이름은 오름차순

			return a->killingCount > b->killingCount ? -1 : 1;
		}
		return a->reachedStageLevel > b->reachedStageLevel ? -1 : 1;
	}
	return a->totalScore > b->totalScore ? -1 : 1;
}

static int countRecordFiles(FILE* fp)
{
	int filesize;
	int n = 0;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	n = filesize / sizeof(Record);
	return n;
}

static size_t getRecordArray(Record arrRecord[MAX_COUNT])
{
	FILE* fp;
	size_t count;

	fp = fopen(RECORD_FILE_NAME, "r+b");
	if (fp == NULL)
	{
		return 0;
	}

	count = countRecordFiles(fp);
	fseek(fp, 0, SEEK_SET);

	for (size_t i = 0;i < count;++i)
	{
		fread(&arrRecord[i], sizeof(Record), 1, fp);
	}
	fclose(fp);

	qsort(arrRecord, count, sizeof(Record), compareRecord);

	return count;
}

static void drawRankingHeader()
{
	gotoxy(HEADER_X_POS, HEADER_Y_POS);		printf("■■■     ■■    ■    ■  ■    ■\n");
	gotoxy(HEADER_X_POS, HEADER_Y_POS + 1); printf("■   ■   ■  ■   ■■  ■  ■  ■  \n");
	gotoxy(HEADER_X_POS, HEADER_Y_POS + 2); printf("■■■   ■■■■  ■ ■ ■  ■■    \n");
	gotoxy(HEADER_X_POS, HEADER_Y_POS + 3); printf("■   ■  ■    ■  ■  ■■  ■  ■  \n");
	gotoxy(HEADER_X_POS, HEADER_Y_POS + 4); printf("■   ■  ■    ■  ■    ■  ■    ■\n");
}

static void drawRankingBody(
	const Record arrRecord[MAX_COUNT],
	size_t		 count
)
{
	size_t maxCount = min(count, 20);
	
	textcolor(BLACK, GRAY);

	drawBox((SMALL_RECT) {
		BODY_HORIZONTAL_PADDING / 2, 
		BODY_Y_POS, 
		(SCREEN_WIDTH - BODY_HORIZONTAL_PADDING) / 2,
		SCREEN_HEIGHT - 4
	});

	if (count == 0)
	{
		gotoxy(HEADER_X_POS, BODY_Y_POS + 2);
		printf("아직 기록이 없습니다.");
		return;
	}
	
	for (size_t i = 0;i < maxCount;++i)
	{
		gotoxy(HEADER_X_POS - 6, BODY_Y_POS + 2 + i);
		printf("%2d등 - %14s %3d점, %d단계, %2d 제압 \n",
			i + 1,
			arrRecord[i].name,
			arrRecord[i].totalScore,
			arrRecord[i].reachedStageLevel,
			arrRecord[i].killingCount);
	}
		
}

int writeRecordFile(const Record* const record)
{
	FILE* fp;

	if ((fp = fopen(RECORD_FILE_NAME, "r+b")) == NULL) { 
		fp = fopen(RECORD_FILE_NAME, "w+b");
		if (fp == NULL) {
			perror("fopen");
			return 1;
		}
	}

	fseek(fp, 0, SEEK_END);
	if (fwrite(record, sizeof(Record), 1, fp) != 1)
	{
		// 에러처리
		return 1;
	}
	fclose(fp);
	return 0;
}

void showRecordScreen()
{

	Record arrRecord[MAX_COUNT];
	size_t count;

	system("cls");

	count = getRecordArray(arrRecord);
	drawRankingHeader();
	drawRankingBody(arrRecord, count);

	while (1)
	{
		if (_kbhit())
		{
			_getch();
			break;
		}
			
	}

	textcolor(BLACK, BLACK);
	system("cls");
}