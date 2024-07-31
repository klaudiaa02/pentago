#include <iostream>
#include <string>
#include <time.h>

using namespace std;

const int wymiarCwiartki = 3;


int wybierzGrę();
void wyświetlMozliwośćWejściaDoMenu(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& zeton1, char& zeton2, int aktualnaGra, string gracz1, string gracz2, int aktualnyGracz, double czasTury, double& suma1, double& suma2);
void pokażMenuObsługiProgramu(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& zeton1, char& zeton2, int aktualnaGra, string gracz1, string gracz2, int aktualnyGracz, double czasTury, double& suma1, double& suma2, bool czyStartRozgrywki);
void wyświetlOpisProgramu(int aktualnaGra);
double wyświetlInformacjeOPrzerwie();

void wypełnijPlanszęStartową(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2]);
void wczytajPredefiniowanąPlanszę(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2);
void wyswietlAktualneDaneGraczy(string gracz1, string gracz2, char zeton1, char zeton2, double suma1, double suma2);
void wyświetlNagłówekPentagoLubKołkoIKrzyzyk(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], string gracz1, string gracz2, char zeton1, char zeton2, bool czyPentago, double suma1, double suma2);

void wyrysujGórnąKrawędźPlanszy();
void wyrysujDolnąKrawędźPlanszy();
void wyrysujSeperatorRzędów();
void wyrysujRządĆwiartek(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], bool czyRządPierwszy);

void wyrysujPlanszę(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2]);

void wybierzŻeton(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& zeton1, char& zeton2, string gracz1, string gracz2);

void wykonajTureGracza(int gracz, string gracz1, string gracz2, char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& wybranaCwiartka, int& wybranePole, char zeton1, char zeton2);
void wykonajDodatkowoObrótĆwiartki(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2]);
bool wstawDoWybranegoMiejscaŻeton(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char wybranaCwiartka, int wybranePole, char zeton, char zeton1, char zeton2);

bool sprawdźRzedyIKolumnyDlaŻetonów(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], bool czySprawdzenieWierszy, char zeton1, char zeton2, bool czyZetonPierwszy);
bool sprawdźSkosyŻetonów(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2, bool czyZetonPierwszy);

void ustalCzasGry(double& suma1, double& suma2);
void liczPozostałyCzasGraczy(double przerwa,double czasTury, double& suma1, double& suma2, int aktualnyGracz);
bool czyPrzekroczonoLimit(double suma1, double suma2);

bool czyWygrano(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2, double suma1, double suma2);

bool czyCałaPlanszaZapełniona(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2]);
int sprawdźwynikGry(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2, double suma1, double suma2);
void wypiszZwyciezceLubPrzegrana(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], string gracz1, string gracz2, char zeton1, char zeton2, double suma1, double suma2);
int wybierzCzyGracDalej();

int main()
{
	char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2];
	int gracz = 1;
	string gracz1, gracz2;
	string aktualnygracz;
	char cwiartka, zeton1 = 'o', zeton2 = 'x';
	int pole;
	int wybranaGra;
	double suma1, suma2;
	bool czyZagracPonownie = true;
	time_t startCzasu, koniecCzasu;
	double sekundyAktualnegoGracza = 0;
	double pauza = 0;

	while (czyZagracPonownie) {

		do {
			wybranaGra = wybierzGrę();
			if (wybranaGra != 1 && wybranaGra != 2) {
				cout << "Blad wyboru gry . Wybierz jeszcze raz." << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
		} while (wybranaGra != 1 && wybranaGra != 2);

		cout << "Podaj imie pierwszego gracza : ";
		cin >> gracz1;
		cout << "Podaj imie drugiego gracza : ";
		cin >> gracz2;
		system("cls");

		wypełnijPlanszęStartową(plansza);

		if (wybranaGra == 1) {

			cout << endl << "Grasz w kolko i krzyzyk 6x6" << endl << endl;

			pokażMenuObsługiProgramu(plansza, zeton1, zeton2, wybranaGra, gracz1, gracz2, gracz, sekundyAktualnegoGracza, suma1, suma2, true);
			ustalCzasGry(suma1, suma2);
			while (!czyWygrano(plansza, zeton1, zeton2, suma1, suma2)) {

				time(&startCzasu);

				system("cls");
				wyświetlNagłówekPentagoLubKołkoIKrzyzyk(plansza, gracz1, gracz2, zeton1, zeton2, false, suma1, suma2);
				wykonajTureGracza(gracz, gracz1, gracz2, plansza, cwiartka, pole, zeton1, zeton2);                               
				system("cls");
				wyświetlNagłówekPentagoLubKołkoIKrzyzyk(plansza, gracz1, gracz2, zeton1, zeton2, false, suma1, suma2);

				if (czyWygrano(plansza, zeton1, zeton2, suma1, suma2))continue;
				pauza = 0;
				wyświetlMozliwośćWejściaDoMenu(plansza, zeton1, zeton2, wybranaGra, gracz1, gracz2, gracz, sekundyAktualnegoGracza, suma1, suma2);

				time(&koniecCzasu);

				sekundyAktualnegoGracza = difftime(koniecCzasu, startCzasu);

				liczPozostałyCzasGraczy(pauza ,sekundyAktualnegoGracza, suma1, suma2, gracz);

				gracz = (gracz % 2) + 1;
			}

			system("cls");

			wypiszZwyciezceLubPrzegrana(plansza, gracz1, gracz2, zeton1, zeton2, suma1, suma1);
		}
		else if (wybranaGra == 2) {

			wybierzŻeton(plansza, zeton1, zeton2, gracz1, gracz2);
			pokażMenuObsługiProgramu(plansza, zeton1, zeton2, wybranaGra, gracz1, gracz2, gracz, sekundyAktualnegoGracza, suma1, suma2, true);
			ustalCzasGry(suma1, suma2);

			while (!czyWygrano(plansza, zeton1, zeton2, suma1, suma2)) {

				time(&startCzasu);

				system("cls");
				wyświetlNagłówekPentagoLubKołkoIKrzyzyk(plansza, gracz1, gracz2, zeton1, zeton2, true, suma1, suma2);
				wykonajTureGracza(gracz, gracz1, gracz2, plansza, cwiartka, pole, zeton1, zeton2);                               
				system("cls");
				wyświetlNagłówekPentagoLubKołkoIKrzyzyk(plansza, gracz1, gracz2, zeton1, zeton2, true, suma1, suma2);
				wykonajDodatkowoObrótĆwiartki(plansza);
				system("cls");
				wyświetlNagłówekPentagoLubKołkoIKrzyzyk(plansza, gracz1, gracz2, zeton1, zeton2, true, suma1, suma2);
				if (czyWygrano(plansza, zeton1, zeton2, suma1, suma2))continue;
				wyświetlMozliwośćWejściaDoMenu(plansza, zeton1, zeton2, wybranaGra, gracz1, gracz2, gracz, sekundyAktualnegoGracza, suma1, suma2);

				time(&koniecCzasu);

				sekundyAktualnegoGracza = difftime(koniecCzasu, startCzasu);

				liczPozostałyCzasGraczy(pauza,sekundyAktualnegoGracza, suma1, suma2, gracz);
				gracz = (gracz % 2) + 1;
			}

			system("cls");

			wypiszZwyciezceLubPrzegrana(plansza, gracz1, gracz2, zeton1, zeton2, suma1, suma2);
		}
		system("PAUSE");

		if (wybierzCzyGracDalej() == 1)
			czyZagracPonownie = true;
		else
			czyZagracPonownie = false;

	}

	system("PAUSE");
	return 0;
}

