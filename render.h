#ifndef __RENDER_H__
#define __RENDER_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "utils.h"
#include "icons.h"

// �ʱ� ���� �÷��̾� �þ߿� ���� �׸���. 
static void _renderInitMap(const Map* const map, const Player* const player);

static void _renderMap(const Map* const map, const Player* const player, COORD prevPosition);

// �÷��̾ �׸��µ� ���� ��ġ�� ���� ��ġ�� �ٸ��� ����� ���� �׸���.
static void _renderPlayer(const Player* const player, COORD prevPosition);

void render(const Stage* const stage, const Player* const player, const Map* const map);

#endif