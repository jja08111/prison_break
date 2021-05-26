#ifndef __RENDER_H__
#define __RENDER_H__

#include "models.h"
#include "utils.h"
#include "icons.h"
#include "constants.h"
#include "sounds.h"

#include <assert.h>
#include <string.h>

void drawEntireMapWith(
	const Map* const map,
	int				 backgroundColor
);

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

void renderMob(
	const MobHandler* const mobHandler,
	const Player* const		player,
	const Map* const		map
);

void render(
	const Stage* const		stage,
	const Player* const		player,
	const MobHandler* const mobHandler,
	Map*					map
);

#endif