int wybierzGrę()
{
	int wyborGry;
	cout << "Wybierzcie w ktora gre chcecie zagrac" << endl;
	cout << "1. KOLKO I KRZYZYK" << endl;
	cout << "2. PENTAGO" << endl;
	cin >> wyborGry;
	system("cls");

	return wyborGry;
}

void wyświetlMozliwośćWejściaDoMenu(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& zeton1, char& zeton2, int aktualnaGra, string gracz1, string gracz2, int aktualnyGracz, double czasTury, double& suma1, double& suma2)
{
	string gracz = aktualnyGracz == 1 ? gracz1 : gracz2;
	string wybranaOpcja;
	do {
		cout << gracz << " w menu znajdziesz wiecej opcji oraz informacje o grze" << endl << endl;
		cout << "Menu  (m - wejdz , p - pomin) :";
		cin >> wybranaOpcja;
		if (wybranaOpcja != "m" && wybranaOpcja != "p") {
			cout << "Nieprawidlowo wprowadzono dane. Wpisz jeszcze raz." << endl;
		}
	} while (wybranaOpcja != "m" && wybranaOpcja != "p");

	if (wybranaOpcja == "m") {
		pokażMenuObsługiProgramu(plansza, zeton1, zeton2, aktualnaGra, gracz1, gracz2,aktualnyGracz, czasTury, suma1, suma2 , false);
	}

}
void pokażMenuObsługiProgramu(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& zeton1, char& zeton2, int aktualnaGra, string gracz1, string gracz2, int aktualnyGracz, double czasTury, double& suma1, double& suma2, bool czyStartRozgrywki)
{
	char opcja;
	bool czyPowtarzacMenu = true;

	system("cls");

	while (czyPowtarzacMenu) {
		cout << "Menu :" << endl;
		if (!czyStartRozgrywki)cout << "p - pauza " << endl;
		if(czyStartRozgrywki)cout << "o - wczytanie predefiniowanej planszy" << endl;
		cout << "h - wejscie do opisu programu (gry) " << endl;
		if(aktualnaGra == 2)cout << "z - zmiana zetonow " << endl;
		cout << "w - opuszczenie menu " << endl;
		cout << "Wpisz opcje : ";
		cin >> opcja;
		system("cls");

		if (opcja != 'o' && opcja != 'h' && opcja != 'p'  && opcja != 'z')
			cout << "Nieprawidlowo wpisano opcje z menu." << endl << endl;

		else if (opcja == 'o') {
			wczytajPredefiniowanąPlanszę(plansza, zeton1, zeton2);
			cout << endl << "Wczytano predefiniowana plansze :)" << endl << endl;
		}

		else if (opcja == 'h') {
			system("cls");
			wyświetlOpisProgramu(aktualnaGra);
			system("cls");
		}

		else if (opcja == 'z') {
			system("cls");
			if (aktualnaGra == 2)
				wybierzŻeton(plansza, zeton1, zeton2, gracz1, gracz2);
			else
				cout << "Nieprawidlowo wpisano opcje z menu." << endl << endl;
		}

		else if (opcja == 'p') {
			double przerwa;
			system("cls");
			przerwa = wyświetlInformacjeOPrzerwie();
			liczPozostałyCzasGraczy(przerwa, czasTury, suma1, suma2, aktualnyGracz);
		}

		if (opcja == 'w')
			czyPowtarzacMenu = false;
	}
	system("cls");
}

