#include <fstream>
#include <iostream>
#include <vector>


bool wczytajDaneZPliku(std::vector<std::vector<double>>& tempDane, 
	int& kolumny, int& wiersze, std::string nazwaPliku);

void wyswietlDane(std::vector<std::vector<double>>& tempDane);


int main()
{
	
	std::vector<std::vector<double>> dane_wejsciowe;
	int liczbaKolumn=0, liczbaWierszy=0;

	if (wczytajDaneZPliku(dane_wejsciowe,liczbaKolumn,liczbaWierszy,"Iris.txt"))
	{
		std::cout<<"Plik nie istnieje!"<<std::endl;
	}

	wyswietlDane(dane_wejsciowe);
	

	return 0;
}


bool wczytajDaneZPliku(std::vector<std::vector<double>>& tempDane, 
	int& kolumny, int& wiersze, std::string nazwaPliku){

	std::ifstream input;
	input.open(nazwaPliku);

	if (!input.good())
	{
		return true;
	}

	int liczbaKlas=0;
	input>>liczbaKlas>>kolumny>>wiersze;
	++kolumny;

	for (int i = 0; i < wiersze; ++i)
	{
		std::vector<double> t;
		t.resize(kolumny);
		tempDane.push_back(t);
		for (int j = 0; j < kolumny; ++j)
		{
			input>>tempDane[i][j];
		}
	}

	input.close();
	return false;
}


void wyswietlDane(std::vector<std::vector<double>>& tempDane){
	for(auto& wiersze: tempDane){
		for (auto& kolumny : wiersze)
		{
			std::cout<<kolumny<<"  ";
		}std::cout<<std::endl;
	}
}