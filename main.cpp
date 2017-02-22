#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>


bool wczytajDaneZPliku(std::vector<std::vector<double>>& tempDane, 
		std::string nazwaPliku);
void wyswietlDane(std::vector<std::vector<double>>& tempDane);
std::vector<std::vector<double>> algorytmTomeka(
		std::vector<std::vector<double>>& tmpDane);
double odlegloscPomiedzyDwomaPunktami(std::vector<double>& pierwszyPunkt,
	std::vector<double>& drugiPunkt);


int main()
{
	std::vector<std::vector<double>> dane_wejsciowe;

	if (wczytajDaneZPliku(dane_wejsciowe,"Iris.txt"))
	{
		std::cout<<"Plik nie istnieje!"<<std::endl;
	}

	//wyswietlDane(dane_wejsciowe);

	return 0;
}


bool wczytajDaneZPliku(std::vector<std::vector<double>>& tempDane, 
		std::string nazwaPliku)
{
	std::ifstream input;
	input.open(nazwaPliku);

	if (!input.good())
	{
		return true;
	}

	int liczbaKlas=0, liczbaKolumn=0, liczbaWierszy=0;
	input>>liczbaKlas>>liczbaKolumn>>liczbaWierszy;
	++liczbaKolumn;

	for (int i = 0; i < liczbaWierszy; ++i)
	{
		std::vector<double> tmpVector;
		tmpVector.resize(liczbaKolumn);
		tempDane.push_back(tmpVector);
		for (int j = 0; j < liczbaKolumn; ++j)
		{
			input>>tempDane[i][j];
		}
	}

	input.close();
	return false;
}


void wyswietlDane(std::vector<std::vector<double>>& tempDane)
{
	for(auto& wiersze: tempDane){
		for (auto& kolumny : wiersze)
		{
			std::cout<<kolumny<<"  ";
		}std::cout<<std::endl;
	}
}


double odlegloscPomiedzyDwomaPunktami(std::vector<double>& pierwszyPunkt,
	std::vector<double>& drugiPunkt)
{
	int rozmiar = pierwszyPunkt.size();
	double wynik = 0.0;

	for (int i = 0; i < rozmiar; ++i)
	{
		wynik += std::pow(pierwszyPunkt[i]-drugiPunkt[i], 2.0);
	}

	return wynik;
}


std::vector<std::vector<double>> algorytmTomeka(
	std::vector<std::vector<double>>& tmpDane)
{
	int liczbaWierszy = tmpDane.size();
	int liczbaKolumn = tmpDane[0].size();

	double odleglosc = 0.0;

	std::vector<std::vector<double>> wynik;
	wynik.push_back(tmpDane[0]);

	for (int i = 0; i < liczbaWierszy; ++i)
	{
		/* code */
	}

	return wynik;
}