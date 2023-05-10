# 2022-2023-4gp-gomond-guyot
TD Capteur
Ce projet s'inscrit dans l'UF **"Du capteur au banc de test"** en 4ème année au département de Génie Physique de l'INSA Toulouse.
***
L'objectif de ce dernier est d'élaborer un **capteur de déformation** low-tech à base de graphite. L'application d'une contrainte mécanique sur un capteur en papier sur lequel un dépôt de crayon à papier à été fait, modifie la distance entre les particules de graphite. La conductivité électrique de la couche de graphite est elle aussi modifiée et celà induit une variation de la résistance. C'est cette donnée qui va nous intéresser.

<p align="center"><img width="550" alt="image" src="https://github.com/MOSH-Insa-Toulouse/2022-2023-4gp-gomond-guyot/blob/main/photos/capteur_graphite.jpg">

L'ensemble des étapes menées pour réaliser ce capteur, en allant du **design** jusqu'à la **réalisation** en passant par le **codage** seront détaillées dans ce dossier.

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
 

## 1. Détail des livrables et description du projet <div id='PremiereSection'/>



## 2. Matériel nécessaire
Pour réaliser le capteur ainsi que le PCB associé, voici la liste des composants nécessaires :
* x2 résistance 100kΩ
* x1 résistance 10kΩ
* x2 résistance 1kΩ
* x1 capacité 1μF
* x3 capacité 100nF
* x1 amplificateur opérationnel LTC1050
* x1 module Bluetooth HC05
* x1 encodeur rotatoire KY_040
* x1 écran OLED I2C 0.91

## 3. Arduino <a id="TroisiemeSection"></a>
### 3.1. Librairies utilisées <a id="TroisiemeSection1"></a>

### 3.2. Code Arduino <a id="TroisiemeSection2"></a>

 

#### Code Graphite_sensor


#### Code Angle_calibration


## 4. Application Android <div id='QuatriemeSection'/>


## 5. KiCad <a id="CinquiemeSection"></a>
### 5.1. Symboles et empreintes des composants <a id="CinquiemeSection1"></a>
* Amplificateur LTC1050



* Ecran OLED



* Encodeur rotatoire KY_040



* Module bluetooth HC05




### 5.2. Schématique <a id="CinquiemeSection2"></a>



### 5.3. Placement des composants <a id="CinquiemeSection3"></a>

### 5.4. Visualisation 3D <a id="CinquiemeSection4"></a>

## 6. Fabrication du shield <a id="SixiemeSection"></a>

### 6.1. Réalisation du PCB <a id="SixiemeSection1"></a> 

  
### 6.2. Perçage et soudure <a id="SixiemeSection2"></a> 


## 7. Simulation <a id="SeptiemeSection"></a> 


## 8. Tests et résultats <a id="HuigtiemeSection"></a> 
### 8.1. Banc de test <a id="HuigtiemeSection1"></a> 




### 8.2. Résultats obtenus <a id="SeptiemeSection2"></a> 


### 8.3. Analyse des résultats et pistes d'améliorations <a id="HuigtiemeSection3"></a> 

 
#### Comparaison avec le Flex-Sensor SEN-10264


 

 
#### Pistes d'améliorations 

  
## 9. Datasheet <a id="NeuviemeSection"></a> 


## Contacts <a id="DixiemeSection"></a> 
