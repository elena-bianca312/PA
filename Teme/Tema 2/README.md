# Dumitru Elena
324CD

# Tema 2 - Proiectarea algoritmilor

## 1. Poduri

Am citit datele din fisier, mai intai dimensiunile matricei si coordonatele no-
dului de start. 
Am alocat dinamic matricea in care vom citi datele.
Pentru fiecare pozitie din matrice, am calculat am encodat valoarea 'char' 
intr-un int pentru eficienta. Asadar, pentru D avem val 3
				      pentru V avem val 2
				      pentru O avem val 1.
Pentru pozitiile fara poduri, valoarea va ramane 0.

Toata logica exercitiului se bazeaza pe cautarea in latime, avand la baza algo-
ritmul lui Lee. In continuare, voi prezenta functia BFSmatrix: <br />

In aceasta functie vom avea o matrice visited in care vom tine cont ce pozitii
au fost explorate pentru a putea extrage pozitiile viitoare.
Pentru a retine datele, avem structura Node care contine coordonatele din ma-
trice si distanta acestora fata de sursa.
Vom marca sursa ca fiind vizitata si o vom introduce in coada cu distanta 0 pen-
tru a vedea care sunt posibilitatile in continuare. <br />

In while, vom explora nodurile. Vom scoate primul nod din coada. Verificam con-
ditia de oprire, si anume sa nu fie un nod marginal.
Daca nu, trebuie sa vedem ce cazuri putem explora. Prin vectorii row si col ex-
primate cele 4 mutari. In functie de celula pe care ne aflam, putem explora ori
toate posibilitatile, ori sus-jos (fluctueaza row si col = 0) ori stanga-dreapta
(fluctueaza col si row = 0). 
Facem inca o verificare sa vedem daca ajungem intr-o pozitie valida (daca depa-
sim dimensiunea matricei sau acea pozitie a fost deja vizitata).
Daca trece verificarea, adaugam nodul in coada cu distanta incrementata (deoare-
ce am explorat o noua pozitie) si continuam cautarea. <br />

Cand coada devine vida inseamna ca am explorat toate posibilitatile si trebuie
sa returnam distanta minima. Daca a indeplinit criteriul de gasire al destinati-
ei, vom intoarce distanta rezultata. Altfel va fi egala cu INF_MAX, deci nu a 
fost gasit drum spre iesire, trebuie sa intoarcem -1. <br />

Printam rezultatul in fisierul de out.


## 2. Adrese

Am creat o structura de persoane pentru a putea retine informatiile despre aces-
tea (nume, numar de email-uri si un set de email-uri - pentru a nu avea duplica-
te), dar si pentru a implementa functia de sortare folosita pentru afisarea
corespunzatoare. Aceasta, ca in enunt, are ca criteriu prioritar numarul de 
mailuri, iar apoi ordinea lexicografica a numelor persoanelor. <br />

Cream un hashmap care va avea ca cheie un mail si ca valoare o lista de indexi
ce reprezinta persoanele care detin acest mail. Asadar, daca o lista va avea mai
mult de un element, inseamna ca acel mail este share-uit de mai multe persoane
si doar una dintre ele este cea reala. <br />

In continuare, realizam citirea din fisier si vom adauga fiecare persoana citita
intr-un vector de persoane si fiecare mail in hash-ul de mail-uri. <br />

Iteram prin hask-ul de mail-uri. Cand gasim duplicate (size > 1), cautam care 
este persoana cu numele minim lexicografic si pe aceasta o vom considera in con-
tinuare ca fiind persoana reala. 
Transferam toate mail-urile noii persoane si o adaugam in lista de hash-uri ale
celorlalte mailuri. Fixam numarul de mail-uri ale persoanelor false pe 0 si re-
actualizam numarul de mail-uri ale persoanei reale la dimensiunea setului. <br />

