#  Supaprastintos blokų grandinės (blockchain) kūrimas

Šios užduoties tikslas – sukurti supaprastintą blokų grandinę (angl. blockchain), kurios duomenų sluoksnio struktūra pavaizduota
žemiau:

![Ekrano kopija (444)](https://github.com/user-attachments/assets/1c228cb7-f59a-4fb0-8c32-44fa634e9660)

**Svarbūs blokų grandinės aspektai:**

* Blokų grandinė (blockchain) yra nuoseklus blokų sąrašas, kur kiekvienas blokas susietas su prieš tai einančio bloko maišos
funkcijos reikšme (angl. hash). Maišos funkcija taikoma 6 pagrindiniams bloko antraštės (angl. block header) elementams.

* Kiekvienas blokas sudarytas iš dviejų dalių: antraštės (angl. header) ir turinio (angl. Body of the Block (Transactions)).

**Antraštę sudaro:**

* Ankstesnio bloko maišos reikšmė ( Prev Block Hash )
* Laiko žyma ( Timestamp )
* Blokų grandinės duomenų struktūros versija ( Version )
* Visų bloko transakcijų maišos reikšmė, gauta naudojant Merkle medį ( Merkel Root Hash )
* Atsitiktinis skaičius, naudojamas tinkamo sudėtingumo (nustatomo pagal nulių skaičių maišos reikšmės pradžioje) bloko
* maišos reikšmei gauti ( Nonce )
* Bloko maišos reikšmės sudėtingumas ( Difficulty Target )

**Turinį sudaro:**

* Visos bloko transakcijos.

## Užduoties formuluotė

Sukurkite "centralizuotą" blokų grandinę (blockchain) ir imituokite jos veikimą kuo realistiškiau. Preliminari veiksmų seka:

1. Sugeneruokite ~1000 tinklo vartotojų, turinčių šiuos atributus:

+ **vardą,**
+ **viešąjį raktą ( public_key ),**
+ **atsitiktinį valiutos balansą (pvz., nuo 100 iki 1000000 valiutos vienetų).**

2.  Sugeneruokite ~10000 naujų transakcijų, kurios dar nėra įtrauktos į jokį bloką. Transakcijos struktūra turi turėti šiuos atributus:

+ **transakcijos ID (kitų transakcijos laukų maišos reikšmė),**
+ **siuntėjas (jo viešasis raktas),**
+ **gavėjas (jo viešasis raktas),**
+ **suma.**

Transakcijų struktūrą galite tobulinti, pvz., vietoj sąskaitos modelio (angl. account model) galite naudoti UTXO modelį.

3.  Atsitiktinai pasirinkite 100 transakcijų iš transakcijų sąrašo ir pabandykite jas įtraukti į naują bloką.

4.  Realizuokite naujų blokų kasimo (angl. mining) procesą, naudojant Proof-of-Work (PoW) algoritmą. Tikslas – rasti naujo bloko
maišos reikšmę, atitinkančią Difficulty Target reikalavimą (nulių skaičių maišos reikšmės pradžioje). Nulių skaičius priklauso
nuo jūsų sukurtos maišos funkcijos.

5. Suradus tinkamą naujo bloko maišos reikšmę:

6. Kartokite 3-5 žingsnius, kol yra neįtrauktų transakcijų. Taip pat galite kartoti 1-5 žingsnius, generuodami naujus vartotojus ir
transakcijas.
## Realizuota blokų grandinė:

**block.cpp, block.h** - apibrėžia Block klasę, kuri naudojama blokų struktūrai blokų grandinėje. Šiuose failuose bus apibrėžta, kaip blokas atrodo, kokie jo laukai yra naudojami, kaip atliekamas maišos skaičiavimas

**blockchain.cpp, blockchain.h** - apibrėžia Blockchain klasę, kuri yra atsakinga už blokų grandinės kūrimą, valdymą ir transakcijų įtraukimą į blokus. Šiuose failuose pateikiama blokų grandinės struktūra bei funkcijos, reikalingos blokų kūrimui ir jų pridėjimui į blokų grandinę.

**hash_function.cpp, hash_functions.h** - apibrėžia ir įgyvendina maišos funkciją, kuri yra naudojama blokų ir transakcijų maišos reikšmėms apskaičiuoti blokų grandinės projekte. Ši maišos funkcija yra svarbi grandinės funkcionalumo dalis, nes ji naudojama tiek blokams, tiek transakcijoms identifikuoti ir apsaugoti jų vientisumą.

**user.cpp, user.h** - apibrėžia ir įgyvendina User klasę, kuri naudojama atstovauti blokų grandinės vartotojus. Kiekvienas vartotojas turi unikalų vardą, viešąjį raktą ir atsitiktinį valiutos balansą, kurį galima naudoti transakcijoms. Ši klasė leis lengvai generuoti ir valdyti vartotojus jūsų blokų grandinėje.

**transaction.cpp, transaction.h** - apibrėžia ir įgyvendina Transaction klasę, kuri reprezentuoja vieną transakciją blokų grandinėje. Transakcijos struktūra apima siuntėjo ir gavėjo viešuosius raktus, pervedamos valiutos sumą ir unikalų transakcijos ID, gautą naudojant maišos funkciją. Ši klasė padės tvarkyti ir įrašyti transakcijas į blokus.
