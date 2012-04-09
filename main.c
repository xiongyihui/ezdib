
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ezdib.h"

int bar_graph( HEZDIMAGE x_hDib, int x1, int y1, int x2, int y2, int x_col, 
			   void *pData, int nDataType, int nDataSize )
{

}


int main( int argc, char* argv[] )
{
	int x, y;

	// Create image
	HEZDIMAGE hDib = ezd_create( 640, -480, 24 );
	if ( !hDib )
		return -1;

	// Fill in the background
	ezd_fill( hDib, 0x606060 );

	// Test fonts
	HEZDFONT hf = ezd_load_font( EZD_FONT_TYPE_MEDIUM, 0, 0 );
	if ( hf )
	{
		// Draw text
		ezd_text( hDib, hf, "--- EZDIB Test ---", -1, 10, 10, 0xffffff );
	
		/// Releases the specified font
		ezd_destroy_font( hf );

	} // end if
	
	// Draw random lines
	for ( x = 100; x < 400; x += 10 )
		ezd_line( hDib, x, ( x & 1 ) ? 50 : 100, x + 10, !( x & 1 ) ? 50 : 100, 0x00ff00 ),
		ezd_line( hDib, x + 10, ( x & 1 ) ? 50 : 100, x, !( x & 1 ) ? 50 : 100, 0x0000ff );
	
	// Random red box
	ezd_fill_rect( hDib, 200, 150, 400, 250, 0x800000 );

	// Random yellow box
	ezd_fill_rect( hDib, 300, 200, 350, 280, 0xffff00 );
	
	// Draw random dots
	for ( y = 150; y < 250; y += 4 )
		for ( x = 50; x < 150; x += 4 )
			ezd_set_pixel( hDib, x, y, 0xffffff );

	// Rectangle
	ezd_rect( hDib, 40, 300, 600, 440, 0x000000 );

	// Circle
	ezd_circle( hDib, 600, 40, 20, 0x000000 );
			
	// Save the test image
	ezd_save( hDib, "test.bmp" );
	
	// Free resources
	ezd_destroy( hDib );
	
	return 0;
}
