## Grile Web

#### 1. Un apel AJAX se poate face catre o resursa statica oferita de end-point-ul de pe server?
- [x] Da, intotdeauna

#### 2. #RRAABB este un cod de culoare valid?
- [x] Nu, deoarece valorile nu sunt specificate in baza 16

#### 3. Care dintre urmatoarele afirmatii referitoare la filtrele de vizibilitate sunt adevarate?
- [x] Selectorul ```:hidden``` se foloseste pentru a selecta toate elementele ascunse in pagina
- [x] Selectorul ```:visible``` se foloseste pentru a selecta toate elementele care ocupa spatiu in pagina

#### 4. Ce indica un cod de raspuns de forma 3xx trimis prin intermediul protocolului HTTP de un server web?
- [x] mutarea documentului cerut la o alta adresa
- [x] redirecteaza clientul spre alt URL

#### 5. De pe client se doreste salvarea unor date despre o persoana (numele si varsta acesteia) folosind un apel AJAX realizat prin metoda HTTP GET. Care dintre urmatoarele apeluri realizeaza acest lucru:
- [x] ```$.get("save.php", {nume: 'Ion', varsta:10})```
- [x] ```$.get("save.php?nume=Ion&varsta=10")```
- [x] ```$.get("save.php", 'nume=Ion&varsta=10')```

#### 6. Ce face urmatoarea secventa de cod:
```js
	$('li:first').addClass('patrat').addClass('deplasat').addClass('colorat');
```
- [x] selecteaza primul element din fiecare lista si ii adauga clasele patrat, deplasat, colorat

#### 7. Un URL de pe back-end poate fi invocat (cerut) atat prin GET cat si prin POST:
- [x] Da

#### 8. Un fisier PHP poate fi executat:
- [x] In linia de comanda folosind interpretorul php.exe pe Windows sau php pe Linux

#### 9. Cum se declara un array vid in PHP:
- [x] ```$emptyArray = [];```
- [x] ```$emptyArray = array();```

#### 10. Ce face urmatoarea secventa de cod:
```js
	$(':not(p)').addClass('patrat').addClass('colorat');
```
- [x] selecteaza toate elementele cu exceptia paragrafelor si le adauga clasele patrat si colorat

#### 11. Pentru a defini o lista ordonata a caror itemi sunt precedati de litere din alfabetul grec in CSS, se foloseste:
- [x] list-type: lower-greek

#### 12. Pentru a redirectiona automat browser-ul spre un nou URL, server-ul poate:
- [x] raspunde clientului cu un nou cod de raspuns de forma 3xx impreuna cu un header Location
- [x] redirectioneaza clientul folosind o secventa de cod in JavaScript de forma window.location = "http://url-nou"
- [x] trimite ca si continut HTML clientului un link de forma ```<a href="http://url-nou">``` si simuleaza din JavaScript un click de mouse pe acest link
