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
- [x] ```$emptyArray = [];``` (recomandata)
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
- [x] strike
- [x] big/small
- [x] acronym
- [x] basefont
- [x] applet
- [x] frame, frameset
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

#### 30. Considerand urmatoarele elemente html:
```html
	<div class="info">John Doe</div>
	<div class="info number" id="age">25></div>
```
Ce selector CSS ar selecta doar cel de-al doilea div (cel cu continutul "25")?
- [x] ```.info.number```
<br>

#### 31. In ce conditii metoda send pe un obiect AJAX se apeleaza intotdeauna cu parametrul sirul vid?
- [x] Daca requestul AJAX se face prin GET
<br>

#### 32. Cum se ascund toate div-urile din pagina folosind jQuery?
- [x] ```$("div").css("visibility", "hidden")```
<br>

#### 33. Care dintre urmatoarele metode jQuery foloseste AJAX:
- [x] ```$.ajax, $.get, load```
<br>


#### 34. Care dintre urmatoarele afirmatii sunt adevarate:
- [x] MySQL Old Extension (mysql_*) nu suporta "prepared statement"-uri, dar permite evitarea injectiilor SQL.
<br>

#### 35. In PHP return este folosit pentru:
- [x] a termina scriptul curent care se executa si a reda controlul executiei unui eventual script care l-a inclus pe scriptul curent cu include sau require
- [x] a termina executia unei functii
<br>

#### 36. Pe ce nivel al stivei TCP/IP se situeaza HTTP?
- [x] Aplicatie
<br>

#### 37. Care sunt moduri valabile de a introduce CSS in HTML:
- [x] inline
- [x] interne
- [x] externe
<br>

#### 38. In ce ordine au sens apelarile metodelor daca resursa nu exista in momentul actual:
- [x] post, put, get, delete
<br>

#### 39. Care dintre tagurile de mai jos au display: block by default:
- [x] ```<div>```
- [x] ```<p>```
- [x] ```<h1>```
<br>

#### 40. Care HTTP status code anunta o eroare:
- [x] 4xx
- [x] 5xx
<br>

#### 41. Care dintre metodele HTTP urmatoare sunt idempotente:
- [x] GET
- [x] HEAD
- [x] DELETE
- [x] PUT
<br>

#### 42. Care dintre metodele HTTP urmatoare sunt cacheable:
- [x] GET
- [x] HEAD
<br>

#### 43. Care sunt headere valide:
- [x] Host
- [x] User-agent
- [x] Content-length
- [x] From
<br>

#### 44. Care dintre urmatoarele sunt atribute ale unui cookie:
- [x] Name
- [x] Value
- [x] Expires
- [x] Max-age
<br>

#### 45. Ce poate semnifica un status code de tip 4xx:
- [x] Bad request
- [x] Unauthorized
<br>

#### 46. Care este diferenta dintre let si var:
- [x] variabilele definite cu let pot avea scop de tip bloc, iar cele cu var nu
- [x] variabilele definite cu var pot fi redeclarate in acelasi bloc, iar cele cu let nu
<br>

#### 47. Care este diferenta intre =, == si ===:
- [x] = este folosit pentru a atribui o valoare unui operand, == pentru a compara valorile operanzilor, iar === pentru a compara si tipul si valoarea operanzilor
<br>

#### 48. Care sunt tipurile de scopuri in JavaScript:
- [x] global scope
- [x] function scope
- [x] block scope
<br>

#### 49. Pentru ce este folosit keyword-ul this in JavaScript:
- [x] refera obiectul window (global)
- [x] cand este folosit intr-o metoda a unui obiect, refera obiectul curent
- [x] intr-o functie obisnuita refera obiectul window
- [x] intr-un eveniment refera obiectul pe care s-a apelat evenimentul
<br>

#### 50. Un apel AJAX este in starea 2 daca:
- [x] s-a facut send dar inca nu a sosit raspunsul de la server
<br>

