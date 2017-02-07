/**
 * CS50x - Problem Set 4 - recover.c
 * 
 * Recover JPEG images from a given source image.
 * 
 * Arugments:
 *     imagefile: Image of storage device to recover JPEG images from.
 * 
 * Usage: ./recover imagefile
 * 
 * Author: Adrian Arumugam
 * Date: 2016-01-13
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE; // rename to BYTE for clarity.

int main(int argc, char *argv[])
{
    unsigned char *buffer; // Initialize buffer ptr for later malloc.
    char *newimgfile;      // Initialize filename ptr for later malloc.
    BYTE block [512];      // Define array for block size on card image.
    int images_found = 0;  // Initialize count for images found.
    
    /* 
     Enforce correcct usage.
    
     Expect binary name and then the imagefile to recover from.
     otherwise exit with relevant exit code.
    */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover imagefile\n");
        return 1;
    }
    
    char *srcimgfile = argv[1]; // Define img ptr - second cli argument provided should be the name of image file.
    
    // Attempt to open the source image with read access.
    FILE *srcimgptr = fopen(srcimgfile, "r"); 
    
    /* 
       Validate whether the src img file could be opened.
       If not exit with relevant exit code.
    */ 
    if (srcimgptr == NULL)
    {
        fprintf(stderr, "Couldn't open file: %s\n", srcimgfile);
        return 2;
    }
    
    FILE *newimgptr = NULL; // Define temporary pointer for later loop validation.
    newimgfile = (char *) malloc(sizeof(BYTE) * 8); // Pointee for filename, allocate heap memory dynamically (8B).
    buffer = (unsigned char *) malloc(sizeof(block)); // Pointee for buffer, allocate heap memory dynamically(512B).
    
    
    /*
      Now the real fun starts!
      
      - Read into buffer, 1 * 512 bytes (Total 512 bytes) from source image.
      - Validate that we're reading in 512 at a time. (Remember we've allocated 512 from the heap to block).
        This protects from the last block of the src file being < 512 as it will copy as much as it 
        can into buffer and then the remaining memory space will be empty(JPGEs don't mind this and 
        are still correct and readable even with padded all-zeros).
      - Look for the start of a JPEG file (Hex = 0xffd8ff, Decimal = 255216255), when found
        create a new jpg file to write the image data to.
      - If the buffer read in does not contain the start of a new jpg image then this data belongs
        to the previously opened image so copy it there.
      - Rinse and Repeat till EOF.
    */
    while(fread(buffer, 1, sizeof(block), srcimgptr) == sizeof(block))
    {
        // Bitwise AND operation to look at the first four bytes of a JPG file
        //
        // 0,1,2 = 0xff, 0xd8, 0xff repectively
        // 3 = can be between 0xe0 - 0xef (The fourth bytes first four bits are always 1110)
        if (buffer[0] == 0xff && 
           buffer[1] == 0xd8 && 
           buffer[2] == 0xff && 
           (buffer[3] & 0xf0) == 0xe0)
        {
            // If we've already found an image then we need to close it
            // before creating a new one.
            if (images_found != 0)
            {
                // close current image file
                fclose(newimgptr);
            }
            
            /* 
               Create a new file with format = XXX.jpg (e.g 000.jpg)

               Use images_found to create the new image in ascending order.
            */
            sprintf(newimgfile, "%03i.jpg", images_found);
            
            /* 
              Open the new jpg image file with write so we can store the recovered image data.
            
               If we can't open the file with write access then return an error.
            */
            newimgptr = fopen(newimgfile, "w");
            if (newimgptr == NULL)
            {
                fprintf(stderr, "Could not create new file: %s\n", newimgfile);
            }
            
            // Write the recovered image data to the jpg image file.
            fwrite(buffer, sizeof(block), 1, newimgptr);
            
            // Increment counter as we've found an image.
            images_found++;
        }
        else
        {
            /* 
              The data read into buffer does not hold a new jpg image this means
               we the data belongs to the previously opened image.
            
               Valid we have an opened image, if yes then write the buffer to the
               open image file.
            */
            if (newimgptr != NULL)
            {
                fwrite(buffer, sizeof(block), 1, newimgptr); 
            }
            
        }
    }
    
    // Cleanup allocated heap memory to prevent any memory leaks.
    free(buffer);
    free(newimgfile);
    
    // Close opene files in a clean manner.
    fclose(srcimgptr);
    fclose(newimgptr);

    // If we've got to this point successfully then return the expected exit code.
    return 0;
}