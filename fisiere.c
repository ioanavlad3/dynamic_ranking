#include "fisiere.h"

int putere_doi(int numar_echipe)
{
    int p = 1;
    while(p <= numar_echipe){
        p = p*2;
    }
    // p iese din while dublu
    p = p/2;
    return p;
}

void addAtBeginning(echipe** head, echipe* aux)
{
    aux->next = *head;
    *head = aux;
}

 void delete(echipe **head, int v)
 {
    // 0. Lista goala
    if (*head==NULL) return;
    // 1. Elementul de sters este capul listei
    echipe *headcopy = *head;
    if (headcopy->punctaj == v){
        *head = (*head)->next;
        free(headcopy); // sterge primul element
        return; 
    }
    // 2. Elementul de sters are o pozitie oarecare
    echipe *prev = *head; // predecesorul elementului cautat
    while (headcopy!=NULL){
        if(headcopy->punctaj != v){
            prev = headcopy;
            headcopy = headcopy->next;
        }else{
            prev->next = headcopy->next;
            free(headcopy); // sterge elementul
            return;
        }
    }
 }

void citire(FILE* fisier, int numar_echipe, echipe** vector_echipe)
{   
    for(int i = 0; i<numar_echipe; i++){
        echipe* echipe_aux = (echipe*)malloc(sizeof(echipe));
        if(echipe_aux == NULL){
            printf("alocare esuata\n");
            exit(1);
        }

        echipe_aux->nume_echipa = (char*)malloc(MAXIM * sizeof(char));
        fscanf(fisier, "%d", &echipe_aux->num_jucatori);
        fgetc(fisier); //goleste buffer ul
        fgets(echipe_aux->nume_echipa, MAXIM, fisier);
        fgetc(fisier);

        echipe_aux->nume_echipa[strlen(echipe_aux->nume_echipa) - 1] = '\0'; //sterg caracterul final de rand
        //verific daca ultimul caracter din nume este ' ' 
        if(echipe_aux->nume_echipa[strlen(echipe_aux->nume_echipa) - 2] == ' '){
            echipe_aux->nume_echipa[strlen(echipe_aux->nume_echipa) - 1] = '\0'; // daca este, atunci il sterg
        }
            
        echipe_aux->jucator = (player*)malloc(echipe_aux->num_jucatori * sizeof(player));

        //citesc jucatorii unei echipe
        for(int j = 0; j < echipe_aux->num_jucatori; j++){
            echipe_aux->jucator[j].firstName = (char*)malloc(MAXIM * sizeof(char));
            echipe_aux->jucator[j].secondName = (char*)malloc(MAXIM * sizeof(char));
            fscanf(fisier, "%s", echipe_aux->jucator[j].firstName);
            fscanf(fisier, "%s", echipe_aux->jucator[j].secondName);
            fscanf(fisier, "%d", &(echipe_aux->jucator[j].points));
            echipe_aux->punctaj += echipe_aux->jucator[j].points; // fac punctajul fiecarei echipe
        }
        fscanf(fisier, "\n"); //ignora linia dintre echipe
        echipe_aux->next = NULL;
        addAtBeginning(vector_echipe, echipe_aux);
    }
}

void task_2(echipe **head, int *numar_echipe)
{
    //memorez numarul nou de echipe ce trebuie obtinut
    int numar_nou = putere_doi(*numar_echipe);
    
    while(*numar_echipe != numar_nou){
        echipe* current = *head;
        int minim = current->punctaj;

        while(current != NULL){
            if(current->punctaj < minim)
              minim = current->punctaj;
            current = current->next;
        }
        delete(head, minim);    // sterg elementul cu valoarea minima
        (*numar_echipe)--;
    }
    
}
void enQueue ( coada *q, echipe *newNode){
    // nodurile noi se adauga la finalul cozii
    // daca nu exista niciun nod in coada
    if (q->right == NULL ) q->right = newNode ;
    else{
        (q->right )->next = newNode ;
        (q->right )= newNode ;
    }
    // daca exita un singur element in coada
    if (q->left == NULL ) q->left = q->right;
}

