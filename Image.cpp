/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * MIT open courseware with some modification
 * http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2003/assignments/
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image.h"

//-------------------------------------------------------------------------
unsigned char ReadByte(FILE *file) 
{
	unsigned char b;
	size_t success = fread((void*)&b,sizeof(unsigned char),1,file);
	assert (success == 1);
	return b;
}
//-------------------------------------------------------------------------
void WriteByte(FILE *file, unsigned char b) 
{
	size_t success = fwrite((void*)&b,sizeof(unsigned char),1,file);
	assert (success == 1);
}
//-------------------------------------------------------------------------
unsigned char ClampColorComponent(float c) 
{
	int tmp = int (c*255);
	if (tmp < 0) tmp = 0;
	if (tmp > 255) tmp = 255;
	return (unsigned char)tmp;
}
//-------------------------------------------------------------------------
void Image::SavePPM(const char *filename) const 
{
	assert(filename != NULL);
	// must end in .ppm
	const char *ext = &filename[strlen(filename)-4];
	assert(!strcmp(ext,".ppm"));
	FILE *file = fopen(filename, "w");
	// misc header information
	assert(file != NULL);
	fprintf (file, "P6\n");
	fprintf (file, "# Creator: Image::SavePPM()\n");
	fprintf (file, "%d %d\n", width,height);
	fprintf (file, "255\n");
	// the data
	// flip y so that (0,0) is bottom left corner
	for (int y = height-1; y >= 0; y--) 
	{
		for (int x=0; x<width; x++) 
		{
			Vec3f v = GetPixel(x,y);
			fputc (ClampColorComponent(v.g()),file);
			fputc (ClampColorComponent(v.b()),file);
			fputc (ClampColorComponent(v.r()),file);
		}
	}
	fclose(file);
}
//-------------------------------------------------------------------------
Image* Image::LoadPPM(const char *filename) 
{
	assert(filename != NULL);
	// must end in .ppm
	const char *ext = &filename[strlen(filename)-4];
	assert(!strcmp(ext,".ppm"));
	FILE *file = fopen(filename,"rb");
	// misc header information
	int width = 0;
	int height = 0;  
	char tmp[100];
	fgets(tmp,100,file); 
	assert (strstr(tmp,"P6"));
	fgets(tmp,100,file); 
	assert (tmp[0] == '#');
	fgets(tmp,100,file); 
	sscanf(tmp,"%d %d",&width,&height);
	fgets(tmp,100,file); 
	assert (strstr(tmp,"255"));
	// the data
	Image *answer = new Image(width,height);
	// flip y so that (0,0) is bottom left corner
	for (int y = height-1; y >= 0; y--) 
	{
		for (int x = 0; x < width; x++) 
		{
			unsigned char r,g,b;
			r = fgetc(file);
			g = fgetc(file);
			b = fgetc(file);
			Vec3f color(r/255.0f,g/255.0f,b/255.0f);
			answer->SetPixel(x,y,color);
		}
	}
	fclose(file);
	return answer;
}
//-------------------------------------------------------------------------


