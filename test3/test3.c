#include <conio.h>
#include <graph.h>
void main()
{
	int color = 0;

	_setvideomode( _MRES256COLOR );
	_setcolor( 1 );
	_ellipse( _GBORDER, 60, 45, 260, 195 );

	while (1)
	{
		_setcolor( color );
		_floodfill( 160, 120, color );
		color++;
	};
	getch();
	_setvideomode( _DEFAULTMODE );
}
