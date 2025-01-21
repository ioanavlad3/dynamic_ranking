#include "fisiere.h"

int main(int argc, char* argv[]){
	
	char *fisier_intrare = strdup(argv[1]);
	FILE *f1 = fopen(fisier_intrare, "rt"); // f1 este pointer pt a deschide fisierul c.in
	free(fisier_intrare);
	verificare_existenta_fisier(f1);
	
	int *vector_c = (int*)malloc(num_cerinte * sizeof(int)); // vector pt a memora cerintele din c.in
	citire_vector_cerinte(f1, vector_c);

	char *fisier_date = strdup(argv[2]);
	FILE *f2 = fopen(fisier_date, "rt"); // f2 deschide d.in
	verificare_existenta_fisier(f2);

	int numar_echipe;
	fscanf(f2, "%d", &numar_echipe);
	echipe* vector_echipe = NULL; // vector_echipe este head ul

	citire(f2, numar_echipe, &vector_echipe);

	//fisier destinatie
	char *fisier_destinatie = (char*) malloc(20 * sizeof(char));
	strcpy(fisier_destinatie, argv[3]);

	FILE *g = fopen(fisier_destinatie, "wt"); //g deschide c.out
	verificare_existenta_fisier(g);

	rezolvare_cerinte(g, vector_c, numar_echipe, vector_echipe);

	// eliberare memorie
	free(fisier_date);
	free(fisier_destinatie);
	free(vector_c);
	
	return 0;
}