#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "mp3_header.h"

void edit_mp3(char *tagg, char *new_name, char *filename)
{
    FILE *fp = fopen(filename, "r"); // open file in read mode
    if (!fp) // check if file opened successfully
    {
		printf("-------------------------------------------------------------\n");
        printf("  File not found or Invalid tag option \n");
        printf("  Use: ./a.out --help  to view all valid tag options.\n");
        printf("-------------------------------------------------------------\n");
		return;
	}

    FILE *fptr = fopen("temp.mp3", "w"); // temporary file to write updated data
    if (!fptr) // check if temp file opened successfully
    {
        printf("-------------------------------------------------------------\n");
        printf("  Unable to create temp file\n");
        fclose(fp);
        fclose(fptr);
        printf("-------------------------------------------------------------\n");
        return;
    }


    char id3[4]; // to check if it is an ID3 file

	fread(id3, sizeof(id3) - 1, 1, fp); // read the first 4 bytes to check if it is an ID3 file

	id3[3] = '\0';

	if(strcmp(id3, "ID3") == 0)
	{
		//printf("it is mp3 file\n");
        rewind(fp); // go to file start
	}
	else
	{
        printf("-------------------------------------------------------------\n");
        printf("  It is not an mp3 file\n");
        fclose(fp);
        fclose(fptr);
        remove("temp.mp3"); // delete temp file if created
        printf("-------------------------------------------------------------\n");
		return;
	}

    
    unsigned char header[10]; // ID3 header is 10 bytes
    fread(header, 1, 10, fp); // read the header
    fwrite(header, 1, 10, fptr); //write the header to temp file


    int found = 0; // flag to check if tag is found
    
    while (1)
    {
        char tag[4]; // reading the tag 
        if (fread(tag, 1, 4, fp) != 4) 
            break;

        int size; // reading the size
        fread(&size, 4, 1, fp);

        unsigned char flags[3]; // store the flag
        if(fread(flags, 1, 3, fp) != 3) 
            break;
        
        convert(&size); // convert the size from big-endian system to little-endian system
        if(size <= 0) // if size is invalid
            break;


        if (strcmp(tag, tagg) != 0)
        {
            // Copy this frame as-is
            fwrite(tag, 1, 4, fptr);

            int temp_size = size;
            convert(&temp_size); // convert the size from  little-endian system to big-endian system
            fwrite(&temp_size, 1, 4, fptr);

            fwrite(flags, 1, 3, fptr); // write the flags and null byte

            //char data[size];
            char *data = malloc(size);
            if(data == NULL) // check if memory allocation is successful
            {
                free(data);
                break;
            }
            
            fread(data, size - 1, 1, fp) ; // read the data
            fwrite(data, size - 1, 1, fptr); // write the data to temp file 
            free(data);
        }
        else // found the tag to edit
        {
            found = 1;
            // Write updated frame
            fwrite(tag, 1, 4, fptr);

            int total_size = strlen(new_name) + 1; // new name size
            convert(&total_size); // convert the size from  little-endian system to big-endian system
            fwrite(&total_size, 1, 4, fptr);

            fwrite(flags, 1, 3, fptr); // write the flags and null byte

            fwrite(new_name, 1, strlen(new_name), fptr); // store the new name

            // Skip old frame data
            fseek(fp, size - 1, SEEK_CUR);
            break; // exit after editing the tag
        }
    }

    

    if (found == 0)
    {
        fclose(fp);
        fclose(fptr);

        remove("temp.mp3"); // delete temp file

        printf("-------------------------------------------------------------\n");
        printf("  Tag '%s' not found in the file.\n", tagg);
        printf("  Use: ./a.out --help  to view all valid tag options.\n");
        printf("-------------------------------------------------------------\n");
    }
    else
    {
        // Copy remaining (audio) data
        char buffer[4096];
        while (fread(buffer, 1, sizeof(buffer), fp)) // read remaining data
        {
           fwrite(buffer, 1, sizeof(buffer), fptr); // write remaining data to temp file
        }

        fclose(fp);
        fclose(fptr);

        // Replace original file with edited one
        remove(filename); // delete original file
        rename("temp.mp3", filename); // rename temp file to original file name

        printf("-------------------------------------------------------------\n");
        printf("  Tag '%s' updated successfully!!!\n", tagg);
        printf("  Use: ./a.out --view %s  to view the updated tags.\n", filename);
        printf("-------------------------------------------------------------\n");
    }
}