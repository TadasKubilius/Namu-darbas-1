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
    deque<studentas> grupe;
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
    cout << "Failu skaitymas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    deque<studentas> kietiakai;
    deque<studentas> vargsiukai;
    laikas = std::chrono::high_resolution_clock::now();
    for (studentas stud : grupe)
    { 
        if (stud.gaut_galut() >= 5.0)
        {
            kietiakai.push_back(stud);
        }
        else
        {
            vargsiukai.push_back(stud);
        }
    }
    cout << "Studentu rusiavimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    grupe.clear();
    laikas = std::chrono::high_resolution_clock::now();
    ofstream kiet("kietiakai.txt");
    if (!kiet)
    {
        cerr << "Nepavyko atidaryti failo kietiakai.txt\n";
        return -1;
    }
    kiet << "Pavarde      Vardas      Galutinis (vid.)\n";
    for (studentas stud : kietiakai)
    {
        kiet << stud.gaut_pavard_vard() << "      " << stud.gaut_galut() << '\n';
    }
    kietiakai.clear();
    kiet.close();
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
    return 0;
}