void wyświetlOpisProgramu(int aktualnaGra)
{
	if (aktualnaGra == 1) {
		cout << "Gra w kolko i krzyzyk na planszy 6x6. Zasady: " << endl;
		cout << "Trzeba postawic piec kolek / krzyzy w linii(poziomej / pionowej badz po skosie). " << endl;
		cout << "Zwycieza osoba, ktora pierwsza ulozy ta linie" << endl << endl;
	}
	else {
		cout << "Pentago jest gra dwuosobowa na planszy.Plansza sklada si3 z 4 ruchomych czesci," << endl;
		cout << "ktore mozna obracac. Kazda czesc zawiera 9 miejsc na zetony. Gracze po kolei " << endl;
		cout << "oddaja ruch skladajacy sie z 2 czesci: " << endl;
		cout << "- dolozenia swojego zetonu na niezajete pole planszy" << endl;
		cout << "- obrot jednej z czesci planszy o 90 stopni w dowolnym kierunku" << endl;
		cout << "Nie mozna zrezygnowac z zadnej czesci ruchu. Wygrywa osoba," << endl;
		cout << "ktorej 5 zetonow, po pelnym ruchu, sa ulozone w rzedzie / kolumnie / po skosach" << endl;
		cout << "(podobnie do gry kolko krzyzyk)." << endl << endl;
	}
	cout << "Jak wstawiaiac zetony :" << endl;
	cout << "Wybranie cwiartki          q - lewa gorna " << endl;
	cout << "                           w - prawa gorna" << endl;
	cout << "                           a - lewa dolna" << endl;
	cout << "                           s - prawa dolna" << endl;
	cout << "Wybor pola od 1 do 9 (klawiatura numeryczna) " << endl;

	int numer[wymiarCwiartki][wymiarCwiartki];
	int liczba = wymiarCwiartki * wymiarCwiartki;

	for (int wiersz = 0; wiersz < wymiarCwiartki; wiersz++) {
		for (int kolumna = 0; kolumna < wymiarCwiartki; kolumna++) {
			numer[wiersz][kolumna] = liczba;
			liczba--;
		}
	}
	for (int wiersz = 0; wiersz < wymiarCwiartki; wiersz++) {
		cout << "                           ";
		for (int kolumna = wymiarCwiartki - 1; kolumna >= 0; kolumna--) {
			cout << ' ' << numer[wiersz][kolumna] << ' ';
		}
		cout << endl;
	}

	if (aktualnaGra == 2) {
		cout << "Jak obrocic cwiartke:" << endl;
		cout << "Wybranie cwiartki  tak samo jak wyzej" << endl;
		cout << "Wybranie strony        	z - obraca w prawo " << endl;
		cout << "                       	x - obraca w lewo";
	}
	cout << endl;
	cout << "GRA JEST NA CZAS , pozostaly czas gry jest wyswietlany obok imienia i zetonu graczy" << endl;
	system("pause");
}

double wyświetlInformacjeOPrzerwie()
{
	time_t poczatekPauzy, koniecPauzy;
	double przerwa;

	time(&poczatekPauzy);
	cout << endl;
	cout << endl;
	cout << "              ****         PAUZA         ****" << endl << endl;
	cout << "(Kliknij cokolwiek, zeby zakonczuc pauze )" << endl;
	system("PAUSE");
	time(&koniecPauzy);
	przerwa = difftime(koniecPauzy, poczatekPauzy);
	return przerwa;

}

// inizjalizuje planszę startową
void wypełnijPlanszęStartową(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2])
{
	for (int wiersz = 0; wiersz < wymiarCwiartki * 2; wiersz++) {
		for (int kolumna = 0; kolumna < wymiarCwiartki * 2; kolumna++) {
			plansza[wiersz][kolumna] = ' ';
		}
	}
}

void wczytajPredefiniowanąPlanszę(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2)
{
	// zeton1 - niebieski   zeton2 - czerwony
	for (int wiersz = 0; wiersz < wymiarCwiartki * 2; wiersz++) {
		for (int kolumna = 0; kolumna < wymiarCwiartki * 2; kolumna++) {
			plansza[wiersz][kolumna] = ' ';
		}
	}
	plansza[0][1] = zeton2;
	plansza[1][2] = zeton2;
	plansza[1][4] = zeton2;
	plansza[4][0] = zeton2;
	plansza[4][4] = zeton2;
	plansza[5][1] = zeton2;
	plansza[5][4] = zeton2;
	plansza[5][5] = zeton2;

	plansza[0][4] = zeton1;
	plansza[1][0] = zeton1;
	plansza[1][1] = zeton1;
	plansza[1][3] = zeton1;
	plansza[2][1] = zeton1;
	plansza[3][0] = zeton1;
	plansza[3][1] = zeton1;
	plansza[4][2] = zeton1;

}
// wyswietla imiona graczy, ich zetony i czasy
void wyswietlAktualneDaneGraczy(string gracz1, string gracz2, char zeton1, char zeton2, double suma1, double suma2)
{

	cout << gracz1 << " twoj zeton '" << zeton1 << "' Pozostalo:" << suma1 << " s" << endl;
	cout << "                            " << gracz2 << " twoj zetono '" << zeton2 << "' Pozostalo:" << suma2 << " s" << endl;
}

