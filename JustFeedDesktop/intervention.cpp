/**
 * @file        intervention.cpp
 * @brief       Définition de la classe Intervention.
 * @details     La classe intervention \c Cette classe permet de définir une
 * intervention
 * @author      Salaun Matthieu <matthieusalaun30@gmail.com>
 * @version     0.1
 * @date        2023
 */

#include "intervention.h"
#include "bac.h"
#include "distributeur.h"
#include "ihmjustfeed.h"

/**
 * @brief Constructeur de la classe Intervention
 */
Intervention::Intervention(
    QVector<Distributeur *> listeDistributeursAIntervenir, IHMJustFeed *parent)
    : QDialog(parent), ihmJustFeed(parent),
      dateIntervention(QDate::currentDate()),
      distributeurs(listeDistributeursAIntervenir), effectuee(false) {
  qDebug() << Q_FUNC_INFO << "dateIntervention" << dateIntervention;
  qDebug() << Q_FUNC_INFO << "nb distributeurs"
           << listeDistributeursAIntervenir.size();
  initialiserBoiteDeDialogue();
}

/**
 * @brief Destructeur de la classe Intervention
 */
Intervention::~Intervention() { qDebug() << Q_FUNC_INFO; }

/**
 * @brief Accesseur de l'attribut dateIntervention
 * @return QDate représente la date de l'intervention sur le
 * distributeur
 */
QDate Intervention::getDateIntervention() const {
  return this->dateIntervention;
}

/**
 * @brief Accesseur de l'attribut distributeurAIntervenir
 * @return QVector<Distributeur*> represente les distributeurs surlequels il
 * faut intervenir
 */
QVector<Distributeur *> Intervention::getDistributeurs() const {
  return this->distributeurs;
}

/**
 * @brief Accesseur de l'attribut effectuee
 * @return effectuee
 */
bool Intervention::estEffectuee() const { return this->effectuee; }

/**
 * @brief Accesseur de l'attribut ARemplir
 * @return aRemplir
 */
bool Intervention::estARemplir() const { return this->aRemplir; }

/**
 * @brief Accesseur de l'attribut ADepanner
 * @return aDepanner
 */
bool Intervention::estADepanner() const { return this->aDepanner; }

/**
 * @brief Accesseur de l'attribut AIntervenir
 * @return !effectuee
 */
bool Intervention::estAIntervenir() const { return !this->effectuee; }

/**
 * @brief Mutateur de l'attribut distributeurAIntervenir
 * @param distributeur distributeur sur lequel il faut intervenir
 */
void Intervention::ajouterDistributeur(Distributeur *distributeur) {
  this->distributeurs.push_back(distributeur);
}

/**
 * @brief Mutateur de l'attribut dateIntervention
 * @param dateIntervention
 */
void Intervention::setDateIntervention(const QDate &dateIntervention) {
  this->dateIntervention = dateIntervention;
}

/**
 * @brief Mutateur de l'attribut effectuee
 * @param effectuee
 */
void Intervention::effectuer(const bool effectuee) {
  this->effectuee = effectuee;
}

void Intervention::remplir(bool aRemplir) { this->aRemplir = aRemplir; }

void Intervention::depanner(bool aDepanner) { this->aDepanner = aDepanner; }

void Intervention::intervenir(bool aIntervenir) {
  this->effectuee = !aIntervenir;
}

/**
 * @brief méthode qui permet de selectionner les bacs
 * @return void
 */
void Intervention::selectionnerBac() {
  for (int i = 0; i < distributeurs.size(); ++i) {
    for (int j = 0; j < distributeurs[i]->getNbBacs(); j++) {
      if (labelsDesCheckbox[i][j]->checkState() == Qt::Checked) {
        if (distributeurs[i]->getBac(j)->getHygrometrie() <=
            TRENTE /*à définir*/) {
          distributeurs[i]->getBac(j)->setADepanner(true);
        }
        distributeurs[i]->getBac(j)->setARemplir(true);
        qDebug() << Q_FUNC_INFO << "etat du bac " << i << " " << j
                 << " à depanner" << distributeurs[i]->getBac(j)->getADepanner()
                 << " à remplir" << distributeurs[i]->getBac(j)->getARemplir();
      } else {
        distributeurs[i]->getBac(j)->setADepanner(false);
        distributeurs[i]->getBac(j)->setARemplir(false);
        qDebug() << Q_FUNC_INFO << "etat du bac " << i << " " << j
                 << " à depanner" << distributeurs[i]->getBac(j)->getADepanner()
                 << " à remplir" << distributeurs[i]->getBac(j)->getARemplir();
      }
    }
  }
  QCheckBox *selectionBac = qobject_cast<QCheckBox *>(sender());
  qDebug() << Q_FUNC_INFO << "checkbox bac" << selectionBac->objectName()
           << "etat" << selectionBac->checkState();
}

