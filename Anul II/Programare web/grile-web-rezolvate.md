## Grile Web - Solutii

#### 1. Un apel AJAX se poate face catre o resursa statica oferita de end-point-ul de pe server?
- [ ] Doar daca in QUERY_STRING / body-ul POST-ului se trimit spre server si parametri
- [x] ___Da, intotdeauna___
- [ ] Nu, niciodata
<br>

#### 2. #RRAABB este un cod de culoare valid?
- [ ] Nu, deoarece codul de culoare hexazecimal trebuie sa contina inca doua cifre pentru opacitate
- [ ] Da, deoarece valorile sunt specificate in baza 16
- [ ] Da, deoarece RR specifica cantitatea de rosu, AA cantitatea de verde si BB cantitatea de albastru
- [x] ___Nu, deoarece valorile nu sunt specificate in baza 16___
<br>

#### 3. Care dintre urmatoarele afirmatii referitoare la filtrele de vizibilitate sunt adevarate?
- [x] ___Selectorul ```:hidden``` se foloseste pentru a selecta toate elementele ascunse in pagina___
- [ ] Selectorul ```:visible``` se foloseste pentru a selecta elementele care au ```display:none``` sau ```width/height: 0```
- [x] ___Selectorul ```:visible``` se foloseste pentru a selecta toate elementele care ocupa spatiu in pagina___
- [ ] Selectorul ```:hidden``` se foloseste pentru a selecta toate elementele care ocupa spatiu in pagina
- [ ] Selectorul ```:visible``` se foloseste pentru a selecta elementele care au ```visibility: hidden``` si ```opacity: 0```
<br>

#### 4. Ce indica un cod de raspuns de forma 3xx trimis prin intermediul protocolului HTTP de un server web?
- [x] ___mutarea documentului cerut la o alta adresa___
- [ ] o eroare efectuata de client
- [x] ___redirecteaza clientul spre alt URL___
- [ ] o eroare aparuta pe partea de server
<br>

#### 5. De pe client se doreste salvarea unor date despre o persoana (numele si varsta acesteia) folosind un apel AJAX realizat prin metoda HTTP GET. Care dintre urmatoarele apeluri realizeaza acest lucru:
- [x] ___```$.get("save.php", {nume: 'Ion', varsta:10})```___
- [x] ___```$.get("save.php?nume=Ion&varsta=10")```___
- [x] ___```$.get("save.php", 'nume=Ion&varsta=10')```___
<br>

#### 6. Ce face urmatoarea secventa de cod:
```js
	$('li:first').addClass('patrat').addClass('deplasat').addClass('colorat');
```
- [ ] selecteaza toate listele si le adauga clasele patrat, deplasat, colorat
- [ ] selecteaza primul element din fiecare lista si ii adauga clasele patrat, deplasat, colorat
- [ ] selecteaza toate elementele din liste si le adauga clasele patrat, deplasat, colorat
- [x] ___selecteaza primul li si ii adauga clasele patrat, deplasat, colorat___
<br>

#### 7. Un URL de pe back-end poate fi invocat (cerut) atat prin GET cat si prin POST:
- [ ] Nu
- [x] ___Da___
- [ ] Doar daca datele primite fie prin GET fie prin POST sunt aceleasi (parametrii trimisi sunt aceeasi)
<br>

#### 8. Un fisier PHP poate fi executat:
- [x] ___In linia de comanda folosind interpretorul php.exe pe Windows sau php pe Linux___
- [ ] De catre browser
- [ ] De catre interpretorul de comenzi al sistemului de operare pe care este instalata stiva AMP
- [ ] De catre un modul din cadrul serverului web
<br>

#### 9. Cum se declara un array vid in PHP:
- [x] ___```$emptyArray = [];```___ (recomandata in versiunile mai noi)
- [x] ___```$emptyArray = array();```___
- [ ] ```$emptyArray = null;```
- [ ] ```$emptyArray = ();```
<br>

#### 10. Ce face urmatoarea secventa de cod:
```js
	$(':not(p)').addClass('patrat').addClass('colorat');
```
- [x] ___selecteaza toate elementele cu exceptia paragrafelor si le adauga clasele patrat si colorat___
- [ ] selecteaza toate elementele care au clasa patrat si clasa colorat cu exceptia paragrafelor
- [ ] selecteaza toate elementele cu exceptia paragrafelor care au clasa patrat si clasa colorat
- [ ] selecteaza toate paragrafele care au clasa patrat si clasa colorat
<br>

#### 11. Pentru a defini o lista ordonata a caror itemi sunt precedati de litere din alfabetul grec in CSS, se foloseste:
- [x] ___list-style-type: lower-greek___
- [ ] list-type: lower-greek
- [ ] list: lower-greek
<br>

#### 12. Pentru a redirectiona automat browser-ul spre un nou URL, server-ul poate:
- [x] ___raspunde clientului cu un nou cod de raspuns de forma 3xx impreuna cu un header Location___
- [x] ___redirectioneaza clientul folosind o secventa de cod in JavaScript de forma ```window.location = "http://url-nou"```___
- [ ] include noul URL direct pe back-end folosind o directiva ```include```
- [x] ___trimite ca si continut HTML clientului un link de forma ```<a href="http://url-nou">``` si simuleaza din JavaScript un click de mouse pe acest link___
<br>

