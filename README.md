# Projet Capteur
***
<p align="center"><img width="550" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/capteur_graphite.jpg">

***


## Sommaire
* [1. Description du projet](#PremiereSection)
* [2. Les livrables](#DeuxiemeSection)
* [3. Matériel nécessaire](#TroisiemeSection)
* [4. Simulation](#QuatriemeSection)
* [5. KiCad](#CinquiemeSection)
  * [5.1. Schématique du circuit et création des symboles et empreintes des composants](#CinquiemeSection1)
  * [5.2. Réalisation du PCB et visualisation 3D](#CinquiemeSection2)
* [6. Fabrication du shield](#SixiemeSection)
  * [6.1. Réalisation du PCB](#SixiemeSection1)
  * [6.2. Perçage et soudure](#SixiemeSection2)
* [7. Arduino](#SeptiemeSection)
  * [7.1. Librairies utilisées](#SeptiemeSection1)
  * [7.2. Code Arduino](#SeptiemeSection2)
* [8. Application Android](#HuigtiemeSection)
* [9. Réalisation des tests et résultats](#NeuviemeSection)
  * [9.1. Banc de test](#NeuviemeSection1)
  * [9.2. Résultats](#NeuviemeSection2)
  * [9.3. Pistes d'améliorations](#NeuviemeSection3)
* [10. Datasheet](#DixiemeSection)
* [Contacts](#OnziemeSection)
 
<div id='PremiereSection'/>

## 1. Description du projet 

Ce projet à lieu dans le cadre de l’UF “Du capteur au banc de test” du département de Génie Physique de l’INSA Toulouse. Basé sur l’article "Pencil Drawn Strain Gauges and Chemiresistor on paper" publié sur Scientific Report en 2014, l’objectif de ce projet est de développer un capteur de déformation low-technologie à base de papier et de graphite. En effet, lorsque l’on déforme le papier, la distance entre les particules de graphite déposées au préalable change selon si l’on applique une tension ou une compression. Cette modification de résistance implique une modification de la conductivité de la couche de graphite. On peut ainsi mesurer une variation de résistance que l’on peut relier à la déformation.
Notre objectif était donc de réaliser ce capteur entièrement, c'est-à-dire que nous allions passer par toutes les étapes de sa conception en partant du design et de la fabrication du PCB jusqu’au test du capteur en passant par de la programmation.

<div id='DeuxiemeSection'/>

## 2. Les livrables
Pour ce projet, nous avions différents livrables à rendre avant le 17/05/2023:
- Un shield PCB fonctionnel connecté à une carte Arduino UNO. Le PCB doit nécessairement contenir un amplificateur transimpédance, un capteur bluetooth, un écran OLED. Il peut également contenir un flex sensor, un potentiomètre digital et un encodeur rotatoir. 
- Un code Arduino permettant de gérer le module bluetooth ainsi que les mesures du capteur de déformation. Si présent sur le shield, le code doit aussi prendre en compte l’écran OLED ainsi que l’encodeur rotatoir. 
- Une application Android APK développée à l’aide du site MIT app inventor. 
- Un protocole de calibration du capteur
- Une datasheet du capteur de déformation développé

Dans notre cas, nous avons choisi d'implémenter en plus du capteur Bluetooth et de l’écran OLED sur notre shield, le flex sensor afin de pouvoir comparer notre capteur avec un capteur industriel et l’encodeur rotatoir afin de pouvoir sélectionner différents modes de mesure pour notre capteur. 

<div id='TroisiemeSection'/>

## 3. Matériel nécessaire 
Pour réaliser le capteur ainsi que le PCB associé, voici la liste des composants nécessaires :

* Résistances : 2 de 1 kOhms, 2 de 10 kOhms, 2 de 100 kOhms
* Capacités : 2 de 100 nF, 1 de 1 uF
* Arduino Uno
* Amplificateur opérationnel LTC1050
* Module Bluetooth HC05
* Encodeur rotatoire KY_040
* Ecran OLED 128x64
* Flex Sensor
 
<div id='QuatriemeSection'/>

## 4. Simulation 
Le but de réaliser en amont la simulation LTSpice du circuit intégré au capteur est de vérifier en théorie qu’il a bien été conçu, c’est-à-dire que l’on a un signal de sortie qui correspond à ce que l’on souhaite avoir pour ensuite pouvoir le traiter à l’aide de l’Arduino UNO. On peut peut l’utiliser également pour vérifier l’impact des différents composants et déterminer les valeurs de résistances, capacités nécessaires pour avoir la tension de sortie souhaitée. Dans notre cas, n’ayant pas conçu le circuit de nous même, nous avons simplement vérifié à l’aide de LTSpice qu’il correspondait à ce dont nous avions besoin pour réaliser pour amplifier le signal du capteur.

Pour cela, nous avons tout d’abord reproduit le circuit sur LTSpice comme montré ci-dessous:

<img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/LTSPICE%20SCHEME.PNG">


Nous avons ensuite réalisé deux types de simulation: .tran (qui correspond à un signal transient en entrée du circuit) et .ac (qui correspond à un signal continu en entrée du circuit). La première simulation a pour but de vérifier que le signal en sortie V(ADC) du circuit est suffisamment amplifié pour que l’Arduino UNO puisse mesurer sa valeur. On cherche à avoir une tension de l’ordre du Volt. Le circuit est bien conçu puisqu’on observe sur une simulation de 12s que le signal est amplifié jusqu’à 1 Volt.

<img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/TRAN12.PNG">


La seconde simulation est due à la présence de trois filtres passe-bas dans le circuit visant à réduire les bruits parasitant le signal de sortie. En réalisant une simulation .ac nous pouvons ainsi afficher le diagramme de Bode de chaque filtre passe-bas et afin de trouver les fréquences de coupure des différents filtres. Nous avons d’abord vérifié la fréquence de coupure des différents filtres (de 1,6 Hz, 16 Hz et 1,6 kHz) puis vérifié leur efficacité en réalisant une simulation .ac en introduisant un bruit de 50 Hz.

<img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/BODE.PNG">


On observe qu’à 50 Hz, le signal est atténué de 78 dB. Le bruit est donc bien filtré.

<div id='CinquiemeSection'/>

## 5. KiCad 
<div id='CinquiemeSection1'/>

### 5.1. Schématique du circuit et création des symboles et empreintes des composants 
La première étape du KICAD a été de réaliser la schématique du circuit, basé sur la simulation réalisée précédemment. Pour cela, nous avons tout d’abord importé le schéma de l’Arduino Uno qui existe déjà sur KiCAD. Nous avons été ensuite amenés à créer les symboles pour les composants non-existants sur LTSpice, ainsi que leur empreinte sur le PCB. Voici ci-dessous les différentes symboles avec leur empreinte associé:

* Amplificateur LTC1050

<img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/LTCL050.jpg">


* Ecran OLED

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/Oled2.jpg"> <img width="250" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/OLED.jpg">


* Encodeur rotatoire KY_040

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/encodeur2.jpg"> <img width="250" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/Encodeur.jpg">


* Module bluetooth HC05

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/Bluetooth2.jpg"> <img width="250" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/Bluetooth.jpg">

* Flex Sensor

<img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/Flex_sensor_shema.jpg"> <img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/3d_flex.jpg">


Pour les résistances nous avons choisi comme empreinte la Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal, excepté pour R2 pour laquelle nous avons pris la même empreinte mais à la verticale (elle a donc été placée à la japonaise). Concernant les capacités, C1 et C2 possède comme empreinte Capacitor_THT: C_Disc_D3.0mm_W1.6mm_P2.50mm, tandis que C4 a pour empreinte Capacitor_THT:C_Rect_L7.0mm_W4.5mm_P5.00mm.

Voici ci-dessous le schéma de la schématique du circuit réalisé sur KiCAD:

<p align="center"><img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/PCB-scheme.jpg">


<div id='CinquiemeSection2'/>

### 5.2. Réalisation du PCB et visualisation 3D 
Pour le PCB, nous avions pour contrainte de n’imprimer que sur une seule face. Il a donc fallu optimiser autant que possible les connexions entre les différents composés afin de limiter la présence de PADs. Nous avons réussi à n’avoir besoin que d'un seul PAD sur notre PCB, qui, n’ayant pas de face arrière, s’est traduit par la connexion du PAD à l’aide d’un fil de résistance. Voici ci-dessous l’empreinte du PCB réalisé:

<p align="center"><img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/PCB.jpg">

Le plan en bleu est le plan de masse. Les PADS sont de formes circulaires de 2mm de diamètre avec une forme de perçage circulaire de 1mm pour l’Arduino et le capteur de déformation et 0,8mm pour le reste. Les largeurs de pistes sont de 1mm et l’isolation entre les pistes et le plan de masse est de 0,3mm. Nous avons choisi ces derniers paramètres afin de faciliter l’étape de soudure.
	
Afin de visualiser en 3D notre composant et pouvoir voir la place que prend chaque composant, nous avons dû, pour les empreintes que nous avons créées, utiliser le site internet GrabCADafin de récupérer le fichier 3D de nos composants. Voici-ci dessous la visualisation 3D du PCB réalisé: 
	
<p align="center"><img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/3D.jpg">

<div id='SixiemeSection'/>

## 6. Fabrication du shield 
<div id='SixiemeSection1'/>

### 6.1. Réalisation du PCB 

Le PCB a été réalisé par Catherine CROUZET du département du Génie Physique de l’INSA Toulouse à l’aide du matériel du département du Génie Physique et du département	Électrique et Informatique. Avant impression, l’empreinte du PCB a été vérifiée par Mme CROUZET qui a ensuite imprimé sur papier le calque de modélisation issu du PCB réalisé sur KiCAD.
 Nous sommes parti d’une plaquette d'époxy couverte d’une couche de cuivre d’environ  60µm sur laquelle nous avons appliqué notre calque qui a permis de tracer les pistes sur la plaquette du PCB à l’aide d’une insolation UV. Une fois les pistes tracées, elles sont ensuite révélées à l’aide d’un révélateur qui après quelques minutes, retire la résine non éclairée pas les UV. La plaquette est ensuite placée dans un bain de perchlorure de fer pendant 7 minutes afin de réaliser la gravure du PCB. Lors de cette étape, le cuivre non protégé par la résine est retiré. Nous obtenons alors le PCB comme désigné sur KiCAD. On applique pour terminer un peu d’acétone afin de retirer les dernières traces de résines encore présentes.
 
 <img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/Shilde.jpg"> <img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/shilde2.jpg">
 
 <div id='SixiemeSection2'/>

### 6.2. Perçage et soudure 
Une fois les pistes du PCB créées, il faut réaliser le perçage du PCB puis la soudure des composants. Pour cela nous avons utilisé la perceuse électrique mise à disposition aux étudiants du Génie Physique. Les tailles de forêts ont été choisies en fonction des tailles de trous de perçage designé sur KiCAD (c’est à dire 0,8mm ou 1mm de diamètre selon les composants). Une fois tous les composants soudés sur la face avant, nous avons pu connecter le PCB à l’Arduino Uno. 

<div id='SeptiemeSection'/>

## 7. Arduino 
<div id='SeptiemeSection1'/>

### 7.1. Librairies utilisées 
Pour la réalisation du code Arduino nous avons utiliser deux librairies qui sont **"SoftwareSerial.h"** pour réaliser un software serial sur deux pin pour l'utilisation du modude bluetooth. La deuxième est **"Adafruit_SSD1306.h"** qui sert pour l'utilisation de l'écran OLED.


<div id='SeptiemeSection2'/>

### 7.2. Code Arduino 
Nous avons réaliser deux code Arduino dans ce projet. Le premier permet de controler le capteur et tout ces composants. Le deuxième sert lors de la procédure de calibration.

#### Code pour le Capteur 
Ce [code](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/arduino/Programme_finaleVFinale.ino) est le coeur du fonctionnement du capteur. 
-Il permet tout d'abord récupérer les valeurs de tension en sortie de l'amplificateur et de réaliser les différents calculs pour retrouver la résistance de notre capteur.
-Il permet également le contrôle et l'utilisaton des différents éléments ajoutés sur le shield:
	
   * il y a le **module Bluetooth** qui permet d'envoyer la valeur de tension lue et de l'envoyer à l'application Android.
	
   * il y a **l'encodeur rotatoir** où nous avons grâce à lui réaliser trois menus en fonction d'où l'on se trouve dans la plage de valeurs de l'encodeur. Il y a un menu avec un mode de lecteur continu de la résistance, un autre mode qui réalise une moyenne sur 200 valeurs de la résistance et n mode pour afficher la lecture du flex sensor. Tout ces menus sont visible sur l'écran OLED.
	
   * il y a **l'écran OLED** qui permet d'afficher la valeur de la résistance de notre capteur ou du flex sensor en fonction du menu que nous avons choisi. Le menu où nous sommes est également affiché.
	
<img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/mode_continue.jpg"> <img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/mode_moyenne.jpg"> <img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/flex_sensor2.jpg">

#### Code pour la calibration
Ce [code](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/arduino/programme_calibration.ino) permet de contrôler un Servo-Moteur qui va se positionner à différent angles déterminés (0, 30, 60, 90, 120). Il va attendre 2 secondes à chaques position pour nous permettre de lire la valeur. La procédure est activée grâce à un bouton poussoir et pendant que le servo-moteur est en mouvement une LED est allumée.

<div id='HuigtiemeSection'/>

## 8. Application Android 
Nous avons développé une application Android fonctionnant à l’aide du module Bluetooth HC-05. L’application se présente comme ci-dessous: 

<p align="center"><img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/app_bluetooth.jpg">

L’application possède un menu de sélection bluetooth permettant de choisir à quel module bluetooth se connecter. Une fois connecté, le code Arduino envoie via le module la valeur de tension en sortie du circuit V(ADC) en Volt sous forme d’un byte à l’application. L’application convertit ces valeurs tout d’abord en float, puis en résistance en M𝛺 à l’aide de la formule: 

<p align="center"><img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/formule.png">
	
Le schéma fonctionnel du programme derrière l’application est visible sous ce lien: [LIEN APK](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/app/Application_Projet.aia)

<div id='NeuviemeSection'/>

## 9. Réalisation des tests et résultats 
<div id='NeuviemeSection1'/>

### 9.1. Banc de test 
Pour réaliser les différents tests de calibration nous avons réaliser deux bancs de tests pour avoir une calibration en fonction de la déformation et en fonction de l'angle. Nous avons réaliser les deux calibrations car nous avons trouvé, sur le point physique, intéressant de la réaliser en fonction de la déformation de la couche de graphite. Mais sur l'aspect utilisation du capteur, il est plus utile et intéressant de connaitre la résistance en fonction de l'angle que fait le capteur.

#### Banc de test pour la calibration en fonction de la deformation
Pour cette methode nous avons découpé des cercles de différents rayons de courbure (1, 2, 4 et 6 cm) comme montrée ci dessous.

<p align="center"><img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/calibration_deformation.jpg">
	
Ce rayon de courbure nous permet de remonter à la déformation ε gracce à la formule suivante qui est expliqué par le shéma ci-dessous.

<img width="500" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/formule_def.png"> <img width="200" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/explication_deformation.png">


#### Banc de test pour la calibration en fonction de l'angle
Pour cette methode nous avons utilisé un module en bois  qui était fournis par le département ainsi qu'un servo-moteur. Nous utilisons le code décrit à la partie 7.2 pour la calibration. Le servo-moteur tord le capteur à différents angles prédéfinis.
	
<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/callibration_angle.jpg"> <img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/callibration_angle2.jpg">


<div id='NeuviemeSection2'/>

### 9.2. Résultats
Les résultats complets ont été réalisé sur Exel dans le dossier [result.](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/result/calcules_deformation.xlsx) Sinon voici les différentes courbes de calibration en fonction de l'angle et de la déformation.
Nous avons réalisé les mesures en fonction de la déformation en compression et en tension. Pour les mesures en fonction de l'angle, nous avons réalisé seulement la compression car les résultats que nous avons obtenu en tension n'était pas exploitables.

* Variation de la résistance en fonction de la deformation (tension)

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/courbe_deformation_tension_.png">

* Variation de la résistance en fonction de la deformation (compression)

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/courbe_deformation_compression.png">

* Variation de la résistance en fonction de l'angle (compression)

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/courbe_deformation_tension_.png">

Quand nous travaillons en tension, la monocouche de graphite déposé sur le papier va s'étirer ce qui va augmenter la distance entre les différents atomes de Carbone et ainsi augmenter la résitance du capteur.
Lorsque nous travaillons en tension, il se passe l'opposé. Les atomes de Carbone vont se rapprocher et la résistance du capteur va diminuer.
En fonction du type de crayon utilisé, les variations relatives de résistance changent. En effet, plus le crayon est gras, c'est à dire qu'il dépose plus de graphite, moins sa variation relative de résistance est élevée. Nous pouvons vérifier cela sur les différentes courbes que nous avons obtenu.

<div id='NeuviemeSection3'/>
 
### 9.3. Pistes d'améliorations
Plusieurs pistes d’améliorations pour ce capteur sont possibles. Tout d’abord, comme nous avons pu l’expérimenter, la répétabilité du capteur est peu fiable dû à plusieurs facteurs:

-Le dépôt de la quantité de graphite n’est pas contrôlée, et cette quantité diminue au cours du temps avec l’air alentour.

-Le papier s’use assez rapidement et ne peut pas supporter des déformations trop importantes.

Ainsi, on pourrait essayer de réaliser une méthode afin de déposer une quantité contrôlée de graphite sur le papier, ainsi que choisir un papier plus élastique. 
Un autre ajout possible sur la partie hardware du capteur serait le potentiomètre digital qui permettrait d’adapter la tension de sortie du capteur en fonction de la résistance du capteur. 
La partie banc de tests pourrait être améliorée en réalisant des tests sur des cylindres solides imprimés en 3D et avec plus de tailles différentes afin d’obtenir plus de données pour tracer nos courbes.


#### Comparaison avec le Flex-Sensor SEN-10264

*Variation de la résistance du flex sensor en compression

<img width="400" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/courbes_flex_compression.png">

Pour comparer la sensibilité des deux capteurs, nous pouvons comparer les coefficients directeur du flex sensor avec celui du capteur de contrainte HB sur la compression. Pour le flex sensor, nous avons obtenu un coefficient de -1.891/° tandis que pour le capteur de contrainte HB nous avons -0.24/°. On peu donc dire que le flex sensor est beaucoup plus sensible à la déformation que notre capteur de contrainte en graphite. Le flex sensor pourrait être plus utile pour detecter de petites déformations grâce à sa plus grande sensibilité. A coté de cela, notre capteur en graphite à plus de difficulté à détecter les petites déformation où les petit angles. Il serait plus utile pour savoir s'il est plié ou non.

<div id='DixiemeSection'/>

## 10. Datasheet
La datasheet du capteur est disponible [ici](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/Datasheet.pdf)

<div id='OnziemeSection'/>

## Contacts 
Nous sommes disponibles pour toute question sur le projet, n'hesitez pas à nous contacter.

-GUYOT Adrien : aguyot@etud.insa-toulouse.fr

-GOMOND François : fgomond@insa-toulouse.fr


