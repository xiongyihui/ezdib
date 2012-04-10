
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ezdib.h"

int bar_graph( HEZDIMAGE x_hDib, HEZDFONT x_hFont, int x1, int y1, int x2, int y2, 
			   int nDataType, void *pData, int nDataSize, int *pCols, int nCols )
{
	int i, w, h;
	int tyw = 0, bw = 0;
	double v, dMin, dMax, dRMin, dRMax;
	char num[ 256 ] = { 0 };

	// Sanity checks
	if ( !pData || 0 >= nDataSize || !pCols || !nCols )
		return 0;
	
	// Figure out the range
	dMin = dMax = ezd_scale_value( 0, nDataType, pData, 0, 1, 0, 1 );
	for ( i = 1; i < nDataSize; i++ )
	{	v = ezd_scale_value( i, nDataType, pData, 0, 1, 0, 1 );
		if ( v < dMin )
			dMin = v;
		else if ( v > dMax )	
			dMax = v;
	} // end for
	
	// Add margin to range
	dRMin = dMin - ( dMax - dMin ) / 10;
	dRMax = dMax + ( dMax - dMin ) / 10;

	// Calculate text width of smallest number
	sprintf( num, "%.2f", dMin );
	ezd_text_size( x_hFont, num, -1, &tyw, &h );
	ezd_text( x_hDib, x_hFont, num, -1, x1, y2 - ( h * 2 ), *pCols );

	// Calculate text width of largest number
	sprintf( num, "%.2f", dMax );
	ezd_text_size( x_hFont, num, -1, &w, &h );
	ezd_text( x_hDib, x_hFont, num, -1, x1, y1 + h, *pCols );
	if ( w > tyw )
		tyw = w;
		
	// For good measure
	tyw += 10;

	// Draw margins
	ezd_line( x_hDib, x1 + tyw, y1, x1 + tyw, y2, *pCols );
	ezd_line( x_hDib, x1 + tyw, y2, x2, y2, *pCols );

	// Bar width
	bw = ( x2 - x1 - tyw ) / nDataSize - nDataSize * 2;
	
	// Draw the bars
	for ( i = 0; i < nDataSize; i++ )
	{	v = ezd_scale_value( i, nDataType, pData, dRMin, dRMax, 0, y2 - y1 - 2 );
		ezd_fill_rect( x_hDib, x1 + tyw + ( ( bw + 2 ) * i ), y2 - v - 2, 
							   x1 + tyw + ( ( bw + 2 ) * i ) + bw, y2 - 2, pCols[ 1 ] );
		ezd_rect( x_hDib, x1 + tyw + ( ( bw + 2 ) * i ), y2 - v - 2, 
						  x1 + tyw + ( ( bw + 2 ) * i ) + bw, y2 - 2, *pCols );
	} // end for

	return 1;
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
	HEZDFONT hFont = ezd_load_font( EZD_FONT_TYPE_MEDIUM, 0, 0 );
	if ( hFont )
		ezd_text( hDib, hFont, "--- EZDIB Test ---", -1, 10, 10, 0xffffff );
	
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
	ezd_rect( hDib, 35, 295, 605, 445, 0x000000 );
	
	// Circle
	ezd_circle( hDib, 525, 150, 80, 0x000000 );
			
	// Draw bar graph
	{
		int data[] = { 11, 54, 23, 87, 34, 54, 75, 44 };
		int cols[] = { 0x202020, 0x400000, 0x004000, 0x000040 };
		bar_graph( hDib, hFont, 40, 300, 600, 440, EZD_TYPE_INT,
				   data, sizeof( data ) / sizeof( data[ 0 ] ),
				   cols, sizeof( cols ) / sizeof( cols[ 0 ] ) );
	}

	// Save the test image
	ezd_save( hDib, "test.bmp" );
	
	/// Releases the specified font
	if ( hFont )
		ezd_destroy_font( hFont );
	
	// Free resources
	if ( hDib )
		ezd_destroy( hDib );
	
	return 0;
}