/**
 * @brief méthode pour créer une intervention
 * @return void
 */
void Intervention::creerUneIntervention() {
  // requettes sql pour créer l'intervention

  this->close();
}
// Méthodes privées

/**
 * @brief Méthode qui initialise la boîte de dialogue
 */
void Intervention::initialiserBoiteDeDialogue() {
  instancierWidgets();
  initialiserWidgets();
  initialiserEtatDistributeur();
  positionnerWidgets();
  initialiserEvenements();
  setWindowTitle(TITRE_INTERVENTION);
}

/**
 * @brief Méthode qui instancie les widgets de la boîte de dialogue
 */
void Intervention::instancierWidgets() {
  qDebug() << Q_FUNC_INFO;
  boutonItervention = new QPushButton(this);
  dateEdit = new QDateEdit(QDate::currentDate(), this);
  heureEdit = new QTimeEdit(QTime::currentTime(), this);
  for (int i = 0; i < distributeurs.size(); i++) {
    nomDistributeurs.push_back(new QLabel(this));
    labelsBac.clear();
    labelsProduit.clear();
    labelsPourcentage.clear();
    labelsCheckbox.clear();
    labelsHygrometrie.clear();
    for (int j = 0; j < distributeurs[i]->getNbBacs(); j++) {
      QCheckBox *checkbox = new QCheckBox(this);
      checkbox->setObjectName(QString::number(i) + "-" + QString::number(j));
      labelsCheckbox.push_back(checkbox);
      labelsBac.push_back(new QLabel(this));
      labelsProduit.push_back(new QLabel(this));
      labelsPourcentage.push_back(new QLabel(this));
      labelsHygrometrie.push_back(new QLabel(this));
    }
    labelsDesCheckbox.push_back(labelsCheckbox);
    labelsDesBacs.push_back(labelsBac);
    labelsDesProduits.push_back(labelsProduit);
    labelsDesPourcentage.push_back(labelsPourcentage);
    labelsDesHygrometries.push_back(labelsHygrometrie);
  }
  qDebug() << Q_FUNC_INFO << labelsDesBacs;
}

/**
 * @brief Méthode qui initialise les widgets de la boîte de dialogue
 */
void Intervention::initialiserWidgets() {
  qDebug() << Q_FUNC_INFO;
  boutonItervention->setText("créer intervention");
  dateEdit->setDisplayFormat("dd/MM/yyyy");
  heureEdit->setDisplayFormat("HH:mm");
  for (int i = 0; i < distributeurs.size(); i++) {
    nomDistributeurs[i]->setText("Distributeur -> " +
                                 distributeurs[i]->getNom());
    nomDistributeurs[i]->setAlignment(Qt::AlignCenter);

    for (int j = 0; j < distributeurs[i]->getNbBacs(); j++) {
      qDebug() << Q_FUNC_INFO << "produit"
               << distributeurs[i]->getNomProduitBac(j) << "poidsActuel"
               << distributeurs[i]->getBac(j)->getPoidsActuel() << "poidsTotal"
               << distributeurs[i]->getBac(j)->getPoidsTotal()
               << "pourcentageRemplissage"
               << distributeurs[i]->getBac(j)->getPourcentageRemplissage();
      labelsDesBacs[i][j]->setText("Bac n°" + QString::number(j + 1));
      labelsDesBacs[i][j]->setAlignment(Qt::AlignCenter);
      labelsDesProduits[i][j]->setText("Produit du bac : " +
                                       distributeurs[i]->getNomProduitBac(j));
      labelsDesProduits[i][j]->setAlignment(Qt::AlignCenter);
      labelsDesPourcentage[i][j]->setText(
          "Poids à prévoir : " +
          QString::number(distributeurs[i]->getBac(j)->getQuantiteARemplir()) +
          " g ou Kg (à définir)");
      labelsDesPourcentage[i][j]->setAlignment(Qt::AlignCenter);
      labelsDesCheckbox[i][j]->setCheckState(Qt::Unchecked);

      labelsDesHygrometries[i][j]->setText(
          "Hygrometrie : " +
          QString::number(distributeurs[i]->getHygrometrieBac(j)) + "%");
      labelsDesHygrometries[i][j]->setAlignment(Qt::AlignCenter);
    }
  }
}

/**
 * @brief Méthode qui positionne les widgets dans la boîte de dialogue
 */
