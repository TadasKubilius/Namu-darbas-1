#include "funkcijos.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>

bool lyginimas(studentas stud1, studentas stud2)
{
    uint8_t lygis = 0;
    while (lygis != (stud1.gaut_pavard_vard().size() - 1) && lygis != (stud2.gaut_pavard_vard().size() - 1))
    {
        if (stud1.gaut_pavard_vard()[lygis] == stud2.gaut_pavard_vard()[lygis]) { lygis++; }
        else { return stud1.gaut_pavard_vard()[lygis] < stud2.gaut_pavard_vard()[lygis]; }
    }
    return false;
}

int pirma_dalis(char uzklaus)
{
    vector<studentas> grupe;
    if (uzklaus == '1')
    {
        std::ifstream duom("kursiokai.txt");
        if (!duom)
        {
            cerr << "Nepavyko atidaryti failo kursiokai.txt\n";
            system("PAUSE");
            return -1;
        }
        char skait = '\0';
        bool pirm_eil_galas = false;
        long long int stud_skaicius = 0;
        while (duom.get(skait))
        {
            if (skait == '\n' && !pirm_eil_galas)
            {
                studentas::zymeklis = duom.tellg();
                pirm_eil_galas = true;
            }
            else if (skait == '\n')
            {
                stud_skaicius++;
            }
            else if (skait == 'N' && !pirm_eil_galas)
            {
                studentas::nd_skaicius++;
            }
        }
        duom.clear();
        duom.seekg(studentas::zymeklis);
        for (long long i = 0; i < stud_skaicius; i++)
        {
            try
            {
                studentas A(duom);
                A.galutinio_skaic_vid();
                A.galutinio_skaic_med();
                grupe.push_back(A);
                A.clear();
            }
            catch (const char* klaida)
            {
                cerr << klaida;
                system("PAUSE");
                return -1;
            }
        }
        duom.close();
    }
    else
    {
        while (true)
        {
            try
            {
                studentas A;
                A.galutinio_skaic_vid();
                A.galutinio_skaic_med();
                grupe.push_back(A);
                A.clear();
            }
            catch (const char* klaida)
            {
                cerr << klaida;
                system("PAUSE");
                return -1;
            }
            atgal1:
            cout << "Ar norite irasyti dar viena studenta? t/n";
            try { uzklaus = gaut_ivesti(CHAR_T_N)[0]; }
            catch (const char* klaida)
            {
                cerr << klaida;
                goto atgal1;
            }
            if (uzklaus == 'n' || uzklaus == 'N')
            {
                break;
            }
        }
    }
    std::sort(grupe.begin(), grupe.end(), lyginimas);
    cout << left << setw(20) << "Pavarde" << left << setw(30) << "Vardas" << left << setw(20) << "Galutinis (Vid.) " << "Galutinis (Med.)\n"
        << "----------------------------------------------------------------------------------------\n";
    for (studentas stud : grupe) { stud.isvestis(); }
    system("PAUSE");
    return 0;
}

int antra_dalis()
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
        system("PAUSE");
        return -1;
    }
    laikas = std::chrono::high_resolution_clock::now();
    ifstream duom(IRASAS);
    if (!duom)
    {
        cerr << "Nepavyko atidaryti failo " << IRASAS << '\n';
        system("PAUSE");
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
    cout << "Failu skaitymas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    laikas = std::chrono::high_resolution_clock::now();
    vector<studentas>::iterator it_riba = std::stable_partition(grupe.begin(), grupe.end(), [](studentas stud) { return stud.gaut_galut() >= 5.0; });
    cout << "Studentu rusiavimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    laikas = std::chrono::high_resolution_clock::now();
    ofstream kiet("kietiakai.txt");
    if (!kiet)
    {
        cerr << "Nepavyko atidaryti failo kietiakai.txt\n";
        system("PAUSE");
        return -1;
    }
    kiet << "Pavarde      Vardas      Galutinis (vid.)\n";
    for (vector<studentas>::iterator it = grupe.begin(); it != it_riba; it++)
    {
        kiet << (*it).gaut_pavard_vard() << "      " << (*it).gaut_galut() << '\n';
    }
    kiet.close();
    ofstream varg("vargsiukai.txt");
    if (!varg)
    {
        cerr << "Nepavyko atidaryti failo vargsiukai.txt\n";
        system("PAUSE");
        return -1;
    }
    varg << "Pavarde     Vardas      Galutinis (vid.)\n";
    for (vector<studentas>::iterator it = it_riba; it != grupe.end(); it++)
    {
        varg << (*it).gaut_pavard_vard() << "      " << (*it).gaut_galut() << '\n';
    }
    cout << "Surusiuotu studentu isvedimas: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - laikas).count() << " milisekundziu\n";
    varg.close();
    system("PAUSE");
    return 0;
}
