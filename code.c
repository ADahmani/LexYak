#include "expr.h"
#include "expr.tab.h"
#include <math.h>

#define MAXPROG 2000         /* Taille maximale d'un programme */
InsMac Prog[MAXPROG];        /* La machine d'éxecution */
InsMac *ProgPtr;             /* Prochain emplacement libre */
InsMac *PC;                  /* Compteur d'éxecution */

InsMac *Code(f)              /* Installe une instruction machine */
	InsMac f;
{	InsMac *Localisation = ProgPtr;

	if (ProgPtr >= &Prog[MAXPROG])
		warning("Biggest program (code)", NULL);
	*ProgPtr++ = f;
	return Localisation;}

Execute(p)                   /* Execute le programme p */
	InsMac *p;
{
	for (PC = p; *PC != STOP; ) 
		(*(*PC++)) ();
}

#define MAXSTACK 256		/* Taille maximale de la Pile */
Data Stack[MAXSTACK];	/* La pile */
Data *StackPtr;		/* Prochain emplacement libre */

Push(d)				/* Stocke d au sommet de la pile */
	Data d;
{
	if (StackPtr >= &Stack[MAXSTACK])
		warning("Stack Overflow (push)", NULL);
	*StackPtr++ = d;
}

Data Pop()				/* Extrait le sommet de la pile */
{
	if (StackPtr <= Stack) 
		warning("Stack empty (pop)", NULL);
	return *--StackPtr;
}

VarPush()                    /* Range une variable */
{	Data d;
	d.symbol = ((Symbol *) *PC++);
	if (d.symbol->type != VAR && d.symbol->type != UNDEF) 
		warning("(VarPush) not a variable", d.symbol->name);
	Push(d);}

Eval()                       /* Evaluation */
{	Data d = Pop();
	if (d.symbol->type == UNDEF) 
		warning("(Eval) undefined variable", d.symbol->name);
	d.value = d.symbol->U.value;
	Push(d);}

Assign()                     /* Assignation */
{	Data d1 = Pop(), d2 = Pop();
	if (d1.symbol->type != VAR && d1.symbol->type != UNDEF) 
		warning("(Assign) can't assign", d1.symbol->name);
	d1.symbol->U.value = d2.value;
	d1.symbol->type    = VAR;}

NbrPush()                    /* Range un nombre */
{	Data d;
	d.value = ((Symbol *) *PC++)->U.value;
	Push(d);}

Add()                        /* Addition */
{	Data d2 = Pop(), d1 = Pop();
	d1.value = d1.value + d2.value;
	Push(d1);}

Sub()                        /* Soustraction */
{	Data d2 = Pop(), d1 = Pop();
	d1.value = d1.value - d2.value;
	Push(d1);}

Mul()                        /* Multiplication */
{	Data d2 = Pop(), d1 = Pop();
	d1.value = d1.value * d2.value;
	Push(d1);}

Power()                        /* Puissance */
{	Data d2 = Pop(), d1 = Pop();
	d1.value = pow(d1.value, d2.value);
	Push(d1);}

Div()                        /* Division */
{	Data d2 = Pop(), d1 = Pop();
	if (d2.value == 0.0)
		warning("(Div) division by zero", NULL);
	d1.value = d1.value / d2.value;
	Push(d1);}

Negate()                     /* Signe */
{	Data d = Pop();
	d.value = - d.value;
	Push(d);}

Predef()		/* Evalue une fonction prédéfinie */
{	Data d;

	d = Pop();
	d.value = (*(double (*)()) (*PC++)) (d.value);
	Push(d);
}

PrintExpr()			/* Affichage d'une expression */
{	Data d;

	d = Pop();
	printf("%.8g\n", d.value);
}

