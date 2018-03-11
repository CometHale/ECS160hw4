// maxTweeter.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
/*

Calculate the top 10 tweeters by volume of tweets in a given CSV file of tweets.

output on valid input:
<tweeter>:<count of tweets>

in decreasing order from the most frequent to the 10th most frequent tweeter.

A valid file is:
-- comma separated : has columns separated with commas, but cannot assume the position of the 'name' column

-- has a header

-- has a column containing tweeter names that is called 'name'

-- has maximum line length not longer than the longest line in the csv file given for hw3

--length <= 20000
-- max number of tweeters is not longer than the set of tweeters in the cl-tweets-short.csv file

-- has no commas inside the tweet



The valid headers were left largely unconstrained deliberately.  There is no guarantee on the number of columns in a valid file, just that 1 column (in potentially any column) is called "name".  You could get a file with just 1 column of names, or several columns with the name column in the beginning, middle, or at the end.  You'd call a file invalid only if the name column didn't appear anywhere in the header row, assuming the file didn't violate another constraint such as being too long in line length or in the number of rows.

max line length, row count, and max number of tweeters

require a name to be at least less than the constraint on line length

can consider empty string as a tweeter name

for ties: just print out whatever you get out of the sort
*/
void exit_tweeter_processor_error(struct stat *buf, FILE *csv_file);
void pre_process_file(FILE * csv_file, struct stat *buf, const char *csv_file_lines[], const int max_line_size, const int max_line_number, int *line_count);

void exit_tweeter_processor_error(struct stat *buf, FILE *csv_file){

	const char *invalid_iput_format = "Invalid Input Format\n";
	printf("%s", invalid_iput_format);
	fclose(csv_file);
	free(buf);
	exit(-1);

}

void pre_process_file(FILE * csv_file, struct stat *buf, const char *csv_file_lines[], const int max_line_size, const int max_line_number, int *line_count){

	char line[max_line_size + 1]; // + 1 for \0

	memset(line, '-', max_line_size - 1);
	line[375] = '\0';

	while (fgets(line, sizeof(line), csv_file)) {
		
		// handle invalid csv files

		// handle too-long file ( > 20000 )
		if (*line_count > max_line_number){
			exit_tweeter_processor_error(buf, csv_file);
		}

		// handle line longer than max line size
		if(!isspace(line[strlen(line) - 1])){ // last char is not \0 \r \n \t etc so strlen(line) > 375
			//  strlen b/c some lines might be shorter than 375 chars
			exit_tweeter_processor_error(buf, csv_file);
		}

		csv_file_lines[*line_count] = line;

		// empty the line
		memset(line, '-', max_line_size - 1);
		line[375] = '\0';
		*line_count = *line_count + 1;
	}


	// handle empty file

	if (*line_count == 0)
	{
		exit_tweeter_processor_error(buf, csv_file);
	}

	return;

}

int main(int argc, char *argv[]){

	const int max_line_size = 375; // assumed max line length of cl-tweets-short.csv 
	const int max_line_number = 20000;
	const char *csv_path;
	const char *top_tweeters[10];
	const char *csv_file_lines[max_line_number];
	const char *header;
	FILE *csv_file;
	struct stat *buf = malloc(sizeof(struct stat));
	int line_count = 0;

	// handle invalid number of command-line inputs
	if (argc == 0 || argc > 2)
	{
		exit_tweeter_processor_error(buf, csv_file);
	}
	
	csv_path = argv[1];
	csv_file = fopen(csv_path, "r");
	stat(csv_path, buf);


	// handle invalid file

	if(csv_file == NULL){
		exit_tweeter_processor_error(buf, csv_file);
	}

	// handle incorrect file type: should not be a dir or
	if(!S_ISREG(buf->st_mode)){
		exit_tweeter_processor_error(buf, csv_file);
	}

	// pre-process the file
	pre_process_file(csv_file, buf, csv_file_lines, max_line_size, max_line_number, &line_count);

	// handle valid csv files

	

		// if(*line_count == 0){
		// 	header = line;
		// }

		// handle files with # lines < 11 ( 1 header line + 10 data lines)
			// just return whatever you do have

	// handle no header && handle no 'name' column
			// define a header as a line that contains at least a 'name' column AND 
			// is the first line of the file


		// handle too many tweeters

		// handle too few tweeters

		// handle commas inside of tweet

	 	// handle new lines inside of tweet

		// handle weird unicode characters inside of tweet

		// handle too-long tweet


	// EXTRA THINGS TO CHECK FOR LATER MAYBE:
	// handle code injection
	
	// define header as a line that contains "name" column then implement checks for: 
	// handle header not on first line

	// handle multiple headers



	// no errors occurred
	fclose(csv_file);
	free(buf);
	return 0;
}
