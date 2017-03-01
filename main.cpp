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
std::vector<double> liczSrodekCiezkosci(std::vector<std::vector<double>> tmpDane);
std::vector<std::vector<double>> sortowanieElementow(std::vector<std::vector<double>> tmpDane,
		std::vector<double> srodek);

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
	//wyswietlDane(dane_wyjsciowe);
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


std::vector<double> liczSrodekCiezkosci(std::vector<std::vector<double>> tmpDane){
	std::vector<double> wynik(tmpDane[0].size()-1,0);
	int rozmiar = tmpDane.size();

	for (int i = 1; i < tmpDane[0].size(); ++i){
		for (int j = 0; j < rozmiar; ++j){
		wynik[i] += tmpDane[j][i];
		}
		wynik[i] /= rozmiar;
	}
	return wynik;
}


std::vector<std::vector<double>> sortowanieElementow(std::vector<std::vector<double>> tmpDane,
	std::vector<double> srodek){

	for (int i = 0; i < tmpDane.size(); ++i)
	{
		for (int j = 0; j < tmpDane.size()-1; ++j)
		{
			if(odlegloscPomiedzyDwomaPunktami(tmpDane[j],srodek) > odlegloscPomiedzyDwomaPunktami(tmpDane[j+1],srodek)){
				std::swap(tmpDane[j],tmpDane[j+1]);
			}
		}
	}

	return tmpDane;
}


std::vector<std::vector<double>> algorytmHarta(std::vector<std::vector<double>> tmpDane){
	std::vector<std::vector<double>> wynik;
	wynik=sortowanieElementow(wynik,liczSrodekCiezkosci(wynik));
	bool stop = true;
	wynik.push_back(tmpDane[0]);
	wynik.erase(wynik.begin());

	/*while(stop){
		
	}*/

	return wynik;
}