#ifndef __RENDER_H__
#define __RENDER_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "utils.h"
#include "icons.h"

static int _inVisionRange(int y, int x, const Map* const map, const Player* const player);

// �ʱ� ���� �÷��̾� �þ߿� ���� �׸���. 
static void _renderInitMap(const Map* const map, const Player* const player);

static void _renderMap(const Map* const map, const Player* const player);

// �÷��̾ �׸��µ� ���� ��ġ�� ���� ��ġ�� �ٸ��� ����� ���� �׸���.
static void _renderPlayer(const Player* const player);

void render(const Stage* const stage, const Player* const player, Map* map);

#endif