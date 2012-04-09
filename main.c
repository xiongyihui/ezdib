
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ezdib.h"

int main( int argc, char* argv[] )
{
	int x, y;

	// Create image
	HEZDIMAGE hDib = ezd_create( 500, -500, 24 );
	if ( !hDib )
		return -1;

	// Fill in the background
	ezd_fill( hDib, 0x002060 );

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
		ezd_line( hDib, x + 10, ( x & 1 ) ? 50 : 100, x, !( x & 1 ) ? 50 : 100, 0xff00ff );
	
	// Random red box
	ezd_fill_rect( hDib, 200, 150, 400, 250, 0x800000 );

	// Random yellow box
	ezd_fill_rect( hDib, 300, 200, 350, 400, 0xffff00 );
	
	// Draw random lines
	for ( y = 150; y < 400; y += 4 )
		for ( x = 50; x < 150; x += 4 )
			ezd_set_pixel( hDib, x, y, 0xff80ff );

	// Save the test image
	ezd_save( hDib, "test.bmp" );
	
	// Free resources
	ezd_destroy( hDib );
	
	return 0;
}
