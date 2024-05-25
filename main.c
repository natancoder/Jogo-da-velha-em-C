/*Uma implementação do jogo da forca

        feito por Natan Frota

          em março de 2024.
*/

#include <conio.h> //getch()
#include <stdio.h>
#include <stdlib.h> //srand(), rand()
#include <string.h> //strcmp()
#include <time.h> //time()

void clearScreen();
int checkRepetition(int *vetor, int num, int tam);
void checkLetter(char *word, char *hits,  char letter, char *mistakes, int *cont_mistakes);
void fillMistakes(char s[], int tam);
void printMistakes(char *s, int cont);
void printHang(int cont);
void fillString(char hits[], int tam);
void printWord(char hits[], int tam);

int main(){

    char *word[] = {"motorista", "cachorro", "individuo", "mercado", "liberalismo",
    "liberdade", "prateleira", "computador", "investigador", "utopia"};
    char *clues[] = {"Profissao", "Animal", "Um unico ser", "Local de comercio", "Doutrina economica",
    "Direito fundamental", "Objeto", "Maquina", "Profissao", "Estado ou lugar imaginario e ideial"};
    char hits[50], mistakes[6], letter;
    int cont_mistakes;
    int repetidos[10], cont_voltas = 0;

    srand(time(NULL));

    char ch;

    do {

        int i;// garante que uma palavra diferente aparecerá a cada volta

        do{ // verifica se o número gerado é repetido, ou seja, a palavra corresponde já apareceu
            i = rand() % 10;
        } while(checkRepetition(repetidos, i, cont_voltas));

        repetidos[cont_voltas] = i;

        fillString(hits, strlen(word[i])); // preenche-a com sublinhas
        fillMistakes(mistakes, 6); // preenche-a com espaços
        cont_mistakes = 0; // inicializa os contadores com 0

        do
        {
            clearScreen();// limpa o terminal

            printf("\n\t\tJOGO DA FORCA\n");
            printMistakes(mistakes, cont_mistakes);
            printf("\t PISTA: %s\n", clues[i]);
            printHang(cont_mistakes);
            printWord(hits, strlen(word[i]));

            do{ //lê e verifica se o carácter digitado é uma letra
                letter = getch();
            } while (letter < 'a' || letter > 'z');


            /*verifica se a letra digitada está contida na palavra ou se já foi digitada
            anteriormente e incrementa o contador de erros*/
            checkLetter(word[i], hits,  letter, mistakes, &cont_mistakes);

        }while (cont_mistakes < 6 && strcmp(word[i], hits) != 0);

        clearScreen();
        printf("\n\t\tJOGO DA FORCA\n");
        printMistakes(mistakes, cont_mistakes);
        printf("\t PISTA: %s\n", clues[i]);
        printHang(cont_mistakes);
        printWord(hits, strlen(word[i]));

        if (strcmp(word[i], hits) == 0)// verifica se elas são iguais
            printf("\n\tYou won!\n");
        else
            printf("\n\tYou lost.\n");

        cont_voltas++;// incrementa o contador

        printf("\n\tDo you want to play again(y/n)?\n\t");
        ch = getchar();
        getchar();

    } while (ch == 'y');
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int checkRepetition(int *vetor, int num, int tam){
    int i;
    for (i = 0; i < tam; i++)
        if (num == vetor[i])
            return 1;

    return 0;
}

void checkLetter(char *word, char *hits,  char letter, char *mistakes, int *cont_mistakes){
    int length, i, contido = 0;

    for (i = 0, length = strlen(word); i < length; i++)
        if (letter == word[i]){
            contido = 1; //a letra está contida na palavra
            hits[i] = letter;// salva a letra na cadeia de caracteres exibida na tela
        }
    /*a letra não está contida e ainda não foi digitada*/
    if (contido == 0 && strchr(mistakes, letter) == NULL){
        mistakes[*cont_mistakes] = letter; // salva a letra na string de erros
        ++(*cont_mistakes);
    }
}

void fillMistakes(char s[], int tam){
    int i;
    for (i = 0; i < tam; i++)
        s[i] = ' ';
}

void printMistakes(char *s, int cont){
    int i;
    printf("\n\t ERROS: ");
    for (i = 0; i < cont; i++)
        printf("%c ", s[i]);
    printf("\n");
}

void printHang(int cont){
    printf("\t   ______\n");
    printf("\t  |      |\n");
    if (cont >= 1)
        printf("\t  |      O\n");
    else
        printf("\t  |\n");
    if (cont == 2)
    {
        printf("\t  |      |\n");
        printf("\t  |      |\n");
    }
    else if (cont == 3){
        printf("\t  |      |/\n");
        printf("\t  |      |\n");
    }

    else if (cont >= 4)
    {
        printf("\t  |     \\|/\n");
        printf("\t  |      |\n");
    }
    else{
        printf("\t  |\n");
        printf("\t  |\n");
    }

    if (cont == 5)
        printf("\t  |     / \n");
    else if (cont == 6)
        printf("\t  |     / \\\n");
    else
        printf("\t  |\n");
    printf("\t__|__\n");
}

void fillString(char hits[], int tam){
    int i;

    for (i = 0; i < tam; i++)
        hits[i] = '_';

    hits[i] = '\0';
}

void printWord(char hits[], int tam){
    int i;
    printf("\n\t");
    for (i = 0; i < tam; i++)
        printf("%c ", hits[i]);

    printf("\n\n\t");
}
