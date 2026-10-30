#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#define CHAR_T_N 0
#define CHAR_SK 1
#define STRING 2
#define IRASAS "pirmas_irasas.txt"
#define STUD_SK 1000
//pirmas_irasas.txt, antras_irasas.txt, trecias_irasas.txt, ketvirtas_irasas.txt, penktas_irasas.txt
//1000,             10'000,             100'000,            1'000'000,          10'000'000

using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

int pirma_dalis(char);
int antra_dalis();
void generavimas();
string gaut_ivesti(uint8_t);
uint8_t gaut_ivesti_int();

class studentas
{
    string vardas, pavard;
    vector<int8_t> nd;
    uint8_t egz;
    float galutinis_vid, galutinis_med;

public:
    static uint8_t nd_skaicius;
    static unsigned int zymeklis;
    studentas();
    studentas(ifstream&);
    studentas(const studentas&);
    ~studentas();
    void clear();
    float gaut_galut();
    string gaut_pavard_vard();
    void galutinio_skaic_vid();
    void galutinio_skaic_med();
    void isvestis();
};

bool lyginimas(studentas, studentas);
