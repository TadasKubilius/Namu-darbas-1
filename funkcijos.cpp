#include "funkcijos.h"

uint8_t studentas::nd_skaicus;
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
		if (skait == '\n')
		{
			studentas::zymeklis = duom.tellg();
			break;
		}
		else if (skait == 'N')
		{
			studentas::nd_skaicus++;
		}
	}
	duom.close();
}
studentas::studentas() {}
studentas::studentas(const studentas& B)
{
	vardas = B.vardas;
	pavard = B.pavard;
	nd = B.nd;
	egz = B.egz;
	galutinis_vid = B.galutinis_vid;
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
studentas::studentas(std::ifstream& duom)
{
	char skait1 = '\0';
	bool laikas_rasyt_pavard = true, laikas_rasyt_vard = false;
	uint8_t sis_nd_skaic = 0;
	while (true)
	{
		duom.get(skait1);
		if (laikas_rasyt_pavard && skait1 != '\n')
		{
			if (skait1 == ' ')
			{
				laikas_rasyt_pavard = false;
				laikas_rasyt_vard = true;
				continue;
			}
			pavard += skait1;
		}
		else if (laikas_rasyt_vard)
		{
			if (skait1 == ' ' && !vardas.empty())
			{
				laikas_rasyt_vard = false;
				continue;
			}
			else if (skait1 != ' ')
			{
				vardas += skait1;
			}
		}
		if (skait1 > '0' && skait1 <= '9' && skait1 != '1' && sis_nd_skaic != nd_skaicus && !laikas_rasyt_pavard && !laikas_rasyt_vard)
		{
			nd.push_back(skait1 - '0');
			sis_nd_skaic++;
		}
		else if (skait1 == '1' && sis_nd_skaic != nd_skaicus && !laikas_rasyt_pavard && !laikas_rasyt_vard)
		{
			duom.get(skait1);
			if (skait1 == ' ')
			{
				nd.push_back(1);
			}
			else if (skait1 == '0')
			{
				nd.push_back(10);
			}
			sis_nd_skaic++;
		}
		else if (sis_nd_skaic == nd_skaicus)
		{
			if (skait1 > '0' && skait1 <= '9' && skait1 != '1')
			{
				egz = skait1 - '0';
				duom.get(skait1);
				break;
			}
			else if (skait1 == '1')
			{
				duom.get(skait1);
				if (skait1 == '\n')
				{
					egz = 1;
				}
				else if (skait1 == '0')
				{
					egz = 10;
					duom.get(skait1);
				}
				break;
			}
		}
	}
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
float studentas::gaut_galut()
{
	return galutinis_vid;
}
string studentas::gaut_pavard_vard()
{
	return pavard + "      " + vardas;
}
