#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define MAXIM 100
#define INT_MIN -214748
#define num_ult_echipe 8
#define num_cerinte 5
struct Player
{
    char* firstName;
    char* secondName;
    int points;
};
typedef struct Player player;

struct Echipe
{
    int num_jucatori;
    float punctaj;
    char* nume_echipa;
    player* jucator;
    struct Echipe* next;
};
typedef struct Echipe echipe;

struct Q
{
    echipe *right, *left;
};
typedef struct Q coada;

struct arb{
    echipe* val;
    struct arb *right, *left;
};
typedef struct arb arbori;

void citire(FILE* fisier, int numar_echipe, echipe** vector_echipe);

void afisare(FILE* g, echipe* e1, echipe* e2);

void afisare_echipe(FILE* g, echipe** vector_echipe);

int putere_doi(int numar_echipe);

void delete(echipe **head, int v);

void task_2(echipe **head, int *numar_echipe);

void eliberare_memorie(echipe **head);

int isEmpty ( coada *q);

echipe* deQueue ( coada *q);

void task3(FILE *g, echipe **head, int *numar_echipe, int task_4, int task_5);

void push (echipe **top , echipe *newNode);

void repetare_lista_echipe(FILE*f, echipe* s_castigat, echipe* s_pierdut, coada **q, int runda, int ok, echipe** ult8);

void task4(FILE* g, echipe** ult8, int task_5);

arbori *inserare_arbori(arbori *root, echipe* element);

void afisare_bst(FILE* g, arbori* root);

arbori* new_arb(echipe* element);

void bst_to_arr(arbori* root, echipe* vect, int* index);

void task5(FILE* g, arbori* bst);

void deleteQueue(coada *q);

void delete_arb(arbori* root);

arbori* create_avl(echipe* vect, int st, int dr);

void print_level_2(FILE* g, arbori* root);

void afisare_castigatori(FILE* g, int runda, echipe* s_castigat, coada** q);

void verificare_existenta_fisier(FILE* fisier);

void citire_vector_cerinte(FILE* f, int* vector);

void rezolvare_cerinte(FILE* g, int* vector_c, int numar_echipe, echipe* vector_echipe);