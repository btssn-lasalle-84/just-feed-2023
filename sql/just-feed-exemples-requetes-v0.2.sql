--- Liste des distributeurs

SELECT * FROM Distributeur;

SELECT Distributeur.nomDistributeur,Distributeur.ville,Distributeur.deviceID,ServeurTTN.hostname,ServeurTTN.applicationID FROM Distributeur
INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN;

--- Nombre de distributeurs

SELECT COUNT(*) AS NbDistributeurs FROM Distributeur;

-- Liste des produits

SELECT * FROM Produit;

-- Bacs

SELECT * FROM Bac;

-- Contenu détaillé d'un distributeur

SELECT Distributeur.nomDistributeur,Distributeur.ville,Distributeur.deviceID,ServeurTTN.applicationID,Produit.nomProduit,Bac.remplissage FROM Bac
INNER JOIN Distributeur ON Distributeur.idDistributeur=Bac.idDistributeur
INNER JOIN Produit ON Produit.idProduit=Bac.idProduit
INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN
WHERE Bac.idDistributeur='1';

SELECT Distributeur.*,Produit.*,Bac.* FROM Bac
INNER JOIN Distributeur ON Distributeur.idDistributeur=Bac.idDistributeur
INNER JOIN Produit ON Produit.idProduit=Bac.idProduit
INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN;

--------------------------------

-- Intervention

SELECT * FROM Intervention
INNER JOIN Distributeur ON Intervention.idDistributeur = Distributeur.idDistributeur
INNER JOIN Operateur ON Operateur.idOperateur=Intervention.idOperateur

SELECT * FROM Intervention
INNER JOIN Distributeur ON Intervention.idDistributeur = Distributeur.idDistributeur
INNER JOIN Operateur ON Operateur.idOperateur=Intervention.idOperateur
INNER JOIN Bac ON Bac.idDistributeur=Distributeur.idDistributeur
INNER JOIN Produit ON Produit.idProduit=Bac.idProduit

SELECT Intervention.dateIntervention,Operateur.nom,Operateur.prenom,Distributeur.nomDistributeur,Distributeur.ville, Distributeur.codepostal,Distributeur.deviceID,Produit.nomProduit FROM Intervention
INNER JOIN Distributeur ON Intervention.idDistributeur = Distributeur.idDistributeur
INNER JOIN Operateur ON Operateur.idOperateur=Intervention.idOperateur
INNER JOIN Bac ON Bac.idDistributeur=Distributeur.idDistributeur
INNER JOIN Produit ON Produit.idProduit=Bac.idProduit