// wyświetla nazwe gry aktualne dane graczy(nazwe i ich zetony) oraz ich czas
void wyświetlNagłówekPentagoLubKołkoIKrzyzyk(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], string gracz1, string gracz2, char zeton1, char zeton2, bool czyPentago, double suma1, double suma2)
{
	if (czyPentago)
		cout << "Gra w PENTAGO               ";
	else
		cout << "Gra w kolko i krzyzyk       ";
	wyswietlAktualneDaneGraczy(gracz1, gracz2, zeton1, zeton2, suma1, suma2);
	wyrysujPlanszę(plansza);
}

// zamienia na wybrane zetony
void wybierzŻeton(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& zeton1, char& zeton2, string gracz1, string gracz2)
{
	char miejsceZetonow[wymiarCwiartki * 2][wymiarCwiartki * 2];

	// zapisanie miejsca w którym sa poszczególne zetony
	for (int wiersz = 0; wiersz < wymiarCwiartki * 2; wiersz++) {
		for (int kolumna = 0; kolumna < wymiarCwiartki * 2; kolumna++) {
			if (plansza[wiersz][kolumna] == zeton1)
				miejsceZetonow[wiersz][kolumna] = 1;
			else if (plansza[wiersz][kolumna] == zeton2)
				miejsceZetonow[wiersz][kolumna] = 2;
		}
	}
	cout << "Jakimi zetonami bedziecie grali ?" << endl;
	cout << gracz1 << " wybierz swoj zeton, ktorym bedziesz grac :";
	cin >> zeton1;
	cout << endl;

	do {
		cout << gracz2 << " wybierz swoj zeton, ktorym bedziesz grac :";
		cin >> zeton2;
		if (zeton2 == zeton1)
			cout << "Nie mozesz wybrac tego samego zetonu co " << gracz1 << endl;
	} while (zeton2 == zeton1);

	// zamiana starych zetonów na nowe
	for (int wiersz = 0; wiersz < wymiarCwiartki * 2; wiersz++) {
		for (int kolumna = 0; kolumna < wymiarCwiartki * 2; kolumna++) {
			if (miejsceZetonow[wiersz][kolumna] == 1)
				plansza[wiersz][kolumna] = zeton1;
			else if (miejsceZetonow[wiersz][kolumna] == 2)
				plansza[wiersz][kolumna] = zeton2;
		}
	}

	system("cls");
}

void wyrysujGórnąKrawędźPlanszy()
{
	char prawyRogGorny = char(187); // ╗ 
	char lewyRogGorny = char(201); // ╔ 
	char separatorKrawedziGornej = char(203); // ╦ 
	char separatorPoziomy = char(205); // ═

	cout << lewyRogGorny;
	for (int i = 0; i < wymiarCwiartki - 1; i++)
	{
		for (int j = 0; j < wymiarCwiartki; j++)
			cout << separatorPoziomy;
		cout << separatorKrawedziGornej;
	}
	for (int i = 0; i < wymiarCwiartki; i++)
		cout << separatorPoziomy;
	cout << prawyRogGorny << "  " << lewyRogGorny;
	for (int i = 0; i < wymiarCwiartki - 1; i++)
	{
		for (int j = 0; j < wymiarCwiartki; j++)
			cout << separatorPoziomy;
		cout << separatorKrawedziGornej;
	}
	for (int i = 0; i < wymiarCwiartki; i++)
		cout << separatorPoziomy;
	cout << prawyRogGorny << endl;
}

void wyrysujDolnąKrawędźPlanszy()
{
	char prawyDolnyRog = char(188); // ╝ 
	char lewyDolnyRog = char(200); // ╚ 
	char separatorKrawedziDolnej = char(202); // ╩ 
	char separatorPoziomy = char(205); // ═

	cout << lewyDolnyRog;
	for (int i = 0; i < wymiarCwiartki - 1; i++)
	{
		for (int i = 0; i < wymiarCwiartki; i++)
			cout << separatorPoziomy;
		cout << separatorKrawedziDolnej;
	}
	for (int i = 0; i < wymiarCwiartki; i++)
		cout << separatorPoziomy;
	cout << prawyDolnyRog << "  " << lewyDolnyRog;
	for (int i = 0; i < wymiarCwiartki - 1; i++)
	{
		for (int i = 0; i < wymiarCwiartki; i++)
			cout << separatorPoziomy;
		cout << separatorKrawedziDolnej;
	}
	for (int i = 0; i < wymiarCwiartki; i++)
		cout << separatorPoziomy;
	cout << prawyDolnyRog << endl;
}

void wyrysujSeperatorRzędów()
{
	char separatorKrawedziBocznejPrawej = char(185); // ╣ 
	char separatorKrawedziBocznejLewej = char(204); // ╠
	char separatorPoziomy = char(205); // ═
	char separatporSrodkowy = char(206); // ╬ 

	cout << separatorKrawedziBocznejLewej;
	for (int m = 0; m < wymiarCwiartki - 1; m++)
	{
		for (int i = 0; i < wymiarCwiartki; i++)
			cout << separatorPoziomy;
		cout << separatporSrodkowy;
	}
	for (int i = 0; i < wymiarCwiartki; i++)
		cout << separatorPoziomy;
	cout << separatorKrawedziBocznejPrawej << "  " << separatorKrawedziBocznejLewej;
	for (int m = 0; m < wymiarCwiartki - 1; m++)
	{
		for (int i = 0; i < wymiarCwiartki; i++)
			cout << separatorPoziomy;
		cout << separatporSrodkowy;
	}
	for (int i = 0; i < wymiarCwiartki; i++)
		cout << separatorPoziomy;
	cout << separatorKrawedziBocznejPrawej << endl;
}

