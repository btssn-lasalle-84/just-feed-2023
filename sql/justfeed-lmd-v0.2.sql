-- LMD (langage de manipulation de données)

INSERT INTO `ServeurTTN` (`idServeurTTN`, `hostname`, `port`, `username`, `password`, `applicationID`, `estActif`) VALUES
(1, 'eu1.cloud.thethings.network', 1883, 'just-feed-2022@ttn', 'NNSXS.2IX3LQUVLTB3AYCPZAP6EC5CEQ2MQT4JK6HPNTY.2UMHBW7PAO7IUKONOUN3QOIH4RULFGFMNUIHPASQAFXRYAFSTAFQ', 'just-feed-2022@ttn', 1);

INSERT INTO `Distributeur` (`idDistributeur`, `idServeurTTN`, `nomDistributeur`, `description`, `adresse`, `ville`, `codepostal`, `dateMiseEnService`, `longitude`, `latitude`, `deviceID`, `nbBacs`) VALUES
(1, 1, 'Gare Orange', 'Distributeur de fruits secs', 'Avenue Frédéric Mistral', 'Orange', '84100', '2022-01-08', '4.81958', '44.137327', 'distributeur-1-sim', 3),
(2, 1, 'Gare Avignon Centre', 'Distributeur de fruits secs', 'Boulevard Saint-Roch', 'Avignon', '84000', '2022-01-09', '4.8008485', '43.9416435', 'distributeur-2-sim', 3),
(3, 1, 'Gare de Carpentras', 'Distributeur de fruits secs', 'Avenue De La Gare', 'Carpentras', '84200', '2022-01-10', '5.0424848', '44.0487018', 'distributeur-3', 3);

INSERT INTO `Produit` (`idProduit`, `nomProduit`, `marque`, `description`, `codeEAN`, `prix`, `poidsUnitaire`, `volumeUnitaire`) VALUES
(1, 'Pruneaux', 'Maître Prunille', 'Les Pruneaux d\'Agen dénoyautés Maître Prunille sont une délicieuse friandise à déguster à tout moment de la journée.', '761234567890', 1.15, 0.008, 0.004),
(2, 'Abricots secs', 'Maître Prunille', 'L\'abricot moelleux, une gourmandise tendre et fruitée !', '761234566000', 1.13, 0.008, 0.004),
(3, 'Cranberries', 'SEEBERGER', 'Cranberries tranchées sucrées séchées', '761234569000', 2.1, 0.0006, 0.0005),
(4, 'Banane CHIPS', 'BIO VILLAGE', 'Banane CHIPS bio', '761234560008', 0.76, 0.003, 0.002),
(5, 'Raisin sec', 'Petit Prix', 'Raisins secs, huile végétale (graine de coton)', '761264569090', 0.39, 0.002, 0.001),
(6, 'Fruits sec', 'FRUIDYLLIC', 'Peut se manger tel que sans préparation.', '761234960940', 1.06, 0.00035, 0.0004),
(7, 'Cacahuète', 'Carrefour', 'Arachide crue blanche décortiquée pour cuisiner ou pâtisserie', '761234561000', 0.49, 0.001, 0.004),
(8, 'Riz Basmati Blanc', 'Grain de Frais', 'Riz Basmati blanc bio Grain de Frais', '358028140500', 0.35, 0.00005, 0.0003),
(9, 'Fèves entières', 'Grain de Frais', 'Fèves entières Pérou/Bolivie Grain de Frais', '3580281315163', 0.3, 0.002, 0.003);

INSERT INTO `Bac` (`idDistributeur`, `poidsActuel`, `poidsTotal`, `hygrometrie`, `idProduit`) VALUES
(1, 1.5, 2, 0, 7),
(1, 0.8, 1.3, 0, 8),
(1, 1.5, 8, 0, 9),
(2, 5, 12, 0, 4),
(2, 14, 16, 0, 2),
(2, 10.5, 16, 0, 5),
(3, 9.6, 9.6, 1, 3),
(3, 7.5, 16, 0, 1),
(3, 6.2, 7, 0, 6);

INSERT INTO Operateur(nom,prenom,identifiant,email) VALUES('DUVAL','Robert','rduval','rduval@justfeed.fr');

INSERT INTO `Intervention` (`idIntervention`, `idOperateur`, `idDistributeur`, `dateIntervention`) VALUES
(1, 1, 1, '2023-06-01');
