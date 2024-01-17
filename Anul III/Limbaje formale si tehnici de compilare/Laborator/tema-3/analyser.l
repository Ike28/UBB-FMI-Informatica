%{
    #include <stdlib.h>
    #include <string.h>

    typedef struct {
        char atom[100];
        int codAtom;
        int codAtomTS;
    }FIP;

    typedef struct {
        char atom[100];
        int codAtomTS;
    }TS;

    int lenFIP = 0, lenTS = 0, codTS = 0;
    FIP fip[300];
    TS ts[300];
    int currentLine = 1;

    void addToFIP(char atom[], int codAtom, int codAtomTS) {
        lenFIP++;
        strcpy(fip[lenFIP - 1].atom, atom);
        fip[lenFIP - 1].codAtom = codAtom;
        fip[lenFIP - 1].codAtomTS = codAtomTS;
    }

    int addToTS(char atom[]) {
        int i, j;
        for (i = 0; i < lenTS; i++) {
            if (strcmp(ts[i].atom, atom) == 0) {
                return ts[i].codAtomTS;
            }
        }
        if ((lenTS == 0) || (strcmp(ts[lenTS - 1].atom, atom) < 0)) {
            strcpy(ts[lenTS].atom, atom);
            ts[lenTS].codAtomTS = codTS;
            codTS++; lenTS++;
        }
        else if (strcmp(ts[0].atom, atom) > 0) {
            lenTS++;
            for (i = lenTS; i > 0; i--)
                ts[i] = ts[i - 1];
            strcpy(ts[0].atom, atom);
            ts[0].codAtomTS = codTS;
            codTS++;
        }
        else {
            i = 0;
            while (strcmp(ts[i].atom, atom) < 0)
                i++;
            lenTS++;
            for (j = lenTS; j > i; j--)
                ts[j] = ts[j - 1];
            strcpy(ts[i].atom, atom);
            ts[i].codAtomTS = codTS;
            codTS++;
        }
        return codTS - 1;
    }

    void printTS() {
        printf("TS:\n");
        int i;
        for (i = 0; i < lenTS; i++)
            printf("%s  |  %d\n", ts[i].atom, ts[i].codAtomTS);
        printf("\n");
    }

    void printFIP() {
        printf("FIP:\n");
        int i;
        for (i = 0; i < lenFIP; i++)
            if (fip[i].codAtomTS == -1)
                printf("%s  |  %d  |  -\n", fip[i].atom, fip[i].codAtom);
            else
                printf("%s  |  %d  |  %d\n", fip[i].atom, fip[i].codAtom, fip[i].codAtomTS);
    }
%}

%option noyywrap

DIGIT 		[0-9]
LETTER 		[a-z]
KEYWORD		DIM|CONST|AS|INTEGER|STRING|BOOLEAN|DOUBLE|LONG|PAIR|STR|IF|THEN|"END IF"|END|FOR|TO|NEXT|PRINT|INPUT|GOTO|TYPE|"END TYPE"|SWAP|WHILE|WEND
OPERATOR	"+"|"-"|"*"|"/"|"^"|"="|"<>"|"MOD"|"AND"|"OR"|"XOR"|"NOT"|"$"|"&"|"+="|"-="|"*="|"/="|"^="|"=&"|"<"|">"|"<="|">="
SEPARATOR	"("|")"|";"|":"|","|"'"
STRING      \"([^\"\\\n]|\\.)*\"

%%

{STRING} {
    int codTS = addToTS(yytext);
	addToFIP(yytext, 1, codTS);
}

