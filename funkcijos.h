#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <stdint.h>
#include <chrono>
#define IRASAS "penktas_irasas.txt"
#define STUD_SK 10'000'000
//pirmas_irasas.txt, antras_irasas.txt, trecias_irasas.txt, ketvirtas_irasas.txt, penktas_irasas.txt
//1000,             10'000,             100'000,            1'000'000,          10'000'000

using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::ifstream;
using std::ofstream;

void generavimas();

class studentas
{
    string vardas, pavard;
    vector <int8_t> nd;
    uint8_t egz;
    float galutinis_vid;

public:
    static uint8_t nd_skaicus;
    static unsigned int zymeklis;
    studentas();
    studentas(ifstream&);
    studentas(const studentas&);
    ~studentas();
    void clear();
    float gaut_galut();
    string gaut_pavard_vard();
    void galutinio_skaic_vid();
};
