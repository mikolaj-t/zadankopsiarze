#include <iostream>
#include <fstream>

using namespace std;

struct osoba{
	string imie;
	string nazwisko;
	int wiek;
	char pies;
};

int ilosc;
osoba* osoby;

bool load(){
	ifstream plik;
	plik.open("ilosc_osob.txt");
	if(!plik.good()) return false;
	plik>>ilosc;
	osoby = new osoba[ilosc];
	plik.close();
	plik.open("osoby.txt");
	if(!plik.good()) return false;
	int item = 0;
	int pole = 0;
	while(!plik.eof()){
		switch(pole){
			case 0:
				plik>>osoby[item].imie;
				break;
			case 1:
				plik>>osoby[item].nazwisko;
				break;
			case 2:
				plik>>osoby[item].wiek;
				break;
			case 3:
				plik>>osoby[item].pies;
				item++;
				pole=-1;
				break;
		}
		pole++;
	}
	return true;
}

bool save(){
	ofstream plik;
	plik.open("ilosc_osob.txt");
	if(!plik.good()) return false;
	plik<<ilosc;
	plik.close();
	plik.open("osoby.txt", ios::app);
	plik.clear();
	if(!plik.good()) return false;
	for(int i=0; i<ilosc; i++){
		plik<<osoby[i].imie<<" ";
		plik<<osoby[i].nazwisko<<" ";
		plik<<osoby[i].wiek<<" ";
		plik<<osoby[i].pies<<" ";
		plik<<endl;
	}
	return true;
}

bool save(osoba os){
	ofstream plik;
	plik.open("ilosc_osob.txt");
	if(!plik.good()) return false;
	plik<<ilosc;
	plik.close();
	plik.open("osoby.txt", ios::app);
	plik.clear();
	if(!plik.good()) return false;
	plik<<endl;
	plik<<os.imie<<" ";
	plik<<os.nazwisko<<" ";
	plik<<os.wiek<<" ";
	plik<<os.pies<<" ";
	return true;
}

void wypisz(){
	for(int i=0; i<ilosc; i++){
		cout<<osoby[i].imie<<" "<<osoby[i].nazwisko<<" "<<osoby[i].pies<<" "<<osoby[i].wiek<<endl;
	}
}

void menu(){
	cout<<"1 - dopisanie"<<endl;
	cout<<"2 - ile osob ma psa"<<endl;
	cout<<"3 - ile osob nie ma psa"<<endl;
	cout<<"4 - srednia wieku"<<endl;
	cout<<"5 - najstarszy"<<endl;
	cout<<"6 - najmlodszy"<<endl;
	cout<<"7 - wyjscie"<<endl<<endl;
}

void dodaj(osoba os){
	osoba* nowaTab;
	nowaTab = new osoba[ilosc+1];
	for(int i=0; i<ilosc; i++){
		nowaTab[i]=osoby[i];
	}
	nowaTab[ilosc] = os;
	osoby = nowaTab;
	ilosc++;
	save(os);
}

void dopisz(){
	osoba os;
	cout<<"Podaj imie"<<endl;
	cin>>os.imie;
	cout<<"Podaj nazwisko"<<endl;
	cin>>os.nazwisko;
	cout<<"Podaj wiek"<<endl;
	cin>>os.wiek;
	cout<<"Podaj czy ma psa"<<endl;
	cin>>os.pies;
	dodaj(os);
}

int ileMa(){
	int ile = 0;
	for(int i=0; i<ilosc; i++){
		if(osoby[i].pies == 't') ile++;
	}
	return ile;
}

int ileNieMa(){
	int ile = 0;
	for(int i=0; i<ilosc; i++){
		if(osoby[i].pies == 'f') ile++;
	}
	return ile;
}

double srednia(){
	int suma = 0;
	for(int i=0; i<ilosc; i++){
		suma+=osoby[i].wiek;
	}
	double srednia = ((double)suma/(double)ilosc);
	return srednia;
}

osoba najstarszy(){
	osoba max = osoby[0];
	for(int i=1; i<ilosc; i++){
		if(osoby[i].wiek > max.wiek){
			max = osoby[i];
		}
	}	
	return max;
}

osoba najmlodszy(){
	osoba min = osoby[0];
	for(int i=1; i<ilosc; i++){
		if(osoby[i].wiek < min.wiek){
			min = osoby[i];
		}
	}	
	return min;
}

int main(){
	if(load()){
		int wybor=-1;
		do{
			cout<<"Wybierz opcje: "<<endl;
			menu();
			cin>>wybor;
			cout<<endl;
			if(wybor==1) dopisz();
			if(wybor==2) cout<<ileMa()<<" osob ma psa"<<endl<<endl;
			if(wybor==3) cout<<ileNieMa()<<" osob nie ma psa"<<endl<<endl;
			if(wybor==4) cout<<"Srednia wieku wynosi "<<srednia()<<" lat"<<endl<<endl;
			if(wybor==5){
				osoba os = najstarszy();
				cout<<"Najstarsza osoba to: "<<os.imie<<" "<<os.nazwisko<<". Ma "<<os.wiek<<" lat"<<endl<<endl;
			}
			if(wybor==6){	
				osoba os = najmlodszy();
				cout<<"Najmlodsza osoba to: "<<os.imie<<" "<<os.nazwisko<<". Ma "<<os.wiek<<" lat"<<endl<<endl;
			}
		}while(wybor!=7);
		return 1;	
	}else{
		cout<<"Nie udalo sie zaladowac pliku!"<<endl;
		return 0;
	}
}