#### 13. Care dintre urmatoarele tag-uri HTML sunt deprecated in HTML5:
- [x] ___center___
- [x] ___font___
- [ ] b
- [ ] body
#### alte tag-uri deprecated: ```strike, big/small, acronym, basefont, applet, frame, frameset```
<br>

#### 14. Cum se insereaza corect un fisier extern JavaScript denumit test.js intr-un document HTML?
- [ ] ```<script name="test.js"></script>```
- [ ] ```<script src="test.js">```
- [ ] ```<script href="test.js">```
- [x] ___```<script src="test.js"></script>```___
<br>

#### 15. Pentru inserarea de diacritice intr-un document HTML se pot folosi:
- [x] ___Editoare capabile sa salveze fisierul UTF-8 si specificarea acestui set de caractere in sectiunea head a documentului HTML___
- [ ] Tastatura setata pe limba romana si specificarea atributului lang="ro-RO" la tagul HTML
- [x] ___Entitati HTML___
<br>

#### 16. Care sunt asemanarile si diferentele dintre atributele id si name?
- [ ] atributul name se foloseste pentru referirea unui element din CSS/JavaScript
- [x] ___doua elemente HTML pot avea acelasi nume, dar nu pot avea acelasi id___
- [x] ___orice tag accepta atributul id, nu toate tagurile accepta atributul name___
- [ ] orice tag accepta atributul name, nu toate tagurile accepta atributul id
- [ ] doua elemente HTML pot avea acelasi id, dar nu pot avea acelasi nume
- [x] ___atributul id se foloseste pentru referirea unui element din CSS/JavaScript___
<br>

#### 17. Dandu-se doua variable $a si $b, cum se poate interschimba valoarea acestora in PHP?
- [x] ___```list($a, $b) = ($b, $a);```___
- [ ] ```array($a, $b) = ($b, $a);```
- [ ] ```$a = $b; $b = $a;```
- [ ] ```array($a, $b) = ($b, $a);```
- [ ] ```list($a, $b) = ($b, $a);```
- [ ] ```array($a, $b) = array($b, $a);```
- [ ] ```array($a, $b) = list($b, $a);```
- [x] ___```list($a, $b) = array($b, $a);```___
- [ ] ```list($a, $b) = list($b, $a);```
<br>

#### 18. In JavaScript typeof 1/0 este NaN pentru ca:
- [ ] type of 1/0 nu are rezultatul NaN, ci Infinity
- [x] ___type of 1 este Number si Number nu se poate imparti la 0, rezultatul fiind NaN___
- [ ] 1/0 este egal cu Infinity si typeof Infinity este NaN
- [ ] 1/0 este NaN si typeof NaN este NaN
<br>

#### 19. Ce se intelege prin scop global in JavaScript?
- [x] ___obiectul window___
- [ ] obiectul document
- [ ] variabila this
- [ ] scopul imediat exterior celui in care este declarata o functie
<br>

#### 20. Aranjati in ordine, de la cea mai simpla si putin customizabila, la cea mai configurabila si parametrizabila urmatoarele functii care permit realizarea unui apel AJAX din jQuery:
- [ ] ```$get, load, $.post```
- [x] ___```load, $.get, $.ajax```___
- [ ] ```$post, load, $.ajax```
- [ ] ```$.ajax, load, $.get```
<br>

#### 21. Care este forma corecta de folosire a tag-ului img in cadrul unui document XHTML:
- [ ] ```<img>poza.jpg</img>```
- [x] ___```<img src="poza.jpg"/>```___
- [ ] ```<img src="poza.jpg"></img>```
- [ ] ```<img src="poza.jpg">```
<br>

#### 22. Care dintre urmatoarele reprezinta masuri pentru evitarea injectiilor SQL:
- [x] ___Verificari riguroase la nivelul backend-ului legate de validitatea datelor introduse precum si folosirea de biblioteci specializate pentru persistarea datelor (ORM-uri)___
- [ ] Dezactivarea in cadrul aplicatiei Web a posibilitatii rularii de cod SQL de catre browser
- [ ] Verificari riguroase la nivelul browserului legate de validitatea datelor introduse
- [x] ___Folosirea la nivelul backend-ului de mecanisme de tipul "prepared statement"___
<br>

#### 23. Ce face urmatoarea secventa de cod:
```js
	var content=$('li').html();
	$('li').append('<em> '+ content +'</em>');
```
- [ ] introduce continutul primului list item inaintea fiecarui list item
- [ ] continutul din toate li-urile vor fi scrise cu italic
- [ ] introduce content dupa primul list item
- [x] ___introduce continutul primului list item dupa fiecare list item___
- [ ] continutul din primul li va fi scris cu italic
<br>

#### 24. Care dintre urmatoarele afirmatii despre metoda HTTP POST sunt adevarate:
- [ ] trebuie neaparat folosita pentru a submite un formular care contine un input de tip video
- [x] ___este recomandat a fi folosita pentru a submite un formular care contine un input de tip password___
- [x] ___trebuie neaparat folosita pentru a submite un formular care contine un input de tip file___
<br>

#### 25. Un formular care contine un input de tip file trebuie:
- [x] ___sa aiba specificat atributul enctype setat la multipart/form-data___
- [x] ___submis prin metoda POST___
- [ ] sa aiba specificat atributul accept care specifica tipul fisierelor ce se pot trimite la server
- [ ] sa aiba specificat atributul content care sa indice spre continutul fisierului
- [ ] submis prin metoda GET
<br>

