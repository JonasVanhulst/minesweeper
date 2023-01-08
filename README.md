# Eindopdracht: Minesweeper 🚩
Hoera, je hebt het tot hier gemaakt! 🥳 Nu voor de echte uitdaging. 
Deze opdracht gaat alle skills die je tot nu toe hebt geleerd op de proef stellen. 
Je gaat Minesweeper implementeren in C.

Op een 8 x 8 veld worden een gegeven aantal bommen verstopt. 
Elk veld is onzichtbaar tot je ze kiest en activeert. 
Het kiezen van de locatie is steeds door een letter met cijfer of cijfer met letter in te geven 
(zowel C5 als 5C als c5), het nummer gaat van 1 tot 8 en de letter van A tot H. 
Mocht daar een bom verstopt zitten, stopt het spel en ben je verloren en toon je alle andere bommen. 
Mocht er geen bom liggen, dan worden het aantal bommen dat in de directe omgeving liggen 
getoond (linksboven, boven, rechtsboven, links, rechts, linksonder, onder en rechtsonder). 
Mochten er geen bommen rondom liggen, zal het alle directe buren tonen gezien het geen bommen 
kunnen zijn en deze functionaliteit herhalen voor alle buren die ook geen naaste bommen hebben. 
Het spel is uitgespeeld eens alle bommen de enige velden zijn die niet vrijgespeeld zijn. 
Je toont steeds de vooruitgang in procenten van het spel als aantal vrijgespeelde velden / aantal vrij 
te spelen velden 😊 8x8 velden - aantal bommen) x 100%. Het is steeds mogelijk een lopend spel 
op te slaan (bij ingave van locatie het woord "bewaren" kiezen) en in te laden m.b.v. 2 hexadecimale getalen 
(1 bitmask met locatie van de bommen en 1 bitmask vrijgespeelde velden).

  - [ ] Documenteer de hele code in een flowchart. Alle arrays mogen globale variabele zijn 
  (gezien we nog geen pointers hebben gezien). Alle andere variabele mogen niet globaal gedefinieerd zijn.

## Flow van het spel 🎲
Begin het spel met de gebruiker welkom te heten en te vragen achter het aantal bommen of "laden". 
Tijdens het laden worden 2 hexadecimale getalen ingegeven die samen zowel het 8 op 8 veld met 
bommen als het gespeelde veld voorstellen. Test of de ingegeven waarden wel kunnen, bv. geen bommen in het veld, of 
bommen die al ontploft zijn, of een veld dat eigenlijk uitgespeeld is. Bij aantal bommen wordt een nieuw 8 op 8 
veld gevuld met het meegegeven aantal bommen op random locaties (zorg dat aantal bommen correct is en
dus geen bommen dubbel liggen). In beide gevallen wordt een visuele 2D array gevuld of bijgehouden (en ingeladen)
met de juiste representatie. Daarna wordt het spel gespeeld.

Het spel wordt gespeeld tot er een bom activeert of het spel afgespeeld is.
Zolang dat niet het geval is dan kan er een locatie als "bewaren" ingegeven worden.
Bij bewaren toont het de 2 64 bit hexadecimale getallen die het veld met bommen en huidige 
toestand van vrijgespeelde velden representeert. Een locatie daarentegen kan zowel een 
letter met cijfer als cijfer met letter (niet hoofdletter gevoelig) zijn. Op die ingegeven 
locatie wordt het veld (visueel 2D array) aangepast om de juiste inhoud te tonen. 
Dit kan een bom zijn en dan is het spel afgelopen en toon je het veld met alle bommen. 
Dit kan een buur van een bom zijn en dan toon je het nummer van aantal bommen als buur.
Dit kan een nul-veld zijn en dan flood fill je het veld vanuit dat punt. Het veld en de 
vooruitgang als een procentuele weergave met 2 cijfers na de komma weergegeven van aantal 
getoonde velden t.o.v. totaal aantal goede velden. Eens het laatste niet bom veld aangeduid 
wordt, feliciteer je de speler.

## Punten waarop beoordeeld wordt ☑️
- [x] Printen van goede verzorgde berichten, velden en menu's
- [x] Juist gebruik van variabele, zinvolle consistente naamgeving, geen overbodige/nutteloze variabelen en correcte datatypes bij scanf()
- [x] Voortgangspercentage is juist berekend en met 2 cijfers na de komma weergegeven
- [x] Bij het spelen van het veld, worden de juiste condities gecontroleerd. M.a.w. wanneer een bom geselecteerd wordt, is het spel afgelopen; wanneer een 0 geselecteerd wordt, worden alle aangesloten velden die ook 0 zijn vrijgespeeld (i.e. flood fill)
- [x] Velden worden geprint en getest met for-loops en het spel (en eventueel input) draait binnen while-lussen
- [x] Gebruik van goede functies, zinvolle consistente naamgeving, geen onnodige duplicaten code indien het in een functie kon en maximaal 32 code-lijnen (geen lege lijnen of lijnen met enkel haakjes) in een functie
- [x] Alle functies in een header file
- [x] Het speelveld is 8x8 groot en wordt voor te printen bijgehouden in een 2D array
- [x] Strings worden gebruikt voor ingave van de plaats op het veld en kunnen nummer met letter of letter met nummer zijn (niet hoofdletter gevoelig). Ook kan er het woord "bewaren" kan zijn (niet hoofdletter gevoelig) om het spel te bewaren. Daarbij kan "laden" i.p.v. aantal bommen ingegeven worden.
- [x] De hele code is netjes gedocumenteerd in een correcte flowchart (zie miro). Zet de link naar de miro in de code in comment !
- [ ] Een 8x8 spel kan bijgehouden worden in een 64 bit getal van alle bommen bij te houden
- [ ] Van een 8x8 spel kan tussentijds het vrijgespeelde veld opgevraagd worden in een 64 bit getal
- [ ] Een 8x8 spel kan ingeladen worden door twee 64 bit getallen (1 van alle bommen en 1 van het vrijgespeelde deel) als hexadecimaal in te lezen en te gebruiken
- [x] Het geheel werk volledig zonder crashen
- [x] Een mooie extra eens de rest werkt (zie de lijst hieronder)

### Mogelijke extra's 👾
Hier kan je mogelijke mooie extra's vinden moest je tijd over hebben.
NOTE: er valt hier maar 1 punt te verdienen!

- [x] ASCII art
- [x] Recursieve functies (flood fill)
- [ ] Highscores met namen