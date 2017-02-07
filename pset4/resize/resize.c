/**
 * CS50x - Problem Set 4 - resize.c
 * 
 * Resize a BMP by given 'resize val'.
 * 
 * Arugments:
 *     resize_val: An integer to resize the BMP by. (Must be between 0 - 100)
 *     infile: BMP File to read.
 *     outfile: File to create as the resized BMP.
 * 
 * Usage: ./resize resizevalue infile outfile
 * 
 * Author: Adrian Arumugam
 * Date: 2016-01-12
 * 
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize resizevalue infile outfile\n");
        return 1;
    }
    
    // Convert resize value to int for later calculations.
    int resize_val = atoi(argv[1]);
    
    // Ensure sane values - validate resize value given by user.
    // Must be positive integer between 0 - 100.
    if ((resize_val < 0) || (resize_val > 100))
    {
        fprintf(stderr, "Usage: ./resize resizevalue infile outfile\n");
        return 1;
    }
    
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
    
    // Maintain the old width, height and padding values
    int old_height = abs(bi.biHeight); 
    int old_width = bi.biWidth;
    int old_padding = (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Calculate new bi.biWidth and bi.biHeight for resizing bitmap.
    bi.biWidth *= resize_val;
    bi.biHeight *= resize_val;
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine biSize for writing into outfile header.
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    
    // determine bfSize for writing into BITMAP FILEHEADER for outfile 
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0; i < old_height; i++)
    {
        // Vertical resizing loop.
        // See below for full explanation on what this loop is achieving.
        for(int j = 0; j < resize_val; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < old_width; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
                // Horizontal resizing loop.
                for(int l = 0; l < resize_val; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Find padding and skip over it if any located from current position
            fseek(inptr, old_padding, SEEK_CUR);
        
            // Attempt to add padding to the end of the line, if we need it(padding > 0).
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }
            
            // Vertical resizing - fseek to go back to the start of the line
            // this allows us to stretch the bitmap pixels vertically by copying
            // each row(resize_val times). 
            //
            // Only go back to the start of the line when resize_val minus 1 lines
            // have been written to our outfile.
            if (j < (resize_val - 1))
            {
                // old_width = pixels (multiply by 3 to get bytes)
                // old_padding = bytes
                // Add them together to get the bytes distance we should back track via fseek.
                //
                // Example:
                // 3x3 pixel BMP. 9 bytes of data per row + 3 bytes of padding.(12 bytes).
                // Once a row is printed we would fseek back (3 * 3) + 3 = 12 bytes to the start of the
                // scanline so that we can vertically resize by writing the line again.
                fseek(inptr, -((old_width * 3) + old_padding), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
