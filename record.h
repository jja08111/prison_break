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

// ������ �Է��Ѵ�. �̶� �Է¿� �����ϸ� 1�� ��ȯ�Ѵ�.
int writeRecordFile(const Record* const record);

void showRecordScreen();

#endif 
