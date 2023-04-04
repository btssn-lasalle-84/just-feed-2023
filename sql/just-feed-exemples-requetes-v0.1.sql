--- Liste des distributeurs

SELECT * FROM Distributeur;

SELECT Distributeur.nom,Distributeur.ville,Distributeur.deviceID,ServeurTTN.hostname,ServeurTTN.applicationID FROM Distributeur
INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN;

--- Nombre de distributeurs

SELECT COUNT(*) AS NbDistributeurs FROM Distributeur;

-- Liste des produits

SELECT * FROM Produit;

-- Stocks

SELECT * FROM StockDistributeur;

-- Contenu détaillé d'un distributeur

SELECT Distributeur.nom,Distributeur.ville,Distributeur.deviceID,ServeurTTN.applicationID,Produit.nom,StockDistributeur.remplissage FROM StockDistributeur
INNER JOIN Distributeur ON Distributeur.idDistributeur=StockDistributeur.idDistributeur
INNER JOIN Produit ON Produit.idProduit=StockDistributeur.idProduit
INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN
WHERE StockDistributeur.idDistributeur='1';

SELECT Distributeur.*,Produit.*,StockDistributeur.* FROM StockDistributeur
INNER JOIN Distributeur ON Distributeur.idDistributeur=StockDistributeur.idDistributeur
INNER JOIN Produit ON Produit.idProduit=StockDistributeur.idProduit
INNER JOIN ServeurTTN ON ServeurTTN.idServeurTTN=Distributeur.idServeurTTN;

--------------------------------

-- Une intervention

SELECT Intervention.dateIntervention,Operateur.nom,Operateur.prenom,Distributeur.nom,Distributeur.ville, Distributeur.codepostal,Distributeur.deviceID,Produit.nom FROM Intervention
INNER JOIN Operateur ON Operateur.idOperateur=Intervention.idOperateur
INNER JOIN Approvisionnement ON Approvisionnement.idIntervention=Intervention.idIntervention
INNER JOIN StockDistributeur ON StockDistributeur.idStockDistributeur=Approvisionnement.idStockDistributeur
INNER JOIN Distributeur ON Distributeur.idDistributeur=StockDistributeur.idDistributeur
INNER JOIN Produit ON Produit.idProduit=StockDistributeur.idProduit
