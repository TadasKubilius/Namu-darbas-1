#include "funkcijos.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <execution>
#include <string>
#include <vector>

uint8_t studentas::nd_skaicius = 0;
unsigned int studentas::zymeklis;

void generavimas()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> dist(1, 10);
	ofstream rez(IRASAS);
	if (!rez)
	{
		throw "Nepavyko atidaryti failo " IRASAS + '\n';
	}
	rez << "Pavarde     Vardas      ND1  ND2  ND3  ND4  ND5  Egzaminas\n";
	for (int i = 1; i <= STUD_SK; i++)
	{
		rez << "Vardas" << i << "     Pavarde" << i << "    " << dist(mt) << "    " << dist(mt) << "    " << dist(mt) << "    " << dist(mt) << "    " << dist(mt) << "    " << dist(mt) << '\n';
	}
	rez.close();
	char skait = '\0';
	ifstream duom(IRASAS);
	if (!duom)
	{
		throw "Nepavyko atidaryti failo " IRASAS + '\n';
	}
	while (true)
	{
		duom.get(skait);
		if (skait == 'N')
		{
			studentas::nd_skaicius++;
		}
		else if (skait == '\n')
		{
			studentas::zymeklis = duom.tellg();
			break;
		}
		
	}
	duom.close();
}
string gaut_ivesti(uint8_t tipas)
{
	string ivesties_buf;
	cin >> ivesties_buf;
	switch (tipas)
	{
		case CHAR_T_N:
		if (ivesties_buf.size() != 1)
		{
			throw "Netinkamas ivesties dydis. Bandykite dar karta\n";
		}
		if (ivesties_buf[0] != 't' && ivesties_buf[0] != 'T' && ivesties_buf[0] != 'n' && ivesties_buf[0] != 'N')
		{
			throw "Netinkamas simbolis. Bandykite dar karta\n";
		}
		break;
		case CHAR_SK:
		if (ivesties_buf.size() != 1)
		{
			throw "Netinkamas ivesties dydis. Bandykite dar karta\n";
		}
		if (ivesties_buf[0] != '1' && ivesties_buf[0] != '2' && ivesties_buf[0] != '3')
		{
			throw "Netinkamas simbolis. Bandykite dar karta\n";
		}
		break;
		case STRING:
		if (!(ivesties_buf[0] > 64 && ivesties_buf[0] < 91))
		{
			throw "Vardas ar pavarde turi buti rasomas is didziosios raides. Bandykite dar karta\n";
		}
		for (unsigned long long i = 1; i < ivesties_buf.size(); i++)
		{
			if (!(ivesties_buf[i] > 96 && ivesties_buf[i] < 123))
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
	if (ivesties_buf[0] == '1' && ivesties_buf[1] == '0')
	{
		return 10;
	}
	if (ivesties_buf[0] > 48 && ivesties_buf[0] < 58)
	{
		return ivesties_buf[0] - '0';
	}
	throw "Skaiciaus turi patekti i intervala 1 - 10. Bandykite dar karta\n";
}
studentas::studentas() 
{
	galutinis_vid = 0;
	galutinis_med = 0;
	atgal2:
	try
	{
		char uzklaus;
		cout << "Iveskite studento varda: ";
		vardas = gaut_ivesti(STRING);
		cout << "Iveskite studento pavarde: ";
		pavard = gaut_ivesti(STRING);
		cout << "Ar pazymius sugeneruot atsitiktinai? t/n";
		uzklaus = gaut_ivesti(CHAR_T_N)[0];
		if (uzklaus == 't' || uzklaus == 'T')
		{
			srand(time(NULL));
			for (int8_t i = 0; i < rand() % 10 + 1; i++) //pazymiu skaicius taip pat atsitiktinis (1 - 10)
			{
				nd.push_back(rand() % 10 + 1);
			}
			egz = rand() % 10 + 1;
			return;
		}
		uint8_t n;
		while (true)
		{
			cout << "Iveskite studento semestro pazymi: ";
			n = gaut_ivesti_int();
			nd.push_back(n);
			cout << "Ar norite ivesti dar viena pazymi? t/n";
			uzklaus = gaut_ivesti(CHAR_T_N)[0];
			if (uzklaus == 'n' || uzklaus == 'N') { break; }
		}
		cout << "Iveskite studento egzamino pazymi: ";
		egz = gaut_ivesti_int();
	}
	catch (const char* klaida)
	{
		cerr << klaida;
		goto atgal2;
	}
}
studentas::studentas(std::ifstream& duom)
{
	galutinis_vid = 0;
	galutinis_med = 0;
	egz = 0;
	char skait = '\0';
	bool laikas_rasyt_pavard = true, laikas_rasyt_vard = false;
	uint8_t sis_nd_skaic = 0;
	while (true)
	{
		duom.get(skait);
		if (laikas_rasyt_pavard)
		{
			if (skait == ' ')
			{
				laikas_rasyt_pavard = false;
				laikas_rasyt_vard = true;
				continue;
			}
			pavard += skait;
		}
		else if (laikas_rasyt_vard)
		{
			if (skait == ' ' && !vardas.empty())
			{
				laikas_rasyt_vard = false;
			}
			else if (skait != ' ')
			{
				vardas += skait;
			}
		}
		else if (skait == ' ')
		{
			continue;
		}
		else if (skait > '0' && skait <= '9' && skait != '1' && sis_nd_skaic != nd_skaicius)
		{
			nd.push_back(skait - '0');
			sis_nd_skaic++;
		}
		else if (skait == '1' && sis_nd_skaic != nd_skaicius)
		{
			duom.get(skait);
			if (skait == ' ')
			{
				nd.push_back(1);
			}
			else if (skait == '0')
			{
				nd.push_back(10);
			}
			sis_nd_skaic++;
		}
		else if (sis_nd_skaic == nd_skaicius)
		{
			if (skait > '0' && skait <= '9' && skait != '1')
			{
				egz = skait - '0';
				duom.seekg(2, std::ios_base::cur);
				break;
			}
			else if (skait == '1')
			{
				duom.get(skait);
				if (skait == '\n')
				{
					egz = 1;
				}
				else if (skait == '0')
				{
					egz = 10;
					duom.seekg(2, std::ios_base::cur);
				}
				break;
			}
		}
	}
}
studentas::studentas(const studentas& B)
{
	vardas = B.vardas;
	pavard = B.pavard;
	nd = B.nd;
	egz = B.egz;
	galutinis_vid = B.galutinis_vid;
	galutinis_med = B.galutinis_med;
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
}
void studentas::galutinio_skaic_vid()
{
	float vidurkis = 0;
	for (int8_t i : nd) { vidurkis += i; }
	vidurkis /= nd.size();
	galutinis_vid = 0.4 * vidurkis + 0.6 * egz;
}
void studentas::galutinio_skaic_med()
{
	float mediana;
	if (nd.size() != 1 && nd.size() != 2)
	{
		std::sort(std::execution::unseq, nd.begin(), nd.end());
		if (nd.size() % 2 != 0) { mediana = nd.at((nd.size() - 1) / 2.0f); }
		else { mediana = (nd.at(nd.size() / 2 - 1) + nd.at(nd.size() / 2)) / 2.0f; }
	}
	else
	{
		mediana = (nd.front() + nd.back()) / 2.0f;
	}
	galutinis_med = 0.4 * mediana + 0.6 * egz;
}
float studentas::gaut_galut()
{
	return galutinis_vid;
}
string studentas::gaut_pavard_vard()
{
	return pavard + "      " + vardas;
}
void studentas::isvestis()
{
	cout << left << setw(20) << pavard << left << setw(42) << vardas << left << setw(20) << fixed << setprecision(2) << galutinis_vid << fixed << setprecision(2) << galutinis_med << '\n';
}
