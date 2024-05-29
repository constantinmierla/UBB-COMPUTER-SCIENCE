#pragma once
#include <string>
using namespace std;
class Error
{
private:
	// mesajul erorii
	string errorMessage;

public:
	// constructorul clasei de erori
	Error(string& errorMessage) : errorMessage(errorMessage) {};

	// getter pentru mesajul erorii
	const string& getMessage() const noexcept
	{
		return errorMessage;
	}
};

class InvalidCarError : public Error
{
public:
	// constructorul clasei de erori de validare
	// eroarea apare atunci cand atributele unei masini sunt invalide
	InvalidCarError(string errorMessage) : Error(errorMessage) {};
};

class InexistentCarError : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand cautam / modificam / stergem o masina inexistenta
	InexistentCarError(string errorMessage) : Error(errorMessage) {};
};

class ExistentCarError : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci adaugam o masina deja existenta
	ExistentCarError(string errorMessage) : Error(errorMessage) {};
};

class EmptyListError : public Error
{
public:
	// constructuroul clasei de erori
	// eroarea apare atunci cand lista de masini este vida (la filtrari)
	EmptyListError(string errorMessage) : Error(errorMessage) {};
};

class InvalidSortingMode : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand utilizatorul introduce un mod de sortare invalid
	InvalidSortingMode(string errorMessage) : Error(errorMessage) {};
};

class InvalidLicensePlate : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand utilizatorul introduce un numar de inmatriculare invalid
	InvalidLicensePlate(string errorMessage) : Error(errorMessage) {};
};

class InvalidGenerateNumber : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand utilizatorul vrea sa genereze mai multe masini decat exista
	// in repository-ul curent
	InvalidGenerateNumber(string errorMessage) : Error(errorMessage) {};
};

class InvalidFileError : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand nu putem deschide un fisier
	InvalidFileError(string errorMessage) : Error(errorMessage) {};
};