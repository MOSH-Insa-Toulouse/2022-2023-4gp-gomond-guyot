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
* [9. Réalisation des teste et résultats](#NeuviemeSection)
  * [9.1. Banc de test](#NeuviemeSection1)
  * [9.2. Résultats](#NeuviemeSection2)
  * [9.3. Pistes d'améliorations](#NeuviemeSection3)
* [10. Datasheet](#DixiemeSection)
* [Contacts](#OnziemeSection)
 
<div id='PremiereSection'/>

## 1. Description du projet 

Ce projet à lieu dans le cadre de l’UF “Du capteur au banc de test” du département de Génie Physique de l’INSA Toulouse. Basé sur l’article …, l’objectif de ce projet est de développer un capteur de déformation low-technologie à base de papier et de graphite. En effet, lorsque l’on déforme le papier, la distance entre les particules de graphite déposées au préalable change selon si l’on applique une tension ou une compression. Cette modification de résistance implique une modification de la conductivité de la couche de graphite. On peut ainsi mesurer une variation de résistance que l’on peut relier à la déformation.
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



Pour les résistances nous avons choisi comme empreinte la Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal, excepté pour R2 pour laquelle nous avons pris la même empreinte mais à la verticale (elle a donc été placée à la japonaise). Concernant les capacités, C1 et C2 possède comme empreinte Capacitor_THT: C_Disc_D3.0mm_W1.6mm_P2.50mm, tandis que C4 a pour empreinte Capacitor_THT:C_Rect_L7.0mm_W4.5mm_P5.00mm.

Voici ci-dessous le schéma de la schématique du circuit réalisé sur KiCAD:

<p align="center"><img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/PCB-scheme.jpg">


<div id='CinquiemeSection2'/>

### 5.2. Réalisation du PCB et visualisation 3D 
Pour le PCB, nous avions pour contrainte de n’imprimer que sur une seule face. Il a donc fallu optimiser autant que possible les connexions entre les différents composés afin de limiter la présence de PADs. Nous avons réussi à n’avoir besoin que d'un seul PADs sur notre PCB, qui, n’ayant pas de face arrière, s’est traduit par la connexion du PADS à l’aide d’un fil de résistance. Voici ci-dessous l’empreinte du PCB réalisé:

<p align="center"><img width="1000" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/PCB.jpg">

Le plan en bleu est le plan de masse. Les PADS sont de formes circulaires de 2mm de diamètre avec une forme de perçage circulaire de 1mm pour l’Arduino et le capteur de déformation et 0,8mm pour le reste. Les largeurs de pistes sont de 1mm et l’isolation entre les pistes et le plan de masse est de 0,3mm. Nous avons choisi ces derniers paramètres afin de faciliter l’étape de soudure.
	
Afin de visualiser en 3D notre composant et pouvoir voir la place que prend chaque composant, nous avons dû, pour les empreintes qie nous avons créées, utiliser le site internet GrabCADafin de récupérer le fichier 3D de nos composants. Voici-ci dessous la visualisation 3D du PCB réalisé: 
	
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

<div id='SeptiemeSection2'/>

### 7.2. Code Arduino 



<div id='HuigtiemeSection'/>

## 8. Application Android 
Nous avons développé une application Android fonctionnant à l’aide du module Bluetooth HC-05. L’application se présente comme ci-dessous: 

<p align="center"><img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/app_bluetooth.jpg">

L’application possède un menu de sélection Bluetooth permettant de choisir à quel module Bluetooth se connecter. Une fois connecté, le code Arduino envoie via le module la valeur de tension en sortie du circuit V(ADC) en Volt sous forme d’un byte à l’application. L’application convertit ces valeurs tout d’abord en float, puis en résistance en M𝛺 à l’aide de la formule: 

<p align="center"><img width="300" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/formule.png">
	
Le schéma fonctionnel du programme derrière l’application est visible sous ce lien: [LIEN APK](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/app/Application_Projet.aia)

<div id='NeuviemeSection'/>

## 9. Réalisation des teste et résultats 
<div id='NeuviemeSection1'/>

### 9.1. Banc de test 

<div id='NeuviemeSection2'/>

### 9.2. Résultats

<div id='NeuviemeSection3'/>
 
### 9.3. Pistes d'améliorations

#### Comparaison avec le Flex-Sensor SEN-10264


<div id='DixiemeSection'/>

## 10. Datasheet
La datasheet du capteur est disponible [ici](https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/Datasheet.pdf)

<div id='OnziemeSection'/>

## Contacts 
Nous somme disponibles pour toute question sur le projet, n'hesitez pas à nous contacter.
-GUYOT Adrien : aguyot@etud.insa-toulouse.fr
-GOMOND François : fgomond@insa-toulouse.fr


