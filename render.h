#ifndef __RENDER_H__
#define __RENDER_H__

#include "models.h"
#include "utils.h"
#include "icons.h"
#include "constants.h"
#include "sounds.h"

#include <assert.h>
#include <string.h>

// �簢���� ������ ���� ������ ������ �鵵�� �����Ѵ�.
//
// ���� ������ map�� �� ĭ�� ��ġ�� ������ 0�� ��ȯ�Ѵ�.
static int _ensureToBeWithinRange(
	const Map* const map, 
	SMALL_RECT*		 rect
);



static void drawBox(SMALL_RECT rect);

static void _drawEmptyIconAt(COORD position);

// �� ������ �簢�� ������� �׸���.
static void _drawDarknessFromRect(
	const Map* const map,
	SMALL_RECT		 rect
);



// map[y][x]�� �׸���.
static void _drawMapCellWith(
	const Map* const map,
	COORD			 position,
	int				 emptyCellColor
);

// ���簢�� ������ ���� �׸���.
//
// topLeft�� ���� ����̾�߸� �ϰ� bottomRight�� ���� �ϴ��̾�߸� �Ѵ�.
static void _drawMapWith(
	const Map* const map,
	SMALL_RECT		 rect,
	int				 emptyCellColor
);

void drawEntireMapWith(
	const Map* const map,
	int				 backgroundColor
);

// ���������� �������Ѵ�.
static void _renderTargetSpace(const Map* const map);

// �÷��̾�� �÷��̾� �þ߸� �׸���.
// 
// ���� ���� ��ġ�� ���� ��ġ�� �ٸ��ٸ� ����� ���� �׸���.
void renderPlayer(
	const Player* const player,
	Map*				map
);

// ���� �þ߸� �������Ѵ�.
//
// position ��ġ���� ���� ���� ���� ������ �������Ѵ�. �ش� ��ġ��
// �÷��̾ ��ġ�ߴٸ� �÷��̾� �Ʒ��� �׸���.
void drawMobVisionInPlayerRange(
	COORD				initPosition,
	Direction			direction,
	const Map* const 	map,
	const Player* const	player
);

static void _renderMobVision(
	const Mob* const	mob,
	const Player* const	player,
	const Map* const	map
);

void renderMob(
	const MobHandler* const mobHandler,
	const Player* const		player,
	const Map* const		map
);



static void _drawCenterAlignedText(
	SMALL_RECT	rect, 
	const char* _Format, 
	...
);

static void _renderInterface(
	const Stage* const	stage, 
	const Player* const player,
	const Map* const	map
);

static void _renderDialogAtMapCenter(
	const Map* const map,
	const char*		 _Format,
	...
);

static void _renderSuccessDialog(const Map* const map);

static void _renderFailDialog(const Map* const map);



void render(
	const Stage* const		stage,
	const Player* const		player,
	const MobHandler* const mobHandler,
	Map*					map
);

#endif