In final, vom avea toate persoanele cu mail-uri corespunzatoare retinute in mod
corect in vectorul people, pe care trebuie sa-l sortam conform cerintei.
La afisare nu vom afisa persoanele care au 0 mail-uri deoarece, cum am mai spus,
sunt false. Afisarea va consta chiar in raspunsul problemei.


## 3. Lego

Citim datele din fisier. 
Generam toate combinarile de n numere din intervalul [1-k] folosind functia
void combination(set<vector<int>> &comb, int limit, int r).
Aceasta functie initializeaza functia recursiva combinationUtil pentru a con-
strui combinatiile dorite. Toate combinatiile trebuie sa contina 1, deci putem
adauga deja 1 in data (vectorul ce contine solutia curenta per iteratie) si sa
incepem alegerea urmatoarelor numere incepand cu al doilea. <br />

Functia combinationUtil se bazeaza pe backtracking. Facem cate un apel de 
functie, o data pentru cand pastram elementul (trecem la urmatorul index) si o
data cand nu-l pastram (transmitem ca parametru alt index pentru a fi supra-
scris). Cand am terminat de completat array-ul data (am atins limita sa r), 
luam elementele si le adaugam in comb, setul de vectori. <br />

Pentru fiecare vector din setul de vectori, trebuie sa calculam toate sumele po-
sibile care se pot forma cu elementele acestuia, in limita t. Pentru a afla a-
ceasta suma, folosim functia subsets.
Aceasta functie primeste un set in care va pune sumele (pentru a nu avea dupli-
cate), vectorul si o secventa care se va completa cu elementele vectorului si
dimensiunea acesteia, bineinteles t.
Functia se va implementa tot folosind backtracking. In sequence, vom adauga pe
fiecare pozitie pe rand toate elementele din vector. Complexitatea pentru aceas-
ta operatie devine asadar n * t. Dupa ce am umplut tot vectorul intr-o iteratie,
calculam suma elementelor alese pe pozitiile vectorului si adaugam noua suma
in setul sums (din nou, pentru a nu avea duplicate). <br />

Acum, ramane doar de calculat secventa de sume consecutive de lungime maxima din
setul sums. Cum toate seturile vor incepe cu 1 (deoarece sunt construite cu 
vectori ce au in componenta lor 1), trebuie sa declaram o variabila length care 
sa calculeze lungime per secventa si sa fie reinitializata de fiecare data cand
intalnim un numar care nu este succesorul celui anterior. <br />

In variabila max vom avea la final lungimea celei mai lungi secvente. Trebuie de
fiecare data sa golim setul pentru a adauga in continuare in el noi sume (si a
nu pastra sume de la combinarile anterioare). <br />

Observatii: O varianta alternativa ar fi fost sa generez permutarile pozitiilor
	o singura data si apoi sa calculez doar sumele in baza acestor permuta-
	ri, dar functia mea de generare nu produce duplicate, deci complexita-
	tea este aceeasi.


## 4. Retea 

In rezolvarea acestei probleme, am folosit algoritmul lui Kosaraju. 
Citim graful pe care il vom retine sub forma unui vector de liste de adiacenta.
Construim o copie a acestui vector - copy. <br />

Apoi, pentru fiecare nod in parte, ii taiem legaturile cu celelalte noduri 
(functia delEdge) si aplicam algoritmul lui Kosaraju pentru a vedea ce componen-
te (tari - graf neorientat) componexe ne-au mai ramas. <br />

Astfel, toata logica programului se bazeaza pe algoritmul lui Kosaraju aplicat
de n ori (nu il voi mai explica). Am mai adaugat variabila p care va tine minte
pentru fiecare componenta conexa in parte dimensiunea sa pentru a putea calcula
legaturile. <br />

Legaturile pot fi descrise de relatia (V - p) * p, insumate unde V-p reprezinta
nr de noduri cu care am pierdut legatura si p numarul de noduri care se afla in
aceasta situatie. Suma aceasta este refacuta pentru cazul in care dispare fiec-
care nod in parte.









