#ifndef __RENDER_H__
#define __RENDER_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "utils.h"
#include "icons.h"
#include "constants.h"

#include <assert.h>
#include <string.h>

static int _inVisionRange(int y, int x, const Map* const map, const Player* const player);

// �簢���� ������ ���� ������ ������ �鵵�� �����Ѵ�.
//
// ���� ������ map�� �� ĭ�� ��ġ�� ������ 0�� ��ȯ�Ѵ�.
static int _ensureToBeWithinRange(const Map* const map, SMALL_RECT* rect);

static void _drawBox(SMALL_RECT rect);



static void _drawEmptyIconAt(COORD position);

// �� ������ �簢�� ������� �׸���.
static void _drawDarknessFromRect(const Map* const map, SMALL_RECT rect);



// map[y][x]�� �׸���.
static void _drawMapCell(const Map* const map, COORD position);

// map[y][x]�� position ��ġ�� �� ĭ �׸���.
static void _drawMapCellAt(const Map* const map, COORD position);

// ���簢�� ������ ���� �׸���.
//
// topLeft�� ���� ����̾�߸� �ϰ� bottomRight�� ���� �ϴ��̾�߸� �Ѵ�.
static void _drawMapFromRect(const Map* const map, SMALL_RECT rect);



// ���������� �������Ѵ�.
static void _renderTargetSpace(const Map* const map);



// �ʱ� ���� �÷��̾� �þ߿� ���� �׸���. 
//
// ���� ������ ���� ���� �ϴ��̴�.
static void _renderInitMap(const Map* const map, const Player* const player);

// �÷��̾ �̵��� ������ ���� �׸���, ���� ���� �κ��� ���� �����.
static void _renderMap(const Map* const map, const Player* const player);

// �÷��̾ �׸���. ���� ���� ��ġ�� ���� ��ġ�� �ٸ��ٸ� ����� ���� �׸���.
static void _renderPlayer(const Player* const player);



static void _drawCenterAlignedText(SMALL_RECT rect, const char* _Format, ...);

static void _renderInterface(const Stage* const stage, const Player* const player, const Map* const map);

static void _renderDialogAtCenterMap(const Map* const map, const char* _Format, ...);

static void _renderSuccessDialog(const Map* const map, const Stage* const stage);



void render(const Stage* const stage, const Player* const player, Map* map);

#endif