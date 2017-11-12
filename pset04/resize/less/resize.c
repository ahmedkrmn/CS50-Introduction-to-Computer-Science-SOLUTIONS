/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy factor infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check for correct input of factor
    if(factor < 1 || factor > 100)
    {
        fprintf(stderr , "Please enter a factor in the range of 1 to 100 inclusive\n");
        return 1;
    }
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


    // determine padding for scanlines
    int paddingOutput = (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOriginal = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //change the value of the BMP's height and width to the new values
    bi.biHeight*=factor;
    bi.biWidth*=factor;

    //Set the new image size after increasing height, width, and adding padding
    //Note : each biWidth unit is of size 3 bytes and each padding unit is 1 byte
    int NewSize = abs(bi.biHeight)*(bi.biWidth*3+paddingOutput);

    //Update bf.size and bi.bisizeimage with the new values
    bf.bfSize -= bi.biSizeImage;
    bf.bfSize += NewSize;
    bi.biSizeImage = NewSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //return biheight and biwidth to their old values
    bi.biHeight/=factor;
    bi.biWidth/=factor;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //repeat each row factor times
        for(int w = 0 ; w < factor ; w++)
        {
            // If it is not the first iteration, set the cursor to the begining of the row to repeat this row input again
            if(w!=0) fseek(inptr , -bi.biWidth*3 , SEEK_CUR);

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                //repeat each pixel factor times
                for(int x = 0 ; x < factor ; x++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding if any at the end of the current row
            for (int k = 0; k < paddingOutput; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip padding if any
        fseek(inptr, paddingOriginal, SEEK_CUR);

    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
