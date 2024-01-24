%{
extern int yylex(void);
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

int yyerror(const char *s);

char productions_string[1000]; 
%}

%token VAR;
%token ARR;
%token INT;
%token STR;
%token READ;
%token IF;
%token ELSE;
%token DO;
%token WHILE;
%token PRINT;

%token PLUS;
%token MINUS;
%token TIMES;
%token DIV;
%token MOD;
%token BIGGEREQ;
%token LESSEQ;
%token BIGGER;
%token LESS;
%token EQQ;
%token EQ;
%token NEQ;

%token SQBRACKETOPEN;
%token SQBRACKETCLOSE;
%token OPEN;
%token CLOSE;
%token BRACKETOPEN;
%token BRACKETCLOSE;
%token DOT;
%token COMMA;
%token COLON;
%token SEMICOLON;

%token IDENTIFIER;
%token INTCONSTANT;
%token STRINGCONSTANT;
%token ERRI;
%token ERRC;


%start program

%%
program : VAR decllist SEMICOLON cmpdstmt	{ printf("-> program -> var decllist ; cmpdstmt\n"); }
        ;



decllist : declaration              		{ printf("-> decllist -> declaration\n"); }
         | decllist SEMICOLON declaration	{ printf("-> decllist -> decllist ; declaration\n"); }
         ;

declaration : IDENTIFIER COLON type		{ printf("-> declaration -> IDENTIFIER : type\n"); }
            ;

type : type1					{ printf("-> type -> type1\n"); }
     | arraydecl				{ printf("-> type -> arraydecl\n"); }
     ;

type1 : INT					{ printf("-> type1 -> int\n"); }
      | STR					{ printf("-> type1 -> str\n"); }
      ;

arraydecl : ARR OPEN type1 SQBRACKETOPEN INTCONSTANT SQBRACKETCLOSE CLOSE	{ printf("-> arraydecl -> arr ( type1 [ INTCONSTANT ] )\n"); }
          ;



cmpdstmt : BRACKETOPEN stmtlist BRACKETCLOSE	{ printf("-> cmpdstmt -> {stmtlist}\n"); }

stmtlist : stmt SEMICOLON stmtlist		{ printf("-> stmtlist -> stmt ; stmtlist\n"); }
	 | stmt SEMICOLON			{ printf("-> stmtlist -> stmt ; \n"); }
         ;

stmt : simplstmt				{ printf("-> stmt -> simplstmt\n"); }
     | structstmt				{ printf("-> stmt -> structstmt\n"); }
     ;



simplstmt : assignstmt           	{ printf("-> simplstmt -> assignstmt\n"); }
          | iostmt               	{ printf("-> simplstmt -> iostmt\n"); }
          ;

assignstmt : IDENTIFIER EQ expression 	{ printf("-> assignstmt -> IDENTIFIER = expression\n"); }
           ;

expression : expression PLUS term	{ printf("-> expression -> expression + term\n"); }
           | expression MINUS term    	{ printf("-> expression -> expression - term\n"); }
           | term                    	{ printf("-> expression -> term\n"); }
           ;

term : term TIMES factor		{ printf("-> term -> term * factor\n"); }
     | term DIV factor			{ printf("-> term -> term / factor\n"); }
     | factor				{ printf("-> term -> factor\n"); }
     ;

factor : OPEN expression CLOSE    	{ printf("-> factor -> ( expression )\n"); }
       | IDENTIFIER               	{ printf("-> factor -> IDENTIFIER\n"); }
       | INTCONSTANT               	{ printf("-> factor -> INTCONSTANT\n"); }
       ;

iostmt : READ OPEN IDENTIFIER CLOSE  	{ printf("-> iostmt -> read ( IDENTIFIER )\n"); }
       | PRINT OPEN IDENTIFIER CLOSE 	{ printf("-> iostmt -> print ( IDENTIFIER )\n"); }
       | PRINT OPEN STRINGCONSTANT CLOSE { printf("-> iostmt -> print ( STRINGCONSTANT )\n"); }
       | PRINT OPEN INTCONSTANT CLOSE 	{ printf("-> iostmt -> print ( INTCONSTANT )\n"); }
       ;



structstmt : ifstmt                 	{ printf("-> structstmt -> ifstmt\n"); }
           | whilestmt              	{ printf("-> structstmt -> whilestmt\n"); }
           ;

ifstmt : IF OPEN condition CLOSE cmpdstmt     						{ printf("-> ifstmt -> if ( condition ) cmpd \n"); }
       | IF OPEN condition CLOSE cmpdstmt SQBRACKETOPEN ELSE cmpdstmt SQBRACKETCLOSE    { printf("-> ifstmt -> if ( condition ) cmpd [else cmpd]\n"); }
       ;
whilestmt : WHILE OPEN condition CLOSE cmpdstmt     					{ printf("-> whilestmt-> while ( condition ) {stmt}\n"); }
       ;

condition : expression RELATION expression						{ printf("-> condition -> expression RELATION expression\n"); }
          ;

RELATION : LESS               { printf("-> RELATION -> <\n"); }
         | LESSEQ             { printf("-> RELATION -> <=\n"); }
         | EQQ                { printf("-> RELATION -> ==\n"); }
         | NEQ                { printf("-> RELATION -> !=\n"); }
         | BIGGER             { printf("-> RELATION -> >\n"); }
         | BIGGEREQ           { printf("-> RELATION -> >=\n"); }
         ;

%%


int yyerror(const char *s) {
    printf("error: %s\n",s);
    return 0;
}

extern FILE *yyin;

int main(int argc, char** argv) {
    if (argc > 1)
        yyin = fopen(argv[1], "r");
    if (!yyparse())
        fprintf(stderr, "\tOK\n");
}