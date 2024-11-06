#  Supaprastintos blokų grandinės (blockchain) kūrimas

Šios užduoties tikslas – sukurti supaprastintą blokų grandinę (angl. blockchain), kurios duomenų sluoksnio struktūra pavaizduota
žemiau:

<img width="500" alt="Drawing 1" src="https://github.com/user-attachments/assets/1c228cb7-f59a-4fb0-8c32-44fa634e9660">

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

+ **block.cpp, block.h** - apibrėžia Block klasę, kuri naudojama blokų struktūrai blokų grandinėje. Šiuose failuose bus apibrėžta, kaip blokas atrodo, kokie jo laukai yra naudojami, kaip atliekamas maišos skaičiavimas

+ **blockchain.cpp, blockchain.h** - apibrėžia Blockchain klasę, kuri yra atsakinga už blokų grandinės kūrimą, valdymą ir transakcijų įtraukimą į blokus. Šiuose failuose pateikiama blokų grandinės struktūra bei funkcijos, reikalingos blokų kūrimui ir jų pridėjimui į blokų grandinę.

+ **hash_function.cpp, hash_functions.h** - apibrėžia ir įgyvendina maišos funkciją, kuri yra naudojama blokų ir transakcijų maišos reikšmėms apskaičiuoti blokų grandinės projekte. Ši maišos funkcija yra svarbi grandinės funkcionalumo dalis, nes ji naudojama tiek blokams, tiek transakcijoms identifikuoti ir apsaugoti jų vientisumą.

+ **user.cpp, user.h** - apibrėžia ir įgyvendina User klasę, kuri naudojama atstovauti blokų grandinės vartotojus. Kiekvienas vartotojas turi unikalų vardą, viešąjį raktą ir atsitiktinį valiutos balansą, kurį galima naudoti transakcijoms. Ši klasė leis lengvai generuoti ir valdyti vartotojus jūsų blokų grandinėje.

+ **transaction.cpp, transaction.h** - apibrėžia ir įgyvendina Transaction klasę, kuri reprezentuoja vieną transakciją blokų grandinėje. Transakcijos struktūra apima siuntėjo ir gavėjo viešuosius raktus, pervedamos valiutos sumą ir unikalų transakcijos ID, gautą naudojant maišos funkciją. Ši klasė padės tvarkyti ir įrašyti transakcijas į blokus.

## Nauodjimosi instrukcija

1. Github'e paspaudę žalią mygtuką parsisiųskite programos ZIP

2. Kodą pasileiskite norimoje aplinkoje pvz: Visual Studio Code

3. Tam, kad paleisti kodą pasirinkite CMD terminalą ir įrašykite:
   
   *main.cpp user.cpp transaction.cpp utxo.cpp hash_function.cpp block.cpp -o blockchain*,
   
   tuomet norint paleisti programą reikės įrašyti
   
    *blockchain_simulation.exe*
4. Terminale pamatysite:

```
Ar norite sugeneruoti vartotojus? (t/n): t
Vartotojai sugeneruoti ir irasyti i users.txt faila.
Ar norite sugeneruoti transakcijas? (t/n): t
Pradinis UTXO sarasas sukurtas is vartotoju balansu.
Generuojamos transakcijos... (10000 transakciju)
Ar norite generuoti blokus tol, kol yra neitrauktu transakciju? (t/n): n
Kiek bloku norite sugeneruoti? 2
Blokas sekmingai irasytas i faila 'block.txt'.
Blokas #1 buvo sekmingai iskastas su 10 transakcijomis.
Blokas sekmingai irasytas i faila 'block.txt'.
Blokas #2 buvo sekmingai iskastas su 10 transakcijomis.
Programos vykdymas baigtas.
```

* Pasirenkama, ar norima sugeneruoti vartotojus. (atsiranda faile users.txt)
  
* Pasirenkama, ar norima sugeneruoti transakcijas. (atsiranda faile transaction_utxo.txt)
  
* (Ar norite generuoti blokus tol, kol yra neitrauktu transakciju? (t/n): n) Pasirenkama, ar norima pačiam įvesti, kiek blokų generuoti, ar generuoti, kol yra neįtrauktų
  transakcijų.

* Jei n, įrašoma, kiek blokų norima sugeneruoti. (atsiranda faile block.txt)

## Vartotojų generavimas

**1. User struktūra (user.h):**

Ši struktūra apibrėžia vartotojo duomenis:

* name: Vartotojo vardas (string tipo).
* publicKey: Vartotojo viešasis raktas, kuris generuojamas naudojant vardo maišą.
* balance: Vartotojo balansas (double tipo).

*user.txt*

```
Vartotojas: Olivia 1
Viešasis raktas: 4f6c697669612031346836673639373636393631323033313468366736393736
Balansas: 31424
Vartotojas: Emma 2
Viešasis raktas: 456d6d61203234353668366a36313230333234353668366a3631323033323334
Balansas: 8354
Vartotojas: Charlotte 3
Viešasis raktas: 436861726c6f74746520333433363836313732366d3672373437343635323033
Balansas: 22651
Vartotojas: Amelia 4
Viešasis raktas: 416d656c69612034343136683635366b3639363132303334343136683635366b
Balansas: 28132
```

## Transakcijų generavimas (UTXO modelis)

**1. UTXO modelis (utxo.h ir utxo.cpp)**

* **UTXO struktūra:** Kiekvienas UTXO turi viešąjį raktą ir sumą.
  
* **UTXO sąrašo inicializavimas:** initializeUTXOListFromUsers funkcija sukuria pradinį UTXO sąrašą iš vartotojų balansų, įrašydama informaciją į failą transaction_utxo.txt.
  
* **UTXO kūrimas ir pašalinimas:** createUTXO funkcija prideda naują UTXO į sąrašą, o removeUTXO pašalina jį, kai jis yra panaudotas transakcijoje.

**Darbo eiga**

1. **Vartotojai generuojami:** Atsitiktiniai vartotojai sukuria unikalius viešuosius raktus ir balansus.
   
3. **Transakcijos generuojamos:** Atsitiktinės transakcijos generuojamos remiantis vartotojų balansais ir UTXO sąrašu.
   
5. **UTXO sąrašas kūrimas:** Sukuriamas UTXO sąrašas, kuriame saugomi nepatvirtinti išmokėjimai, ir iš jų vykdomos transakcijos.
   
7. **Blokai kūriami:** Blokai generuojami ir tikrinama, kad visi neįtraukti UTXO būtų apdoroti. Maišos generuojamos ir atliekama kasyba per Proof-of-Work.
   
9. **Balansų atnaujinimas:** Po blokų kūrimo atnaujinami vartotojų balansai ir įrašomi į failą.

**transaction_utxo.txt**

```
Transakcija: 1515e718141410111416e13f1814d1115f15151216f1415f1414151500000000,

Siuntėjas: 416c6c69736f6e20313030303431366736693639373336723673323033313330,

Gavėjas: 536f70686961203330353533366a373036383639363132303333333033353533,

Suma: 51BTC


Transakcija: 9151418e12c141712141418e12c124b1418ba121291212121416160000000000,

Siuntėjas: 456d696c7920333138343536683639366b373932303333333133383435366836,

Gavėjas: 4b656e6e6564792037373234643635366b366d36353634373932303337333733,

Suma: 79BTC
```

## Transakcijų įtraukimas į bloką


