# Variantă de rezolvare colocviu ianuarie 2025

## Cerință

Compania Q&V se ocupă cu organizarea de licitații pentru diverse articole.
Statisticile interne au observat o descreștere a prețului de cumpărare, astfel compania dorește să își modernizeze
uneltele de analiză. Aceștia aleg să folosească o aplicație în C++ care să le permită să simuleze o posibilă sesiune
de licitație.

Fiecare obiect ce se găsește la licitație are un ID unic, prin care este identificat în inventarul companiei.
În momentul prezentării se anunță numele, data sau era aproximativă din care datează și prețul inițial de listare.
Aceste artefacte se pot încadra în mai multe categorii:
- artefacte istorice, pentru care ne interesează numele persoanelor renumite cu care este asociat
- artefacte artistice, pentru care se dorește să se cunoască tipul (pictură, sculptură) și materialul (acrilic, ulei pentru picturi, lemn, piatră sau marmură pentru sculpturi)
- artefacte prețioase, pentru care se anunță numele designer-ului (sau “Necunoscut” dacă nu se cunoaște) și greutatea (în grame)

La licitație fiecare entitate se identifică printr-un număr unic pe care îl ridică în momentul în care vor să anunțe interesul pentru artefact. Aceștia pot fi persoane fizice (pentru care se cunoaște numele real sau un alias), sau persoane juridice (pentru care se cunoaște numele organizației și persoanele fizice ce reprezintă organizația).

În momentul în care începe licitația, fiecare participant are un anumit buget pe care îl poate cheltui, un pas de licitare fix și o valoare de confort.

De asemenea, aceștia au un tip preferat de artefact (pentru care își vor depăși valoarea de confort ca să îl obțină) și unul pe care îl ignoră.

Persoanele fizice continuă licitarea, dacă se încadrează în bugetul propriu și este un tip de artefact preferat.

Persoanele juridice continuă licitarea dacă jumătate din reprezentanți aleg să continue licitația sau dacă este un obiectiv al companiei și minim o persoană alege să continue (și este ignorat, dacă compania ignoră acel tip de articol).

Aplicația va ilustra următoarele funcționalități:
- adăugarea de participanți
- adăugarea de artefacte
- afișarea participanților
- afișarea articolelor ce sunt disponibile pentru licitație
- simularea unei sesiunii de licitații pentru un artefact cu valoarea unui ID dat de la tastatură și efectuarea operațiilor aferente (scăderea bugetului, eliminarea din inventar și adăugarea într-un istoric de licitație)
- afișarea participanților în ordine descrescătoare numărului de artefacte cumpărate
- afișarea obiectelor cumpărate în ordinea descrescătoare a prețului cu care au fost cumpărate

Pentru sortări, folosiți `std::sort`, nu sortări implementate manual (în $O(n^2)$). Cel mai simplu
este să folosiți funcții lambda pentru funcțiile de comparare.

Nu uitați să citiți și precizările. Nu pierdeți timp să implementați ceva ce nu se cere, deoarece nu se va puncta.

## Rezolvare

În continuare, prezentăm subiectul din ianuarie 2025 împreună cu variante posibile de rezolvare.

Reiterăm faptul că nu există o singură soluție corectă.

> Compania Q&V se ocupă cu organizarea de licitații pentru diverse articole.
> Statisticile interne au observat o descreștere a prețului de cumpărare, astfel compania dorește să își modernizeze
> uneltele de analiză. Aceștia aleg să folosească o aplicație în C++ care să le permită să simuleze o posibilă sesiune
> de licitație.
>
> Fiecare obiect ce se găsește la licitație are un ID unic, prin care este identificat în inventarul companiei.
> În momentul prezentării se anunță numele, data sau era aproximativă din care datează și prețul inițial de listare.
> Aceste artefacte se pot încadra în mai multe categorii.

Așadar, avem clasa de bază `Artefact` cu mai multe atribute. Pentru dată/eră este suficient aici să folosim
`std::string`.
În alte subiecte, dacă este cazul, recomandăm să folosiți `std::tm` sau `std::chrono::year_month_day`/
`std::chrono::sys_date`
și funcții predefinite din biblioteca standard, nu să pierdeți timp să reinventați roata.

> • artefacte istorice, pentru care ne interesează numele persoanelor renumite cu care este asociat
>
> • artefacte artistice, pentru care se dorește să se cunoască tipul (pictură, sculptură) și materialul (acrilic, ulei
> pentru picturi, lemn, piatră sau marmură pentru sculpturi)
>
> • artefacte prețioase, pentru care se anunță numele designer-ului (sau “Necunoscut” dacă nu se cunoaște) și
> greutatea (în grame)

Urmează clasele derivate.

Pentru artefactele artistice, avem de făcut validări: fie la nivel de compilator cu enumerări,
fie cu excepții. O validare corectă va verifica și compatibilitatea materialului cu tipul de artefact.

