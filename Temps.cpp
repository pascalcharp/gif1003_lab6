/****************************************************************************//**
 * \file Temps.cpp
 *
 *  \Created on: 2020-10-01
 *  \Author: Pascal Charpentier
 */

#include "Temps.h"
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>

static const int MAX_HEURE = 24;


static const int MAX_MINUTE = 60;
static const int MAX_SECONDE = 60;

static const int HEURE_PAR_DEFAUT = 0;
static const int MINUTE_PAR_DEFAUT = 0;
static const int SECONDE_PAR_DEFAUT = 0;

bool Temps::valider()
{
	return validerHeure(m_heure) && validerMinute(m_minute) && validerSeconde(m_seconde);
}
/**
 *
 * \brief Vérifie qu'une heure possède une valeur acceptable
 *
 * \param[in] heure La valeur entière à vérifier.
 *
 * \return true si la valeur est supérieure à zéro et inférieure à 24.
 */

bool Temps::validerHeure(int heure)
{
	return (heure < MAX_HEURE) and (heure >= 0);
}

/**
 * \fn validerMinute
 *
 * \brief Vérifie qu'une valeur entière puisse désigner un nombre de minutes
 *
 * \param[in] valeur entière à tester
 *
 * \return true si la valeur est comprise entre 0 et 60
 */

bool Temps::validerMinute(int minute)
{
	return (minute >= 0) and (minute < MAX_MINUTE);
}

/**
 * \fn validerSeconde
 *
 * \brief Vérifie si une valeur entière désigne un nombre de secondes
 *
 * \param[in] la valeur entière à vérifier
 *
 * \return true si la valeur est comprise entre 0 et 60
 */

bool Temps::validerSeconde(int seconde)
{
	return (seconde >= 0) and (seconde < MAX_SECONDE);
}

int Temps::convertirHeure() const
{

	return (m_heure == 12) ? 12 : (m_heure % 12);

}

/****************************************************************************//**
 * \fn Constructeur
 *
 * \brief Crée un objet Temps à partir de 3 entiers
 *
 * \param[in] heure Nombre entier représentant les heures
 * \param[in] minute Nombre entier représentant les minutes
 * \param[in] secondes Nombre entier représentant les secondes
 *
 */

Temps::Temps(const int heure, const int minute, const int seconde) : m_heure(heure), m_minute(minute), m_seconde(seconde)
{
	assert(validerHeure(heure) && validerMinute(minute) && validerSeconde(seconde));
	assert(valider());
}


/****************************************************************************//**
 * \fn Constructeur par défaut
 *
 * \brief Crée un objet Temps à partir de l'heure système
 *
 */

Temps::Temps()
{
	std::time_t maintenant = std::time(0);
	struct std::tm *heureActuelle = std::localtime(&maintenant);

	m_heure = heureActuelle->tm_hour;
	m_minute = heureActuelle->tm_min;
	m_seconde = heureActuelle->tm_sec;

	assert(valider());
}

/****************************************************************************//**
 * \fn reqHeure
 *
 * \brief Accède au membre m_heure
 *
 * \return La valeur du membre m_heure
 */

int Temps::reqHeure() const
{
	return m_heure;
}

/****************************************************************************//**
 * \fn reqMinute
 *
 * \brief Accède au membre m_minute
 *
 * \return La valeur du membre m_minute
 */

int Temps::reqMinute() const
{
	return m_minute;
}

/****************************************************************************//**
 * \fn reqSeconde
 *
 * \brief Accède au membre m_seconde
 *
 * \return La valeur du membre m_minute
 */

int Temps::reqSeconde() const
{
	return m_seconde;
}

/****************************************************************************//**
 * \fn modifierHeure
 *
 * \brief Change la valeur du champ heure
 *
 * Si la valeur entrée n'est pas admissible, soit comprise entre 0 et 24, une valeur
 * par défaut de 0 est utilisée.
 *
 * \param[in] La nouvelle valeur
 *
 */

void Temps::modifierHeure(const int nouvelleHeure)
{
	assert(validerHeure(nouvelleHeure));
	m_heure = validerHeure(nouvelleHeure) ? nouvelleHeure : HEURE_PAR_DEFAUT;
	assert(valider());
}

/****************************************************************************//**
 * \fn modifierMinute
 *
 * \brief Change la valeur du champ minute
 *
 * Si la valeur entrée n'est pas admissible, soit comprise entre 0 et 60, une valeur
 * par défaut de 0 est utilisée.
 *
 * \param[in] La nouvelle valeur
 */

