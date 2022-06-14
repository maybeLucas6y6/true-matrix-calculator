#include "Globals.h"

// aici declara si eventual initializeaza variabile globale 

std::vector<MatriceRezultat> rezultate;
Matrice A("A", "Matrice A"), B("B", "Matrice B");
Operatii _A(&A, &B, "Operatii A");
Operatii _B(&B, &A, "Operatii B");
Eroare eroare;