Din moment ce este vorba doar despre atribute, nu și funcționalități (până acum), nu pare să avem nevoie de
virtualizare pentru această ierarhie (dar vedeți mai jos). În acest caz, destructorul ar trebui să fie protected
și non-virtual.

Totuși, dacă vreți să arătați că știți ceva din funcții virtuale, un pretext valid este să faceți afișări virtuale.

> La licitație fiecare entitate se identifică printr-un număr unic pe care îl ridică în momentul în care vor să anunțe
> interesul pentru artefact. Aceștia pot fi persoane fizice (pentru care se cunoaște numele real sau un alias),
> sau persoane juridice (pentru care se cunoaște numele organizației și persoanele fizice ce reprezintă organizația).

Pentru persoanele fizice și persoane juridice, ar fi 3 variante:

- clase complet independente
- ierarhie fără virtualizare (destructor protected și non-virtual)
- ierarhie cu virtualizare, având o clasă de bază `Participant`

Clasa `PersoanaJuridica` va avea ca date membru un vector de `PersoanaFizica`, nu de `Participant`.

Pentru punctaj maxim ar trebui evitată duplicarea de cod.

> În momentul în care începe licitația, fiecare participant are un anumit buget pe care îl poate cheltui,
> un pas de licitare fix și o valoare de confort.

Pas de licitare înseamnă cu cât să crească prețul.
Valoarea de confort se referă la valoarea maximă pe care participantul este dispus să o plătească.