int isEmpty ( coada *q){
    return (q->left == NULL );
}

echipe* deQueue ( coada *q) { // elimin ultimul element din coada si il returnez
    if ( isEmpty (q)) return NULL ;

    echipe *temp = q->left;
    q->left =(q->left )->next ;
    if(q->left == NULL)
        q->right = NULL;
    temp->next = NULL;
    return temp; 
}

void deleteQueue(coada *q){
    echipe* aux;
    while (!isEmpty(q)){
        aux = q->right;
        q->right = q->right->next;
        free(aux);
    }
    free(q);
 }

void push (echipe **top , echipe *newNode){ //adauga element in stiva
    newNode->next = *top;
    *top = newNode ;
}

int isEmpty_stiva ( echipe *top ){ // 1 daca e empty
    return top == NULL ;
}

echipe* pop( echipe **top) {// returneaza informatia stocata in varf si sterge nodul
    if ( isEmpty_stiva ( *top )) return NULL;
    // stocheaza adresa varfului in temp
    echipe *temp = ( *top );
    // stocheaza valoarea din varf in aux
    echipe *aux = temp;
    // sterge elementul din varf
    *top =(* top)->next ;
    return aux ;
}

void deleteStack ( echipe **top ){
    echipe *temp ;
    while ((* top )!= NULL ){
        temp =* top;
        *top =(* top)->next ;
        free ( temp );
    }
}

void afisare_castigatori(FILE* g, int runda, echipe* s_castigat, coada** q){
    fprintf(g, "\nWINNERS OF ROUND NO:%d\n", runda);
    while( !isEmpty_stiva(s_castigat) ){
        echipe* current = pop(&s_castigat);
        for(int i = 0; i < (strlen(current->nume_echipa) - 1); i++){
            fprintf(g, "%c", current->nume_echipa[i]);
        }
        for(int i = (strlen(current->nume_echipa) - 1); i < 33; i++){
            fprintf(g, " ");
        }
        fprintf(g, " - ");
        fprintf(g, " %1.2f\n", current->punctaj);
        enQueue(*q, current);
    }
    deleteStack(&s_castigat);
}

void repetare_lista_echipe(FILE *g, echipe* s_castigat, echipe* s_pierdut, coada **q, int runda, int ok, echipe** ult8){
    fprintf(g, "\n--- ROUND NO:%d\n", runda); 
    while( !isEmpty(*q) ){
        echipe* e1 = deQueue(*q);
        echipe* e2 = deQueue(*q);
        afisare(g, e1, e2); 

        if(ok == 1){
            echipe* aux1 = (echipe*)malloc(sizeof(echipe));
            memcpy(aux1, e1, sizeof(echipe));
            aux1->next = NULL;
            addAtBeginning(ult8, aux1);

            echipe* aux2 = (echipe*)malloc(sizeof(echipe));
            memcpy(aux2, e2, sizeof(echipe));
            aux2->next = NULL;
            addAtBeginning(ult8, aux2);
        }

        if(e1->punctaj > e2->punctaj)
        {
            e1->punctaj = e1->punctaj + 1.0;
            push(&s_castigat, e1);
            push(&s_pierdut, e2);
        } else{
            e2->punctaj = e2->punctaj + 1.0;
            push(&s_castigat, e2);
            push(&s_pierdut, e1);
        }
    }
    deleteStack(&s_pierdut); 
    afisare_castigatori(g, runda, s_castigat, q);
}


