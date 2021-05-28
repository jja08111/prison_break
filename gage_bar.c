#include "gage_bar.h"
#include "utils.h"
#include "colors.h"

#define BAR_WIDTH 13

#define DISABLED_COLOR DARK_GRAY

void drawGageBar(int pct, COORD position, int color)
{
	double convertedPCT = pct * BAR_WIDTH / 10.;
	goto2xy(position.X - BAR_WIDTH / 2, position.Y);

	for (int i = 0;i < BAR_WIDTH;++i)
	{
		if (i * 10 < (int)convertedPCT)
		{
			textcolor(color, BACKGROUND_COLOR);
			printf("бс");
		}
		else
		{
			textcolor(DISABLED_COLOR, BACKGROUND_COLOR);
			printf("бр");
		}	
	}
}