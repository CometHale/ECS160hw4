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

void exit_tweeter_processor_error(struct stat *buf, FILE *csv_file){

	const char *invalid_iput_format = "Invalid Input Format\n";
	printf("%s", invalid_iput_format);
	fclose(csv_file);
	free(buf);
	exit(-1);

}

// void exit_tweeter_processor_success(struct stat *buf, char *top_tweeters[10]){

// 	free(buf);
// 	exit(0);
// }

int main(int argc, char *argv[]){

	const char *csv_path;
	const char *top_tweeters[10];
	FILE *csv_file;
	const int max_line_size = 375; // assumed max line length of cl-tweets-short.csv
	char line[max_line_size];
	struct stat *buf = malloc(sizeof(struct stat));

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

// handle too-long file ( > 20000 )

	// handle invalid csv files


	// handle empty file
	
	// handle code injection
	
	// handle no header

	// handle no 'name' column
	
	// handle too many tweeters

	// handle too few tweeters

	// handle commas inside of tweet

 	// handle new lines inside of tweet

	// handle weird unicode characters inside of tweet

	// handle too-long tweet

// handle valid csv files
/* 

*/


	memset(line, '-', max_line_size - 1);
	line[374] = '\0';

	while (fgets(line, sizeof(line), csv_file)) {

		// printf("%d \n", (int) line[374]);

		// following if doesn't work with cl-tweets-short.csv due to a whitespace char at the end of the header line
		// if((!isspace(line[374]) || line[374] != '\0') && line[374] != '-'){ // line is longer than the max line size
		// 	// check if the last char is any kind of whitespace, since not guaranteed that the lines will be separated by newlines
		// 	exit_tweeter_processor_error(buf, csv_file);
		// }


		// empty the line
		memset(line, '-', max_line_size - 1);
		line[374] = '\0';
	}




	// no errors occurred
	fclose(csv_file);
	free(buf);
	return 0;
}