#### 26. Fie doua variabile $a si $b in PHP ce contin siruri de caractere. Aceste doua siruri in PHP se pot concatena folosind:
- [ ] ```$s = $a + $b```
- [x] ___```$s = $a . $b;```___
- [x] ___```$s = "$a$b";```___
- [ ] ```$s = '$a$b';```
<br>

#### 27. Pozitionarea relative este folosita pentru:
- [x] ___a pozitiona/muta un element in diferite directii relativ la pozitia sa normala___
- [ ] a pozitiona un element relativ la obiectul document
- [ ] a pozitiona un element relativ la fereastra browserului (obiectul window)
- [x] ___un container parinte care are elemente fiu pozitionate absolut___
<br>

#### 28. Care dintre urmatoarele metode HTTP nu presupun trimiterea de continut dupa antete in cadrul unei cereri HTTP:
- [x] ___GET___
- [ ] POST
- [ ] PUT
- [x] ___HEAD___
<br>

#### 29. In functie de context, in jQuery ```$(this)``` poate fi folosit pentru:
- [ ] a returna obiectul JavaScript de baza in jurul caruia este construit obiectul jQuery curent
- [ ] a construi un wrapper jQuery in jurul documentului
- [x] ___a construi un wrapper jQuery in jurul obiectului window___
- [x] ___a construi un wrapper jQuery in jurul obiectului pe care se apeleaza un eveniment in interiorul functiei de tratare a evenimentului___
<br>

#### 30. Considerand urmatoarele elemente html:
```html
	<div class="info">John Doe</div>
	<div class="info number" id="age">25></div>
```
Ce selector CSS ar selecta doar cel de-al doilea div (cel cu continutul "25")?
- [x] ___```.info.number```___
- [ ] ```.info .number```
- [ ] ```.info #age```
- [ ] ```.info[id]```
<br>

#### 31. In ce conditii metoda ```send``` pe un obiect AJAX se apeleaza intotdeauna cu parametrul sirul vid?
- [x] ___Daca requestul AJAX se face prin GET___
- [ ] Daca requestul AJAX se face prin HTTP
- [ ] Metoda ```send``` nu se poate apela cu parametrul sirul vid
<br>

#### 32. Cum se ascund toate div-urile din pagina folosind jQuery?
- [ ] ```$("div").hidden()```
- [ ] ```$("div").visibility(false)```
- [x] ___```$("div").css("visibility", "hidden")```___
- [ ] ```$("div").css("visibility", "hide")```
<br>

#### 33. Care dintre urmatoarele metode jQuery folosesc AJAX:
- [x] ___```$.ajax, $.get, load```___
- [ ] ```$.post, $.request, load```
- [ ] ```$.ajax, $.get, $.post, $.request```
- [ ] ```$.get, load, unload```
<br>

#### 34. Care dintre urmatoarele afirmatii sunt adevarate:
- [x] ___MySQL Old Extension (mysql_*) nu suporta "prepared statement"-uri, dar permite evitarea injectiilor SQL___
- [ ] MySQL Improved Extension (mysqli_*) asigura in plus fata de PDO independenta fata de sistemul de gestiune a bazelor de date folosit
- [ ] MySQL Improved Extension (mysqli_*) asigura in plus fata de PDO posibilitatea folosirii de "prepared statement"-uri
<br>

#### 35. In PHP ```return``` este folosit pentru:
- [x] ___a termina scriptul curent care se executa si a reda controlul executiei unui eventual script care l-a inclus pe scriptul curent cu ```include``` sau ```require```___
- [ ] a termina executia logicii ce se executa pe server si a trimite raspunsul complet clientului
- [ ] a trimite clientului un anumit raspuns in urma cererii facute de acesta
- [x] ___a termina executia unei functii___
<br>

#### 36. Pe ce nivel al stivei TCP/IP se situeaza HTTP?
- [x] ___Aplicatie___
- [ ] Internet
- [ ] Legatura de date
- [ ] Transport
<br>

#### 37. Care sunt moduri valabile de a introduce CSS in HTML:
- [x] ___inline___
- [x] ___interne___
- [x] ___externe___
<br>

#### 38. In ce ordine au sens apelarile metodelor daca resursa nu exista in momentul actual:
- [x] ___post, put, get, delete___
<br>

#### 39. Care dintre tagurile de mai jos au display: block by default:
- [x] ___```<div>```___
- [x] ___```<p>```___
- [x] ___```<h1>```___
<br>

#### 40. Care HTTP status code anunta o eroare:
- [x] ___4xx___
- [x] ___5xx___
<br>

#### 41. Care dintre metodele HTTP urmatoare sunt idempotente:
- [x] ___GET___
- [x] ___HEAD___
- [x] ___DELETE___
- [x] ___PUT___
<br>

#### 42. Care dintre metodele HTTP urmatoare sunt cacheable:
- [x] ___GET___
- [x] ___HEAD___
<br>

#### 43. Care sunt headere valide:
- [x] ___Host___
- [x] ___User-agent___
- [x] ___Content-length___
- [x] ___From___
<br>

#### 44. Care dintre urmatoarele sunt atribute ale unui cookie:
- [x] ___Name___
- [x] ___Value___
- [x] ___Expires___
- [x] ___Max-age___
<br>

#### 45. Ce poate semnifica un status code de tip 4xx:
- [x] ___Bad request___
- [x] ___Unauthorized___
<br>

