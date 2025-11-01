#include<stdio.h>
#include<string.h>

#include "mp3_header.h"

void view_mp3(char *filename)
{
	FILE* fp = fopen(filename,"r");

	//for checking file is exist or not

	if(fp == NULL)
	{
		printf("-------------------------------------------------------------\n");
        printf("  File not found or Invalid tag option \n");
        printf("  Use: ./a.out --help  to view all valid tag options.\n");
        printf("-------------------------------------------------------------\n");
		return;
	}

	//for check the  file is id3 format or mp3 format
	
	char id3[4];

	fread(id3, sizeof(id3) - 1, 1, fp);

	id3[3] = '\0';

	if(strcmp(id3, "ID3") == 0)
	{
		//printf("it is mp3 file\n");
	}
	else
	{
		printf("-------------------------------------------------------------\n");
		printf("  It is not an mp3 file\n");
		fclose(fp);
		printf("  Use: ./a.out --help  to view all valid tag options.\n");
		printf("-------------------------------------------------------------\n");
		return;
	}

	fseek(fp, 7, SEEK_CUR); // skip the version and flags

	const char *id3_tags[6][2] = 
	{
		{"TIT2", "Title"},
		{"TPE1", "Artist"},
		{"TALB", "Album"},
		{"TYER", "Year"},
		{"COMM", "Comment"},
		{"TCON", "music"}
	}; // id3 tag options



	printf("\n==================================================================\n");
    printf("               MP3 TAG INFORMATION \n");
    printf("==================================================================\n\n");
    printf("%-20s | %s\n", "Tag Name", "Tag Value");
    printf("--------------------------------------------------------------------\n");

	while(1)
	{
		char tag[5];
		if(fread(tag, 1, 4, fp) != 4) // read the tag
		{
			break;
		}
		tag[4] = '\0';
				
		int flag = -1; // flag to check if tag is valid

		for(int j = 0 ; j < 6 ; j++) // check if tag is valid
		{
			if(strcmp(tag, id3_tags[j][0]) == 0)
			{
				//printf("%s : ", id3_tags[j][1]);
				flag = j;
			}
		}

		int size;

		fread(&size, sizeof(size), 1, fp); // read the size of the tag
		
		convert(&size);	 // convert the size from big-endian to little-endian

		fseek(fp, 3, SEEK_CUR); // skip the flags and null byte
		
		if(flag != -1) // if tag is valid
		{
			char data[size];
			fread(data, sizeof(data) - 1, 1 , fp);
			data[size - 1] = '\0';

			//puts(data); // print the tag

			printf("%-20s | %s\n", id3_tags[flag][1], data);
			//printf("\n");
		}
		else	 // if tag is not valid
		{
			fseek(fp, size - 1, SEEK_CUR); // skip the tag
		}

	}
	printf("--------------------------------------------------------------------\n");

	fclose(fp);
}


void convert(int *size) // convert the size from big-endian to little-endian
{
	unsigned char *ptr = (char*)size; // convert int to char pointer

	int n = 4; // size of int in bytes

	for(int i = 0; i < n / 2; i++) // swap the bytes
	{
		unsigned char temp = ptr[i];
		ptr[i] = ptr[n - i - 1];
		ptr[n - i - 1]  = temp;
	}
}


	






