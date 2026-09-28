#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H
#define CHAR 0
#define STRING 1
//pragma once alternatyva
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <deque>
#include <stdio.h>
#include <stdint.h> //naudojami mazesnio dydzio (1 baito) sveikieji sk. atminties taupymui

using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::vector;
using std::deque;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

string gaut_ivesti(uint8_t);
uint8_t gaut_ivesti_int(uint8_t);

class studentas
{
    string vardas, pavard;
    deque <int8_t> nd;
    uint8_t egz;
    float galutinis_vid, galutinis_med;

    public:
    static uint8_t nd_skaicus;
    static unsigned int zymeklis;
    static bool ar_skaityt_faila;
    uint8_t pavard_vard_dyd;
    studentas();
    studentas(string, string, deque<int8_t>, uint8_t);
    studentas(const studentas&);
    ~studentas();
    void clear();
    string gaut_pavard();
    void galutinio_skaic_vid();
    void galutinio_skaic_med();
    void ivestis();
    void isvestis();
};
#endif
