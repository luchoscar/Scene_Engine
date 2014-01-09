/*	wBitmap.h
bitmap loading header file for Warlock rendering engine
copyright 2002 Daniel Holbert	*/

#ifndef	WBITMAP_H
#define	WBITMAP_H

#include <windows.h>

typedef struct
{
	BITMAPFILEHEADER	Header;
	BITMAPINFOHEADER	Info;
	BYTE				*pixels;
	char				*name;
} wBitmap;

// returns a pointer to the loaded bitmap
wBitmap* wLoadBitmap(char *filename);
void     wFreeBitmap(wBitmap* bitmap);
// saves a bitmap to a file
void	 wSaveBitmap(char *filename, wBitmap *bmp);

#endif