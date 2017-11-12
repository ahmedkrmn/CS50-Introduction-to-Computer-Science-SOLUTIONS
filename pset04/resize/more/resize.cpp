/**
 * Resize an input BMP image with a decimal factor form 0.1 to 100
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    float factor = atof(argv[1]);

    if(factor >100 || factor <= 0) fprintf(stderr, "Please enter a float number in the range of 0.1 to 100 inclusive");

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //find padding in both input and output files
    int padding = (4 - (bi.biWidth *  sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new = (4 - ((int)(bi.biWidth *factor) *  sizeof(RGBTRIPLE)) % 4) % 4;

    //Update the BMP properties of the output file

    int newSize, oldheight, oldwidth,oldsize;
    oldheight = bi.biHeight;
    oldwidth = bi.biWidth;
    oldsize = bi.biSizeImage;


    bi.biWidth*=factor;
    bi.biHeight*=factor;

    newSize = abs(bi.biHeight)*(bi.biWidth*3+padding_new);

    bi.biSizeImage = newSize;
    bf.bfSize = bf.bfSize - oldsize + newSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Creating a dynamic 2-d array of RGBTRIPLEs containing all the pixels of the original image
    RGBTRIPLE **originalimage = malloc(abs(oldheight) * sizeof(RGBTRIPLE*));

    for(int i = 0 ; i < abs(oldheight) ; i ++)
    {
        // iterate over pixels in scanline
        originalimage[i]=malloc(oldwidth*sizeof(RGBTRIPLE));
        for (int j = 0; j < oldwidth; j++)
        {
            // read RGB triple from infile
            fread(&originalimage[i][j], sizeof(RGBTRIPLE), 1, inptr);

        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

    }

    //Fill the output file with the required pixels from the original image
    for (int i = 0 ; i < abs(bi.biHeight) ; i++)
    {
        for(int y = 0 ; y < bi.biWidth ; y++)
        {
            //We can find the needed equivilant pixel with the formula : original pixel location = output pixel location/factor;
            fwrite(&originalimage[(int)(i/factor)][(int)(y/factor)],sizeof (RGBTRIPLE) ,1,outptr);
        }
        //Add padding
        for(int x = 0 ; x < padding_new ; x++) fputc (0,outptr);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