#### 51. Elementul ```<th>``` trebuie folosit in cadrul unui tabel pentru:
- [x] definirea unei celule avand semnificatia de celula ce face parte din header-ul tabelului
<br>


#### 52. Cum se declara corect un array in JavaScript?
- [x] var studenți = ["Mihai", "Cristina", "Paula", "Dan"]
<br>

#### 53. Pentru evitarea injectiilor SQL in PHP 7 se recomanda:
- [x] Folosirea de "prepared statement"-uri
<br>


#### 54. Injectiile JavaScript se datoreaza:
- [x] Validarii insuficiente server-side la nivelul scriptului ce prelucreaza datele din formular
<br>


#### 55. Unde se poate defini un stil CSS pentru o anumita clasa?
- [x] in interiorul tag-ului ```<style>```, localizat in antetul paginii html
- [x] intr-un fisier extern specificat cu ajutorul tag-ului ```<link>```
<br>


#### 56. Pentru a verifica succesul unui apel AJAX trebuie ca:
- [x] readyState sa fie 4 si request.status 200
<br>

#### 57. Care dintre urmatoarele elemente au toate display-ul implicit block?
- [x] ```div, p, ul, ol, h1```
<br>

#### 58. Unde se poate insera cod JavaScript in cadrul unui document HTML?
- [x] atat in sectiunea ```<head>``` cat si ```<body>```
<br>

#### 59. Fie urmatoarea secventa de cod HTML/CSS. Pe ce fundal va fi afisat textul Cocosul canta?
```html
	<style type="text/css">
		#id2 {
			background-color: blue;
		}

		div #id1 .class2 {
			background-color: green;
		}
		div .class1 #id2 {
			background-color: yellow;
		}

		#id1 {
			background-color: red;
		}
	</style>
	<div>
		<div class="class1" id="id1">
			<div class="class2" id="id2">
				Cocosul canta
			</div>
		</div>
	</div>
```
- [x] Galben
<br>


#### 60. Care dintre urmatoarele functii PHP este folosita pentru a preveni vulnerabilitatile de tip Cross-Site Scripting (XSS)?
- [x] htmlentities
<br>

#### 61. Cum se poate "fura" un cookie de sesiune al unui alt utilizator?
- [x] Prin intermediul unui cod JavaScript injectat de catre atacator
- [x] Prin lipsa invalidarii sesiunii (logout) si navigarea in continuarea pe un site malitios
- [x] Prin interceptarea datelor la nivelul retelei de transport in lipsa folosirii unei conexiuni sigure
<br>

#### 62. Care dintre urmatoarele vulnerabilitati ar putea fi exploatata pentru a fura sesiunea unui utilizator autentificat?
- [x] Cross-Site Request Forgery (CSRF)
- [x] Cross-Site scripting (XSS)
<br>

#### 63. Ce se va afisa in consola browserului dupa executarea urmatorului cod JavaScript?
- [x] 1 == true
<br>

#### 64. Raspunsul sosit printr-un apel AJAX poate fi:
- [x] un fisier text
- [x] un fisier JSON
- [x] un fisier XML
- [x] un fisier JavaScript ???
<br>

#### 65. Care dintre urmatoarele categorii de aplicatii se pot folosit de DOCTYPE pentru a "intelege" mai bine documentul HTML?
- [x] Editoare si medii IDE (Integrated Development Environment)
- [x] Motoare de cautare
- [x] Browsere
<br>

#### 66. Care dintre informatiile de mai jos despre atributele readonly si disabled sunt adevarate?
- [x] valoarea unui input readonly se trimite serverului la submit, pe cand cea a unui input disabled nu se trimite serverului
<br>

#### 67. Care dintre urmatoarele elemente au toate display-ul implicit inline?
- [x] ```img, span, b, i, a```
<br>

#### 68. Care dintre urmatoarele informatii despre tagul ```<title>``` sunt adevarate?
- [x] este afisat in bara de titlu sau de bookmarks (favorite)
<br>