{KEYWORD} {
	int codAtom = -1;
	if (strcmp("DIM", yytext) == 0) codAtom = 2;
	if (strcmp("CONST", yytext) == 0) codAtom = 3;
	if (strcmp("AS", yytext) == 0) codAtom = 4;
	if (strcmp("INTEGER", yytext) == 0) codAtom = 5;
	if (strcmp("STRING", yytext) == 0) codAtom = 6;
	if (strcmp("BOOLEAN", yytext) == 0) codAtom = 7;
	if (strcmp("DOUBLE", yytext) == 0) codAtom = 8;
	if (strcmp("LONG", yytext) == 0) codAtom = 9;
	if (strcmp("PAIR", yytext) == 0) codAtom = 10;
	if (strcmp("STR", yytext) == 0) codAtom = 11;
	if (strcmp("IF", yytext) == 0) codAtom = 12;
	if (strcmp("THEN", yytext) == 0) codAtom = 13;
	if (strcmp("END IF", yytext) == 0) codAtom = 14;
	if (strcmp("END", yytext) == 0) codAtom = 15;
	if (strcmp("FOR", yytext) == 0) codAtom = 16;
	if (strcmp("TO", yytext) == 0) codAtom = 17;
	if (strcmp("NEXT", yytext) == 0) codAtom = 18;
	if (strcmp("PRINT", yytext) == 0) codAtom = 19;
	if (strcmp("INPUT", yytext) == 0) codAtom = 20;
	if (strcmp("GOTO", yytext) == 0) codAtom = 21;
	if (strcmp("TYPE", yytext) == 0) codAtom = 22;
	if (strcmp("END TYPE", yytext) == 0) codAtom = 23;
	if (strcmp("SWAP", yytext) == 0) codAtom = 24;
	if (strcmp("WHILE", yytext) == 0) codAtom = 25;
	if (strcmp("WEND", yytext) == 0) codAtom = 26;
	addToFIP(yytext, codAtom, -1);
}

{LETTER}+ {
	if (strlen(yytext) > 8) {
        printf("Error on line %d. Identifier '%s' exceeds the maximum length of 8 characters.\n", currentLine, yytext);
    } else {
        int codTS = addToTS(yytext);
        addToFIP(yytext, 0, codTS);
    }
}

{DIGIT}+ {
	int codTS = addToTS(yytext);
	addToFIP(yytext, 1, codTS);
}

{DIGIT}"."{DIGIT}{DIGIT}* {
	int codTS = addToTS(yytext);
	addToFIP(yytext, 1, codTS);
}

{OPERATOR} {
	int codAtom = -1;
	if (strcmp("+", yytext) == 0) codAtom = 27;
	if (strcmp("-", yytext) == 0) codAtom = 28;
	if (strcmp("*", yytext) == 0) codAtom = 29;
	if (strcmp("/", yytext) == 0) codAtom = 30;
	if (strcmp("^", yytext) == 0) codAtom = 31;
	if (strcmp("=", yytext) == 0) codAtom = 32;
	if (strcmp("<>", yytext) == 0) codAtom = 33;
	if (strcmp("MOD", yytext) == 0) codAtom = 34;
	if (strcmp("AND", yytext) == 0) codAtom = 35;
	if (strcmp("OR", yytext) == 0) codAtom = 36;
	if (strcmp("XOR", yytext) == 0) codAtom = 37;
	if (strcmp("NOT", yytext) == 0) codAtom = 38;
	if (strcmp("$", yytext) == 0) codAtom = 39;
	if (strcmp("&", yytext) == 0) codAtom = 40;
	if (strcmp("+=", yytext) == 0) codAtom = 41;
	if (strcmp("-=", yytext) == 0) codAtom = 42;
	if (strcmp("*=", yytext) == 0) codAtom = 43;
	if (strcmp("/=", yytext) == 0) codAtom = 44;
	if (strcmp("^=", yytext) == 0) codAtom = 45;
	if (strcmp("=&", yytext) == 0) codAtom = 46;
	if (strcmp("<", yytext) == 0) codAtom = 47;
	if (strcmp(">", yytext) == 0) codAtom = 48;
	if (strcmp("<=", yytext) == 0) codAtom = 49;
	if (strcmp(">=", yytext) == 0) codAtom = 50;
	addToFIP(yytext, codAtom, -1);
}

{SEPARATOR} {
	int codAtom = -1;
	if (strcmp("(", yytext) == 0) codAtom = 51;
	if (strcmp(")", yytext) == 0) codAtom = 52;
	if (strcmp(";", yytext) == 0) codAtom = 53;
	if (strcmp(":", yytext) == 0) codAtom = 54;
	if (strcmp(",", yytext) == 0) codAtom = 55;
	if (strcmp("'", yytext) == 0) codAtom = 56;
	addToFIP(yytext, codAtom, -1);
}

[\n] {
	currentLine++;
}

[ \t\n]+ ;

. {
	printf("Error on line %d. Unrecognized character: %s\n", currentLine, yytext);
}


%%
int main(argc, argv)
int argc;
char **argv;
{
	++argv, --argc;
	if (argc > 0)
		yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
	yylex();
	printTS();
	printFIP();
}