#include <ctype.h> // tolower()
#include <conio.h> //getch()
#include <stdio.h>
#include <stdlib.h> //srand(), rand()
#include <string.h> //strcmp(), strchr()
#include <time.h> //time()

void clearScreen();
int checkRepetition(int *array, int num, int tam);
int checkLetter(char *word, char *hits,  char letter);
void initializeMistakes(char s[], int tam);
void fillMistakes(char *mistakes, int *mistakesCount, char letter);
void printMistakes(char *s, int cont);
void printHang(int cont);
void initializeString(char hits[], int tam);
void printWord(char hits[], int tam);

int main(){

    char *word[] = {"motorista", "cachorro", "individuo", "mercado", "liberalismo",
    "liberdade", "prateleira", "computador", "investigador", "utopia"};
    char *clues[] = {"Profissao", "Animal", "Um unico ser", "Local de comercio", "Doutrina economica",
    "Direito fundamental", "Objeto", "Maquina", "Profissao", "Estado ou lugar imaginario e ideial"};
    char hits[50], mistakes[6], letter;
    int repeated[10], turnsCount = 0, mistakesCount, contained;

    srand(time(NULL));

    do {

        int i;// garante que uma palavra diferente aparecerá a cada volta

        do{ // verifica se o número gerado é repetido, ou seja, a palavra corresponde já apareceu
            i = rand() % 10;
        } while(checkRepetition(repeated, i, turnsCount));

        repeated[turnsCount] = i;

        initializeString(hits, strlen(word[i])); // preenche-a com sublinhas
        initializeMistakes(mistakes, 6); // preenche-a com espaços
        mistakesCount = 0; // inicializa os contadores com 0

        do
        {
            clearScreen();// limpa o terminal

            printf("\n\t\tJOGO DA FORCA\n");
            printMistakes(mistakes, mistakesCount);
            printf("\t PISTA: %s\n", clues[i]);
            printHang(mistakesCount);
            printWord(hits, strlen(word[i]));

            do{ //lê e verifica se o carácter digitado é uma letra
                letter = getch();
                letter = tolower(letter);
            } while (letter < 'a' || letter > 'z');


            /*verifica se a letra digitada está contida na palavra ou se já foi digitada
            anteriormente*/
            contained = checkLetter(word[i], hits,  letter);
            if (contained == 0)
                fillMistakes(mistakes, &mistakesCount, letter);

        }while (mistakesCount < 6 && strcmp(word[i], hits) != 0);

        clearScreen();
        printf("\n\t\tJOGO DA FORCA\n");
        printMistakes(mistakes, mistakesCount);
        printf("\t PISTA: %s\n", clues[i]);
        printHang(mistakesCount);
        printWord(hits, strlen(word[i]));

        if (strcmp(word[i], hits) == 0)// verifica se elas são iguais
            printf("\n\tGanhaste!\n");
        else
            printf("\n\tPerdeste.\n");

        turnsCount++;// incrementa o contador

        getchar();

    } while (turnsCount < 10);
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int checkRepetition(int *array, int num, int tam){
    int i;
    for (i = 0; i < tam; i++)
        if (num == array[i])
            return 1;

    return 0;
}

int checkLetter(char *word, char *hits,  char letter){
    int length, i, contained = 0;

    for (i = 0, length = strlen(word); i < length; i++)
        if (letter == word[i]){
            contained = 1; //a letra está contida na palavra
            hits[i] = letter;// salva a letra na cadeia de caracteres exibida na tela
        }
    return contained;
}

void fillMistakes(char *mistakes, int *mistakesCount, char letter){
    /*a letra não está contida e ainda não foi digitada*/
    if (strchr(mistakes, letter) == NULL){
        mistakes[*mistakesCount] = letter; // salva a letra na string de erros
        ++(*mistakesCount);
    }
}

void initializeMistakes(char s[], int tam){
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

void initializeString(char hits[], int tam){
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