#### 69. Care dintre urmatoarele antete sunt obligatorii pentru o cerere HTTP in cazul folosirii protocolului HTTP/1.1:
- [x] Host
<br>

#### 70. Care dintre urmatoarele afirmatii sunt adevarate:
- [x] o definitie de stil aplicata clasei "bate" ca prioritate definitia de stil aplicata pe "tag"
- [x] o proprietate din cadrul unui stil inline suprascrie o proprietate dintr-o definitie de stil aplicata elementului folosind un selector bazat pe id
<br>

#### 71. Ce face functia ```session_start()``` in PHP?
- [x] Daca este vorba de o sesiune noua, genereaza un cookie aleator de sesiune pe care il trimite folosind antetul HTTP clientului
- [x] Daca este vorba de o sesiune veche, determina despre ce sesiune este vorba pe baza valorii cookie-ului de sesiune prin intermediul antetului HTTP Cookie si populeaza tabloul ```$_SESSION``` in mod corespunzator
<br>

#### 72. Care dintre urmatoarele declaratii este corecta pentru definirea tabloului $fructe in PHP?
- [x] ```$fructe=array("struguri", "mere", "pere");```
<br>

#### 73. Unde se poate folosi functia header in PHP?
- [x] in primul scriptlet din fisierul PHP si doar cu conditia ca scriptul PHP sa nu fi trimis anterior spre browser orice forma de continut (cu exceptia unor eventuale antete)
<br>

#### 74. Care dintre urmatoarele informatii despre un URL accesat prin POST sunt adevarate:
- [x] Reaccesarea URL-ului respectiv prin reload (refresh) la pagina presupune o confirmare din partea utilizatorului
<br>

#### 75. Care dintre urmatoarele sunt adevarate despre un server web:
- [x] un server web poate fi configurat sa accepte cereri prin protocolul HTTP pe portul 443
- [x] implicit un server web asteapta cereri prin protocolul HTTP pe portul 80 si cereri prin protocolul HTTPS pe portul 443
<br>

#### 76. Dandu-se doua containere, unul parinte si unul fiu, care dintre urmatoarele pozitionarii are/au sens:
- [x] pozitionarea unui fiu "absolute" in cadrul unui parinte cu pozitionare "relative"
<br>

#### 77. Cum se introduc comentarii intr-un scriptlet PHP?
- [x] ```//```
- [x] ```/*...*/```
- [x] ```#```
<br>

#### 78. Functia specificata ca si valoare pentru proprietatea onreadystatechange se apeleaza:
- [x] Este posibil sa se apeleze si atunci cand obiectul nu isi schimba starea dar continua sa vina raspuns de la server
- [x] Atunci cand obiectul AJAX isi schimba starea
<br>

#### 79. Conectarea la o baza de date intr-o aplicatie web Java se recomanda a fi facuta:
- [x] La fiecare request in cadrul metodei doGet sau doPut
<br>

#### 80. Care dintre urmatoarele expresii jQuery se pot folosi interschimbabil?
- [x] ```$(ready(function() {})) cu $(document).ready(function() {})```
<br>

#### 81. Care dintre urmatoarele reprezinta masuri pentru evitarea vulnerabilitatilor de tip XSS:
- [x] Inlocuirea anumitor caractere din datele primite de la client cu entitatile HTML corespunzatoare
<br>

#### 82. Care dintre urmatoarele tag-uri este folosit pentru definirea de stiluri CSS interne?
- [x] style
<br>

#### 83. Care dintre sintaxele CSS de mai jos este corecta/sunt corecte?
- [x] ```body{color:#abc}```
- [x] ```body{color:yellow}```
<br>

#### 84. O baza de date embedded in cadrul unei aplicatii web Java se recomanda a fi memorata:
- [x] In folderul WEB-INF al aplicatiei web intrucat acesta nu este accesibil de catre un client web
- [x] Oriunde alt undeva in cadrul sistemului de fisiere dar nu in cadrul directorului aplicatiei web intrucat de acolo baza de date ar putea fi accesata de catre clientii web
<br>

