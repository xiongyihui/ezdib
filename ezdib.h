/*------------------------------------------------------------------
// Copyright (c) 1997 - 2012
// Robert Umbehant
// ezdib@wheresjames.com
// http://www.wheresjames.com
//
// Redistribution and use in source and binary forms, with or
// without modification, are permitted for commercial and
// non-commercial purposes, provided that the following
// conditions are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * The names of the developers or contributors may not be used to
//   endorse or promote products derived from this software without
//   specific prior written permission.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------*/

#pragma once

#if defined( __cplusplus )
extern "C"
{
#endif

	// Declare handle
	struct _HEZDIMAGE; 
	typedef struct _HEZDIMAGE *HEZDIMAGE;

	/// Creates an empty image
	/**
		\param [in]  x_lWidth	- Image width
		\param [in]  x_lHeight	- Image height
		\param [in]  x_lBpp		- Image bits per pixel

		\return Image handle or NULL if failure

		\see
	*/
    HEZDIMAGE ezd_create( int x_lWidth, int x_lHeight, int x_lBpp );

	/// Releases the dib handle
	void ezd_destroy( HEZDIMAGE x_hDib );
	
	/// Writes the DIB to a file
	/**
		\param [in] x_hDib		- Handle to a dib
		\param [in] x_pFile		- New image filename
		
		\return Non zero on success
	*/
	int ezd_save( HEZDIMAGE x_hDib, const char *x_pFile );


	/// Fills the image with the specified color
	/**
		\param [in] x_hDib		- Handle to a dib
		\param [in] x_col		- Fill color
		
		\return Non zero on success
	*/
	int ezd_fill( HEZDIMAGE x_hDib, int x_col );
	
	/// Returns the width of the specified image
	int ezd_get_width( HEZDIMAGE x_hDib );

	/// Returns the height of the specified image
	int ezd_get_height( HEZDIMAGE x_hDib );

	/// Returns the bits per pixel of the specified image
	int ezd_get_bpp( HEZDIMAGE x_hDib );

	/// Returns the size in bytes of the image data
	int ezd_get_image_size( HEZDIMAGE x_hDib );

	/// Returns a raw image
	void* ezd_get_image_ptr( HEZDIMAGE x_hDib );

	/// Sets the specified pixel color
	/**
		\param [in] x_hDib		- Handle to a dib
		\param [in] x			- X coord
		\param [in] y			- Y coord
		\param [in] x_col		- Pixel color
		
		\return Non zero on success
	*/
	int ezd_set_pixel( HEZDIMAGE x_hDib, int x, int y, int x_col );
	
	/// Returns the specified pixel color
	/**
		\param [in] x_hDib		- Handle to a dib
		\param [in] x			- X coord
		\param [in] y			- Y coord

		\return The color of the specified pixel
	*/
	int ezd_get_pixel( HEZDIMAGE x_hDib, int x, int y );
	
	
	/// Draws a line between the specified points
	/**
		\param [in] x_hDib		- Handle to a dib
		\param [in] x1			- First X coord
		\param [in] y1			- First Y coord
		\param [in] x2			- Second X coord
		\param [in] y2			- Second Y coord
		\param [in] x_col		- Line color

		\return Non zero on success
	*/
	int ezd_line( HEZDIMAGE x_hDib, int x1, int y1, int x2, int y2, int x_col );
	
	/// Fills the specified rectangle
	/**
		\param [in] x_hDib		- Handle to a dib
		\param [in] x1			- Top Left X coord
		\param [in] y1			- Top Left Y coord
		\param [in] x2			- Bottom Right X coord
		\param [in] y2			- Bottom Right Y coord
		\param [in] x_col		- Fill color

		\return Non zero on success
	*/
	int ezd_fill_rect( HEZDIMAGE x_hDib, int x1, int y1, int x2, int y2, int x_col );

	//--------------------------------------------------------------
	// Font functions
	//--------------------------------------------------------------
	
	// Declare handle
	struct _HEZDFONT; 
	typedef struct _HEZDFONT *HEZDFONT;

	// Built in small font
#	define EZD_FONT_TYPE_SMALL		((unsigned char*)1)

	// Built in medium font
#	define EZD_FONT_TYPE_MEDIUM		((unsigned char*)2)

	// Built in large font
#	define EZD_FONT_TYPE_LARGE		((unsigned char*)3)
	
	/// Set this flag to invert the font
#	define EZD_FONT_FLAG_INVERT		0x01

	/// Loads a font map
	/**
		\param [in] x_pFt		-	Handle to a font map
		\param [in] x_pFtSize	-	Size of the specified font table
		
		This function basically just copies the specified
		font map and creates and index. 
		
		\return Returns a handle to the loaded font
	*/
	HEZDFONT ezd_load_font( const void *x_pFt, int x_nFtSize, unsigned int x_uFlags );

	/// Releases the specified font
	void ezd_destroy_font( HEZDFONT x_hFont );
	
	/// Draws the specified text string into the image
	/**
		\param [in] x_hDib		- Image in which to draw the text
		\param [in] x_hFont		- Font handle returned by ezd_load_font()
		\param [in] x_pText		- Text string to draw
		\param [in] x_nTextLen	- Length of the string in x_pText or zero
								  for null terminated string.
		\param [in] x			- The x coord to draw the text
		\param [in] y			- The y coord to draw the text
		\param [in] x_col		- Text color

		\return Returns non-zero on success
	*/
	int ezd_text( HEZDIMAGE x_hDib, HEZDFONT x_hFont, const char *x_pText, int x_nTextLen, int x, int y, int x_col );

	/// Calculates the size of the specified text
	/**
		\param [in] x_hFont		- Font handle returned by ezd_load_font()
		\param [in] x_pText		- Text string to draw
		\param [in] x_nTextLen	- Length of the string in x_pText or zero
								  for null terminated string.
		\param [in] pw			- Recieves the calculated width
		\param [in] ph			- Receives the calculated height

		\return Returns non-zero on success
	*/
	int ezd_text_size( HEZDFONT x_hFont, const char *x_pText, int x_nTextLen, int *pw, int *ph );
	
#if defined( __cplusplus )	
};
#endif