void task3(FILE* g, echipe **head, int *numar_echipe, int task_4, int task_5)
{
    coada *q;
    q = ( coada *) malloc ( sizeof ( coada ));
    if (q == NULL ) {
        printf("alocare esuata");
        exit(1);
    }
    q->left = q->right = NULL;
    echipe* current = *head;
    //creez coada cu elementele din lista
    while (current != NULL) {
        current->punctaj = ((1.0* current->punctaj) / current->num_jucatori); 
        enQueue(q, current);
        current = current->next;
    } 
    echipe* s_castigat = NULL;
    echipe* s_pierdut = NULL;

    int runda = 1;
    // retin umarul nou de echipe
    int nr_echipe = putere_doi(*numar_echipe);
    
    echipe* ult8 = NULL; // lista cu ultimii 8 jucatori
    int ok;
    while (nr_echipe != 1){
        // daca au ramas 8 echipe atunci le retin 
        if(nr_echipe == 8)
            ok = 1;
        else ok = 0;
        // daca ok e 1 retin elemente in ult8
        repetare_lista_echipe(g, s_castigat, s_pierdut, &q, runda, ok, &ult8); 
        runda++;
        nr_echipe /=2;
    }
    
    if(task_4 == 1){
        task4(g, &ult8, task_5);
    }
        
}

void afisare(FILE* g, echipe* e1, echipe* e2){
    for(int i = 0; i < (strlen(e1->nume_echipa) - 1); i++){
        fprintf(g, "%c", e1->nume_echipa[i]);
    }
    for(int i = (strlen(e1->nume_echipa) - 1); i < 33; i++){
        fprintf(g, " ");
    }
    fprintf(g, "-");
    for(int i = 34; i < 68 - strlen(e2->nume_echipa); i++){
        fprintf(g, " ");
    }
    for(int i = 0; i < (strlen(e2->nume_echipa) - 1); i++){
        fprintf(g, "%c", e2->nume_echipa[i]);
    }
    fprintf(g, "\n");
}


void afisare_echipe(FILE* g, echipe** vector_echipe)
{
    echipe* curent = *vector_echipe;
    
    while (curent != NULL){
        fprintf(g, "%s\n", curent->nume_echipa);
        curent = curent->next;
    }
}

arbori* new_arb(echipe* element){
    arbori* nod = (arbori*) malloc (sizeof (arbori) );
    nod->val = element;
    nod->left = nod->right = NULL;
    return nod;
}

arbori *inserare_arbori(arbori *root, echipe* element){
    if(root == NULL)
        return new_arb(element);
    if(element->punctaj < root->val->punctaj)
        root->left = inserare_arbori(root->left, element);
    else if(element->punctaj > root->val->punctaj)
        root->right = inserare_arbori(root->right, element);
    else if(element->punctaj == root->val->punctaj){
        if(strcmp(root->val->nume_echipa, element->nume_echipa) > 0)
            root->left = inserare_arbori(root->left, element);
        else
            root->right = inserare_arbori(root->right, element);
    }
    return root;
}

void afisare_bst(FILE* g, arbori* root){
    // afisez elementele in ordine descrescatoare
    if(root){
        // merg cat mai in dreapta
        afisare_bst(g, root->right);
        for(int i = 0; i < (strlen(root->val->nume_echipa) - 1); i++){
            fprintf(g, "%c", root->val->nume_echipa[i]);
        }
        for(int i = 35; i > strlen(root->val->nume_echipa); i--)
            fprintf(g, " ");
        fprintf(g, "-  ");
        fprintf(g, "%1.2f\n", root->val->punctaj);
        // ma intorc in stanga 
        afisare_bst(g, root->left);
    }
}

void task4(FILE* g, echipe** ult8, int task_5){
    arbori* bst = NULL;
    echipe* curent = *ult8;
    while(curent != NULL){
        bst = inserare_arbori(bst, curent);
        curent = curent->next;
    }
    fprintf(g, "\nTOP 8 TEAMS:\n");
    afisare_bst(g, bst);
    
    if(task_5 == 1)
        task5(g, bst);
}

void bst_to_arr(arbori* root, echipe* vect, int* index)
{
    if (root == NULL) return;
    bst_to_arr(root->left, vect, index);
    vect[(*index)++] = *(root->val);
    bst_to_arr(root->right, vect, index);
}

void delete_arb(arbori* root)
{
    if(root != NULL)
    {
        delete_arb(root->left);
        delete_arb(root->right);
        free(root);
        root = NULL;
    }
}

