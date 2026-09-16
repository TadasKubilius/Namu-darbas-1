#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdint.h> //int8_t - 1 baito sveikasis sk. vietoj 4 (naudojau tik vietose, kur neieina i std::cin)

using std::cout;
using std::wcout; //naudojamas su stdint bibliotekos sinonimais kaip int8_t
using std::cin;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

class studentas
{
    string vardas, pavard;
    vector <int8_t> nd;
    int egz;
    float galutinis;

    public:
    studentas() //numatytasis konstruktorius
    {
        ivestis();
    }
    studentas(string vardas, string pavard, vector<int8_t> nd, int8_t egz)
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
    void galutinio_skaic()
    {
        float vidurkis = 0;
        for (int8_t i : nd){ vidurkis += i; }
        vidurkis /= nd.size();
        galutinis = 0.4 * vidurkis + 0.6 * egz;
    }
    void ivestis()
    {
        cout << "Iveskite studento varda: ";
        cin >> vardas;
        cout << "Iveskite studento pavarde: ";
        cin >> pavard;
        int n;
        char uzklaus;
        while(true)
        {
            cout << "Iveskite studento semestro pazimi: ";
            cin >> n;
            nd.push_back(n);
            cout << "Ar norite ivesti dar viena pazimi? t/n";
            cin >> uzklaus;
            if(uzklaus == 'n' || uzklaus == 'N'){ break; }
        }
        cout << "Iveskite studento egzamino pazimi: ";
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
    while(true)
    {
        studentas A;
        A.galutinio_skaic();
        grupe.push_back(A);
        A.clear();
        cout << "Ar norite ivesti dar viena studenta? t/n ";
        cin >> uzklaus;
        if(uzklaus == 'n' || uzklaus == 'N'){ break; }
    }
    cout << left << setw(20) << "Pavarde" << left << setw(30) << "Vardas" << "Galutinis (Vid.)\n"
        << "--------------------------------------------------------------------\n";
    for(studentas stud : grupe){ stud.isvestis(); }
    return 0;
}
