# Studentų Skaičiuoklė
Konsolės programa, kuri apskaičiuoja studentų galutinio įverčio reikšmę pagal pažymius bei egzamino įvertį, remdamasi šia formule:
`galutinis = 0.4 * (vidurkis arba mediana) + 0.6 * egzaminas`.

# Atsisiuntimas
Atsisiųskite programos instaliuotoją „releases“ sekcijoje.

# Rezultatai
2 strategijai itin efektyvus buvo <strong>sąrašo</strong> konteineris, kadangi, priešingai nei <strong>vektoriaus</strong> konteineris, jis nėra dinaminėje atmintyje saugomas viename bloke, o atskirais mazgais. Tad, kaskart išėmus elementą iš konteinerio vidurio, pats konteineris nebuvo vis iš naujo perrikiuojamas tam, kad būtų išlaikomas konteinerio vientisumas.

Studentų rūšiavimą galima optimizuoti tiek atminties, tiek greičio prasme, naudojant `std::stable_partition` funkciją, tokiu būdu duomenys yra paskirstomi į dvi dalis viename konteineryje.

Detalūs užduoties rezultatai yra pateikti rezultatai.txt faile.

