#include "funkcijos.h"

int main()
{
    auto laikas = std::chrono::high_resolution_clock::now();
    system("type nul > " IRASAS " & type nul > kietiakai.txt & type nul > vargsiukai.txt");
    try
    {
        generavimas();
        cout << "Failu kurimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    }
    catch (const char* klaida)
    {
        cerr << klaida;
        return -1;
    }
    list<studentas> grupe;
    laikas = std::chrono::high_resolution_clock::now();
    ifstream duom(IRASAS);
    if (!duom)
    {
        cerr << "Nepavyko atidaryti failo " << IRASAS << '\n';
        return -1;
    }
    duom.seekg(studentas::zymeklis);
    for (long long int i = 0; i < STUD_SK; i++)
    {
        studentas A(duom);
        A.galutinio_skaic_vid();
        grupe.push_back(A);
        A.clear();
    }
    duom.close();
    duom.clear();
    cout << "Failu skaitymas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    list<studentas> vargsiukai;
    laikas = std::chrono::high_resolution_clock::now();
    for (std::list<studentas>::iterator it = grupe.begin(); it != grupe.end(); )
    {
        if ((*it).gaut_galut() < 5.0)
        {
            vargsiukai.push_back(*it);
            it = grupe.erase(it);
        }
        else { std::advance(it, 1); }
    }
    cout << "Studentu rusiavimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    laikas = std::chrono::high_resolution_clock::now();
    ofstream kiet("kietiakai.txt");
    if (!kiet)
    {
        cerr << "Nepavyko atidaryti failo kietiakai.txt\n";
        return -1;
    }
    kiet << "Pavarde      Vardas      Galutinis (vid.)\n";
    for (studentas stud : grupe)
    {
        kiet << stud.gaut_pavard_vard() << "      " << stud.gaut_galut() << '\n';
    }
    grupe.clear();
    kiet.close();
    kiet.clear();
    ofstream varg("vargsiukai.txt");
    if (!varg)
    {
        cerr << "Nepavyko atidaryti failo vargsiukai.txt\n";
        return -1;
    }
    varg << "Pavarde     Vardas      Galutinis (vid.)\n";
    for (studentas stud : vargsiukai)
    {
        varg << stud.gaut_pavard_vard() << "      " << stud.gaut_galut() << '\n';
    }
    cout << "Surusiuotu studentu isvedimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    vargsiukai.clear();
    varg.close();
    varg.clear();
    return 0;
}
