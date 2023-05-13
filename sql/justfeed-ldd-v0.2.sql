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
DROP TABLE IF EXISTS Bac;
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
  `nomDistributeur` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `adresse` varchar(255) DEFAULT NULL,
  `ville` varchar(255) DEFAULT NULL,
  `codepostal` varchar(5) DEFAULT NULL,
  `dateMiseEnService` date NOT NULL,
  `longitude` varchar(255) DEFAULT NULL,
  `latitude` varchar(255) DEFAULT NULL,
  `deviceID` varchar(255) NOT NULL,
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
  `nomProduit` varchar(255) DEFAULT NULL,
  `marque` varchar(255) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `codeEAN` varchar(13) DEFAULT NULL,
  `prix` double DEFAULT NULL,
  `poidsUnitaire` double DEFAULT NULL,
  `volumeUnitaire` double DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Produit`
  ADD UNIQUE KEY `codeEAN` (`codeEAN`);

-- --------------------------------------------------------

--
-- Structure de la table `Bac`
--

CREATE TABLE `Bac` (
  `idBac` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idDistributeur` int NOT NULL,
  `idProduit` int NOT NULL,
  `poidsActuel` double,
  `poidsTotal`  double NOT NULL,
  `hygrometrie` int DEFAULT '0',
  `remplissage` double DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Bac`
  ADD KEY `Bac_fk_1` (`idDistributeur`),
  ADD KEY `Bac_fk_2` (`idProduit`);

ALTER TABLE `Bac`
  ADD CONSTRAINT `Bac_fk_1` FOREIGN KEY (`idDistributeur`) REFERENCES `Distributeur` (`idDistributeur`) ON DELETE CASCADE,
  ADD CONSTRAINT `Bac_fk_2` FOREIGN KEY (`idProduit`) REFERENCES `Produit` (`idProduit`) ON DELETE CASCADE;

-- --------------------------------------------------------

--
-- Structure de la table `Intervention`
--

CREATE TABLE `Intervention` (
  `idIntervention` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idOperateur` int NOT NULL,
  `idDistributeur` int NOT NULL,
  `dateIntervention` date NOT NULL,
  `aRemplir` int DEFAULT '0',
  `aDepanner` int DEFAULT '0',
  `etat` enum('EN_COURS','VALIDEES','A_FAIRE') NOT NULL DEFAULT 'A_FAIRE'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Intervention`
  ADD KEY `Intervention_fk_1` (`idOperateur`),
  ADD KEY `Intervention_fk_2` (`idDistributeur`);

ALTER TABLE `Intervention`
  ADD CONSTRAINT `Intervention_fk_1` FOREIGN KEY (`idOperateur`) REFERENCES `Operateur` (`idOperateur`) ON DELETE CASCADE;

ALTER TABLE `Intervention`
  ADD CONSTRAINT `Intervention_fk_2` FOREIGN KEY (`idDistributeur`) REFERENCES `Distributeur` (`idDistributeur`);

-- --------------------------------------------------------

--
-- Structure de la table `Approvisionnement`
--

CREATE TABLE `Approvisionnement` (
  `idApprovisionnement` int NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `idIntervention` int NOT NULL,
  `idBac` int NOT NULL,
  `poidsAPrevoir` float NOT NULL,
  `heureApprovisionnement` time NOT NULL,
  `effectue` int DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `Approvisionnement`
  ADD KEY `Approvisionnement_fk_1` (`idIntervention`),
  ADD KEY `Approvisionnement_fk_2` (`idBac`);

ALTER TABLE `Approvisionnement`
  ADD CONSTRAINT `Approvisionnement_fk_1` FOREIGN KEY (`idIntervention`) REFERENCES `Intervention` (`idIntervention`) ON DELETE CASCADE,
  ADD CONSTRAINT `Approvisionnement_fk_2` FOREIGN KEY (`idBac`) REFERENCES `Bac` (`idBac`) ON DELETE CASCADE;

-- --------------------------------------------------------
