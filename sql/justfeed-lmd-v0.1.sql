--- LMD (langage de manipulation de données)

INSERT INTO `ServeurTTN` (`idServeurTTN`, `hostname`, `port`, `username`, `password`, `applicationID`, `estActif`) VALUES
(1, 'eu1.cloud.thethings.network', 1883, 'just-feed-2022@ttn', 'NNSXS.2IX3LQUVLTB3AYCPZAP6EC5CEQ2MQT4JK6HPNTY.2UMHBW7PAO7IUKONOUN3QOIH4RULFGFMNUIHPASQAFXRYAFSTAFQ', 'just-feed-2022@ttn', 1);

INSERT INTO `Distributeur` (`idDistributeur`, `idServeurTTN`, `nom`, `description`, `adresse`, `ville`, `codepostal`, `dateMiseEnService`, `longitude`, `latitude`, `deviceID`, `hygrometrie`, `nbBacs`) VALUES
(1, 1, 'Gare Orange', 'Distributeur de fruits secs', 'Avenue Frédéric Mistral', 'Orange', '84100', '2022-01-08', '4.81958', '44.137327', 'distributeur-1-sim', 0, 3),
(2, 1, 'Gare Avignon Centre', 'Distributeur de fruits secs', 'Boulevard Saint-Roch', 'Avignon', '84000', '2022-01-09', '4.8008485', '43.9416435', 'distributeur-2-sim', 0, 3),
(3, 1, 'Gare de Carpentras', 'Distributeur de fruits secs', 'Avenue De La Gare', 'Carpentras', '84200', '2022-01-10', '5.0424848', '44.0487018', 'distributeur-3', 0, 3);

INSERT INTO `Produit` (`idProduit`, `nom`, `marque`, `description`, `codeEAN`, `prix`, `poidsUnitaire`, `volumeUnitaire`) VALUES
(1, "Pruneaux","Maître Prunille","Les Pruneaux d\'Agen dénoyautés Maître Prunille sont une délicieuse friandise à déguster à tout moment de la journée.","761234567890",1.15,0.008,0.004),
(2, "Abricots secs","Maître Prunille","L'abricot moelleux, une gourmandise tendre et fruitée !","761234566000",1.13,0.008,0.004),
(3, "Cranberries","SEEBERGER","Cranberries tranchées sucrées séchées","761234569000",2.1,0.0006,0.0005),
(4, "Banane CHIPS","BIO VILLAGE", "Banane CHIPS bio", "761234560008", 0.76,0.003,0.002),
(5, "Raisin sec","Petit Prix","Raisins secs, huile végétale (graine de coton)","761264569090",0.39,0.002,0.001),
(6, "Fruits sec","FRUIDYLLIC","Peut se manger tel que sans préparation.","761234960940",1.06,0.00035,0.0004),
(7, "Cacahuète","Carrefour","Arachide crue blanche décortiquée pour cuisiner ou pâtisserie","761234561000",0.49,0.001,0.004);

INSERT INTO `StockDistributeur` (`idStockDistributeur`, `idDistributeur`, `idProduit`, `remplissage`) VALUES
(1, 1, 3, 100),
(2, 1, 7, 90),
(3, 2, 1, 25),
(4, 2, 2, 10),
(5, 3, 4, 60),
(6, 3, 6, 20);