#### 46. Care este diferenta dintre let si var:
- [x] ___variabilele definite cu let pot avea scop de tip bloc, iar cele cu var nu___
- [x] ___variabilele definite cu var pot fi redeclarate in acelasi bloc, iar cele cu let nu___
<br>

#### 47. Care este diferenta intre =, == si ===:
- [x] ___= este folosit pentru a atribui o valoare unui operand, == pentru a compara valorile operanzilor, iar === pentru a compara si tipul si valoarea operanzilor___
<br>

#### 48. Care sunt tipurile de scopuri in JavaScript:
- [x] ___global scope___
- [x] ___function scope___
- [x] ___block scope___
<br>

#### 49. Pentru ce este folosit keyword-ul this in JavaScript:
- [x] ___refera obiectul window (global)___
- [x] ___cand este folosit intr-o metoda a unui obiect, refera obiectul curent___
- [x] ___intr-o functie obisnuita refera obiectul window___
- [x] ___intr-un eveniment refera obiectul pe care s-a apelat evenimentul___
<br>

#### 50. Un apel AJAX este in starea 2 daca:
- [x] ___s-a facut send dar inca nu a sosit raspunsul de la server___
- [ ] s-a facut receive, dar nu s-a facut send
- [ ] s-a facut si send si receive, chiar inainte de close
- [ ] s-a facut open dar inca nu s-a facut send
<br>

#### 51. Elementul ```<th>``` trebuie folosit in cadrul unui tabel pentru:
- [ ] centrarea textului si bold-area continutului unei celule
- [x] ___definirea unei celule avand semnificatia de celula ce face parte din header-ul tabelului___
- [ ] definirea unui nou rand in tabel
<br>