// wypisuje zawartosci planszy (z ramką)
void wyrysujRządĆwiartek(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], bool czyRządPierwszy)
{
	char separatorPionowy = char(186); // ║
	int numerWierszaPoczątkowego = czyRządPierwszy ? 0 : 3;

	for (int wiersz = numerWierszaPoczątkowego; wiersz < numerWierszaPoczątkowego + wymiarCwiartki; wiersz++)
	{
		cout << separatorPionowy;
		//cwiartka lewa górna || lewa dolna
		for (int kolumna = 0; kolumna < wymiarCwiartki; kolumna++)
		{
			cout << ' ' << plansza[wiersz][kolumna] << ' ' << separatorPionowy;
		}
		cout << "  " << separatorPionowy;

		//cwiartka prawa górna || prawa dolna
		for (int kolumna = wymiarCwiartki; kolumna < wymiarCwiartki * 2; kolumna++)
		{
			cout << ' ' << plansza[wiersz][kolumna] << ' ' << separatorPionowy;
		}
		cout << endl;

		if (wiersz == numerWierszaPoczątkowego + wymiarCwiartki - 1) continue;
		wyrysujSeperatorRzędów();
	}
}

// funkcja wyrysowuje planszę w ramce
void wyrysujPlanszę(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2])
{

	cout << 'q' << "                " << 'w' << endl;
	wyrysujGórnąKrawędźPlanszy();

	wyrysujRządĆwiartek(plansza, true); // cwiartka q i w

	wyrysujDolnąKrawędźPlanszy();
	wyrysujGórnąKrawędźPlanszy();

	wyrysujRządĆwiartek(plansza, false); // cwiartka a i s

	wyrysujDolnąKrawędźPlanszy();

	cout << 'a' << "                " << 's' << endl << endl;
}

// funkcja wczytuje w ktorym miejscu wstawic zetony, sprawdza czy wogóle mozna je tam postawic 
void wykonajTureGracza(int gracz, string gracz1, string gracz2, char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char& wybranaCwiartka, int& wybranePole, char zeton1, char zeton2)
{
	string aktualnyGracz = gracz == 1 ? gracz1 : gracz2;
	char zeton = gracz == 1 ? zeton1 : zeton2;
	do {
		cout << aktualnyGracz;
		cout << " wybierz miejsce na wstawienie '" << zeton << "' ." << endl;
		do {
			cout << "Na poczatku podaj cwiartke do wstawienia (q, w, a, s ): ";
			cin >> wybranaCwiartka;
			if (wybranaCwiartka != 'q' && wybranaCwiartka != 'w' && wybranaCwiartka != 'a' && wybranaCwiartka != 's')
				cout << "Nie ma takiej cwiartki" << endl;;
		} while (wybranaCwiartka != 'q' && wybranaCwiartka != 'w' && wybranaCwiartka != 'a' && wybranaCwiartka != 's');

		cout << "Podaj pole (od 1 do 9 ) : ";
		while (!(cin >> wybranePole) || !(wybranePole >= 1 && wybranePole <= wymiarCwiartki * wymiarCwiartki)) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Podaj pole (od 1 do 9 - klawiatura numeryczna( 1 - lewy dol ) : ";
		}
	} while (!(wstawDoWybranegoMiejscaŻeton(plansza, wybranaCwiartka, wybranePole, zeton, zeton1, zeton2)));

}

// wczytywanie danych do wpisania zetonow  
bool wstawDoWybranegoMiejscaŻeton(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char wybranaCwiartka, int wybranePole, char zeton, char zeton1, char zeton2)
{
	int poczatekKolumny, poczatekWiersza;
	bool czyMoznaWstawic;

	if (wybranaCwiartka == 'q') {
		poczatekWiersza = 0;
		poczatekKolumny = 0;
	}
	else if (wybranaCwiartka == 'w') {
		poczatekWiersza = 0;
		poczatekKolumny = wymiarCwiartki;
	}
	else if (wybranaCwiartka == 'a') {
		poczatekWiersza = wymiarCwiartki;
		poczatekKolumny = 0;
	}
	else {
		poczatekWiersza = wymiarCwiartki;
		poczatekKolumny = wymiarCwiartki;
	}

	int pole = wybranePole - 1;

	int wiersz = poczatekWiersza + ((wymiarCwiartki * wymiarCwiartki - 1 - pole) / wymiarCwiartki);
	int kolumna = poczatekKolumny + (pole % wymiarCwiartki);

	if (plansza[wiersz][kolumna] == zeton1 || plansza[wiersz][kolumna] == zeton2) {
		czyMoznaWstawic = false;
	}
	else {
		czyMoznaWstawic = true;
		plansza[wiersz][kolumna] = zeton;
	}

	return czyMoznaWstawic;
}

