Tipa Dan-Dumitru
gr 335CB

Am pornit de la laboratorul 6  la care am adaugat camera de la laboratorul5.
Im functia init imi initializez pozitile coloanelor pe x cu vectorul posx si adaug in mesh cuburile de culoare, cu care o sa imi fac mai departe platformele.

In update refac matricea pentru sfera dar ii tin minte pozitiile prin sx,sy si sz. Sfera nu se misca doar coloanele se misca spre spatele sferei.Dupa care pun pe ecran cele 2 seturi de coloane un set intial plasat sub sfera si unul mai in fata. Odata ca setul 1 a ajuns in spatele bilei se va plasa dupa setul 2 si dupa ce stul 2 ajung in spatele bilei va ajunge in fata setului 1 si tot asa.In acelasi timp salvez ce culoare am pe platforma cu vectorul de culoare v si w . Prin functia de coliziune fac platforma de sub sfera mov si aplic efectul in fucntie de culoarea platformei.

Dupa daca am facut coliziune atunci schimb shaderul de la sfera ca sa para um pic deformata altfel daca nu am coliziune atunci sfera cade.Efectul de deformare este folosit printr-un efect de tip noise.

Dupa verific daca am lovit o platforma rosie sau daca sfera este sub platforme atunci opresc jocul.