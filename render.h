#ifndef __RENDER_H__
#define __RENDER_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "utils.h"
#include "icons.h"

#include <assert.h>

static int _inVisionRange(int y, int x, const Map* const map, const Player* const player);

static int rangedNum(int num, int minNum, int maxNum);

// �簢���� ������ ���� ������ ������ �鵵�� �����Ѵ�.
//
// ���� ������ map�� �� ĭ�� ��ġ�� ������ 0�� ��ȯ�Ѵ�.
static int _ensureToBeWithinRange(const Map* const map, SMALL_RECT* rect);

static void _drawEmptyIconAt(COORD position);

// �� ������ �簢�� ������� �׸���.
static void _drawEmptyIconFromRect(const Map* const map, SMALL_RECT rect);


// map[y][x]�� �׸���.
static void _drawMapCell(const Map* const map, COORD position);

// map[y][x]�� position ��ġ�� �� ĭ �׸���.
static void _drawMapCellAt(const Map* const map, COORD position);

// ���簢�� ������ ���� �׸���.
//
// topLeft�� ���� ����̾�߸� �ϰ� bottomRight�� ���� �ϴ��̾�߸� �Ѵ�.
static void _drawMapFromRect(const Map* const map, SMALL_RECT rect);


static void _drawCenterAlignedText(const char* str, SMALL_RECT rect);


// �ʱ� ���� �÷��̾� �þ߿� ���� �׸���. 
static void _renderInitMap(const Map* const map, const Player* const player);

// �÷��̾ �̵��� ������ ���� �׸���, ���� ���� �κ��� ���� �����.
static void _renderMap(const Map* const map, const Player* const player);

// �÷��̾ �׸���. ���� ���� ��ġ�� ���� ��ġ�� �ٸ��ٸ� ����� ���� �׸���.
static void _renderPlayer(const Player* const player);

static void _renderInterface(const Stage* const stage, const Player* const player);

void render(const Stage* const stage, const Player* const player, Map* map);

#endif