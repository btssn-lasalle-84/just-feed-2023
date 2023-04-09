-- LDD (langage de définition de données)

-- Voir aussi : https://www.db4free.net/phpMyAdmin/

DROP DATABASE IF EXISTS `justfeed`;

CREATE DATABASE IF NOT EXISTS `justfeed` CHARACTER SET utf8;

--
-- Base de données : `justfeed`
--

USE justfeed;

DROP TABLE IF EXISTS Approvisionnement;
DROP TABLE IF EXISTS Intervention;
DROP TABLE IF EXISTS StockDistributeur;
DROP TABLE IF EXISTS Produit;
DROP TABLE IF EXISTS Distributeur;
DROP TABLE IF EXISTS Operateur;
DROP TABLE IF EXISTS ServeurTTN;

-- --------------------------------------------------------

--
-- Structure de la table `ServeurTTN`
--

CREATE TABLE `ServeurTTN` (
  `idServeurTTN` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `hostname` varchar(255) NOT NULL,
  `port` int NOT NULL DEFAULT '1883',
  `username` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `applicationID` varchar(255) NOT NULL,
  `estActif` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `Operateur`
--

CREATE TABLE `Operateur` (
  `idOperateur` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `nom` varchar(64) NOT NULL,
  `prenom` varchar(64) NOT NULL,
  `identifiant` varchar(255) DEFAULT NULL,
  `email` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `Distributeur`
--

CREATE TABLE `Distributeur` (
  `idDistributeur` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idServeurTTN` int NOT NULL,
  `nom` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `adresse` varchar(255) DEFAULT NULL,
  `ville` varchar(255) DEFAULT NULL,
  `codepostal` varchar(5) DEFAULT NULL,
  `dateMiseEnService` date NOT NULL,
  `longitude` varchar(255) DEFAULT NULL,
  `latitude` varchar(255) DEFAULT NULL,
  `deviceID` varchar(255) NOT NULL,
  `hygrometrie` int DEFAULT '0',
  `nbBacs` int NOT NULL DEFAULT '2'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


ALTER TABLE `Distributeur`
  ADD UNIQUE KEY `deviceID` (`deviceID`),
  ADD KEY `Distributeur_fk_1` (`idServeurTTN`);

ALTER TABLE `Distributeur`
  ADD CONSTRAINT `Distributeur_fk_1` FOREIGN KEY (`idServeurTTN`) REFERENCES `ServeurTTN` (`idServeurTTN`) ON DELETE CASCADE;

-- --------------------------------------------------------

--
-- Structure de la table `Produit`
--

CREATE TABLE `Produit` (
  `idProduit` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `nom` varchar(255) DEFAULT NULL,
  `marque` varchar(255) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `codeEAN` varchar(12) DEFAULT NULL,
  `prix` double DEFAULT NULL,
  `poidsUnitaire` double DEFAULT NULL,
  `volumeUnitaire` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Produit`
  ADD UNIQUE KEY `codeEAN` (`codeEAN`);

-- --------------------------------------------------------

--
-- Structure de la table `StockDistributeur`
--

CREATE TABLE `StockDistributeur` (
  `idStockDistributeur` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idDistributeur` int NOT NULL,
  `idProduit` int NOT NULL,
  `remplissage` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `StockDistributeur`
  ADD KEY `Stock_fk_2` (`idProduit`);

ALTER TABLE `StockDistributeur`
  ADD CONSTRAINT `Stock_fk_1` FOREIGN KEY (`idDistributeur`) REFERENCES `Distributeur` (`idDistributeur`) ON DELETE CASCADE,
  ADD CONSTRAINT `Stock_fk_2` FOREIGN KEY (`idProduit`) REFERENCES `Produit` (`idProduit`) ON DELETE CASCADE;

-- --------------------------------------------------------

--
-- Structure de la table `Intervention`
--

CREATE TABLE `Intervention` (
  `idIntervention` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idOperateur` int NOT NULL,
  `dateIntervention` date NOT NULL,
  `effectuee` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Intervention`
  ADD KEY `Intervention_fk_1` (`idOperateur`);

ALTER TABLE `Intervention`
  ADD CONSTRAINT `Intervention_fk_1` FOREIGN KEY (`idOperateur`) REFERENCES `Operateur` (`idOperateur`) ON DELETE CASCADE;

-- --------------------------------------------------------

--
-- Structure de la table `Approvisionnement`
--

CREATE TABLE `Approvisionnement` (
  `idApprovisionnement` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idIntervention` int NOT NULL,
  `idStockDistributeur` int NOT NULL,
  `dateApprovisionnement` date NOT NULL,
  `effectue` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Approvisionnement`
  ADD KEY `Approvisionnement_fk_1` (`idIntervention`),
  ADD KEY `Approvisionnement_fk_2` (`idStockDistributeur`);

ALTER TABLE `Approvisionnement`
  ADD CONSTRAINT `Approvisionnement_fk_1` FOREIGN KEY (`idIntervention`) REFERENCES `Intervention` (`idIntervention`) ON DELETE CASCADE,
  ADD CONSTRAINT `Approvisionnement_fk_2` FOREIGN KEY (`idStockDistributeur`) REFERENCES `StockDistributeur` (`idStockDistributeur`) ON DELETE CASCADE;

-- --------------------------------------------------------