void Temps::modifierMinute(const int nouvelleMinute)
{
	assert(validerMinute(nouvelleMinute));
	m_minute = validerMinute(nouvelleMinute) ? nouvelleMinute : MINUTE_PAR_DEFAUT;
	assert(valider());
}

/****************************************************************************//**
 * \fn modifierSeconde
 *
 * \brief Change la valeur du champ seconde
 *
 * Si la valeur entrée n'est pas admissible, soit comprise entre 0 et 60, une valeur
 * par défaut de 0 est utilisée.
 *
 * \param[in] La nouvelle valeur
 */

void Temps::modifierSeconde(const int nouvelleSeconde)
{
	assert(validerSeconde(nouvelleSeconde));
	m_seconde = validerSeconde(nouvelleSeconde) ? nouvelleSeconde : SECONDE_PAR_DEFAUT;
	assert(valider());
}

/****************************************************************************//**
 * \fn modifier
 *
 * \brief Change les valeurs des champs à partir de 3 valeurs
 *
 * \param[in] la nouvelle heure
 * \param[in] la nouvelle minute
 * \param[in] la nouvelle valeur des secondes
 *
 */

void Temps::modifier(const int nouvelleHeure, const int nouvelleMinute, const int nouvelleSeconde)
{
	modifierHeure(nouvelleHeure);
	modifierMinute(nouvelleMinute);
	modifierSeconde(nouvelleSeconde);

	assert(valider());
}

/****************************************************************************//**
 * \fn modifier
 *
 * \brief Modifie les champs à-partir d'un texte contenant le nouveau temps.
 *
 * La chaîne de caractère peut contenir une heure, une heure et des minutes,
 * une heure et des minutes et des secondes.  Les champs sont séparés par un caractère
 * qui est systématiquement ignoré.
 *
 * param[in] Une chaîne de caractères
 */

void Temps::modifier(const std::string texte)
{
	std::stringstream champs;

	int heure = m_heure;
	int minute = m_minute;
	int seconde = m_seconde;

	champs << texte;

	if (champs >> heure)
	{
		champs.ignore();
		if (champs >> minute)
		{
			champs.ignore();
			champs >> seconde;
		}
	}

	modifier(heure, minute, seconde);
	assert(valider());
}

void Temps::avancerUneHeure()
{
	m_heure = (m_heure == 23) ? 0 : (m_heure + 1);
	assert(valider());
}

void Temps::avancerUneMinute()
{
	if (m_minute == 59)
	{
		m_minute = 0;
		avancerUneHeure();
	}
	else
	{
		m_minute += 1;
	}
	assert(valider());
}

void Temps::tic()
{
	if (m_seconde == 59)
	{
		m_seconde = 0;
		avancerUneMinute();
	}
	else
	{
		m_seconde += 1;
	}
	assert(valider());
}

/****************************************************************************//**
 * \fn formatter
 *
 * \brief Génère une chaîne de caractères à partir d'un objet Temps au format 24h
 *
 * La chaîne contient les champs heure minute et seconde séparés par un caractère.
 *
 * \param[in] le caractère séparateur
 */

std::string Temps::formatter(const std::string separateur) const
{
	std::stringstream flux;
	std::string texte;

	flux << std::setfill('0') << std::setw(2) << m_heure << separateur << std::setfill('0') << std::setw(2) << m_minute << separateur << std::setfill('0') << std::setw(2) << m_seconde;
	flux >> texte;

	return texte;
}

/****************************************************************************//**
 * \fn formatter12
 *
 * \brief Génère une chaîne de caractères à partir d'un objet Temps au format 12h am-pm
 *
 * La chaîne contient les champs heure minute et seconde séparés par un caractère.
 *
 * \param[in] le caractère séparateur
 */
std::string Temps::formatter12(const std::string separateur) const
{
	std::stringstream flux;
	std::string texte;
	std::string marqueur = (m_heure / 12) ? "PM" : "AM";

	flux << std::setfill('0') << std::setw(2) << convertirHeure() << separateur << std::setfill('0') << std::setw(2) << m_minute << separateur << std::setfill('0') << std::setw(2) << m_seconde << marqueur;
	flux >> texte;

	return texte;
}

/****************************************************************************//**
 * \fn affiche
 *
 * \brief fonction de déboggage qui affiche à l'écran les champs d'un objet Temps
 *
 */

void Temps::affiche() const
{
	std::cout << "H: " << m_heure << " M: " << m_minute << " S: " << m_seconde << std::endl;
}

std::ostream& operator<< (std::ostream& os, const Temps& temps)
{
	os << temps.formatter();
	return os;
}



