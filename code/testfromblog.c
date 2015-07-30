#include<math.h>
#include<stdio.h>
 
#include"expression_parser.h"
 
/**
 @brief macro to compare values as computed by C to those computed by the parser. creates a scope, initializes the parser and parses the string, then prints the expression, C result and parsed result.  Does not handle the exponent operator '^', since it is not equivalent in C.
*/
#define parser_check( expr ) printf( "Parsing: '%s'\n", #expr ); \
        printf( "  C:      %f\n", expr ); \
        printf( "  parser: %f\n\n", parse_expression( #expr ) );
 
void parser_test( const char *expr ){
 double val = parse_expression( expr );
 printf( "%s=%f\n", expr, val );
}
 
int main( int argc, char **argv ){
  
 parser_check( 1.0 + 2.0 );
 parser_check( -1.e-03 + 2E+1 );
 parser_check( asin( sin( 1.0 ) ) );
 parser_check( pow( sin(1.0), 2.0 ) + pow( cos(1.0), 2.0 ) );
 parser_check( (0.1 + 4.9)*(2.5*2)*(-3.0-2.0) );
 parser_check( log( exp( 25.0 ) ) );
 
 parser_test( "2^2^3" );
 parser_test( "sin(1.0)^2 + cos(1.0)^2" );
 parser_test( "2^-2" );
 parser_test( "2^-(2.0*fabs(-sqrt(sin(0.5)^2 + cos(0.5)^2)))" );
   
 return 0;
}
