#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


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

int main(){
	std::vector<std::vector<double>> dane_wejsciowe;
	std::vector<std::vector<double>> dane_wyjsciowe;

	if (wczytajDaneZPliku(dane_wejsciowe,"Iris.txt")){
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
		std::string nazwaPliku){
	std::ifstream input;
	input.open(nazwaPliku);

	if (!input.good()){
		return true;
	}

	int liczbaKlas=0, liczbaKolumn=0, liczbaWierszy=0;
	input>>liczbaKlas>>liczbaKolumn>>liczbaWierszy;
	++liczbaKolumn;

	for (int i = 0; i < liczbaWierszy; ++i){
		std::vector<double> tmpVector;
		tmpVector.resize(liczbaKolumn);
		tempDane.push_back(tmpVector);
		for (int j = 0; j < liczbaKolumn; ++j){
			input>>tempDane[i][j];
		}
	}

	input.close();
	return false;
}


void wyswietlDane(std::vector<std::vector<double>>& tempDane){
	for(auto& wiersze: tempDane){
		for (auto& kolumny : wiersze){
			std::cout<<kolumny<<"  ";
		}
		std::cout<<std::endl;
	}
}


double odlegloscPomiedzyDwomaPunktami(std::vector<double>& pierwszyPunkt,
	std::vector<double>& drugiPunkt){
	int rozmiar = pierwszyPunkt.size();
	double wynik = 0.0;

	for (int i = 1; i < rozmiar; ++i){
		wynik += std::pow(pierwszyPunkt[i]-drugiPunkt[i], 2.0);
	}

	return wynik;
}


std::vector<double> liczSrodekCiezkosci(std::vector<std::vector<double>> tmpDane){
	std::vector<double> wynik(tmpDane[0].size(),0);
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

	for (int i = 0; i < tmpDane.size(); ++i){
		for (int j = 0; j < tmpDane.size()-1; ++j){
			if(odlegloscPomiedzyDwomaPunktami(tmpDane[j],srodek) > odlegloscPomiedzyDwomaPunktami(tmpDane[j+1],srodek)){
				std::swap(tmpDane[j],tmpDane[j+1]);
			}
		}
	}

	return tmpDane;
}


std::vector<std::vector<double>> algorytmHarta(std::vector<std::vector<double>> tmpDane){
	std::vector<std::vector<double>> wynik;
	tmpDane=sortowanieElementow(tmpDane,liczSrodekCiezkosci(tmpDane));
	bool stop = true;
	std::vector<bool> sprCzyOdwiedzony(tmpDane.size(),false);
	
	while(std::find(sprCzyOdwiedzony.begin(),sprCzyOdwiedzony.end(),false) != sprCzyOdwiedzony.end()){
		if (wynik.empty()){
			wynik.push_back(tmpDane[0]);
			tmpDane.erase(tmpDane.begin());
			sprCzyOdwiedzony.erase(sprCzyOdwiedzony.begin());
			continue;
		}

		sprCzyOdwiedzony.clear();
		sprCzyOdwiedzony.resize(tmpDane.size(),false);

		for (int i = 0; i < tmpDane.size(); ++i){
			double aktualnaOdleglosc = 0.0; 
			int indexNajblizszegoElementu = 0;
			for (int j = 0; j < wynik.size(); ++j){
				double obliczonaOdleglosc = odlegloscPomiedzyDwomaPunktami(tmpDane[i],wynik[j]);
				if (aktualnaOdleglosc == 0.0){
					aktualnaOdleglosc = obliczonaOdleglosc;
				}
				else if(aktualnaOdleglosc > obliczonaOdleglosc){
					aktualnaOdleglosc = obliczonaOdleglosc;
					indexNajblizszegoElementu = j;
				}
			}

			if(wynik[indexNajblizszegoElementu][0] == tmpDane[i][0]){
				sprCzyOdwiedzony[i]=true;
			}
			else{
				wynik.push_back(tmpDane[i]);
				tmpDane.erase(tmpDane.begin()+i);
				sprCzyOdwiedzony.erase(sprCzyOdwiedzony.begin()+i);
			}

			for (int j = 0; j < wynik.size(); ++j){
				if(sprCzyOdwiedzony[i]){
					double obliczonaOdleglosc = odlegloscPomiedzyDwomaPunktami(tmpDane[i],wynik[j]);
					if(aktualnaOdleglosc == 0.0){
						aktualnaOdleglosc = obliczonaOdleglosc;
					}
					else if(aktualnaOdleglosc > obliczonaOdleglosc){
						aktualnaOdleglosc = obliczonaOdleglosc;
						indexNajblizszegoElementu = j;
					}
				}
			}

			if(wynik[indexNajblizszegoElementu][0] != tmpDane[i][0]){
				wynik.push_back(tmpDane[i]);
				tmpDane.erase(tmpDane.begin()+i);
				sprCzyOdwiedzony.erase(sprCzyOdwiedzony.begin()+i);
			}
		}
	}

	return wynik;
}