#include "record.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define MAX_COUNT 256

// 내림차순
static int compareRecord(Record* a, Record* b)
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

int countRecordFiles(FILE* fp)
{
	int filesize;
	int n;
	fseek(fp, 0, SEEK_END); 
	filesize = ftell(fp); 
	n = filesize / sizeof(Record);
	return n;
}

void showRecordScreen()
{
	FILE* fp;
	Record arrRecord[MAX_COUNT];
	int count;

	system("cls");

	fp = fopen(RECORD_FILE_NAME, "r+b");
	if (fp == NULL)
	{
		perror("fopen");
		Sleep(2000);
		return;
	}
	
	count = countRecordFiles(fp);
	fseek(fp, 0, SEEK_SET);

	for (int i = 0;i < count;++i)
	{
		fread(&arrRecord[i], sizeof(Record), 1, fp);
	}

	qsort(arrRecord, count, sizeof(Record), compareRecord);

	for (int i = 0;i < count;++i)
		printf("%d등 : %s - %d점, %d 단계, %d 제압 \n",
			i + 1,
			arrRecord[i].name,
			arrRecord[i].totalScore,
			arrRecord[i].reachedStageLevel,
			arrRecord[i].killingCount);

	while (1)
	{
		if (_kbhit())
		{
			getch();
			break;
		}
			
	}

	fclose(fp);
	system("cls");
}