void Intervention::positionnerWidgets() {
  qDebug() << Q_FUNC_INFO;
  layoutDistributeurs = new QHBoxLayout;
  for (int i = 0; i < distributeurs.size(); i++) {
    totalBac += distributeurs[i]->getNbBacs();
  }
  QVector<QHBoxLayout *> layoutBac(totalBac);

  QVector<QVBoxLayout *> layoutInfoDistributeurs(nomDistributeurs.size());
  for (int i = 0; i < distributeurs.size(); i++) {
    layoutInfoDistributeurs[i] = new QVBoxLayout();
    layoutInfoDistributeurs[i]->addWidget(nomDistributeurs[i]);
    for (int j = 0; j < distributeurs[i]->getNbBacs(); j++) {
      layoutBac[j] = new QHBoxLayout();
      layoutBac[j]->addStretch();
      layoutBac[j]->addWidget(labelsDesBacs[i][j]);
      layoutBac[j]->addWidget(labelsDesCheckbox[i][j]);
      layoutBac[j]->addStretch();
      layoutInfoDistributeurs[i]->addLayout(layoutBac[j]);
      layoutInfoDistributeurs[i]->addWidget(labelsDesProduits[i][j]);
      layoutInfoDistributeurs[i]->addWidget(labelsDesPourcentage[i][j]);
      layoutInfoDistributeurs[i]->addWidget(labelsDesHygrometries[i][j]);
    }
    layoutDistributeurs->addLayout(layoutInfoDistributeurs[i]);
  }
  layoutDistributeurs->addWidget(dateEdit);
  layoutDistributeurs->addWidget(heureEdit);
  layoutDistributeurs->addWidget(boutonItervention);
  setLayout(layoutDistributeurs);
}

/**
 * @brief Méthode qui initialise les connexions signal/slot
 */
void Intervention::initialiserEvenements() {
  for (int i = 0; i < distributeurs.size(); i++) {
    for (int j = 0; j < distributeurs[i]->getNbBacs(); j++) {
      connect(labelsDesCheckbox[i][j], SIGNAL(clicked(bool)), this,
              SLOT(selectionnerBac()));
    }
  }
  connect(boutonItervention, SIGNAL(clicked()), this,
          SLOT(creerUneIntervention()));
}

/**
 * @brief Méthode qui initialise les couleurs des bacs en fonction des
 * pourcentages
 */
void Intervention::initialiserEtatDistributeur() {
  for (int i = 0; i < distributeurs.size(); i++) {
    for (int j = 0; j < distributeurs[i]->getNbBacs(); j++) {
      if ((distributeurs[i]->getPourcentageBac(j) >= ZERO) &&
          (distributeurs[i]->getPourcentageBac(j) <= TRENTE)) {
        qDebug() << Q_FUNC_INFO << "fonction rouge "
                 << distributeurs[i]->getPourcentageBac(j);
        labelsDesBacs[i][j]->setStyleSheet("color: #FF0000;");
      } else if ((distributeurs[i]->getPourcentageBac(j) > TRENTE) &&
                 (distributeurs[i]->getPourcentageBac(j) <= SOIXANTE)) {
        qDebug() << Q_FUNC_INFO << "fonction orange "
                 << distributeurs[i]->getPourcentageBac(j);
        labelsDesBacs[i][j]->setStyleSheet("color: #FFA500;");
      } else if ((distributeurs[i]->getPourcentageBac(j) > SOIXANTE) &&
                 (distributeurs[i]->getPourcentageBac(j) <= CENT)) {
        qDebug() << Q_FUNC_INFO << "fonction vert "
                 << distributeurs[i]->getPourcentageBac(j);
        labelsDesBacs[i][j]->setStyleSheet("color: #023518;");
      }

      if ((distributeurs[i]->getHygrometrieBac(j)) >= ZERO &&
          (distributeurs[i]->getHygrometrieBac(j) <= QUINZE)) {
        labelsDesHygrometries[i][j]->setStyleSheet("color: #FF0000;");
      } else if ((distributeurs[i]->getHygrometrieBac(j)) > QUINZE &&
                 (distributeurs[i]->getHygrometrieBac(j) <= CINQUANTE)) {
        labelsDesHygrometries[i][j]->setStyleSheet("color: #FFA500;");
      } else if ((distributeurs[i]->getHygrometrieBac(j)) > CINQUANTE &&
                 (distributeurs[i]->getHygrometrieBac(j) <= CENT)) {
        labelsDesHygrometries[i][j]->setStyleSheet("color: #023518;");
      }

      if ((distributeurs[i]->getBac(j)->getADepanner()) == true ||
          distributeurs[i]->getBac(j)->getARemplir() == true) {
        labelsDesCheckbox[i][j]->setEnabled(false);
      } else {
        labelsDesCheckbox[i][j]->setEnabled(true);
      }
    }
  }
}
