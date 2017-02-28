#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>


bool wczytajDaneZPliku(std::vector<std::vector<double>>& tempDane, 
		std::string nazwaPliku);
void wyswietlDane(std::vector<std::vector<double>>& tempDane);
std::vector<std::vector<double>> algorytmHarta(
		std::vector<std::vector<double>> tmpDane);
double odlegloscPomiedzyDwomaPunktami(std::vector<double>& pierwszyPunkt,
	std::vector<double>& drugiPunkt);


int main()
{
	std::vector<std::vector<double>> dane_wejsciowe;
	std::vector<std::vector<double>> dane_wyjsciowe;

	if (wczytajDaneZPliku(dane_wejsciowe,"Epj.txt"))
	{
		std::cout<<"Plik nie istnieje!"<<std::endl;
	}

	//wyswietlDane(dane_wejsciowe);
	dane_wyjsciowe = algorytmHarta(dane_wejsciowe);
	wyswietlDane(dane_wyjsciowe);
	std::cout<<"\n";
	std::cout<<"Liczba znalezionych probek: "<<dane_wyjsciowe.size()<<std::endl;

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

	for (int i = 1; i < rozmiar; ++i)
	{
		wynik += std::pow(pierwszyPunkt[i]-drugiPunkt[i], 2.0);
	}

	return wynik;
}


std::vector<std::vector<double>> algorytmHarta(
	std::vector<std::vector<double>> tmpDane)
{
	std::vector<std::vector<double>> wynik;
	int maxIloscProbek = tmpDane.size();
	int iloscWylosowanychProbek = 0;
	std::random_device rd;
    std::mt19937 gen(rd());

	while(iloscWylosowanychProbek <= maxIloscProbek) {
		++iloscWylosowanychProbek;
		int obecnyRozmiar = tmpDane.size();
		std::uniform_int_distribution<> dist(0, obecnyRozmiar-1);
		int wylosowanaProbka = dist(gen);
		double aktualnaNajblizszaOdleglosc = 0.0;
		int najblizszyIndex = 0;

		for (int i = 0; i < obecnyRozmiar; ++i)
		{
			if(i == wylosowanaProbka)
				continue;

			double liczeNajblizszaOdleglosc = 
					odlegloscPomiedzyDwomaPunktami(tmpDane[wylosowanaProbka],tmpDane[i]);
		
			if(aktualnaNajblizszaOdleglosc == 0.0){
				aktualnaNajblizszaOdleglosc = liczeNajblizszaOdleglosc;
				najblizszyIndex = i;
			}
			else if(liczeNajblizszaOdleglosc < aktualnaNajblizszaOdleglosc){
				aktualnaNajblizszaOdleglosc = liczeNajblizszaOdleglosc;
				najblizszyIndex = i;
			}
		}

		if(tmpDane[wylosowanaProbka][0] != tmpDane[najblizszyIndex][0]){
			wynik.push_back(tmpDane[najblizszyIndex]);
			tmpDane.erase(tmpDane.begin()+najblizszyIndex);
		}
	}

	return wynik;
}