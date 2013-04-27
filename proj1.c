/*
 * Soubor:  proj1.c
 * Datum:   07.10.2012 17:39
 * Autor:   Luká¹ Vokráèko, xvokra00@stud.fit.vutbr.cz
 * Projekt: 1IZP
 * Popis:   výpis èetnosti znakù
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

//ètení znakù na vstupu a ukládání jejich poètu do pole na pozici svého ascii kódu
void readInput(unsigned char *p)
{
    //deklarace promìnné, která bude obsahovat ascii kód
    int c;
    //ètení vstupu
    while((c = getchar()) != EOF && c >= 0 && c <= 255)
    {
        //inkrementace výskytu znaku
        if(p[c] < UCHAR_MAX)
        {
            ++p[c];
        }
    }
}

//tisk správnì formátovaného znaku
void printChar(unsigned char x, unsigned char count)
{
	//má se tisknout
	if(count > 0 && count < UCHAR_MAX)
	{
		//je tisknutelný
		if(isprint(x))
		{
			printf("%d '%c': %d\n",x,x,count);
		}
		//není
		else
		{
			printf("%d: %d\n",x,count);
		}
	}
	//maximální hodnota
	else if(count == UCHAR_MAX)
	{
		if(isprint(x))
		{
			printf("%d '%c': NNN\n",x,x);
		}
		else
		{
			printf("%d: NNN\n",x);
		}
	}
}

//výpis v¹ech znakù, které se vyskytly alespoò jednou, seøazeno podle ordinálních hodnot
void printChars(unsigned char *p)
{
    //procházení celého pole
    for(int i = 0;i <= 255;i++)
    {
		  printChar(i,p[i]);
    }
}

//výpis @limit èísel s nejvìt¹í èetností
void printMax(unsigned char *p, int limit)
{
    //procházení celého pole
    int max_val = 0;
    int max_i = 0;

    for(int j = 0;j<=limit-1;j++)
    {
        for(int i = 0;i <= UCHAR_MAX;i++)
        {
            if(p[i] > max_val)
            {
                max_val =  p[i];
                max_i = i;
            }
        }

		  printChar(max_i,p[max_i]);
		  max_val = 0;
      p[max_i] = 0;
    }
}

//vrací true pokud je èíslo, jinak else
bool isNumber(int c)
{
	return (bool) (c >= 0 && c <= 9);
}

//ètení èíselného parametru
int readNum(char *p)
{
    int val, num = 0, i = 0;

	  //pøiøazení prvního znaku
	  val = p[i]-'0';
		//dokud je znak èíslo
		while(p[i] != '\0' && isNumber(val))
		{
		  //pokud pøekroèí hranici vrátí neplatnou hodnotu
		  if(num < 0 || num > UCHAR_MAX+1) return 0;
			//vypoèítej hodnotu
			num = num*10+val;
			val = p[++i]-'0';
		}
    return num;
}

void printHelp(void)
{
    printf(
        "PROGRAM\n  proj1\n"
        "AUTOR\n    Luká¹ Vokráèko\n"
        "POPIS\n   Program vypí¹e poèet výskytù v¹ech znakù z ASCII tabulky\n"
        "   seøazených podle ordinální­ch hodnot\n"
        "POU®ITÍ\n  proj1 [-h|--help|N]\n"
        "PARAMETRY:\n"
        "   -h, --help - vypí¹e nápovìdu\n"
        "    N - vypí¹e N nejèastìj¹ích znakù seøazených podle èetnosti,\n       N mù¾e nabývat hodnot od 1 do 256\n"
        "PØÍKLAD POU®ITÍ\n   proj1 10 < textfile\n"
        "   Výpí¹e 10 znakù nejèastìji se vyskytujících v souboru textfile\n"
    );
}

int main(int agrc, char *agrv[])
{
    //definice pole a ukazatele na nìj
    unsigned char arr[UCHAR_MAX+1] = {0};
    unsigned char *parr = arr;

    //pokud je program spu¹tìn bez parametrù
    if(agrc == 1)
    {
        //ètení stdin
        readInput(parr);
        //výpis èetnost znakù
        printChars(parr);
    }
    //pokud je program spu¹tìn s jedním parametrem
    else if(agrc == 2)
    {
        //pokus o pøeètení èísla
        int num = readNum(agrv[1]);

        //je èíslo
        if(num > 0)
        {
            readInput(parr);
            printMax(parr,num);
        }
        //není èíslo, je parametr -h nebo --help?
        else if((strcmp(agrv[1],"-h") == 0) || (strcmp(agrv[1],"--help") ==0))
        {
            //tisk nápovìdy
            printHelp();
        }
        //není èíslo, -h ani --help
        else
        {
            fprintf(stderr, "Chybnì zadaný parametr\n");
            //ukonèení programu chybou
            return EXIT_FAILURE;
        }
    }
    //více parametrù ne¾ jeden není povoleno
    else
    {
        fprintf(stderr,"Je povolen pouze jeden parametr\n");
        //ukonèení programu chybou
        return EXIT_FAILURE;
    }
    //ukonèení programu
    return EXIT_SUCCESS;
}