#### 85. In care element HTML se plaseaza codul JavaScript?
- [x] ```<script>```
<br>

#### 86. In cate instante se instantiaza un servlet?
- [x] Intr-o singura instanta
<br>

#### 87. Parametrii de configurare ai unei aplicatii web Java sunt preluati din fisierul de configurare ai aplicatiei web in cadrul metodei:
- [x] ```init()```
<br>

#### 89. O sesiune intr-o aplicatie web Java se termina cu:
- [x] ```session.invalidate()```
<br>

#### 90. Ce eveniment se genereaza la un click de mouse pe un element din cadrul documentului?
- [x] onclick
<br>

#### 91. Care dintre urmatoarele expresii jQuery se pot folosi interschimbabil?
- [x] ```$("#myelem")[0]``` si ```document.getElementById("myelem")```
- [x] ```$("#myelem")``` si ```$(document.getElementById("myelem"))```
- [x] ```$``` si ```jQuery```
<br>

#### 92. Care dintre urmatoarele reprezinta specificatii ale unor metode din API-ul jQuery?
- [x] ca pot fi apelate atat in mod sincron cat si in mod asincron
- [x] ca intorc referinta la obiectul pe care au fost apelate
- [x] ca pot fi folosite atat ca functii Setter cat si ca functii Getter
<br>

#### 93. Cum se afiseaza un mesaj prin intermediul unei ferestre de dialog modale in JavaScript?
- [x] ```alert("Mesaj")```
<br>

#### 94. Ce face urmatoarea secventa de cod:
```js
	$('ul:has(li)').addClass('patrat').addClass('deplasat').addClass('colorat');
```
- [x] selecteaza listele neordonate care au cel putin un element si le adauga clasele patrat, deplasat, colorat
<br>

#### 95. Un client face o cerere iar serverul ii raspunde cu '404 Not found'. Care dintre urmatoarele afirmatii sunt adevarate:
- [x] Chiar daca nu a gasit fisierul cerut de client, serverul ii poate da totusi acestuia un anumit continut HTML
<br>

#### 96. Care dintre urmatoarele sunt prefixe acceptate pe unele browsere pentru proprietatile CSS experimentale?
- [x] ```-webkit```
- [x] ```-o-```
- [x] ```-moz-```
- [x] ```-ms-```
<br>

#### 97. Care dintre urmatoarele sunt scriptlet-uri valide in PHP?
- [x] ```<? ?```, cu conditia setarii unei optiuni de configurare in php.ini
- [x] ```<?php ?>```
<br>

#### 98. Care dintre urmatoarele cuvinte/caractere nu sunt rezervate in JavaScript si se pot folosi ca si nume de variabile?
- [x] $, a, b
<br>

#### 99. Pentru a centra un element cu display-ul block in cadrul unui alt container se foloseste:
- [x] ```margin: 0 auto```
<br>

#### 100. Care dintre urmatoarele metode HTTP nu presupun trimiterea de continut dupa antete in cadrul unui raspuns HTTP:
- [x] HEAD
<br>

#### 101. Care dintre urmatoarele afirmatii sunt adevarate: (de verificat)
- [x] o definitie de stil aplicata clasei "bate" ca prioritate definita de stil aplicata pe "tag"
- [x] o proprietate din cadrul unui stil inline suprascrie o proprietate dintr-o definitie de stil aplicata elementului unui selector bazat pe id
<br>

#### 102. Care dintre urmatoarele reprezinta proprietati membre ale unui obiect de tipul XMLHttpRequest:
- [x] readyState, response, responseText, status
<br>

#### 103. Un client face o cerere iar serverul ii raspuinde cu "404 Not Found". Care dintre urmatoarele afirmatii sunt adevarate:
- [x] Chiar daca nu a gasit fisierul cerut de client, serverul ii poate da totusi acestuia un anumit continut HTML
<br>

