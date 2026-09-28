#include "funkcijos.h"

int main()
{
    char uzklaus;
    atgal:
    cout << "Ar norite nuskaityti duomenis iš failo kursiokai.txt? t/n";
    try{ uzklaus = gaut_ivesti(CHAR)[0]; } //raktazodis throw yra funkcijos viduje
    catch(const char* klaida)
    {
        cerr << klaida;
        goto atgal;
    }
    int8_t stud_skaicius = 1;
    if(uzklaus == 't' || uzklaus == 'T')
    {
        stud_skaicius = 0;
        studentas::ar_skaityt_faila = true;
        char skait = '\0';
        bool pirm_eil_galas = false;
        std::ifstream duom("kursiokai.txt");
        if(!duom)
        {
            cerr << "Nepavyko atidaryti failo kursiokai.txt\n";
            return -1;
        }
        while(duom.get(skait)) //Suskaiciuoja studentus ir perkelia failo skaitymo zymekli per viena eilute
        {
            if(skait == '\n' && !pirm_eil_galas)
            {
                studentas::zymeklis = duom.tellg();
            }
            if(skait == '\n')
            { 
                pirm_eil_galas = true;
                stud_skaicius++;
            }
            else if(skait == 'N' && !pirm_eil_galas)
            {
                studentas::nd_skaicus++;
            }
        }
        duom.close();
    }
    vector<studentas> grupe;
    for(uint8_t i = 0; i < stud_skaicius; i++)
    {
        try 
        { 
            studentas A;
            A.galutinio_skaic_vid();
            A.galutinio_skaic_med();
            grupe.push_back(A);
            A.clear();
        }
        catch(const char* klaida)
        {
            cerr << klaida;
            return -1;
        }
        if(!studentas::ar_skaityt_faila)
        {
            atgal1:
            cout << "Ar norite irasyti dar viena studenta? t/n";
            try{ uzklaus = gaut_ivesti(CHAR)[0]; }
            catch(const char* klaida)
            {
                cerr << klaida;
                goto atgal1;
            }
            if(uzklaus == 'n' || uzklaus == 'N')
            {
                break;
            }
            stud_skaicius++;
        }
    }
    uint8_t did_pavard = 0;
    for(studentas stud : grupe) //Isrenka dydziausia pavardes ir vardo jungini
    { 
        if(stud.pavard_vard_dyd > did_pavard)
        {
            did_pavard = stud.pavard_vard_dyd;
        }
    }
    //Surikiuoja studentus pagal ju pavardziu ir vardu junginius abeceles tvarka
    vector<studentas> baigta_grupe;
    uint8_t string_lyg = 0, index, stud_skaicius_static = stud_skaicius;
    string did(did_pavard, 123);
    string atnaujint(did_pavard, 123);
    std::size_t maz_dyd = 0;
    for(unsigned int I = 0; I < stud_skaicius_static; I++)
    {
        for(unsigned int i = 0; i < stud_skaicius; i++)
        {
            if(grupe.at(i).gaut_pavard()[string_lyg] < did[string_lyg])
            {
                did = grupe.at(i).gaut_pavard();
                index = i;
                string_lyg = 0;
            }
            else if(grupe.at(i).gaut_pavard()[string_lyg] == did[string_lyg] && string_lyg <= maz_dyd)
            {
                if(string_lyg == 0)
                {
                    grupe.at(i).gaut_pavard().size() > did.size() ? 
                    maz_dyd = did.size() : maz_dyd = grupe.at(i).gaut_pavard().size();
                }
                string_lyg++;
                i--;
            }
            else{ string_lyg = 0; }
        }
        baigta_grupe.push_back(grupe.at(index));
        grupe.erase(grupe.begin() + index);
        stud_skaicius--;
        did = atnaujint;
    }

    cout << left << setw(20) << "Pavarde" << left << setw(30) << "Vardas" << left << setw(20) << "Galutinis (Vid.) " << "Galutinis (Med.)\n"
        << "----------------------------------------------------------------------------------------\n";
    for(studentas stud : baigta_grupe){ stud.isvestis(); }
    return 0;
}
