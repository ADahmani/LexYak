#include "expr.h"
#include "expr.tab.h"

// gcc -c symbol.c

static Psymbol symbolList = SYMB_NULL;

void printSymbolList(void) {
	Psymbol sp;
	for (sp = symbolList; sp != SYMB_NULL; sp = sp->next)
		if(sp->type == VAR)
			printf("%s is a variable with %.8g value\n", sp->name, sp->U.value);
		else if (sp->type == PREDEF)
			printf("%s is a function\n", sp->name);
		else if (sp->type == UNDEF)
			printf("%s is something undefined\n", sp->name);
}

Psymbol lookUpSymbol (const char * tokenName) {
	Psymbol sp;
	for(sp = symbolList ; sp != SYMB_NULL ; sp = sp->next)
		if (strcmp(sp->name, tokenName) == 0)
			return sp;
	return SYMB_NULL;
}

Psymbol installSymbol (const char * tokenName, const short tokenType, const double tokenValue) {
	Psymbol sp = (Psymbol) malloc(sizeof(Symbol));
	sp->name = (char *) malloc(strlen(tokenName) + 1);
	strcpy(sp->name, tokenName);
	sp->type = tokenType;
	sp->U.value = tokenValue;

	// Changement des pointeurs de la liste
	sp->next = symbolList;
	symbolList = sp;
	return sp;
}
