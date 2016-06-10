#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct symbol {
	char * name;
	short type;
	union {
		double value;
		double ((* func)());
	} U;
	struct symbol * next;
} Symbol, * Psymbol;

#define SYMB_NULL ((Psymbol) 0)

Psymbol lookUpSymbol (const char * tokenName);
Psymbol installSymbol (const char * tokenName, const short tokenType, const double tokenValue);
void prompt (void);
void init(void);
void warning(const char * mess, const char * type);
void printSymbolList(void);

typedef int (*InsMac) ();	/* Instruction machine */
#define STOP (InsMac) 0 	/* Instruction nulle */
extern InsMac Prog[];		/* Table du code intermédiaire */
extern InsMac *ProgPtr; 	/* Pointeur sur la première case libre de la table */
extern InsMac *PC;	 	/* Pointeur sur la prochaine instruction à exécuter */	

extern InsMac *Code();	 	/* Fonction qui range une instruction dans la table */
#define Code2(c1,c2)	Code(c1); Code(c2)
#define Code3(c1,c2,c3)	Code(c1); Code(c2); Code(c3)
extern execute();		/* Fonction d’exécution du code intermédiaire */

typedef union Data {
	double value; Symbol *symbol; } Data;

extern Data Stack[];
extern Data *StackPtr;

extern Data Pop();		/* Fonction qui dépile une donnée de la pile */
extern Push();			/* Fonction qui empile une donnée dans la pile */
extern VarPush();
extern Eval();
extern Assign();
extern NbrPush();
extern Add();
extern Sub();
extern Div();
extern Mul();
extern Power();
extern Negate();
extern Predef();
extern PrintExpr();

