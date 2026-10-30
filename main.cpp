#include "funkcijos.h"
#include <iostream>

int main()
{
    char uzklaus;
    cout << "1 - skaityti duomenis is failo kursiokai.txt\n2 - kurti atsitiktinius duomenis is pasirinkto IRASO\n3 - rasyti duomenis\n";
    try { uzklaus = gaut_ivesti(CHAR_SK)[0]; }
    catch(const char* klaida)
    {
        cerr << klaida;
        return -1;
    }
    switch (uzklaus)
    {
        case '1': return pirma_dalis(uzklaus); break;
        case '2': return antra_dalis(); break;
        case '3': return pirma_dalis(uzklaus); break;
    }
}
