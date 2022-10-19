# Tema 1 - Proiectarea algoritmilor
# Dumitru Elena-Bianca

## 1. Crypto

Am citit datele din fisier intr-un vector ce contine structuri de tip calcula-
tor, care contin campurile aferente power, respectiv cost. <br />

Am sortat datele descrescator in functie de power, pentru a creste gradual pute-
rea minima pe care o au toate procesoarele. M-am folosit de functia sort din c++
careia i-am dat cat ca parametru o functie proprie, compareByPower. <br />

Pentru algoritmul propriu-zis, am urmat pasii:
- Cat timp puterea calculatorului este <= puterea minima, adaugam 
   costul acestuia la o suma pentru a vedea cat ne costa un upgrade pana
   la urmatoarea putere; incrementam k pentru a itera.
   Suma se calculeaza cat timp nu am trecut prin toate calculatoarele.
   Exista si cazuri cand putem face upgrade chiar si peste puterea celui
   mai performant calculator, deci trebuie sa avem doar suma calculatoa-
   relor deja existente.
- Cand gasim calculatorului cu puterea superioara fata de puterea mi-
   nima suportata pana atunci, vedem daca ne putem permite noul update.
   Daca da, scadem din suma totala cat am cheltuit, actualizam minPower
   la noua putere si continuam cautarea de la acelasi k (pentru a putea
   adauga si aceasta valoare la suma).
   Daca nu, adunam la puterea minima cat ne permitem cu banii ramasi si
   suma curenta.
- Aceste operatii se intampla cat timp bugetul este >= 0.
La final, in variabila minPower vom ramane cu raspunsul corect.
Complexitatea rezolvarii este mai mica decat O(nlogn + n) = O(nlogn) deoarece nu 
trecem pas cu pas prin toate valorile de putere, ci avem salturi mai mari la 
unele diferente consecutive. Asadar, complexitatea este dictata de operatia de
sortare care se efectueaza in nlogn.


## 2. Stocks

Pentru a retine datele, am folosit o structura act care contine campurile
currentValue, minValue si maxValue pe care le-am retinut in vectorul v. Deoarece
am abordat aceasta problema folosind programare dinamica si voi folosi un cub
de stocare a datelor, primul element din vectorul v este null - struct {0, 0, 0}
pentru a nu produce ulterior confuzie de indici. <br />

Dimensiunile cubului de date vor fi (n + 1 -> numarul de actiuni, b + 1 -> bugetul, l + 1 -> pierderea maxima). Am ales aceasta reprezentare 3D pentru a putea contoriza si nivelul de loss in functie de alegerile anterioare. <br />

Algoritmul consta in parcurgerea celor 3 niveluri folosind 3 for-uri imbricate.
Vom analiza elementele de la 1 la n pentru a vedea la fiecare pas al algoritmului daca si unde putem adauga elementul.
Pentru a putea adauga elementul k, trebuie ca valoarea sa de cumparare 
(currentValue) sa fie <= j, adica pentru a putea completa corect coloane corespunzatoare bugetului maxim de j. Acum trebuie sa verificam daca alegerea acestei actiuni este intr-adevar mai avantajoasa. <br />

Pentru asta, verificam daca valoarea de la pozitia [i - 1] (inainte de adaugarea
elementului) [j - v[i].currentValue] (inainte de plata valorii acestuia) 
[k - v[i].currentValue + v[i].minValue] (si inainte de a lua in considerare loss
ul adus de adaugarea acestuia) + (v[i].maxValue - v[i].currentValue) (profitul
maxim) este mai buna decat valoarea de la pozitia [i - 1][j][k]. <br />

Daca da, inseamna ca este mai bine sa adaugam elementul asa ca punem la pozitia
table[i][j][k], primul element calculat. Altfel, ramanem cu solutia deja calcu-
lata table[i][j][k] = table[i - 1][j][k]. <br />

Astfel, valoarea maxima se va afla in ultima "casuta" a cubului, adica pe pozi-
tia table[n][b][l]. Complexitatea programului va fi O(n*b*l), data de parcurge-
rea intregului cub. <br />


## 3. Valley


Pentru valley, am retinut datele in vectorul v. La citire, am retinut pozitia pe
care se afla elementul minim, deoarece am considerat ca acela ar fi cel jos
punct al vaii (daca ar fi sa alegem alta reprezentare, ar fi mai costisitor sa
sapam sub acest punct). <br />

Bineinteles, daca acest punct este primul sau ultimul element, nu s-ar mai putea
numi o vale, ci o rampa, respectiv o panta. Asadar, in aceste situatii am trans-
latat pozitia pe care o consideram minima pentru al doilea + penultimul element. <br />

Am considerat capetele ca fiind cele 2 cele mai inalte puncte, peak1 si peak2,
iar tot ce se afla intre peak[1] si minPos trb sa fie <= peak1 si tot ce este
intre peak[2] si minPos trebuie sa respecte aceeasi conditie. Astfel, am parcurs
vectorul de inaltimi din cele 2 directii diferite. <br />