#### 104. O variabila x ce contine valoarea numerica 7 poate fi declarata in JavaScript astfel:
- [x] ```var x = 7```
- [x] ```x = new Number(7)```
- [x] ```let x = 7```
- [x] ```x = 7```
<br>

#### 105. In care element HTML se plaseaza codul JavaScript?
- [x] ```<script>```
<br>

#### 106. Care dintre urmatoarele informatii despre plugin-urile jQuery sunt adevarate:
- [x] Permit extinderea functionalitatii API-ului standard jQuery cu noi metode si functionalitati
- [x] Unele plugin-uri jQuery permit incadrarea librariei de pe diversele CDN-uri (Content Delivery Network)
<br>

#### 107. Care dintre urmatoarele reprezinta un avantaj al metodei GET fata de POST?
- [x] Permite salvarea raspunsului ca bookmark
<br>

#### 108. Cum se pot obtine parametrii in backend in conditiile in care urmatoarea ancora este apasata?
```html
<a href="www.siteulmeu.com?addFav=1">Adauga la favorite</a>
```
- [x] ```$_GET[“addFav”]```
<br>

#### 109. In care dintre urmatoarele limbaje este posibilia crearea unei animatii care sa apara pe ecranul utilizatorului?
- [x] CSS
- [x] JavaScript
<br>

#### 110. Ce trebuie adaugat urmatoruli cod HTML pentru a fi corect?
```html
	<table style="width:100%"> 
		<tr> 
			<th>Company</th> 
			<th>Contract</th> 
			<th>Country</th>
		</tr> 
		<tr>
			<td>Alfreds</td>
			<td>Maria</td>
			<td>Germany</td>
		</tr>
	</table>
```
- [x] Nimic, tabelul se afiseaza
<br>

#### 111. Carui fisier i se trimit datele cand se da submit la urmatorul formular?
```html
	<form>
		<input type=”text” id=”fname” name=”fname”><br>
		<input type=”text” id=”lname” name=”lname”><br><br>
		<input type=”submit” value=”Submit”>
	</form>
```
- [x] Datele nu se trimit deloc
<br>

#### 112. Care este un query string posibil daca se da submit la urmatorul formular?
```html
	<form>
		<input type=”text” id=”fname” name=”fname”><br>
		<input type=”text” id=”lname”><br>
		<input type=”email” id=”email” name=”email” validate><br>
		<input type=”submit” value=”Submit”>
	</form>
```
- [x] "fname=Ion&email=ionpopescu@gmail.com"
<br>

#### 113. Unde se va putea deschide resursa ceruta de urmatoarea ancora?
```html
<a href="www.google.com" target="nume1" />
```
- [x] Intr-un ```<iframe>``` cu numele "nume1" 
- [x] Intr-un nou tab sau in acelasi tab in care s-a deschis la apasarea trecuta
<br>

#### 114. Cum este posibil sa existe 2 butoane de submit intr-un formular?
- [x] Doua input-uri submit cu nume diferite
<br>

#### 115. Care spatiu va ocupa pe latime un div daca i se aplica urmatorul stil, iar fereastra browser-ului are o latime de 1920px?
```css
	div {
		width: 100px;
		height: 120px;
		margin: 10px;
		border: 1px solid #4CAF50;
		padding: 10px;
	}
```
- [x] 140px
<br>

#### 116. Care este motivul de utilizare al sprite-urilor?
- [x] Reducerea numarului de request-uri
<br>

#### 117. Care va fi culoarea si inaltimea div-ului cu id-ul “id1” daca sunt definite urmatoarele stiluri?
```html
	<style>
		#id1 {
			height: 100px;
			background-color: red;
		}
	</style>
		#id1 {
			background-color: blue;
		}
	<style>
	</style>
```
- [x] culoare = blue, inaltime = 100px
<br>
