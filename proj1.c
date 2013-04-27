/*
 * Soubor:  proj1.c
 * Datum:   07.10.2012 17:39
 * Autor:   Luk� Vokr��ko, xvokra00@stud.fit.vutbr.cz
 * Projekt: 1IZP
 * Popis:   v�pis �etnosti znak�
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

//�ten� znak� na vstupu a ukl�d�n� jejich po�tu do pole na pozici sv�ho ascii k�du
void readInput(unsigned char *p)
{
    //deklarace prom�nn�, kter� bude obsahovat ascii k�d
    int c;
    //�ten� vstupu
    while((c = getchar()) != EOF && c >= 0 && c <= 255)
    {
        //inkrementace v�skytu znaku
        if(p[c] < UCHAR_MAX)
        {
            ++p[c];
        }
    }
}

//tisk spr�vn� form�tovan�ho znaku
void printChar(unsigned char x, unsigned char count)
{
	//m� se tisknout
	if(count > 0 && count < UCHAR_MAX)
	{
		//je tisknuteln�
		if(isprint(x))
		{
			printf("%d '%c': %d\n",x,x,count);
		}
		//nen�
		else
		{
			printf("%d: %d\n",x,count);
		}
	}
	//maxim�ln� hodnota
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

//v�pis v�ech znak�, kter� se vyskytly alespo� jednou, se�azeno podle ordin�ln�ch hodnot
void printChars(unsigned char *p)
{
    //proch�zen� cel�ho pole
    for(int i = 0;i <= 255;i++)
    {
		  printChar(i,p[i]);
    }
}

//v�pis @limit ��sel s nejv�t�� �etnost�
void printMax(unsigned char *p, int limit)
{
    //proch�zen� cel�ho pole
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

//vrac� true pokud je ��slo, jinak else
bool isNumber(int c)
{
	return (bool) (c >= 0 && c <= 9);
}

//�ten� ��seln�ho parametru
int readNum(char *p)
{
    int val, num = 0, i = 0;

	  //p�i�azen� prvn�ho znaku
	  val = p[i]-'0';
		//dokud je znak ��slo
		while(p[i] != '\0' && isNumber(val))
		{
		  //pokud p�ekro�� hranici vr�t� neplatnou hodnotu
		  if(num < 0 || num > UCHAR_MAX+1) return 0;
			//vypo��tej hodnotu
			num = num*10+val;
			val = p[++i]-'0';
		}
    return num;
}

void printHelp(void)
{
    printf(
        "PROGRAM\n  proj1\n"
        "AUTOR\n    Luk� Vokr��ko\n"
        "POPIS\n   Program vyp�e po�et v�skyt� v�ech znak� z ASCII tabulky\n"
        "   se�azen�ch podle ordin�ln�ch hodnot\n"
        "POU�IT�\n  proj1 [-h|--help|N]\n"
        "PARAMETRY:\n"
        "   -h, --help - vyp�e n�pov�du\n"
        "    N - vyp�e N nej�ast�j��ch znak� se�azen�ch podle �etnosti,\n       N m��e nab�vat hodnot od 1 do 256\n"
        "P��KLAD POU�IT�\n   proj1 10 < textfile\n"
        "   V�p�e 10 znak� nej�ast�ji se vyskytuj�c�ch v souboru textfile\n"
    );
}

int main(int agrc, char *agrv[])
{
    //definice pole a ukazatele na n�j
    unsigned char arr[UCHAR_MAX+1] = {0};
    unsigned char *parr = arr;

    //pokud je program spu�t�n bez parametr�
    if(agrc == 1)
    {
        //�ten� stdin
        readInput(parr);
        //v�pis �etnost znak�
        printChars(parr);
    }
    //pokud je program spu�t�n s jedn�m parametrem
    else if(agrc == 2)
    {
        //pokus o p�e�ten� ��sla
        int num = readNum(agrv[1]);

        //je ��slo
        if(num > 0)
        {
            readInput(parr);
            printMax(parr,num);
        }
        //nen� ��slo, je parametr -h nebo --help?
        else if((strcmp(agrv[1],"-h") == 0) || (strcmp(agrv[1],"--help") ==0))
        {
            //tisk n�pov�dy
            printHelp();
        }
        //nen� ��slo, -h ani --help
        else
        {
            fprintf(stderr, "Chybn� zadan� parametr\n");
            //ukon�en� programu chybou
            return EXIT_FAILURE;
        }
    }
    //v�ce parametr� ne� jeden nen� povoleno
    else
    {
        fprintf(stderr,"Je povolen pouze jeden parametr\n");
        //ukon�en� programu chybou
        return EXIT_FAILURE;
    }
    //ukon�en� programu
    return EXIT_SUCCESS;
}
