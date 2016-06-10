%{
	#include "expr.h"
	#include "expr.tab.h"
	extern int lineNo;
%}

%%
[ \t]	;
"PRINT"	return PRINT;
[0-9]+\.?|[0-9]*\.[0-9]+	{
		yylval.symbol = installSymbol("", NUMBER, atof(yytext));
		return NUMBER;
	}
[a-zA-Z][a-zA-Z0-9]*	{
		Psymbol sp = lookUpSymbol(yytext);
		if(sp==SYMB_NULL) sp=installSymbol(yytext, UNDEF, 0.0);
		yylval.symbol=sp;return sp->type;
	}
\n	{
		lineNo++;
		return '\n';
	}
.	return yytext[0];
<<EOF>>	return 0;
%%
