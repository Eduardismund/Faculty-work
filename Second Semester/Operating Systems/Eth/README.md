# Eth
The most stressful exam juding from the demanding period. During the same week, we also had exams for Graph Algorithms and Geometry,

## 1. Inversarea ordinii cuvintelor folosind thread-uri

Se dă o propoziție de minim 5 cuvinte și, folosind 5 thread-uri, trebuie să inversezi ordinea cuvintelor (de exemplu, "ana are mere" devine "mere are ana").

## 2. Inversarea ordinii numerelor

Aceeași sarcină ca mai sus, doar că în loc de cuvinte se folosesc numere.

## 3. Calcularea sumei factorialelor

Se dă o variabilă globală și o sumă. Fiecare din cele 5 thread-uri incrementă variabila, calculează factorialul acesteia și adaugă factorialul la sumă. Acest proces continuă până când variabila globală atinge un număr dat de la tastatură. La final, în funcția `main`, se afișează suma.

## 4. Decrementarea variabilei globale cu valori aleatoare

Se scrie un program care citește un număr natural \( N \) de la tastatură într-o variabilă globală "g" și creează 5 thread-uri, fiecare primind ca parametru numărul de ordine cu care este creat. Thread-urile decrementează, pe rând (în funcție de numărul de ordine), variabila "g" cu o valoare aleatoare din intervalul [0-9] până când "g" ajunge la valoarea 0. După fiecare decrementare, fiecare thread va afișa mesajul:

## 5. Distribuirea numerelor în vectori și calcularea sumei

Se citește \( N \) și se creează \( N \) thread-uri. Fiecare thread primește un număr de la tastatură \( i \). Funcția așteaptă ca toate thread-urile să fie create și primește ca parametri doi vectori \( U \) și \( V \), un integer \( S \) și numărul \( i \). Dacă prima cifră a numărului \( i \) este pară, acesta se adaugă la \( U \), iar dacă este impară, se adaugă la \( L \). În \( S \) se calculează suma. Dacă este prima valoare introdusă în vector, se afișează un mesaj.

## 6. Decrementarea variabilei globale cu valori aleatoare până la negativ

Se primește un număr ca parametru, care se salvează într-o variabilă globală. Se pornesc 5 thread-uri și fiecare, pe rând, scade din variabila globală o valoare aleatoare între 0 și 9, până când aceasta devine mai mică decât 0.
