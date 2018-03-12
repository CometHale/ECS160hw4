#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
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
// EXTRA THINGS TO CHECK FOR LATER MAYBE:
// handle code injection
// define header as a line that contains "name" column then implement checks for: 
// handle header not on first line
// handle multiple headers
// handle new lines inside of tweet
// handle weird unicode characters inside of tweet
// handle too-long tweet; if there is such a thing
*/

// Source: https://stackoverflow.com/questions/4384359/quick-way-to-implement-dictionary-in-c
struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    // char *defn; /* replacement text */
	int defn; // changed for the purposes of HW4
};

#define HASHSIZE 6295
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
static int num_in_hash;

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, int defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        np->defn = defn; // added 
        hashtab[hashval] = np;
    } 
    else{ /* already there */ // changed from original
    	np->defn = defn;
    	hashtab[hashval] = np; // replace with the new key-val pair
    }
    //else /* already there */
        // free((void *) np->defn); /*free previous defn */
    // if ((np->defn = defn) == NULL)
    //    return NULL;
    return np;
}


// maxTweeter.c
void exit_tweeter_processor_error(struct stat *buf, FILE *csv_file);

void exit_tweeter_processor_error(struct stat *buf, FILE *csv_file){

	const char *invalid_iput_format = "Invalid Input Format\n";
	printf("%s", invalid_iput_format);
	fclose(csv_file);
	free(buf);
	exit(-1);
}

int hashval_comp(const void* elem1, const void* elem2){
	// Source : https://stackoverflow.com/questions/1787996/c-library-function-to-do-sort
	// the names should be guaranteed to be in the hash, so no null checking
	const char *name1 = *(const char **) elem1;
	const char *name2 = *(const char **) elem2;
	int f = 0;
	int s = 0;

	if(name1 != NULL){
		f = lookup((char *) name1)->defn;
	}

	if(name2 != NULL){
		s = lookup((char *) name2)->defn;
	}
	
    if (f < s) return  1;
    if (f > s) return -1;

    return 0;
}

int main(int argc, char *argv[]){

	const int max_line_size = 375; // assumed max line length of cl-tweets-short.csv 
	const int max_line_number = 20000;
	const int max_num_tweeters = 6294; // set pof tweeters in cl-tweets-short.csv
	const char *csv_path;
	const char *header;
	char *tweeters[max_num_tweeters];
	char line[max_line_size + 1]; // + 1 for \0
	char temp_line[max_line_size + 1];

	char *buffer; 
	FILE *csv_file;
	struct stat *buf = malloc(sizeof(struct stat));
	int name_col_position;
	int line_count = 0;
	int num_header_cols = 0;
	int num_line_cols = 0;

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

	// handle valid csv files
	
	num_in_hash = 0;

	// for (int i = 0; i < HASHSIZE; ++i){
	// 	hashtab[i] = NULL;
	// }

	memset(line, '-', max_line_size - 1);
	line[375] = '\0';

	while (fgets(line, sizeof(line), csv_file)) {
		
		// handle invalid csv files

		// handle too-long file ( > 20000 )
		if (line_count > max_line_number){
			exit_tweeter_processor_error(buf, csv_file);
		}

		// handle line longer than max line size
		if(!isspace(line[strlen(line) - 1])){ // last char is not \0 \r \n \t etc so strlen(line) > 375
			//  strlen b/c some lines might be shorter than 375 chars
			exit_tweeter_processor_error(buf, csv_file);
		}

		strcpy(temp_line, line); // save a copy of the line

		// empty out the buffer
		buffer = "";
		buffer = strtok(temp_line, ",");

		if (line_count == 0)
		{
			// first line of the file, check to make sure it's a valid header
			
			// handle no header and header without 'name' column
			if (strstr(line, "\"name\"") == NULL && strstr(line, "name") == NULL && strstr(line, "\'name\'") == NULL) { // cover the bases, could have "name" column or name column
			   exit_tweeter_processor_error(buf, csv_file);
			}

			header = line;

			// handle csv isn't comma separated and singular column isn't 'name'
			if(strlen(line) == strlen(buffer) && strncmp(buffer, "name", 4) != 0 && strncmp(buffer, "\"name\"", 6) != 0 && strncmp(buffer, "\'name\'", 6) != 0){
				exit_tweeter_processor_error(buf, csv_file);
			}
		}

		num_line_cols = 0; // reset num_line_cols before each line is strtok'd

		while(buffer != NULL){

			if (line_count == 0){
				if(strncmp(buffer, "name", 4) == 0 || strncmp(buffer, "\"name\"", 6) == 0 || strncmp(buffer, "\'name\'", 6) == 0){
					name_col_position = num_header_cols;
				}
				num_header_cols++;
			}

			// handle commas inside of tweet
			if(num_line_cols > num_header_cols){
				// if the num_line_cols >  num_header_cols, there's a comma where there shouldn't be one
				exit_tweeter_processor_error(buf, csv_file);
			}

			// get the tweeter's name
			char *name = NULL;

			if(num_line_cols == name_col_position){
				
				name = buffer;
			}

			if(name != NULL){
				// if the name isn't in the hash already, add name : 1

				if(lookup(name) == NULL){ // name isn't already in the hash
					install(name, 1);
					num_in_hash++;

					tweeters[num_in_hash] = (char *)malloc(sizeof(char) * max_line_size);
    				strcpy(tweeters[num_in_hash], name);

				}
				else{ // name is in the hash already
					// increase the number of tweets associated with the name
					install(name, lookup(name)->defn + 1);
				}
			}

			// handle too many tweeters
			if (num_in_hash > max_num_tweeters)
			{
				exit_tweeter_processor_error(buf, csv_file);
			}

			buffer = strtok(NULL,",");
			num_line_cols++;
		}

		// empty the line
		memset(line, '-', max_line_size - 1);
		line[375] = '\0';
		line_count++;
	}

	// handle empty file

	if (line_count == 0)
	{
		exit_tweeter_processor_error(buf, csv_file);
	}

	qsort(tweeters, num_in_hash, sizeof(sizeof(char *) * max_line_size), hashval_comp);
	
	// handle files with # lines < 11 ( 1 header line + 10 data lines)
	// handle too few tweeters
		// just return whatever you do have
	for (int i = 0; i < (int) fmin(num_in_hash, 10); ++i)
	{
		if(tweeters[i] != NULL){
			printf("%s : %d\n", tweeters[i], lookup(tweeters[i])->defn);
		}
	}

	// no errors occurred
	for (int i = 0; i < num_in_hash; ++i)
	{
		free(tweeters[i]);
	}

	fclose(csv_file);
	free(buf);
	return 0;
}