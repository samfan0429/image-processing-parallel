/**************************************************************

	The program reads an BMP image file and creates a new
	image that is the negative of the input file.

**************************************************************/

#include "qdbmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Creates a negative image of the input bitmap file */
int main( int argc, char* argv[] )
{
	UCHAR	r, g, b, rtmp, gtmp, btmp;
	UINT	width, height;
	UINT	x, y;
	BMP*	bmp;

	/* Check arguments */
	if ( argc != 3 )
	{
		fprintf( stderr, "Usage: %s <input file> <output file>\n", argv[ 0 ] );
		return 0;
	}

	/* Getting the file and output paths */
	char* filePath = malloc(sizeof(char)*255);
	strcpy(filePath,"images/");

	char* output = malloc(sizeof(char)*255);
	strcpy(output,"images/");

	strcat(filePath, argv[1]);
	strcat(filePath,".bmp");

	strcat(output, argv[2]);
	strcat(output,".bmp");
	//Debug
	// printf("Input file %s\n", filePath);
	// printf("Output file %s", output);

	/* Read an image file */
	bmp = BMP_ReadFile( filePath );
	BMP_CHECK_ERROR( stdout, -1 );

	/* Get image's dimensions */
	width = BMP_GetWidth( bmp );
	height = BMP_GetHeight( bmp );

	/* Iterate through all the image's pixels */
	for ( y = 0 ; y < height ; ++y )
	{
		for ( x = 0 ; x < width/2 ; ++x )
		{
			/* Get pixel's RGB values */
			BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
			BMP_GetPixelRGB( bmp, width-1-x, y, &rtmp, &gtmp, &btmp );

			/* Swap RGB values */
			BMP_SetPixelRGB( bmp, x, y, rtmp, gtmp, btmp );
			BMP_SetPixelRGB( bmp, width-1-x, y, r, g, b );
		}
	}

	/* Save result */
	BMP_WriteFile( bmp, output );
	BMP_CHECK_ERROR( stdout, -2 );


	/* Free all memory allocated for the image */
	BMP_Free( bmp );
	free(filePath);
	free(output);

	return 0;
}

