#ifndef __RECORD_H__
#define __RECORD_H__

#define MAX_NAME_LENGTH 40

#define RECORD_FILE_NAME "record.bin"

typedef struct _Record {
	char name[MAX_NAME_LENGTH];

	unsigned short totalScore;
	
	unsigned short killingCount;

	unsigned short reachedStageLevel;
} Record;

// 파일을 입력한다. 이때 입력에 실패하면 1을 반환한다.
int writeRecordFile(const Record* const record);

void showRecordScreen();

#endif 