[//]: # (de unde am aflat că îi zice pas de licitare: https://bt.ase.ro/EI/resurse/okazii.htm)

[//]: # (termenul de "valoare de confort" nu pare să fie consacrat)

> De asemenea, aceștia au un tip preferat de artefact
> (pentru care își vor depăși valoarea de confort ca să îl obțină) și unul pe care îl ignoră.

În cazul în care nu ați folosit funcții virtuale mai devreme, aici aveți încă un pretext.
Pe scurt, logica ar putea fi următoarea:

```c++
for(const auto& participant : licitatie.participanti) {
    if(participant->ignora(artefact) ||
       (participant->getValConfort() < preturi[artefact] && !participant->prefera(artefact))
      )
        continue;
    if(participant->continuaLicitatiaPentru(artefact))
        preturi[artefact] += participant->getPasLicitare();
}
```

Prin urmare, în clasa `Participant` am putea avea:

```c++
virtual bool prefera(const Artefact&) const = 0;
virtual bool ignora(const Artefact&) const = 0;
```

> Persoanele fizice continuă licitarea, dacă se încadrează în bugetul propriu și este un tip de artefact preferat.
>
> Persoanele juridice continuă licitarea dacă jumătate din reprezentanți aleg să continue licitația
> sau dacă este un obiectiv al companiei și minim o persoană alege să continue
> (și este ignorat, dacă compania ignoră acel tip de articol).

În acest punct avem o cu totul altă variantă de implementare a algoritmului propus mai sus:

- constrângerea de preferință/ignorare ar veni implementată la nivel de compilator, oricare variantă dintre următoarele
  fiind validă
    - cu șabloane
    - cu `std::type_info`
    - cu `dynamic_cast`
- funcție de continuare licitație (`virtual bool bid(const Artefact&) const`)

Oricare variantă va primi cel puțin punctaj parțial, însă punctajul cel mai mare îl veți primi dacă
arătați utilizarea _cu sens_ a cât mai multor noțiuni și concepte _diferite_.

În continuare, prezentăm schițe de rezolvare pentru variantele cu șabloane și cu `std::type_info`.

Este prezentată doar logica pentru artefacte preferate.
Pentru artefactele ignorate, ideea de rezolvare este identică.

O parte din logica de mai jos pentru aceste verificări de preferințe poate fi mutată și în clasa de bază
dacă se consideră mai natural astfel.

Soluția cu șabloane:

```c++
#include <typeinfo>
#include <iostream>

class Artefact {
public:
    virtual ~Artefact() {}
};

class ArtefactIstoric : public Artefact {};
class ArtefactPretios : public Artefact {};

class Persoana {
public:    
    virtual bool bid(Artefact* ob) const = 0;
    virtual ~Persoana() {}
};

template <typename T>
class PersoanaFizica : public Persoana {
public:
    bool bid(Artefact* ob) const {
        // este suficient acest rând
        return typeid(T) == typeid(*ob); 
        
        // aici este scris explicit pentru a vedea că funcționează corect
        if(typeid(T) == typeid(*ob)) {
            std::cout << "preferat\n";
            return true;
        }
        return false;
    }
};

int main() {
    PersoanaFizica<ArtefactIstoric> pf;
    auto aa = new ArtefactIstoric{};
    auto ab = new ArtefactPretios{};
    pf.bid(aa);
    pf.bid(ab);
    delete aa;
    delete ab;
}
```

Soluția cu `std::type_onfo`:

```c++
#include <typeinfo>
#include <iostream>

class Artefact {
public:
    virtual ~Artefact() {}
};
class ArtefactIstoric : public Artefact {};

class ArtefactPretios : public Artefact {};

class Persoana {
public:    
    virtual bool bid(Artefact* ob) const = 0;
    virtual ~Persoana() {}
};

class PersoanaFizica : public Persoana {
    // fie asta, eventual fără `&`
    const std::type_info &produsPreferat;
    
    // fie string către ce returnează type_info.name()
    const std::string strProdusPreferat;
public:
    // așa sau altă variantă este să transmitem la constructor tot un `std::type_info`
    PersoanaFizica(Artefact* produsPreferat):
        produsPreferat(typeid(*produsPreferat)),
        strProdusPreferat(typeid(*produsPreferat).name()) {}

    bool bid(Artefact* ob) const {
        return produsPreferat == typeid(*ob);
        
        // sau scris explicit ca să arătăm că funcționează corect
        // fie
        if(produsPreferat == typeid(*ob)) {
            std::cout << "preferat\n";
            return true;
        }
        // fie
        if(strProdusPreferat == typeid(*ob).name()) {
            std::cout << "preferat\n";
            return true;
        }
        return false;
    }
};

int main() {
    auto aa = new ArtefactIstoric{};
    PersoanaFizica pf(aa);
    auto ab = new ArtefactPretios{};
    pf.bid(aa);
    pf.bid(ab);
    delete aa;
    delete ab;
}
```

Menționăm că logica de preferințe putea fi implementată și cu funcții simple, însă așa nu arătam că
știm și alte noțiuni. Varianta cu șabloane este cea mai eficientă dpdv al memoriei,
deoarece stocarea preferinței este "gratuită" (codificată în tip), dar are un posibil dezavantaj
la crearea obiectelor. Varianta cu `std::type_info` ne oferă flexibilitate
atunci când construim obiecte `Participant`.

O altă variantă prin care să ilustrați ceva nou, dar mai complicată și un pic forțată,
ar fi să utilizați șablonul de proiectare Abstract Factory. Se punctează și o astfel de abordare.

> Aplicația va ilustra următoarele funcționalități:
>
> • adăugarea de participanți
>
> • adăugarea de artefacte
>
> • afișarea participanților
>
> • afișarea articolelor ce sunt disponibile pentru licitație

Fiind vorba de aplicație, avem pretext să ilustrăm un alt șablon de proiectare și anume Singleton.

Menționăm că în cazul afișării participanților ar putea fi folosite funcții virtuale.

```
• afișarea gradului de colectibilitate pentru fiecare artefact (ridicat/scăzut).
  Un artefact este considerat de colectibilitate ridicată dacă:
    ◦ pentru artefactele istorice, dacă sunt menționate mai mult de trei persoane istorice
    ◦ pentru artefactele artistice, dacă sunt făcute din ulei sau marmură
    ◦ pentru artefactele prețioase, dacă au mai mult de 250g și au designer cunoscut
```

Încă un pretext pentru o funcție virtuală. Se punctează și o soluție fără funcții virtuale,
deoarece atributele respective nu se modifică, deci pot fi stabilite și la construirea obiectului.

Nu ar trebui să se înțeleagă să aplicați virtualizare orbește peste tot. O soluție fără virtualizare aici
este corectă cât timp aplicați virtualizarea cu sens în alte locuri (tot la artefacte pentru afișare sau
la participanți). Totuși, dacă nu aveți nicăieri funcții virtuale, nu avem ce să punctăm.

> • simularea unei sesiunii de licitații pentru un artefact cu valoarea unui ID dat de la tastatură
> și efectuarea operațiilor aferente (scăderea bugetului, eliminarea din inventar și
> adăugarea într-un istoric de licitație)

Se precizează la sfârșit de tot că nu este obligatoriu să folosiți meniu, deci puteți adapta cerința
să scoateți citirea de la tastatură. Aveți voie să deviați un pic de la subiect fără să fiți depunctați,
dar să nu deviați până când rezolvați cu totul alt subiect.

Pentru ștergere, algoritmul de mai sus trebuie adaptat

Pentru adăugarea artefactului într-un istoric, aveți nevoie de `clone` dacă folosiți pointeri de bază
pentru artefacte.

> • afișarea participanților în ordine descrescătoare numărului de artefacte cumpărate
>
> • afișarea obiectelor cumpărate în ordinea descrescătoare a prețului cu care au fost cumpărate

Pentru sortări, folosiți `std::sort`, nu sortări implementate manual (în $O(n^2)$). Cel mai simplu
este să folosiți funcții lambda pentru funcțiile de comparare.

Nu uitați să citiți și precizările. Nu pierdeți timp să implementați ceva ce nu se cere, deoarece nu se va puncta.
