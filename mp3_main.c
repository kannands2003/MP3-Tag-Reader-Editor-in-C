/* 
    Name: Kannan D S
	Roll No: ECEP 25021B 065
    mp3_tag_reader : MP3 tag reader and editor
*/

#include<stdio.h>
#include<string.h>

#include "mp3_header.h"

int main(int argc, char *argv[])
{

	if(argc == 2 && strcmp(argv[1], "--help") == 0) // for help option
	{
		printf("=============================================================\n");
        printf("                 MP3 TAG READER AND EDITOR \n");
        printf("=============================================================\n\n");

        printf("USAGE:\n");
        printf("  View MP3 tags  :  ./a.out -v <file_name>\n");
        printf("  Edit MP3 tags  :  ./a.out -e <tag_option> <new_value> <file_name>\n\n");

        printf("TAG OPTIONS:\n");
        printf("  -t  : Title\n");
        printf("  -a  : Artist\n");
        printf("  -A  : Album\n");
        printf("  -y  : Year\n");
        printf("  -c  : Comment\n");
        printf("  -C  : Music\n");
		
        printf("EXAMPLES:\n");
        printf("  ./a.out -v song.mp3\n");
        printf("  ./a.out -e -t \"New Title\" song.mp3\n\n");
        printf("=============================================================\n");
        return 0;
	}

	if (argc < 3) // for invalid arguments
	{
		printf("-------------------------------------------------------------\n");
        printf("  Invalid usage!\n");
        printf("  Use: ./a.out --help  for correct syntax and options.\n");
        printf("-------------------------------------------------------------\n");
        return 0;
	}

	// id3 tag options
	char *id3_tags[6][2] = 
	{
		{"-t", "TIT2"}, {"-a", "TPE1"}, {"-A", "TALB"}, {"-y", "TYER"}, {"-c", "COMM"}, {"-C", "TCON"}
	};

	
	if ((strcmp(argv[1], "-v") == 0) && argc == 3) // view option
	{
		int last = argc - 1; // last argument is file name
		char *filename = argv[last]; // file name
		view_mp3(filename);
	}
	else if (strcmp(argv[1], "-e") == 0) // edit option
	{
		if (argc < 5) // must have at least 5 arguments
		{
			printf("-------------------------------------------------------------\n");
			printf("  Invalid usage for edit option!\n");
			printf("  Correct format: ./a.out -e <tag_option> <new_value> <file_name>\n");
			printf("-------------------------------------------------------------\n");
			return 0;
		}

		int j, flag = 0;
		for(j = 0 ; j < 6 ; j++)
		{
			if(strcmp(argv[2], id3_tags[j][0]) == 0) // checking valid tag option
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0) // invalid tag option
		{
			printf("-------------------------------------------------------------\n");
            printf("  Invalid tag option \n");
            printf("  Use: ./a.out --help  to view all valid tag options.\n");
            printf("-------------------------------------------------------------\n");
            return 0;
		}

		int last = argc - 1; // last argument is file name

		char new_name[500] = "";

		for(int i = 3 ; i < last ; i++) // concatenating new name from arguments
		{
			strcat(new_name, argv[i]);
			if(i != last - 1) // if not last argument, add space
			{
				strcat(new_name, " ");
			}
		}

		char *filename = argv[last]; // file name
		edit_mp3(id3_tags[j][1], new_name, filename);
	}
	else // invalid arguments
	{
		printf("-------------------------------------------------------------\n");
        printf("  Invalid tag option \n");
        printf("  Use: ./a.out --help  to view all valid tag options.\n");
        printf("-------------------------------------------------------------\n");
	}


	return 0;
}

