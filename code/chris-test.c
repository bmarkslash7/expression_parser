/* chris-test
 * me testing out how this parser works and how to make it work for us
 * need a makefile
 * 
*/

#include<math.h>
#include<stdio.h>
#include<string.h>

#include"expression_parser.h"

double x = 2.0;
double y = 4.0;

int variable_callback( void *user_data, const char *name, double *value ){
	// look up the variables by name
	if( strcmp( name, "var0" ) == 0 ){
		// set return value, return true
		*value = x;
		return PARSER_TRUE;
	} else if( strcmp( name, "var1" ) == 0 ){
		// set return value, return true
		*value = y;
		return PARSER_TRUE;
	}
	// failed to find variable, return false
	return PARSER_FALSE;
}

/* taken right from example.c
 * because function_callback does not automatically go to NULL
*/
int function_callback( void *user_data, const char *name, const int num_args, const double *args, double *value ){
	int i, max_args;
	double tmp;
	
	// example to show the user-data parameter, sets the maximum number of
	// arguments allowed for the following functions from the user-data function
	max_args = *((int*)user_data);
	
	if( strcmp( name, "max_value") == 0 && num_args >= 2 && num_args <= max_args ){
		// example 'maximum' function, returns the largest of the arguments, this and 
		// the min_value function implementation below allow arbitrary number of arguments
		tmp = args[0];
		for( i=1; i<num_args; i++ ){
			tmp = args[i] >= tmp ? args[i] : tmp;
		}
		// set return value and return true
		*value = tmp;
		return PARSER_TRUE;
	} else if( strcmp( name, "min_value" ) == 0 && num_args >= 2 && num_args <= max_args ){
		// example 'minimum' function, returns the smallest of the arguments
		tmp = args[0];
		for( i=1; i<num_args; i++ ){
			tmp = args[i] <= tmp ? args[i] : tmp;
		}
		// set return value and return true
		*value = tmp;
		return PARSER_TRUE;
	} 
	
	// failed to evaluate function, return false
	return PARSER_FALSE;
}

int main( int argc, char **argv ){
	/* double val = parse_expression( expr ); 
	 * where expr is a "string"
	*/
	
	double value;
	parser_data pd;
	
	
	/**
 @brief convenience function for using the library that exposes the callback interface to the variable and function features.  Initializes a parser_data structure on the stack (i.e. no malloc() or free()), sets the appropriate fields and then calls the internal library functions.
 @param[in] expr expression to parse
 @param[in] variable_cb the user-defined variables callback function. set to NULL if unused. see the parser_data structure and the header documentation for this file for more information.
 @param[in] function_cb the user-defined functions callback function. set to NULL if unused. see the parser_data structure and the header documentation of this file for more information.
 @param[in] user_data void pointer that is passed unaltered to the variable_cb and function_cb pointers, for storing application state needed to look up variables and to evaluate functions. set to NULL if unused

double parse_expression_with_callbacks( const char *expr, parser_variable_callback variable_cb, parser_function_callback function_cb, void *user_data );
*/
	
	// parse and expression with no variables or functions
	printf("Test from example.c\n");
	const char *expr2 = "2^3 + 2.0 - 8.0";
	
	value = parse_expression( expr2 );
	if( value == value )
		printf( "%s = %f\n\n", expr2, value );
	else
		printf("\n");
	
	printf("Test to see if variable declaration works.\n");
	const char *expr3 = "x^3 + 2.0 - 8.0";
	printf("%s\n", expr3);
	
	value = parse_expression( expr3 );
	if( value == value )
		printf( "%s = %f\n\n", expr3, value );
	else
		printf("\n");

/* either need to make x and y a variable
 * or make x and y functions -- but I think that would require x() and y()
*/
	
	printf("Test to see if variable_callback works.\n");
	const char *expr4 = "var0^3 + 2.0 - 8.0";
	int num_arguments = 4; 
	value = parse_expression_with_callbacks( expr4, variable_callback, function_callback, &num_arguments ); 
	if( value == value )
		printf( "%s = %f\n\n", expr4, value );
	else 
		printf( "\n" );

	
	
	return(0);
}