void wykonajDodatkowoObrótĆwiartki(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2])
{
	int poczatekKolumny, poczatekWiersza;
	char wybranaStrona;
	char wybranaCwiartka;
	bool zleDane = true;

	while (zleDane) {
		cout << "Wybierz cwiartke do obrotu(q, w, a, s ): ";
		cin >> wybranaCwiartka;
		if (wybranaCwiartka == 'q' || wybranaCwiartka == 'w' || wybranaCwiartka == 'a' || wybranaCwiartka == 's')
			zleDane = false;
	}
	zleDane = true;
	while (zleDane) {
		cout << "Wybierz w ktora strone cwiartka ma sie obrocic (z- w prawo , x- w lewo): ";
		cin >> wybranaStrona;
		if (wybranaStrona == 'z' || wybranaStrona == 'x')
			zleDane = false;
	}

	if (wybranaCwiartka == 'q') {
		poczatekWiersza = 0;
		poczatekKolumny = 0;
	}
	else if (wybranaCwiartka == 'w') {
		poczatekWiersza = 0;
		poczatekKolumny = wymiarCwiartki;
	}
	else if (wybranaCwiartka == 'a') {
		poczatekWiersza = wymiarCwiartki;
		poczatekKolumny = 0;
	}
	else {
		poczatekWiersza = wymiarCwiartki;
		poczatekKolumny = wymiarCwiartki;
	}

	int licznik = 0;
	char buf[wymiarCwiartki * wymiarCwiartki];

	// obrót ćwiartki w prawo 
	if (wybranaStrona == 'z') {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				buf[licznik] = plansza[j + poczatekWiersza][i % 3 + poczatekKolumny];
				licznik++;
			}
		}
		licznik = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				plansza[i % 3 + poczatekWiersza][2 + poczatekKolumny - j] = buf[licznik];
				licznik++;
			}
		}
	}
	// obrót ćwiartki w lewo 
	else {
		for (int powtorzono = 0; powtorzono < wymiarCwiartki; powtorzono++) {
			licznik = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					buf[licznik] = plansza[j + poczatekWiersza][i % 3 + poczatekKolumny];
					licznik++;
				}
			}
			licznik = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					plansza[i % 3 + poczatekWiersza][2 + poczatekKolumny - j] = buf[licznik];
					licznik++;
				}
			}
		}
	}
}

// sprawdza wygrana dla poziomu lub pionu dla żetonu1 lub żetonu2
bool sprawdźRzedyIKolumnyDlaŻetonów(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], bool czySprawdzenieWierszy, char zeton1, char zeton2, bool czyZetonPierwszy) {

	int liczbaZetonow = 0;
	bool czy5v6Podrzad = false;

	string poTymPrzeszukujeTablice = czySprawdzenieWierszy ? "wiersz" : "kolumna";


	char badanyZeton = czyZetonPierwszy ? zeton1 : zeton2;

	for (int poTymPrzeszukujeTablice = 0; poTymPrzeszukujeTablice < wymiarCwiartki * 2; poTymPrzeszukujeTablice++) {

		//od poczatku wiersza do końca
		if (czySprawdzenieWierszy)
		{
			if (plansza[poTymPrzeszukujeTablice][0] == badanyZeton) {
				liczbaZetonow = 1;
				for (int kolumna = 1; kolumna < wymiarCwiartki * 2; kolumna++) {
					if (plansza[poTymPrzeszukujeTablice][kolumna] == badanyZeton)
						liczbaZetonow++;
					else
						liczbaZetonow = 0;
				}

				if (liczbaZetonow >= (wymiarCwiartki * 2 - 1)) {
					czy5v6Podrzad = true;
				}
			}
		}
		// od poczatku kolumny na dół
		else
		{
			if (plansza[0][poTymPrzeszukujeTablice] == badanyZeton) {
				liczbaZetonow = 1;
				for (int wiersz = 1; wiersz < wymiarCwiartki * 2; wiersz++) {
					if (plansza[wiersz][poTymPrzeszukujeTablice] == badanyZeton)
						liczbaZetonow++;
					else
						liczbaZetonow = 0;
				}

				if (liczbaZetonow >= (wymiarCwiartki * 2 - 1)) {
					czy5v6Podrzad = true;
				}
			}
		}

	}
	liczbaZetonow = 0;
	for (int poTymPrzeszukujeTablice = 0; poTymPrzeszukujeTablice < wymiarCwiartki * 2; poTymPrzeszukujeTablice++) {

		//od końca wiersza do poczatku
		if (czySprawdzenieWierszy)
		{
			if (plansza[poTymPrzeszukujeTablice][wymiarCwiartki * 2 - 1] == badanyZeton) {
				liczbaZetonow = 1;
				for (int kolumna = (wymiarCwiartki * 2 - 2); kolumna >= 0; kolumna--) {
					if (plansza[poTymPrzeszukujeTablice][kolumna] == badanyZeton)
						liczbaZetonow++;
				}

				if (liczbaZetonow >= (wymiarCwiartki * 2 - 1)) {
					czy5v6Podrzad = true;
				}
			}
		}
		// od końca kolumny na górę
		else
		{
			if (plansza[wymiarCwiartki * 2 - 1][poTymPrzeszukujeTablice] == badanyZeton) {
				liczbaZetonow = 1;
				for (int wiersz = (wymiarCwiartki * 2 - 2); wiersz >= 0; wiersz--) {
					if (plansza[wiersz][poTymPrzeszukujeTablice] == badanyZeton)
						liczbaZetonow++;
				}

				if (liczbaZetonow >= (wymiarCwiartki * 2 - 1)) {
					czy5v6Podrzad = true;
				}
			}
		}

	}

	return czy5v6Podrzad;
}

