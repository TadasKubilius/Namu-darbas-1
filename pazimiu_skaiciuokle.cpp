#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <deque>
#include <stdio.h>
#include <stdint.h> //int8_t

using std::cout;
using std::wcout; //naudojamas su stdint bibliotekos sinonimais kaip int8_t
using std::cin;
using std::string;
using std::vector;
using std::deque;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

class studentas
{
    string vardas, pavard;
    deque <int8_t> nd; //deque tam, kad butu galima lengvai apskaiciuoti mediana
    int egz; //vietoj 4 baitų naudojamas 1
    float galutinis;

    public:
    studentas() //numatytasis konstruktorius
    {
        ivestis();
    }
    studentas(string vardas, string pavard, deque<int8_t> nd, int8_t egz)
    {
        this->vardas = vardas;
        this->pavard = pavard;
        this->nd = nd;
        this->egz = egz;
    }

    studentas(const studentas &B)
    {
        vardas = B.vardas;
        pavard = B.pavard;
        nd = B.nd;
        egz = B.egz;
        galutinis = B.galutinis;
    }
    ~studentas()
    {
        clear();
    }
    void clear()
    {
        vardas.clear();
        pavard.clear();
        nd.clear();
        egz = 0;
    }
    void galutinio_skaic_vidurkis()
    {
        float vidurkis = 0;
        for (int8_t i : nd){ vidurkis += i; }
        vidurkis /= nd.size();
        galutinis = 0.4 * vidurkis + 0.6 * egz;
        /*for(int8_t u : nd) gautu pazimiu spausdinimui
        {
            wcout << u << " ";
        }
        wcout << egz;
        cout << '\n';*/
    }
    void galutinio_skaic_mediana()
    {
        //strategija: pazymiai, atrinkti i didejimo seka, yra paverciami nuliais o jų kopijos yra nukeliamos i deko gala (back).
        //Visi nuliai patenka deko pradzioje, kur jie yra isvalomi (pop_front())
        float mediana;
        if(nd.size() != 1 && nd.size() != 2)
        {
            int8_t mazas = 10, index;
            std::size_t dydis = nd.size();
            for(int8_t I = 0; I < dydis; I++)
            {
                for(int8_t i = 0; i < dydis; i++)
                {
                    if(nd.at(i) <= mazas && nd.at(i) != 0)
                    {
                        mazas = nd.at(i);
                        index = i;
                    }
                }
                nd.push_back(mazas);
                nd.at(index) = 0;
                mazas = 10;
            }
            while(nd.front() == 0)
            {
                nd.pop_front();
            }
            /*for(int8_t u : nd) gautu pazimiu didejimo tvarka spausdinimui
            {
                wcout << u << " ";
            }
            wcout << egz;
            cout << '\n';*/
            while(true)
            {
                nd.pop_front();
                nd.pop_back();
                if(nd.size() == 2)
                {
                    mediana = (nd.front() + nd.back()) / (float)2;
                    break;
                }
                else if(nd.size() == 1)
                {
                    mediana = nd.front();
                    break;
                }
            }
        }
        else
        {
            mediana = (nd.front() + nd.back()) / (float)2;
        }
        galutinis = 0.4 * mediana + 0.6 * egz;
    }
    void ivestis()
    {
        int n;
        char uzklaus;
        cout << "Iveskite studento varda: ";
        cin >> vardas;
        cout << "Iveskite studento pavarde: ";
        cin >> pavard;
        cout << "Ar pazymius sugeneruot atsitiktinai? t/n";
        cin >> uzklaus;
        if(uzklaus == 't' || uzklaus == 'T')
        {
            srand(time(NULL));
            for(int8_t i = 0; i < rand() % 10 + 1; i++) //pazymiu skaicius taip pat atsitiktinis (1 - 10)
            {
                nd.push_back(rand() % 10 + 1);
            }
            egz = rand() % 10 + 1;
            return;
        }
        while(true)
        {
            cout << "Iveskite studento semestro pazymi: ";
            cin >> n;
            nd.push_back(n);
            cout << "Ar norite ivesti dar viena pazymi? t/n";
            cin >> uzklaus;
            if(uzklaus == 'n' || uzklaus == 'N'){ break; }
        }
        cout << "Iveskite studento egzamino pazymi: ";
        cin >> egz;
    }
    void isvestis()
    {
        cout << left << setw(20) << pavard << left << setw(30) << vardas << left << setw(30) << fixed << setprecision(2) << galutinis << '\n';
    }
};

int main()
{
    vector <studentas> grupe;
    char uzklaus;
    string galutinio_budas;
    cout << "Ar galutinius pazymius apskaiciuoti mediana? t/n";
    cin >> uzklaus;
    if(uzklaus == 'n' || uzklaus == 'N'){ galutinio_budas = "(Vid.)"; }
    else if(uzklaus == 't' || uzklaus == 'T'){ galutinio_budas = "(Med.)"; }
    while(true)
    {
        studentas A;
        if(galutinio_budas == "(Vid.)"){ A.galutinio_skaic_vidurkis(); }
        else{ A.galutinio_skaic_mediana(); }
        
        grupe.push_back(A);
        A.clear();
        cout << "Ar norite ivesti dar viena studenta? t/n ";
        cin >> uzklaus;
        if(uzklaus == 'n' || uzklaus == 'N'){ break; }
    }
    cout << left << setw(20) << "Pavarde" << left << setw(30) << "Vardas" << "Galutinis " << galutinio_budas << '\n'
        << "--------------------------------------------------------------------\n";
    for(studentas stud : grupe){ stud.isvestis(); }
    return 0;
}
