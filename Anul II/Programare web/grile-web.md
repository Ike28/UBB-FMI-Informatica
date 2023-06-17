## Grile Web

#### 1. Un apel AJAX se poate face catre o resursa statica oferita de end-point-ul de pe server?
- [x] Da, intotdeauna
<br>

#### 2. #RRAABB este un cod de culoare valid?
- [x] Nu, deoarece valorile nu sunt specificate in baza 16
<br>

#### 3. Care dintre urmatoarele afirmatii referitoare la filtrele de vizibilitate sunt adevarate?
- [x] Selectorul ```:hidden``` se foloseste pentru a selecta toate elementele ascunse in pagina
- [x] Selectorul ```:visible``` se foloseste pentru a selecta toate elementele care ocupa spatiu in pagina
<br>

#### 4. Ce indica un cod de raspuns de forma 3xx trimis prin intermediul protocolului HTTP de un server web?
- [x] mutarea documentului cerut la o alta adresa
- [x] redirecteaza clientul spre alt URL
<br>

#### 5. De pe client se doreste salvarea unor date despre o persoana (numele si varsta acesteia) folosind un apel AJAX realizat prin metoda HTTP GET. Care dintre urmatoarele apeluri realizeaza acest lucru:
- [x] ```$.get("save.php", {nume: 'Ion', varsta:10})```
- [x] ```$.get("save.php?nume=Ion&varsta=10")```
- [x] ```$.get("save.php", 'nume=Ion&varsta=10')```
<br>

#### 6. Ce face urmatoarea secventa de cod:
```js
	$('li:first').addClass('patrat').addClass('deplasat').addClass('colorat');
```
- [x] selecteaza primul element din fiecare lista si ii adauga clasele patrat, deplasat, colorat
<br>

#### 7. Un URL de pe back-end poate fi invocat (cerut) atat prin GET cat si prin POST:
- [x] Da
<br>

#### 8. Un fisier PHP poate fi executat:
- [x] In linia de comanda folosind interpretorul php.exe pe Windows sau php pe Linux
<br>

#### 9. Cum se declara un array vid in PHP:
- [x] ```$emptyArray = [];```
- [x] ```$emptyArray = array();```
<br>

#### 10. Ce face urmatoarea secventa de cod:
```js
	$(':not(p)').addClass('patrat').addClass('colorat');
```
- [x] selecteaza toate elementele cu exceptia paragrafelor si le adauga clasele patrat si colorat
<br>

#### 11. Pentru a defini o lista ordonata a caror itemi sunt precedati de litere din alfabetul grec in CSS, se foloseste:
- [x] list-type: lower-greek
<br>

#### 12. Pentru a redirectiona automat browser-ul spre un nou URL, server-ul poate:
- [x] raspunde clientului cu un nou cod de raspuns de forma 3xx impreuna cu un header Location
- [x] redirectioneaza clientul folosind o secventa de cod in JavaScript de forma window.location = "http://url-nou"
- [x] trimite ca si continut HTML clientului un link de forma ```<a href="http://url-nou">``` si simuleaza din JavaScript un click de mouse pe acest link
<br>

#### 13. Care dintre urmatoarele tag-uri HTML sunt deprecated in HTML5:
- [x] center
- [x] font
<br>

#### 14. Cum se insereaza corect un fisier extern JavaScript denumit test.js intr-un document HTML?
- [x] ```<script src="test.js"></script>```
<br>

#### 15. Pentru inserarea de diacritice intr-un document HTML se pot folosi:
- [x] Editoare capabile sa salveze fisierul UTF-8 si specificarea acestui set de caractere in sectiunea head a documentului HTML
- [x] Entitati HTML
<br>

#### 16. Care sunt asemanarile si diferentele dintre atributele id si name?
- [x] doua elemente HTML pot avea acelasi nume, dar nu pot avea acelasi id
- [x] orice tag accepta atributul id, nu toate tagurile accepta atributul name
- [x] atributul id se foloseste pentru referirea unui element din CSS/JavaScript
<br>

#### 17. Dandu-se doua variable $a si $b, cum se poate interschimba valoarea acestora in PHP?
- [x] ```list($a, $b) = ($b, $a);```
- [x] ```list($a, $b) = array($b, $a);```
<br>

#### 18. In JavaScript typeof 1/0 este NaN pentru ca:
- [x] type of 1 este Number si Number nu se poate imparti la 0, rezultatul fiind NaN
<br>

#### 19. Ce se intelege prin scop global in JavaScript?
- [x] obiectul window
<br>

#### 20. Aranjati in ordine, de la cea mai simpla si putin customizabila, la cea mai configurabila si parametrizabila urmatoarele functii care permit realizarea unui apel AJAX din jQuery:
- [x] ```load, $.get, $.ajax```
<br>

#### 21. Care este forma corecta de folosire a tag-ului img in cadrul unui document XHTML:
- [x] ```<img src="poza.jpg"/>```
<br>

#### 22. Care dintre urmatoarele reprezinta masuri pentru evitarea injectiilor SQL:
- [x] Verificari riguroase la nivelul backend-ului legate de validitatea datelor introduse precum si folosirea de biblioteci specializate pentru persistarea datelor (ORM-uri)
- [x] Folosirea la nivelul backend-ului de mecanisme de tipul "prepared statement"
<br>

#### 23. Ce face urmatoarea secventa de cod:
```js
	var content=$('li').html();
	$('li').append('<em> '+ content +'</em>');
```
- [x] introduce continutul primului list item dupa fiecare list item
<br>

#### 24. Care dintre urmatoarele afirmatii despre metoda HTTP POST sunt adevarate:
- [x] este recomandat a fi folosita pentru a submite un formular care contine un input de tip password
- [x] trebuie neaparat folosita pentru a submite un formular care contine un input de tip file
<br>

#### 25. Un formular care contine un input de tip file trebuie:
- [x] sa aiba specificat atributul enctype setat la multipart/form-data
- [x] submis prin metoda POST
<br>

#### 26. Fie doua variabile $a si $b in PHP ce contin siruri de caractere. Aceste doua siruri in PHP se pot concatena folosind:
- [x] ```$s = $a . $b;```
- [x] ```$s = "$a$b";```
<br>

#### 27. Pozitionarea relative este folosita pentru:
- [x] a pozitiona/muta un element in diferite directii relativ la pozitia sa normala
- [x] un container parinte care are elemente fiu pozitionate absolut
<br>

#### 28. Care dintre urmatoarele metode HTTP nu presupun trimiterea de continut dupa antete in cadrul unei cereri HTTP:
- [x] GET
- [x] HEAD
<br>

#### 29. In functie de context, in jQuery $(this) poate fi folosit pentru:
- [x] pentru a construi un wrapper jQuery in jurul obiectului window
- [x] a construi un wrapper jQuery in jurul obiectului pe care se apeleaza un eveniment in interiorul functiei de tratare a evenimentului
<br>
