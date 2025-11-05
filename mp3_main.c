
#include<stdio.h>
#include<string.h>

#include "mp3_header.h"

int main(int argc, char *argv[])
{

	if(argc == 2 && strcmp(argv[1], "--help") == 0) // for help option
	{
		printf("=============================================================\n");
        printf("                 MP3 TAG READER AND EDITOR (v1.0)\n");
        printf("=============================================================\n\n");

        printf("USAGE:\n");
        printf("  View MP3 tags  :  ./a.out -v <file_name>\n");
        printf("  Edit MP3 tags  :  ./a.out -e <tag_option> <new_value> <file_name>\n\n");

        printf("TAG OPTIONS:\n");
        printf("  -t  : Title\n");
        printf("  -a  : Artist\n");
        printf("  -b  : Band\n");
        printf("  -d  : Conductor\n");
        printf("  -r  : Remixer\n");
        printf("  -A  : Album\n");
        printf("  -n  : Track Number\n");
        printf("  -p  : Disc Number\n");
        printf("  -g  : Genre\n");
        printf("  -y  : Year\n");
        printf("  -D  : Date/Time\n");
        printf("  -l  : Language\n");
        printf("  -c  : Comment\n");
        printf("  -x  : Custom Tag\n");
        printf("  -w  : Lyricist\n");
        printf("  -m  : Composer\n");
        printf("  -C  : Copyright\n");
        printf("  -P  : Publisher\n");
        printf("  -s  : ISRC Code\n");
        printf("  -L  : Lyrics\n");
        printf("  -o  : Original Artist\n");
        printf("  -S  : Album Sort\n");
        printf("  -O  : Performer Sort\n");
        printf("  -T  : Title Sort\n\n");

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
	char *id3_tags[24][2] = 
	{
		{"-t", "TIT2"},  {"-a", "TPE1"}, {"-b", "TPE2"}, {"-d", "TPE3"}, {"-r", "TPE4"}, {"-A", "TALB"},   
        {"-n", "TRCK"},  {"-p", "TPOS"}, {"-g", "TCON"}, {"-y", "TYER"}, {"-D", "TDRC"}, {"-l", "TLAN"},    
        {"-c", "COMM"},  {"-x", "TXXX"}, {"-w", "TEXT"}, {"-m", "TCOM"}, {"-C", "TCOP"}, {"-P", "TPUB"},    
        {"-s", "TSRC"},  {"-L", "USLT"}, {"-o", "TOPE"}, {"-S", "TSOA"}, {"-O", "TSOP"}, {"-T", "TSOT"},    
	};


	if (strcmp(argv[1], "-v") == 0) // view option
	{
		int last = argc - 1; // last argument is file name
		char *filename = argv[last]; // file name
		view_mp3(filename);
	}
	else if (strcmp(argv[1], "-e") == 0) // edit option
	{
		int j, flag = 0;
		for(j = 0 ; j < 24 ; j++)
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
            printf("  Invalid tag option: %s\n", argv[2]);
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
            printf("  Invalid tag option: %s\n", argv[2]);
            printf("  Use: ./a.out --help  to view all valid tag options.\n");
            printf("-------------------------------------------------------------\n");
	}


	return 0;
}