arbori* create_avl(echipe* vect, int st, int dr)
{
    if(dr < st)
        return NULL;
    int mij = (st + dr) /2;
    arbori* root = new_arb(&vect[mij]);

    root->left = create_avl(vect, st, mij-1);
    root->right = create_avl(vect, mij+1, dr);
    

    return root;
}

void print_level_2(FILE* g, arbori* root){ 
    if(root != NULL){
        //daca nodul exista, merg in stanga lui si ii afisez copiii
        if(root->left != NULL){                
            if(root->right->left != NULL){
                for(int i = 0; i < (strlen(root->left->left->val->nume_echipa) - 1); i++){
                    fprintf(g, "%c", root->left->left->val->nume_echipa[i]);
                }
                fprintf(g, "\n");
            }

            if(root->left->right != NULL){
                for(int i = 0; i < (strlen(root->left->right->val->nume_echipa) - 1); i++){
                    fprintf(g, "%c", root->left->right->val->nume_echipa[i]);
                }
                fprintf(g, "\n");
            }
        }

        if(root->right != NULL){ 
            // daca nodul din dreapta exista, ii afisez copiii               
            if(root->right->left != NULL){
                for(int i = 0; i < (strlen(root->right->left->val->nume_echipa) - 1); i++){
                    fprintf(g, "%c", root->right->left->val->nume_echipa[i]);      
                }
                fprintf(g, "\n");
            }
            if(root->right->right != NULL){
                for(int i = 0; i < (strlen(root->right->right->val->nume_echipa) - 1); i++){
                    fprintf(g, "%c", root->right->right->val->nume_echipa[i]);
                }
                fprintf(g, "\n");
            } 
        }
    }

}

void task5(FILE* g, arbori* bst){
     // in vect am retinut elementele pe care le am scrise in bst
    echipe *vect = (echipe*)malloc(num_ult_echipe * sizeof(echipe));
    int num = 0;
    bst_to_arr(bst, vect, &num);

    // dau free la bst pentru ca nu mai am nevoie de el
    delete_arb(bst);

    //in vect_copie inversez elementele din vect pentru a fi mai usor la crearea avl-ului
    echipe *vect_copie = (echipe*)malloc(num_ult_echipe * sizeof(echipe));   
    for(int i = 0; i < 8; i++){
        vect_copie[i] = vect[7-i];
    }
    arbori* avl = create_avl(vect_copie, 0, 7);

    fprintf(g, "\nTHE LEVEL 2 TEAMS ARE:\n");
    print_level_2(g, avl);

    eliberare_memorie(&vect);
    eliberare_memorie(&vect_copie);
    delete_arb(avl);
}

void eliberare_memorie(echipe **head)
{
    echipe* current = *head;
    echipe* urm;

    while(current != NULL){
        urm = current->next;
        free(current);
        current = urm;
    }

    *head = NULL;  // in while nu apuc sa eliberez head-ul
}

void verificare_existenta_fisier(FILE* fisier){
    if(!fisier){
		printf("eroare\n");
		exit(1);
	}
}

void citire_vector_cerinte(FILE* f, int* vector){
    for(int i = 0; i < num_cerinte; i++)
	{
		fscanf(f, "%d", &vector[i]);
		fscanf(f, " ");
	}
}

void rezolvare_cerinte(FILE* g, int* vector_c, int numar_echipe, echipe* vector_echipe){
    int task_5 = vector_c[4];
	int task_4 = vector_c[3];

	if(vector_c[2] == 1){
		task_2(&vector_echipe, &numar_echipe);
		afisare_echipe(g, &vector_echipe);
		task3(g, &vector_echipe, &numar_echipe, task_4, task_5);  
	}
	else if(vector_c[1] == 1)
	{
		task_2(&vector_echipe, &numar_echipe);
		afisare_echipe(g, &vector_echipe);
	}
	else afisare_echipe(g, &vector_echipe);
}