Daca intalneam o valoare mai mare decat peak1 sau peak2, adaugam diferenta in
variabila minPower (practic crestam muntii ca sa fie la acelasi nivel cu inal-
timea anterioara). Daca valoarea era mai mica, trebuie sa actualizez peak1 si
peak2; asta inseamna ca a scazut nivelul si trebuie sa tin cont in continuare
pentru a efectua corect sapaturile. <br />

La final, suma tuturor diferentelor dintre munti, stocata in minPower reprezinta
fix numarul de ore minim de care are nevoie gigel pentru a transforma lantul
muntos intr-o vale. Complexitatea este O(n+n), pentru citire si pentru parcurge-
rea vectorului, deci in final O(n). <br />


## 4. Ridge

Am retinut datele intr-un vector de structuri de tip mountain cu campurile 
height si cost. Pentru ca am folosit tot programare dinamica, primul element
este de tip ({0, 0}). <br />

Pentru a tine cont de sapaturile precedente, am alocat dinamic o matrice cu ur-
matoarele dimensiuni: 
- n: pentru a tine cont de costurile sapaturilor pentru primii i munti,
      0 <= i <= n
- 3: pentru ca fiecare munte poate fi sapat de 0, 1 sau 2 ori. Daca di-
      ferenta dintre 2 munti este > 2, nu va trebui sa umblam la inalti-
      mea acestuia. Altfel, alte sapaturi pot schimba si influenta inal-
      timi care trebuie contorizate.
		
Asadar, luam cazurile urmatoare:
Cand 2 inaltimi consecutive sunt diferite, mai intai initializam matricea co-
respunzatoare muntelui i cu minimul anterior + costul sapaturilor acestui munte
de 0 ori (pentru coloana 0), 1 pentru coloana 1 si 2 pentru coloana 2.
Apoi avem urmatoarele situatii pentru a evita egalitatile de inaltime:
- Cand muntele actual este mai mare cu 1 decat cel precedent:
	*Daca l-as excava cu 0, se pastreaza diferenta, deci pentru co-
	loana 0 putem considera minimul de pe linia anterioara.
	*Daca l-as excava cu 1, ar fi la fel cu muntele precedent, deci,
	pentru a evita acest lucru, nu luam in considerare cazul in care
	muntele precedent a fost excavat cu 0. Deci vom face minimul 
	dintre coloanele corespunzatoare lui 1 si 2 de pe linia ante-
	rioara + costul excavarii muntelui curent
	*Daca l-as excava cu 2, in mod asemanator, nu trebuie sa luam
	in considerare cazul cand muntele precedent e excavat cu 1 ca sa
	nu aiba aceeasi inaltime, deci vom avea minimul dintre coloanele
	pentru 0 si 2 de pe linia precenta + 2 * costul ex
- Cand muntele actual este mai mare cu 2 decat cel precedent:
	*Daca il excavez cu 0 sau 1 nu se influenteaza reciproc
	*Daca il excavez cu 2, nu iau in considerare cazul in care mun-
	tele precedent este excavat cu 0
- Cand muntele actual este mai mic cu 1 decat cel precedent:
	*Daca il excavez cu 0, nu iau in considerare cazul in care mun-
	tele precedent este excavat cu 1
	*Daca il excavez cu 1, nu iau in considerare cazul in care mun-
	tele precedent este excavat cu 2
	*Daca il excavez cu 2, devine prea mic pentru a mai putea fi 
	egal cu muntele precedent => min toate cazurile
- Cand muntele actual este mai mic cu 2 decat cel precedent:
	*Daca il excavez cu 0, nu iau in considerare cazul in care mun-
	tele precedent este excavat cu 2
	*Daca il excavez cu 1 sau 2, devine prea mic pentru a mai putea 
	fi egal cu muntele precedent => min toate cazurile
Cand cele 2 inaltimi sunt egale:
- Daca excavez cu 0, nu iau in considerare cazul cand muntele precedent
este excavat cu 0
- Analog pentru celelalte
Pentru ca nu am mentionat de fiecare data, cand excavam cu 1, adaugam si costul
la cheltuiala respectiva, respectiv de 2 ori costul pt o excavare cu 2.

Tratam si cazurile cand inaltimea muntelui poate ajunge sub 0: 
- Daca inaltimea este 0, nu mai putem excava cu 1 sau 2 -> deci setam
	aceasta valoare ca fiind cel mai mare numar LONG LONG din C++
	pentru a ne asigura ca nu mai luam niciodata cazurile acelea
- Asemanator, daca diferenta este 1, nu mai putem excava cu 2, deci
	nu luam in considerare acel caz.

La final, pretul minim pe care trebuie sa-l plateasca Gigel pentru a obtine
creasta montana mult dorita va fi minimul valorile de pe ultima linie din matri-
cea construita.
