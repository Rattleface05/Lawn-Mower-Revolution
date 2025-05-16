# Lawn-Mower-Revolution
The Second Project for my OOP class

# Compilare
Programul a fost scris pe o masina Linux, daca exista erori de incarcare a texturilor din file, asta probabil este motivul.  
De asemenea, comanda folosita pentru a compila este urmatoarea:  
g++ *.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o joc

# Descriere generala
Esti un om caruia ii place sa isi tina gazonul bine ingrijit. Din pacate, gazonului nu ii place sa ramana asa, probabil e vecinul de vina, o fi facut el ceva...  
Foloseste mouse-ul pentru a taia toata iarba care creste si a-ti pastra gazonul curat si ordonat!  

# Clase
## Entity:  
Este clasa pe care se bazeaza fiecare alta clasa a jocului, ea pastreaza pozitia si in ea se gasesc funtii pur virtuale folosite de derivate, cum ar fi getBounds() pentru a vedea daca ar trebui sa se intample coliziuni intre ele.  
Contine o varabila "position" care ii pastreaza pozitia.

## Player:  
Clasa jucatorului, derivata din Entity, este cea de care te folosesti pentru a interactiona cu gazonul.  
Contine textura, sprite-ul si valoarea de damage a jucatorului, si o functie pentru a creste damage-ul sau.

## Enemy:
Clasa pe care se bazeaza plantele care trebuie taiate de catre jucator, si este derivata a clasei Entity.  
Contine sprite-ul inamicului, HP-ul sau si o valoare aleatorie RNG pentru a aparea aleatoriu pe ecran.  
Contine si functii pentru a lua damage de catre jucator, si pentru a zice daca aceasta este "taiata de tot", adica daca i-a ajuns HP-ul la 0.

## Grass:
Primul inamic al unui gazon curat. Este prima planta care apare si este si cea mai usor de taiat, derivata a clasei Enemy.
Contine o textura, care este incarcata o singura data de catre program si folosita pentru toti inamicii de tip Grass.

## Weed:
O iarba mai puternica. Apare mai tarziu si este mai greu taiat, dar ofera puncte duble.
Asemenea clasei Grass, este o derivata a lui Enemy, cu o textura unica, dar cu mai mult HP.


# Bibliografie
W3Schools C++ Data structures and STL: https://www.w3schools.com/cpp/cpp_data_structures.asp  
Official SFML Website: https://www.sfml-dev.org/documentation/3.0.1/  
Tutorialele pentru SFML de Mesos Aurum: https://www.youtube.com/@MesosAurum  
Textura pentru jucator si Muzica de fundal din Leaf Blower Revolution, jocul care m-a inspirat: https://store.steampowered.com/app/1468260/Leaf_Blower_Revolution__Idle_Game/  
