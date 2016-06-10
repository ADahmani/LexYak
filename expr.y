%{
	#include "expr.h"
%}
%union {
	double value;
	Psymbol symbol;
}
%token<symbol> VAR UNDEF PREDEF NUMBER DEF
%token PRINT
%type<value> expr
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%right '#'
%%
list:	vide
	| list '\n'	{ Code(STOP); return 1;}
	| list help '\n' {prompt();}
	| list func '\n' {prompt();}
	| list asgn '\n'	{ Code(STOP); return 1; }
	| list expr '\n'	{
                        Code2(PrintExpr,  STOP); return 1;
		}
	| list error '\n'	{yyerrok;prompt();}
vide:	;
asgn:	VAR '=' expr	{ Code3(VarPush, (InsMac) $1, Assign); }
			| UNDEF '=' expr	{ Code3(VarPush, (InsMac) $1, Assign); };
func:	UNDEF '(' ')' '{' bloc '}' {
				$1->type = DEF;
				printf("nouvelle fonction");
			}
			|
			DEF '(' ')' '{' bloc '}' {
						printf("redif fonction");
			};
bloc:	inst
inst:	expr ';'
			|
			asgn ';'
			;
help:	PRINT { printSymbolList(); }
expr:	NUMBER	{ Code2(NbrPush, (InsMac) $1); }
	| VAR	{ Code3(VarPush, (InsMac) $1, Eval); }
	| PREDEF '(' expr ')'	{
			Code2(Predef,  (InsMac) $1->U.func);
		}
	| '(' expr ')'	{ $$ = $2; }
	| '-' expr %prec UNARYMINUS { Code(Negate); }
	| expr '+' expr { Code(Add); }
	| expr '*' expr { Code(Mul); }
	| expr '-' expr { Code(Sub); }
	| expr '#' expr	{ Code(Power); }
	| expr '/' expr { Code(Div); }
	;
%%
char * progName;
int lineNo = 0;
void warning(const char * mess, const char * type) {
	fprintf(stderr, "%s :--", progName);
	if (mess) { fprintf(stderr, "%s--", mess);}
	if (type) { fprintf(stderr, "%s--", type);}
	fprintf(stderr, " at line %d--\n", lineNo);
}
yyerror(const char * mess) {
	warning(mess, NULL);
}
void prompt(void) { fprintf(stdout, "$Achraf>");}
void initCode(void) {
	prompt();
	ProgPtr = Prog;
	PC = Prog;
	StackPtr = Stack;
}
int main(int argc, char* argv[])
{
	progName = argv[0];
	fprintf(stdout, "Bienvenue dans l'Animus\n");
	init();
	printSymbolList();
	for(initCode(); yyparse(); Execute(Prog), initCode());
	fprintf(stdout, "Au revoir\n");
	exit(EXIT_SUCCESS);
}