bool sprawdźSkosyŻetonów(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2, bool czyZetonPierwszy)
{
	int liczbaZetonow = 0;
	bool czy5v6Podrzad = false;

	char badanyZeton = czyZetonPierwszy ? zeton1 : zeton2;

	//od poczatku wiersza i kolumny (z prawej górnej do lewej dolnej)
	if (plansza[0][0] == badanyZeton) {
		liczbaZetonow = 1;
		for (int wiersz = 1; wiersz < wymiarCwiartki * 2; wiersz++) {
			if (plansza[wiersz][wiersz] == badanyZeton)
				liczbaZetonow++;
			else if ((plansza[wiersz][wiersz] != badanyZeton) && liczbaZetonow != 5)
				liczbaZetonow = 0;
		}
	}
	if (liczbaZetonow >= (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	//od końca wiersza i kolumny (z lewej dolnej do prawej górnej)
	liczbaZetonow = 0;
	if (plansza[5][5] == badanyZeton) {
		liczbaZetonow = 1;
		for (int wiersz = 4; wiersz >= 0; wiersz--) {
			if (plansza[wiersz][wiersz] == badanyZeton)
				liczbaZetonow++;
			else if ((plansza[wiersz][wiersz] != badanyZeton) && liczbaZetonow != 5)
				liczbaZetonow = 0;
		}
	}
	if (liczbaZetonow >= (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	//od końca wiersza i poczatku kolumny ( z prawej górnej do lewej dolnej)
	liczbaZetonow = 0;
	if (plansza[0][wymiarCwiartki * 2 - 1] == badanyZeton) {
		liczbaZetonow = 1;
		for (int i = 1; i < wymiarCwiartki * 2; i++) {
			if (plansza[i][wymiarCwiartki * 2 - 1 - i] == badanyZeton)
				liczbaZetonow++;
			else if ((plansza[i][wymiarCwiartki * 2 - 1 - i] != badanyZeton) && liczbaZetonow != 5)
				liczbaZetonow = 0;
		}
	}
	if (liczbaZetonow >= (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	//od poczatku wiersza i konca kolumny ( z lewej dolnej do prawej górnej )
	liczbaZetonow = 0;
	if (plansza[wymiarCwiartki * 2 - 1][0] == badanyZeton) {
		liczbaZetonow = 1;
		for (int i = (wymiarCwiartki * 2 - 2); i >= 0; i--) {
			if (plansza[i][wymiarCwiartki * 2 - 1 - i] == badanyZeton)
				liczbaZetonow++;
			else if ((plansza[i][wymiarCwiartki * 2 - 1 - i] != badanyZeton) && liczbaZetonow != 5)
				liczbaZetonow = 0;
		}
	}

	if (liczbaZetonow >= (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	// skos dolny z lewej góry do prawego dołu 
	liczbaZetonow = 0;
	for (int wiersz = 1; wiersz < wymiarCwiartki * 2; wiersz++) {
		if (plansza[wiersz][wiersz - 1] == badanyZeton)
			liczbaZetonow++;
	}
	if (liczbaZetonow == (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	// skos górny z lewej góry do prawego dołu
	liczbaZetonow = 0;
	for (int wiersz = 0; wiersz < wymiarCwiartki * 2; wiersz++) {
		if (plansza[wiersz][wiersz + 1] == badanyZeton)
			liczbaZetonow++;
	}
	if (liczbaZetonow == (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	//skos góryny z prawej góry do lewego dołu 
	liczbaZetonow = 0;
	for (int wiersz = 0; wiersz < wymiarCwiartki * 2 - 1; wiersz++) {
		if (plansza[wiersz][wymiarCwiartki + 1 - wiersz] == badanyZeton)
			liczbaZetonow++;
	}
	if (liczbaZetonow == (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	//skos dolny z prawej góry do lewego dołu
	liczbaZetonow = 0;
	for (int wiersz = 1; wiersz < wymiarCwiartki * 2; wiersz++) {
		if (plansza[wiersz][wymiarCwiartki * 2 - wiersz] == badanyZeton)
			liczbaZetonow++;
	}
	if (liczbaZetonow == (wymiarCwiartki * 2 - 1))
		czy5v6Podrzad = true;

	return czy5v6Podrzad;
}

void ustalCzasGry(double& suma1, double& suma2)
{
	double suma;

	cout << "Podajcie limit czasu, ktory chcecie miec na gre w sekundach (np. '180' sekund)" << endl;
	cout << "Zakres czasu nalezy podac od 60 do 300" << endl;
	while (!(cin >> suma) || !(suma >= 60 && suma <= 300 ) ){
		cout << "Zle wprowadzony czas, podaj jeszcze raz . (od 60 do 300)";
		cin.clear();
		cin.ignore(100, '\n');
	}
	system("cls");

	suma1 = suma;
	suma2 = suma;

}

void liczPozostałyCzasGraczy( double przerwa, double czasTury, double& suma1, double& suma2, int aktualnyGracz)
{
	if (aktualnyGracz == 1) {
		suma1 -= czasTury;
		suma1 += przerwa;
	}
	else {
		suma2 -= czasTury;
		suma2 += przerwa;
	}
}

bool czyPrzekroczonoLimit(double suma1, double suma2)
{
	bool czyKtosPrzekroczyl;
	if (suma1 <= 0)
		czyKtosPrzekroczyl = true;

	else if (suma2 <= 0)
		czyKtosPrzekroczyl = true;

	else
		czyKtosPrzekroczyl = false;
	return czyKtosPrzekroczyl;
}

bool czyCałaPlanszaZapełniona(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2])
{
	int liczbaZajetychPol = 0;
	bool czyZapelniona;

	for (int wiersz = 0; wiersz < wymiarCwiartki * 2; wiersz++) {
		for (int kolumna = 0; kolumna < wymiarCwiartki * 2; kolumna++) {
			if (plansza[wiersz][kolumna] == ' ') {
				liczbaZajetychPol++;
			}
		}
	}
	if (liczbaZajetychPol == 0) {
		czyZapelniona = true;
	}
	else
		czyZapelniona = false;

	return czyZapelniona;

}

bool czyWygrano(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2, double suma1, double suma2)
{
	bool czyWarunkiWygranejSpelniono = false;

	if (sprawdźRzedyIKolumnyDlaŻetonów(plansza, true, zeton1, zeton2, true) || sprawdźRzedyIKolumnyDlaŻetonów(plansza, false, zeton1, zeton2, true))
		czyWarunkiWygranejSpelniono = true;

	else if (sprawdźRzedyIKolumnyDlaŻetonów(plansza, true, zeton1, zeton2, false) || sprawdźRzedyIKolumnyDlaŻetonów(plansza, false, zeton1, zeton2, false))
		czyWarunkiWygranejSpelniono = true;

	else if (sprawdźSkosyŻetonów(plansza, zeton1, zeton2, true) || sprawdźSkosyŻetonów(plansza, zeton1, zeton2, false))
		czyWarunkiWygranejSpelniono = true;

	// brak możliwości wygranej(cała plansza zapełniona) spełnia wyjście z funkcji czy wygrano
	else if (czyCałaPlanszaZapełniona(plansza))
		czyWarunkiWygranejSpelniono = true;

	//  brak możliwości wygranej(skończył się czas) spełnia wyjście z funkcji czy wygrano 
	else if (czyPrzekroczonoLimit(suma1, suma2))
		czyWarunkiWygranejSpelniono = true;

	return czyWarunkiWygranejSpelniono;
}

int sprawdźwynikGry(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], char zeton1, char zeton2, double suma1, double suma2)
{
	int zwyciezca = 6;

	if ((sprawdźRzedyIKolumnyDlaŻetonów(plansza, true, zeton1, zeton2, true) || sprawdźRzedyIKolumnyDlaŻetonów(plansza, false, zeton1, zeton2, true) || sprawdźSkosyŻetonów(plansza, zeton1, zeton2, true)) && !czyPrzekroczonoLimit(suma1, suma2))
		zwyciezca = 1;
	else if ((zwyciezca == 1) && czyPrzekroczonoLimit(suma1, suma2)) {
		if (suma1 <= 0)
			zwyciezca = 4;
	}
	if ((sprawdźRzedyIKolumnyDlaŻetonów(plansza, true, zeton1, zeton2, false) || sprawdźRzedyIKolumnyDlaŻetonów(plansza, false, zeton1, zeton2, false) || sprawdźSkosyŻetonów(plansza, zeton1, zeton2, false)) && !czyPrzekroczonoLimit(suma1, suma2))
	{
		if (zwyciezca == 1) {
			zwyciezca = 3;
		}
		else {
			zwyciezca = 2;
		}
	}
	else if ((zwyciezca == 2) && czyPrzekroczonoLimit(suma1, suma2)) {
		if (suma2 <= 0)
			zwyciezca = 5;
	}
	else if (czyPrzekroczonoLimit(suma1, suma2)) {
		if (suma2 <= 0)
			zwyciezca = 5;
		else if (suma1 <= 0)
			zwyciezca = 4;
	} 

	return zwyciezca;
}

void wypiszZwyciezceLubPrzegrana(char plansza[wymiarCwiartki * 2][wymiarCwiartki * 2], string gracz1, string gracz2, char zeton1, char zeton2, double suma1, double suma2)
{

	switch (sprawdźwynikGry(plansza, zeton1, zeton2, suma1, suma2)) {
	case 1:
		cout << endl;
		cout << "  ***     Gratulacje wygrywa        ***    " << gracz1 << "    ***" << endl;
		wyrysujPlanszę(plansza);
		break;
	case 2:
		cout << endl;
		cout << "  ***     Gratulacje wygrywa        ***    " << gracz2 << "    ***" << endl;
		wyrysujPlanszę(plansza);
		break;
	case 3:
		cout << endl;
		cout << "  ***      Gratulacje REMIS      ***" << endl;
		wyrysujPlanszę(plansza);
		break;
	case 4:
		cout << endl;
		cout << "             BRAK WYGRANEJ   :(((((((((" << endl;
		cout << gracz1 << " przekroczyles limit czasu przegrywasz :(" << endl;
		wyrysujPlanszę(plansza);
		break;
	case 5:
		cout << endl;
		cout << "             BRAK WYGRANEJ   :(((((((((" << endl;
		cout << gracz2 << " przekroczyles limit czasu przegrywasz :(" << endl;
		wyrysujPlanszę(plansza);
		break;
	default:
		cout << endl;
		cout << "             BRAK WYGRANEJ   :(((((((((" << endl;
		wyrysujPlanszę(plansza);
		break;
	}
}

int wybierzCzyGracDalej()
{
	string odpowiedzCzyGracDalej;
	int decyzja;
	do {
		system("cls");
		cout << endl;
		cout << "Czy chcecie grac dalej ? ( t - tak , n - nie )" << endl;
		cin >> odpowiedzCzyGracDalej;
	} while (odpowiedzCzyGracDalej != "T" && odpowiedzCzyGracDalej != "t" && odpowiedzCzyGracDalej != "N" && odpowiedzCzyGracDalej != "n");
	if (odpowiedzCzyGracDalej == "t" || odpowiedzCzyGracDalej == "T") {
		decyzja = 1;
	}
	else
		decyzja = 2;
	return decyzja;
}

