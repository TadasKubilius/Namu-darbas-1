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
    laikas = std::chrono::high_resolution_clock::now();
    ifstream duom(IRASAS);
    if (!duom)
    {
        cerr << "Nepavyko atidaryti failo " << IRASAS << '\n';
        return -1;
    }
    duom.seekg(studentas::zymeklis);
    vector<studentas> grupe;
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
    laikas = std::chrono::high_resolution_clock::now();
    vector<studentas>::iterator it_riba = std::stable_partition(grupe.begin(), grupe.end(), [](studentas stud) { return stud.gaut_galut() >= 5.0; });
    cout << "Studentu rusiavimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    laikas = std::chrono::high_resolution_clock::now();
    ofstream kiet("kietiakai.txt");
    if (!kiet)
    {
        cerr << "Nepavyko atidaryti failo kietiakai.txt\n";
        return -1;
    }
    kiet << "Pavarde      Vardas      Galutinis (vid.)\n";
    for (vector<studentas>::iterator it = grupe.begin(); it != it_riba ; it++)
    {
        kiet << (*it).gaut_pavard_vard() << "      " << (*it).gaut_galut() << '\n';
    }
    kiet.close();
    kiet.clear();
    ofstream varg("vargsiukai.txt");
    if (!varg)
    {
        cerr << "Nepavyko atidaryti failo vargsiukai.txt\n";
        return -1;
    }
    varg << "Pavarde     Vardas      Galutinis (vid.)\n";
    for (vector<studentas>::iterator it = it_riba; it != grupe.end(); it++)
    {
        varg << (*it).gaut_pavard_vard() << "      " << (*it).gaut_galut() << '\n';
    }
    cout << "Surusiuotu studentu isvedimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    varg.close();
    varg.clear();
    return 0;
}
