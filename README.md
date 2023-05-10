# 2022-2023-4gp-gomond-guyot
Projet Capteur

***
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
 
<div id='PremiereSection'/>

## 1. Description du projet 

Ce projet à lieu dans le cadre de l’UF “Du capteur au banc de test” du département de Génie Physique de l’INSA Toulouse. Basé sur l’article …, l’objectif de ce projet est de développer un capteur de déformation low-technologie à base de papier et de graphite. En effet, lorsque l’on déforme le papier, la distance entre les particules de graphite déposées au préalable change selon si l’on applique une tension ou une compression. Cette modification de résistance implique une modification de la conductivité de la couche de graphite. On peut ainsi mesurer une variation de résistance que l’on peut relier à la déformation.
	Notre objectif était donc de réaliser ce capteur entièrement, c'est-à-dire que nous allions passer par toutes les étapes de sa conception en partant du design et de la fabrication du PCB jusqu’au test du capteur en passant par de la programmation.



<div id='DeuxiemeSection'/>

## 2. Les livrables
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

<div id='TroisiemeSection'/>

## 3. Matériel nécessaire 


 


<div id='QuatriemeSection'/>

## 4. Simulation 


<div id='CinquiemeSection'/>

## 5. KiCad 
### 5.1. Schématique du circuit et création des symboles et empreintes des composants <div id='CinquiemeSection1'/>
* Amplificateur LTC1050



* Ecran OLED



* Encodeur rotatoire KY_040



* Module bluetooth HC05




### 5.2. Réalisation du PCB et visualisation 3D <div id='CinquiemeSection2'/>




<div id='SixiemeSection'/>

## 6. Fabrication du shield 

### 6.1. Réalisation du PCB <div id='SixiemeSection1'/>

  
### 6.2. Perçage et soudure <div id='SixiemeSection2'/>


<div id='SeptiemeSection'/>

## 7. Arduino 

### 7.1. Librairies utilisées <div id='SeptiemeSection1'/>

### 7.2. Code Arduino <div id='SeptiemeSection2'/>



<div id='HuigtiemeSection'/>

## 8. Application Android 


<div id='NeuviemeSection'/>

## 9. Réalisation des teste et résultats 

### 9.1. Banc de test <div id='NeuviemeSection1'/>

### 9.2. Résultats <div id='NeuviemeSection2'/>

### 9.3. Pistes d'améliorations <div id='NeuviemeSection3'/>

#### Comparaison avec le Flex-Sensor SEN-10264


<div id='DixiemeSection'/>

## 10. Datasheet



<div id='OnziemeSection'/>

## Contacts 