#### 52. Cum se declara corect un array in JavaScript?
- [ ] var studenti = ("Mihai, "Cristina", "Paula", "Dan")
- [ ] var studenti = {"Mihai", "Cristina", "Paula", "Dan"}
- [ ] var studenti = "Mihai", "Cristina", "Paula", "Dan"
- [x] ___var studenti = ["Mihai", "Cristina", "Paula", "Dan"]___
<br>

#### 53. Pentru evitarea injectiilor SQL in PHP 7 se recomanda:
- [x] ___Folosirea de "prepared statement"-uri___
- [ ] Evitarea acestora folosind functia ```mysql_real_escape_string```
- [ ] Eliminarea ghilimelelor si apostroafelor din datele primite de la client
<br>

#### 54. Injectiile JavaScript se datoreaza:
- [ ] Folosirii protocolului http in locul protocolului https
- [ ] Validarii insuficiente chiar la nivelul codului JavaScript
- [ ] Unor buguri prezente la nivelul browserului web
- [x] ___Validarii insuficiente server-side la nivelul scriptului ce prelucreaza datele din formular___
<br>

#### 55. Unde se poate defini un stil CSS pentru o anumita clasa?
- [x] ___in interiorul tag-ului ```<style>```, localizat in antetul paginii html___
- [ ] inline, cu ajutorul atributului style aplicat pe un tag html
- [x] ___intr-un fisier extern specificat cu ajutorul tag-ului ```<link>```___
<br>

#### 56. Pentru a verifica succesul unui apel AJAX trebuie ca:
- [x] ___readyState sa fie 4 si request.status 200___
- [ ] readyState sa fie 4 si request.status 100
- [ ] readyState sa fie 1 si request.status 200
- [ ] readyState sa fie 0 si request.status 100
<br>

#### 57. Care dintre urmatoarele elemente au toate display-ul implicit block?
- [ ] ```ul, ol, p, img, div```
- [ ] ```ul, ol, p, table, input```
- [ ] ```input, div, p, form```
- [x] ___```div, p, ul, ol, h1```___
<br>

#### 58. Unde se poate insera cod JavaScript in cadrul unui document HTML?
- [ ] doar in sectiunea ```<body>```
- [ ] doar in sectiunea ```<head>```
- [x] ___atat in sectiunea ```<head>``` cat si ```<body>```___
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
- [ ] Rosu
- [ ] Verde
- [ ] Galben
- [ ] Albastru
<br>


#### 60. Care dintre urmatoarele functii PHP este folosita pentru a preveni vulnerabilitatile de tip Cross-Site Scripting (XSS)?
- [ ] ```mysqli_real_escape_string```
- [ ] ```htmlentities```
- [ ] ```filter_xss```
<br>

#### 61. Cum se poate "fura" un cookie de sesiune al unui alt utilizator?
- [ ] Prin intermediul unui cod JavaScript injectat de catre atacator
- [ ] Prin lipsa invalidarii sesiunii (logout) si navigarea in continuarea pe un site malitios
- [ ] Prin interceptarea datelor la nivelul retelei de transport in lipsa folosirii unei conexiuni sigure
<br>

#### 62. Care dintre urmatoarele vulnerabilitati ar putea fi exploatata pentru a fura sesiunea unui utilizator autentificat?
- [ ] Cross-Site Request Forgery (CSRF)
- [ ] SQL Injection
- [ ] Cross-Site scripting (XSS)
<br>

#### 63. Ce se va afisa in consola browserului dupa executarea urmatorului cod JavaScript?
```js
	if (1 === '1') {
		console.log("1 === '1'");
	} else if (1 == true) {
		console.log("1 == true");
	} else if (1 === 1.0) {
		console.log("1 === 1.0");
	}
```
- [ ] nimic
- [ ] 1 === 1.0
- [ ] 1 == true
- [ ] 1 === '1'
<br>

#### 64. Raspunsul sosit printr-un apel AJAX poate fi:
- [ ] un fisier text
- [ ] un fisier JSON
- [ ] un fisier XML
- [ ] un fisier JavaScript
<br>

#### 65. Care dintre urmatoarele categorii de aplicatii se pot folosit de DOCTYPE pentru a "intelege" mai bine documentul HTML?
- [ ] Servere web
- [ ] Editoare si medii IDE (Integrated Development Environment)
- [ ] Motoare de cautare
- [ ] Browsere
<br>

#### 66. Care dintre informatiile de mai jos despre atributele readonly si disabled sunt adevarate?
- [ ] valoarea unui input readonly se trimite serverului la submit, pe cand cea a unui input disabled nu se trimite serverului
- [ ] valoarea unui input readonly poate fi modificata din JavaScript, pe cand cea a unui input disabled nu poate fi editata nici din JavaScript
- [ ] atributele specifica acelasi lucru, faptul ca un input readonly sau disabled nu poate fi editat
<br>

#### 67. Care dintre urmatoarele elemente au toate display-ul implicit inline?
- [ ] ```a, span, b, i, li```
- [ ] ```img, span, b, i, a```
- [ ] ```p, a, b, i, span```
- [ ] ```b, i, li, span, img```
<br>

#### 68. Care dintre urmatoarele informatii despre tagul ```<title>``` sunt adevarate?
- [ ] este folosit in mare masura de catre motoarele de cautare
- [ ] este optional
- [ ] este afisat in bara de titlu sau de bookmarks (favorite)
- [ ] nu exista tag-ul ```<title``` ci doar atributul ```title```
<br>

#### 69. Care dintre urmatoarele antete sunt obligatorii pentru o cerere HTTP in cazul folosirii protocolului HTTP/1.1:
- [ ] Content-Type
- [ ] Host
- [ ] User-Agent
- [ ] Cookie
<br>

#### 70. Care dintre urmatoarele afirmatii sunt adevarate:
- [ ] definitiile de stil interne au prioritate inaintea celor externe
- [ ] o definitie de stil aplicata clasei "bate" ca prioritate definitia de stil aplicata pe "tag"
- [ ] o proprietate din cadrul unui stil inline suprascrie o proprietate dintr-o definitie de stil aplicata elementului folosind un selector bazat pe id
<br>

#### 71. Ce face functia ```session_start()``` in PHP?
- [ ] Daca este vorba de o sesiune noua, genereaza un cookie aleator de sesiune pe care il trimite folosind antetul HTTP clientului
- [ ] Initializeaza intotdeauna o noua sesiune
- [ ] Porneste sesiunea existenta deja si trimite clientului cookie-ul de sesiune prin intermediul antetului HTTP Cookie
- [ ] Daca este vorba de o sesiune veche, determina despre ce sesiune este vorba pe baza valorii cookie-ului de sesiune prin intermediul antetului HTTP Cookie si populeaza tabloul ```$_SESSION``` in mod corespunzator
<br>

#### 72. Care dintre urmatoarele declaratii este corecta pentru definirea tabloului ```$fructe``` in PHP?
- [ ] ```$fructe=array("struguri", "mere", "pere");```
- [ ] ```$fructe=("struguri, "mere", "pere");```
- [ ] ```$fructe="struguri", "mere", "pere";```
- [ ] ```$fructe={"struguri", "mere", "pere"};```
- [ ] ```$fructe=array["struguri", "mere", "pere"];```
<br>

#### 73. Unde se poate folosi functia header in PHP?
- [ ] in primul scriptlet din fisierul PHP si doar cu conditia ca scriptul PHP sa nu fi trimis anterior spre browser orice forma de continut (cu exceptia unor eventuale antete)
- [ ] in cadrul unui scriptlet PHP plasat in sectiunea documentului HTML generat de fisierul PHP
- [ ] in orice scriptlet din cadrul fisierului PHP
<br>

#### 74. Care dintre urmatoarele informatii despre un URL accesat prin POST sunt adevarate:
- [ ] Reaccesarea URL-ului respectiv prin reload (refresh) la pagina presupune o confirmare din partea utilizatorului
- [ ] URL-ului respectiv i se poate face bookmark (poate fi adaugat la favorite)
- [ ] URL-ul respectiv poate fi partajat (share) pe Facebook, Whatsapp, Skype, etc.
<br>

#### 75. Care dintre urmatoarele sunt adevarate despre un server web:
- [ ] un server web poate fi configurat sa accepte cereri prin protocolul HTTP pe portul 443
- [ ] un server web poate fi configurat sa accepte cereri printr-un URL de forma ```file://...```
- [ ] implicit un server web asteapta cereri prin protocolul HTTP pe portul 80 si cereri prin protocolul HTTPS pe portul 443
<br>

#### 76. Dandu-se doua containere, unul parinte si unul fiu, care dintre urmatoarele pozitionarii are/au sens:
- [ ] pozitionarea unui fiu "absolute" in cadrul unui parinte cu pozitionare "relative"
- [ ] pozitionarea unui fiu "relative" intr-un parinte cu pozitionare "virtual"
- [ ] pozitionarea unui fiu "flex" intr-un parinte "relative"
- [ ] pozitionarea unui fiu "fixed" intr-un parinte cu pozitionare "relative"
<br>

#### 77. Cum se introduc comentarii intr-un scriptlet PHP?
- [ ] ```//```
- [ ] ```<!-- -->```
- [ ] ```/*...*/```
- [ ] ```#```
<br>

#### 78. Functia specificata ca si valoare pentru proprietatea ```onreadystatechange``` se apeleaza:
- [ ] Este posibil sa se apeleze si atunci cand obiectul nu isi schimba starea dar continua sa vina raspuns de la server
- [ ] Atunci cand serverul schimba codul de raspuns (response code-ul) care e trimis clientului
- [ ] Atunci cand obiectul AJAX isi schimba starea
<br>

#### 79. Conectarea la o baza de date intr-o aplicatie web Java se recomanda a fi facuta:
- [ ] La initializarea aplicatiei web / a contextului
- [ ] La fiecare request in cadrul metodei ```doGet``` sau ```doPut```
- [ ] La pornirea containerului, o singura conexiune pentru toate aplicatiile web (din motive de performanta)
<br>

#### 80. Care dintre urmatoarele expresii jQuery se pot folosi interschimbabil?
- [ ] ```$(ready(function() {}))``` cu ```$(document).ready(function() {})```
- [ ] ```$(function() {})``` cu ```$(document).ready(function() {})```
- [ ] ```$(selector).each(function() {})``` cu ```$(selector.each).function() {}```
<br>

#### 81. Care dintre urmatoarele reprezinta masuri pentru evitarea vulnerabilitatilor de tip XSS:
- [ ] Verificari riguroase la nivelul browserului legate de validitatea datelor introduse
- [ ] Folosirea la nivelul browserului a unor biblioteci de functii JavaScript consacrate si testate anterior
- [ ] Inlocuirea anumitor caractere din datele primite de la client cu entitatile HTML corespunzatoare
- [ ] Dezactivarea din cadrul aplicatiei web a posibilitatii rularii de cod JavaScript de catre browser
<br>

#### 82. Care dintre urmatoarele tag-uri este folosit pentru definirea de stiluri CSS interne?
- [ ] script
- [ ] css
- [ ] style
- [ ] class
<br>

#### 83. Care dintre sintaxele CSS de mai jos este corecta/sunt corecte?
- [ ] ```body:color=red```
- [ ] ```{body: color=red}```
- [ ] ```body{color:#abc}```
- [ ] ```{body; color:blue}```
- [ ] ```body{color:yellow}```
<br>

#### 84. O baza de date embedded in cadrul unei aplicatii web Java se recomanda a fi memorata:
- [ ] In cadrul folderului app/databases/, unde app reprezinta directorul (numele) aplicatiei web
- [ ] In folderul WEB-INF al aplicatiei web intrucat acesta nu este accesibil de catre un client web
- [ ] Oriunde alt undeva in cadrul sistemului de fisiere dar nu in cadrul directorului aplicatiei web intrucat de acolo baza de date ar putea fi accesata de catre clientii web
<br>

#### 85. In care element HTML se plaseaza codul JavaScript?
- [ ] ```<javascript>```
- [ ] ```<js>```
- [ ] ```<script>```
<br>

#### 86. In cate instante se instantiaza un servlet?
- [ ] In nici una, un servlet este executat direct de catre container/application server
- [ ] Intr-o singura instanta
- [ ] Se creeaza o instanta separata la fiecare cerere facuta de catre un client
<br>

#### 87. Parametrii de configurare ai unei aplicatii web Java sunt preluati din fisierul de configurare ai aplicatiei web in cadrul metodei:
- [ ] ```init()```
- [ ] ```applicationCreated()```
- [ ] ```contextInitialized()```
<br>

#### 89. O sesiune intr-o aplicatie web Java se termina cu:
- [ ] ```session.destroy()```
- [ ] ```session.close()```
- [ ] ```session.invalidate()```
<br>

#### 90. Ce eveniment se genereaza la un click de mouse pe un element din cadrul documentului?
- [ ] onclick
- [ ] ondoubleclick
- [ ] onmouseover
- [ ] onmouseclick
<br>

#### 91. Care dintre urmatoarele expresii jQuery se pot folosi interschimbabil?
- [ ] ```$("#myelem")[0]``` si ```document.getElementById("myelem")```
- [ ] ```$("#myelem")``` si ```$(document.getElementById("myelem"))```
- [ ] ```$(document.myelem)``` si ```$(document.getElementById("myelem"))```
- [ ] ```$``` si ```jQuery```
- [ ] ```$(document).myelem``` si ```$("#myelem")[0]```
<br>

#### 92. Care dintre urmatoarele reprezinta specificatii ale unor metode din API-ul jQuery?
- [ ] ca pot fi apelate atat in mod sincron cat si in mod asincron
- [ ] ca intorc referinta la obiectul pe care au fost apelate
- [ ] ca pot fi apelate atat pe obiectul din DOM cat si pe wrapperul jQuery continut in jurul lui
- [ ] ca pot fi folosite atat ca functii Setter cat si ca functii Getter
<br>

#### 93. Cum se afiseaza un mesaj prin intermediul unei ferestre de dialog modale in JavaScript?
- [ ] ```modalMessage("Mesaj")```
- [ ] ```alertBox("Mesaj")```
- [ ] ```alert("Mesaj")```
- [ ] ```modalBox("Mesaj")```
<br>

#### 94. Ce face urmatoarea secventa de cod:
```js
	$('ul:has(li)').addClass('patrat').addClass('deplasat').addClass('colorat');
```
- [ ] selecteaza toate elementele din liste si le adauga clasele patrat, deplasat, colorat
- [ ] selecteaza listele neordonate care au cel putin un element si le adauga clasele patrat, deplasat, colorat
- [ ] selecteaza toate listele care au cel putin un element si le adauga clasele patrat, deplasat, colorat
- [ ] selecteaza listele ordonate care au cel putin un element si le adauga clasele patrat, deplasat, colorat
- [ ] selecteaza toate listele si le adauga clasele patrat, deplasat, colorat
<br>

#### 95. Un client face o cerere iar serverul ii raspunde cu '404 Not found'. Care dintre urmatoarele afirmatii sunt adevarate:
- [ ] Chiar daca nu a gasit fisierul cerut de client, serverul ii poate da totusi acestuia un anumit continut HTML
- [ ] Daca nu a gasit fisierul cerut, serverul nu ii mai poate returna clientului nimic dupa codul de raspuns 404
- [ ] Chiar daca serverul a raspuns cu "404 Not found", browserele raspund cu "200 OK" pentru a-i spune serverului ca au primit mesajul de eroare
<br>

#### 96. Care dintre urmatoarele sunt prefixe acceptate pe unele browsere pentru proprietatile CSS experimentale?
- [ ] ```-webkit```
- [ ] ```-o-```
- [ ] ```-moz-```
- [ ] ```-safari```
- [ ] ```-chrome-```
- [ ] ```-ms-```
<br>

#### 97. Care dintre urmatoarele sunt scriptlet-uri valide in PHP?
- [ ] ```<% %>```
- [ ] ```<?php></?>```
- [ ] ```<? ?>```, cu conditia setarii unei optiuni de configurare in php.ini
- [ ] ```<?php ?>```
- [ ] ```<?= ?>```
<br>

#### 98. Care dintre urmatoarele cuvinte/caractere nu sunt rezervate in JavaScript si se pot folosi ca si nume de variabile?
- [ ] this, a, b
- [ ] with, a, b
- [ ] $, a, b
- [ ] let, a, b
<br>

#### 99. Pentru a centra un element cu display-ul block in cadrul unui alt container se foloseste:
- [ ] ```align: center```
- [ ] ```margin: 0 auto```
- [ ] ```align: middle```
- [ ] ```text-align: center```
<br>

#### 100. Care dintre urmatoarele metode HTTP nu presupun trimiterea de continut dupa antete in cadrul unui raspuns HTTP:
- [ ] GET
- [ ] PUT
- [ ] POST
- [ ] HEAD
<br>

#### 101. Care dintre urmatoarele afirmatii sunt adevarate:
- [ ] definitiile de stil interne au prioritate inaintea celor externe (conteaza ordinea lor de definire)
- [ ] o definitie de stil aplicata clasei "bate" ca prioritate definita de stil aplicata pe "tag"
- [ ] o proprietate din cadrul unui stil inline suprascrie o proprietate dintr-o definitie de stil aplicata elementului unui selector bazat pe id
<br>

#### 102. Care dintre urmatoarele reprezinta proprietati membre ale unui obiect de tipul XMLHttpRequest:
- [ ] readyState, response, responseText, status
- [ ] state, request, response, status
- [ ] readyState, request, response, status
<br>

#### 103. O variabila x ce contine valoarea numerica 7 poate fi declarata in JavaScript astfel:
- [ ] ```var x = 7```
- [ ] ```var x:= 7```
- [ ] ```x = new Number(7)```
- [ ] ```let x = 7```
- [ ] ```x = 7```
<br>

#### 104. Care dintre urmatoarele informatii despre plugin-urile jQuery sunt adevarate:
- [ ] Unele plugin-uri permit portarea codului jQuery pe diferite browsere
- [ ] Permit extinderea functionalitatii API-ului standard jQuery cu noi metode si functionalitati
- [ ] Unele plugin-uri jQuery permit incadrarea librariei de pe diversele CDN-uri (Content Delivery Network)
- [ ] Unele plugin-uri permit rularea codului jQuery independent
<br>

#### 105. Care dintre urmatoarele reprezinta un avantaj al metodei GET fata de POST?
- [ ] Este mai buna pentru date confidentiale
- [ ] Permite salvarea raspunsului ca bookmark
- [ ] Nu are limita maxima de dimensiune
- [ ] Nu are avantaje
<br>

#### 106. Cum se pot obtine parametrii in backend in conditiile in care urmatoarea ancora este apasata?
```html
	<a href="www.siteulmeu.com?addFav=1">Adauga la favorite</a>
```
- [ ] ```$_GET[“addFav”]```
- [ ] ```$_SESSION["addFav"]```
- [ ] ```$_POST["addFav"]```
- [ ] Nu se trimit parametri
<br>

#### 107. In care dintre urmatoarele limbaje este posibilia crearea unei animatii care sa apara pe ecranul utilizatorului?
- [ ] HTML
- [ ] CSS
- [ ] JavaScript
- [ ] PHP
<br>

#### 108. Ce trebuie adaugat urmatorului cod HTML pentru a fi corect?
```html
	<table style="width:100%"> 
		<tr> 
			<th>Company</th> 
			<th>Contact</th> 
			<th>Country</th>
		</tr> 
		<tr>
			<td>Alfreds Futterkiste</td>
			<td>Maria Anders</td>
			<td>Germany</td>
			<td>Optional</td>
		</tr>
	</table>
```
- [ ] ```rowspan="2"``` in tagul ```<th>``` de la Country
- [ ] ```colspan="2"``` in tagul ```<th>``` de la Country
- [ ] Nimic, tabelul se afiseaza
- [ ] ```rowspan="2"``` si ```colspan="2"``` in tagul ```<th>``` de la Country
<br>

#### 109. Carui fisier i se trimit datele cand se da submit la urmatorul formular?
```html
	<form>
		<input type=”text” id=”fname” name=”fname”><br>
		<input type=”text” id=”lname” name=”lname”><br><br>
		<input type=”submit” value=”Submit”>
	</form>
```
- [ ] Datele nu se trimit deloc
- [ ] Scriptului de pe backend care afiseaza formularul
- [ ] Unui fisier setat intr-un fisier de configurare
<br>

#### 110. Care este un query string posibil daca se da submit la urmatorul formular?
```html
	<form>
		<input type=”text” id=”fname” name=”fname”><br>
		<input type=”text” id=”lname”><br>
		<input type=”email” id=”email” name=”email” validate><br>
		<input type=”submit” value=”Submit”>
	</form>
```
- [ ] ```"fname=Ion&lname=Popescu&email=ionpopescu@gmail.com"```
- [ ] ```"fname=Ion&email=ionpopescu@gmail.com"```
- [ ] ```"fname=Ion&lname=Popescu&email=ionpopescu"```
- [ ] ```"fname=Ion&email=ionpopescu"```
<br>

#### 111. Unde se va putea deschide resursa ceruta de urmatoarea ancora?
```html
	<a href="www.google.com" target="nume1" />
```
- [ ] Intr-un ```<iframe>``` cu numele "nume1" 
- [ ] Intr-un nou tab sau in acelasi tab in care s-a deschis la apasarea trecuta
- [ ] Nu se va deschide
<br>

#### 112. Cum este posibil sa existe 2 butoane de submit intr-un formular?
- [ ] Nu se poate
- [ ] Doua input-uri submit cu nume diferite
- [ ] Doua butoane dintre care unul dintre ele are setat atributul ```formaction``` catre alt fisier decat cel al formularului
<br>

#### 113. Cat spatiu va ocupa pe latime un div daca i se aplica urmatorul stil, iar fereastra browser-ului are o latime de 1920px?
```css
	div {
		width: 100px;
		height: 120px;
		margin: 10px;
		border: 1px solid #4CAF50;
		padding: 10px;
	}
```
- [ ] 142px
- [ ] 122px
- [ ] 100px
- [ ] 140px
<br>

#### 114. Care este motivul de utilizare al sprite-urilor?
- [ ] Reducerea numarului de request-uri
- [ ] Simplitate
- [ ] Realizarea de animatii
<br>

#### 115. Care va fi culoarea si inaltimea div-ului cu id-ul "id1" daca sunt definite urmatoarele stiluri?
```html
	<style>
		#id1 {
			height: 100px;
			background-color: red;
		}
	</style>
	<style>
		#id1 {
			background-color: blue;
		}
	</style>
```
- [ ] culoare = red, inaltime = 100px
- [ ] culoare = blue, inaltime = 100px
- [ ] culoare = blue, inaltime nedefinita
<br>

#### 116. Considerand urmatorul element jQuery:
```js
	var wrapper = $("#someId");
```
#### Cum se poate obtine obiectul "original" JavaScript din interiorul obiectului jQuery ```wrapper```?
- [ ] ```wrapper.get()```
- [ ] ```wrapper[0]```
- [ ] ```wrapper.query('#someId')```
<br>

#### 117. Care dintre urmatoarele antete este returnat de care server atunci cand este creata o sesiune (de exemplu folosind functia ```session_start()``` in PHP)?
- [ ] Create-Session
- [ ] Set-Cookie
- [ ] Send-Cookie
- [ ] Cookie
- [ ] Set-Session
- [ ] Session
<br>

#### 118. Cum se declara in JavaScript o functie anonima care se si apeleaza?
- [ ] ```(function(){ // fa ceva })()```
- [ ] ```(function())({ // fa ceva})```
- [ ] ```function(){ // fa ceva }()```
<br>

#### 119. Care dintre urmatoarele reprezinta metode valide HTTP?
- [ ] CONNECT
- [ ] REMOVE
- [ ] PUT
- [ ] OPTIONS
- [ ] UPDATE
<br>

#### 120. Cum se face cel mai usor o imagine responsive?
- [ ] ```<img src="picture.jpg" style="width: auto; height: responsive">```
- [ ] ```<img src="picture.jpg" style="max-width: 100%; height: auto">```
- [ ] ```<img src="picture.jpg" style="max-height: 100%"; width: auto">```
- [ ] ```<img src="picture.jpg" style="width: responsive; height: auto">```
<br>

#### 121. Cum arata un raspuns de redirectare trimis de catre server?
- [ ] status code-ul returnat incepe cu 3, iar URL-ul la care se face redirectarea este trimis in body-ul raspunsului
- [ ] status code-ul returnat incepe cu 3, iar URL-ul la care se face redirectarea este trimis in header-ul Redirect
- [ ] status code-ul returnat incepe cu 4, iar URL-ul la care se face redirectarea este trimis in header-ul Redirect
- [ ] status code-ul returnat incepe cu 3, iar URL-ul la care se face redirectarea este trimis in header-ul Location
- [ ] status code-ul returnat incepe cu 4, iar URL-ul la care se face redirectarea este trimis in body-ul raspunsului
<br>
