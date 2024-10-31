# Blockchain

## Realizuota blokų grandinė:

block.cpp, block.h - apibrėžia Block klasę, kuri naudojama blokų struktūrai blokų grandinėje. Šiuose failuose bus apibrėžta, kaip blokas atrodo, kokie jo laukai yra naudojami, kaip atliekamas maišos skaičiavimas

blockchain.cpp, blockchain.h - apibrėžia Blockchain klasę, kuri yra atsakinga už blokų grandinės kūrimą, valdymą ir transakcijų įtraukimą į blokus. Šiuose failuose pateikiama blokų grandinės struktūra bei funkcijos, reikalingos blokų kūrimui ir jų pridėjimui į blokų grandinę.

hash_function.cpp, hash_functions.h - apibrėžia ir įgyvendina maišos funkciją, kuri yra naudojama blokų ir transakcijų maišos reikšmėms apskaičiuoti blokų grandinės projekte. Ši maišos funkcija yra svarbi grandinės funkcionalumo dalis, nes ji naudojama tiek blokams, tiek transakcijoms identifikuoti ir apsaugoti jų vientisumą.

user.cpp, user.h - apibrėžia ir įgyvendina User klasę, kuri naudojama atstovauti blokų grandinės vartotojus. Kiekvienas vartotojas turi unikalų vardą, viešąjį raktą ir atsitiktinį valiutos balansą, kurį galima naudoti transakcijoms. Ši klasė leis lengvai generuoti ir valdyti vartotojus jūsų blokų grandinėje.

transaction.cpp, transaction.h - apibrėžia ir įgyvendina Transaction klasę, kuri reprezentuoja vieną transakciją blokų grandinėje. Transakcijos struktūra apima siuntėjo ir gavėjo viešuosius raktus, pervedamos valiutos sumą ir unikalų transakcijos ID, gautą naudojant maišos funkciją. Ši klasė padės tvarkyti ir įrašyti transakcijas į blokus.
