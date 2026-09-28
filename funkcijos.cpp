#include "funkcijos.h"

uint8_t studentas::nd_skaicus = 0;
unsigned int studentas::zymeklis;
bool studentas::ar_skaityt_faila = false;

string gaut_ivesti(uint8_t tipas)
{
    string ivesties_buf;
    cin >> ivesties_buf;
	switch(tipas)
	{
		case CHAR:
		if(ivesties_buf.size() != 1)
    	{
        	throw "Netinkamas ivesties dydis. Bandykite dar karta\n";
    	}
    	if(ivesties_buf[0] != 't' && ivesties_buf[0] != 'T' && ivesties_buf[0] != 'n' && ivesties_buf[0] != 'N')
    	{
        	throw "Netinkamas simbolis. Bandykite dar karta\n";
    	}
		break;
		case STRING:
		if(!(ivesties_buf[0] > 64 && ivesties_buf[0] < 91))
		{
			throw "Vardas ar pavarde turi buti rasomas is didziosios raides. Bandykite dar karta\n";
		}
		for(unsigned long long i = 1; i < ivesties_buf.size(); i++)
		{
			if(!(ivesties_buf[i] > 96 && ivesties_buf[i] < 123))
			{
				throw "Vardas ar pavarde turi buti rasoma mazosiomis raidemis (isskyrus pirmaja). Bandykite dar karta\n";
			}
		}
		break;
	}
	return ivesties_buf;
}
uint8_t gaut_ivesti_int()
{
	string ivesties_buf;
	cin >> ivesties_buf;
	if(ivesties_buf[0] == '1' && ivesties_buf[1] == '0')
	{
		return 10;
	}
	if(ivesties_buf[0] > 48 && ivesties_buf[0] < 58)
	{
		return ivesties_buf[0] - '0';
	}
	throw "Skaiciaus turi patekti i intervala 1 - 10. Bandykite dar karta\n";
}
studentas::studentas()
{
    ivestis();
}
studentas::studentas(string vardas, string pavard, deque<int8_t> nd, uint8_t egz)
{
	this->vardas = vardas;
	this->pavard = pavard;
	this->nd = nd;
	this->egz = egz;
}
studentas::studentas(const studentas &B)
{
	vardas = B.vardas;
	pavard = B.pavard;
	nd = B.nd;
	egz = B.egz;
	galutinis_vid = B.galutinis_vid;
	galutinis_med = B.galutinis_med;
	pavard_vard_dyd = B.pavard_vard_dyd;
}
studentas::~studentas()
{
	clear();
}
void studentas::clear()
{
	vardas.clear();
	pavard.clear();
	nd.clear();
	egz = 0;
}
string studentas::gaut_pavard()
{
	string pavard_vardas = vardas;
	pavard_vardas.at(0) += 32;
	pavard_vardas.insert(0, pavard);
	return pavard_vardas;
}
void studentas::galutinio_skaic_vid()
{
	float vidurkis = 0;
	for (int8_t i : nd) {
		vidurkis += i;
	}
	vidurkis /= nd.size();
	galutinis_vid = 0.4 * vidurkis + 0.6 * egz;
}
void studentas::galutinio_skaic_med()
{
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
	galutinis_med = 0.4 * mediana + 0.6 * egz;
}
void studentas::ivestis()
{
	if(ar_skaityt_faila)
	{
		char skait1 = '\0', skait2 = '\0';
		bool laikas_rasyt_pavard = true, laikas_rasyt_vard = false;
		uint8_t sis_nd_skaic = 0;
		std::ifstream duom("kursiokai.txt");
		if(!duom)
		{
			throw "Nepavyko atidaryti failo kursiokai.txt\n";
		}
		duom.seekg(zymeklis);
		while(true)
		{
			duom.get(skait1);
			if(laikas_rasyt_pavard && skait1 != '\n')
			{
				if(skait1 == ' ')
				{
					laikas_rasyt_pavard = false;
					laikas_rasyt_vard = true;
					continue;
				}
				pavard += skait1;
			}
			else if(laikas_rasyt_vard)
			{
				if(skait1 == ' ' && !vardas.empty())
				{
					laikas_rasyt_vard = false;
					continue;
				}
				else if(skait1 != ' ')
				{
					vardas += skait1;
				}
			}
			if(skait1 > '0' && skait1 <= '9' && skait1 != '1' && sis_nd_skaic != nd_skaicus)
			{
				nd.push_back(skait1 - '0');
				sis_nd_skaic++;
			}
			else if(skait1 == '1' && sis_nd_skaic != nd_skaicus)
			{
				duom.get(skait1);
				if(skait1 == ' ')
				{
					nd.push_back(1);
				}
				else if(skait1 == '0')
				{
					nd.push_back(10);
				}
				skait2 = '1';
				sis_nd_skaic++;
			}
			else if(sis_nd_skaic == nd_skaicus)
			{
				if(skait1 > '0' && skait1 <= '9' && skait1 != '1')
				{
					egz = skait1 - '0';
					duom.get(skait1);
					break;
				}
				else if(skait1 == '1')
				{
					duom.get(skait1);
					if(skait1 == '\n')
					{
						egz = 1;
					}
					else if(skait1 == '0')
					{
						egz = 10;
						duom.get(skait1);
					}
					break;
				}
			}
			skait2 = skait1;
		}
		zymeklis = duom.tellg();
		pavard_vard_dyd = pavard.size() + vardas.size();
		duom.close();
	}
	else
	{
		atgal2:
		try
		{
			char uzklaus;
			cout << "Iveskite studento varda: ";
			vardas = gaut_ivesti(STRING);
			cout << "Iveskite studento pavarde: ";
			pavard = gaut_ivesti(STRING);
			pavard_vard_dyd = pavard.size() + vardas.size();
			cout << "Ar pazymius sugeneruot atsitiktinai? t/n";
			uzklaus = gaut_ivesti(CHAR)[0];
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
			uint8_t n;
			while(true)
			{
				cout << "Iveskite studento semestro pazymi: ";
				n = gaut_ivesti_int();
				nd.push_back(n);
				cout << "Ar norite ivesti dar viena pazymi? t/n";
				uzklaus = gaut_ivesti(CHAR)[0];
				if(uzklaus == 'n' || uzklaus == 'N') { break; }
			}
			cout << "Iveskite studento egzamino pazymi: ";
			egz = gaut_ivesti_int();
		}
		catch(const char* klaida)
		{
			cerr << klaida;
			goto atgal2;
		}
	}
}
void studentas::isvestis()
{
	cout << left << setw(20) << pavard << left << setw(42) << vardas << left << setw(20) << fixed << setprecision(2) << galutinis_vid << fixed << setprecision(2) << galutinis_med << '\n';
}
//Testavimui
	/*for(int8_t u : nd)//
	{
		cout << (int)u << " ";
	}
	cout << (int)egz << '\n';*/
