#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "parser.h"
#include "linkedlist.h"
#include "interpreter.h"

FILE* source;

int main(int argc, char** argv) {

	/*store arc and argv for use by other fnc if necessary*/
	args_count = argc;
	args = argv;

	/*TODO: implement better help options*/
	/*if (argc != 2) {
		print_usage();
		exit(1);
	}*/

	/*handle file --> open, load, into RAM and then close*/
	char* file_path = "hello.bf\0";
	errno_t err = fopen_s(&source ,file_path, "r");
	if (source == NULL || err!=0)
	{
		printf("Invalid File\n");
		if (source)
			fclose(source);
		exit(1);
	}
	fseek(source, 0, SEEK_END);
	size_t file_size = ftell(source);
	program = (char*) malloc( file_size + 4);
	char* _program = program;
	if (program == NULL) {
		fclose(source);
		exit(1);
	}
	fseek(source, 0, SEEK_SET);
	size_t bytes_loaded = fread(program, sizeof(char), file_size + 4, source);
	assert(bytes_loaded == file_size);
	fclose(source);

	/*pass through parser
	check for pairing of [ and ] -> terminate if necessary	
	create a map for locations of [ and their corresponding ]
	*/
	PCODE parse_code = parse_program();

	if (parse_code == FALIURE)
		goto freeMemory;

	/*pass through interpreter
	use the map of [ and ] for looping / conditionals
	*/
	//printf("Interpreter NOT implemented\n");
	interpret();


	/*free up program from memory*/
freeMemory: 
	free(_program);
	deleteList();

	return 0;

}

void print_usage() {
	printf("\n");
	printf("USAGE:");
	printf("    bf FILE\n");
}