#include "Globals.h"

// aici declara si eventual initializeaza variabile globale 

std::vector<MatriceRezultat> rezultate;
Matrice A("A"), B("B");
Operatii _A(&A, &B);
Operatii _B(&B, &A);
Eroare eroare;