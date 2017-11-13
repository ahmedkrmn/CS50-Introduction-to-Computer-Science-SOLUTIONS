#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
int main(int argc , char **argv)
{
    if(argc!=2)
    {
        fprintf(stderr,"Please choose the input file for recovery !\n");
        return 1;
    }

    FILE *input_image = fopen(argv[1],"r");

    if(input_image == NULL)
    {
        fprintf(stderr , "There was a problem opening input file !\n");
        return 2;
    }
    // Create an unsigned char buffer( ie. unsigned 8 bits 0-255 ) of size 512 + 1(null terminating char) to store each readed block
    unsigned char image_data[513];
    // A char array that will contain the image name
    char image_name[10];
    // No of images
    int image_counter=0;
    // Declaring a file pointer to the output
    FILE *output_x = NULL;

    //keep reading 512 bytes at a time from the input file and store them in the buffer array
    while(fread( image_data , sizeof (char) , 512 , input_image) == 512 )
    {
        // If this block starts with 0xff 0xd8 0xff (ie. It's a jpeg file)
        if(image_data[0]==0xff && image_data[1]==0xd8 && image_data[2]==0xff)
        {
            //set image_name with 3 leading zeros
            sprintf(image_name , "%03d.jpg" , image_counter);
            //increment the image counter
            image_counter++;
            //only close the image file if there is one already created to avoid seg faults
            if(image_counter!=1) fclose(output_x);
            //Create a new image file
            output_x = fopen(image_name , "w");
            //Check for creation success
            if(output_x == NULL)
            {
                fprintf(stderr , "Couldn't recover this image !\n");
                return 3;
            }
        }
        //Write this block of bytes in the already opened image file wether it's a new file or a one already created and containg previous byte blocks
        //The if condition checks if there is an image file already opened to avoid seg faults
        if(image_counter!=0)
        {
        fwrite(image_data,sizeof (char) , 512 ,output_x );
        }

    }
    //Close the input image and the last outout image files
    fclose(output_x);
    fclose(input_image);
}
