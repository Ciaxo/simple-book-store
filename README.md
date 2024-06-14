Magazyn Książek - README
Opis Projektu

Magazyn Książek to aplikacja desktopowa napisana w języku C z użyciem biblioteki GTK+, która umożliwia zarządzanie kolekcją książek. Aplikacja pozwala na dodawanie, usuwanie, wyszukiwanie oraz wyświetlanie listy książek w magazynie. Dane o książkach są przechowywane w pliku tekstowym, co umożliwia ich trwałe przechowywanie pomiędzy uruchomieniami aplikacji.
Funkcjonalności

    Dodawanie książki: Użytkownik może dodać nową książkę do magazynu, podając autora, tytuł, cenę oraz ilość dostępnych egzemplarzy.
    Usuwanie książki: Użytkownik może usunąć książkę z magazynu, podając tytuł książki.
    Wyszukiwanie książki: Użytkownik może wyszukać książkę w magazynie po tytule.
    Wyświetlanie listy książek: Użytkownik może wyświetlić pełną listę książek dostępnych w magazynie.
    Zapis i odczyt z pliku: Aplikacja automatycznie zapisuje dane o książkach do pliku przy dodawaniu lub usuwaniu książki oraz odczytuje dane z pliku przy uruchamianiu.

Struktury Danych
Struktura Book

Przechowuje informacje o pojedynczej książce.

c

typedef struct {
    char *autor;
    char *tytul;
    double cena;
    int ilosc;
} Book;

Struktura Bookstore

Dynamiczna lista przechowująca książki.

typedef struct {
    Book *books;
    int size;
} Bookstore;

Struktura GuiData

Przechowuje widgety GTK+ oraz wskaźnik na magazyn książek, potrzebne do obsługi interfejsu graficznego.

typedef struct {
    GtkWidget *autor_entry;
    GtkWidget *tytul_entry;
    GtkWidget *cena_entry;
    GtkWidget *ilosc_entry;
    GtkWidget *wynik;
    Bookstore *store;
} GuiData;

Instalacja i Uruchomienie

    Zainstaluj GTK+:
        Na Ubuntu: sudo apt-get install libgtk-3-dev
        Na Fedora: sudo dnf install gtk3-devel
        Na MacOS: brew install gtk+3
    Skompiluj kod:

    gcc -o magazyn_ksiazek magazyn_ksiazek.c `pkg-config --cflags --libs gtk+-3.0`

Uruchom aplikację:

    ./magazyn_ksiazek

Użycie

    Dodawanie książki: Kliknij przycisk "Dodaj książkę" i wypełnij pola w oknie dialogowym.
    Usuwanie książki: Kliknij przycisk "Usuń książkę" i wprowadź tytuł książki do usunięcia.
    Wyszukiwanie książki: Kliknij przycisk "Znajdź książkę" i wprowadź tytuł książki do wyszukania.
    Wyświetlanie listy książek: Kliknij przycisk "Wyświetl listę", aby zobaczyć wszystkie książki w magazynie.

Szczegóły Techniczne
Funkcje

    Dodawanie książki:

    void add_book(Bookstore *store, const char *autor, const char *tytul, double cena, int ilosc);

    Usuwanie książki:

    void remove_book(Bookstore *store, int id);

    Wyszukiwanie książki:

    int find_book(Bookstore *store, const char *tytul);

    Wyszukiwanie wielu książek:

    int find_books(Bookstore *store, const char *tytul, int *indeksy, int max_id);

    Zapisywanie danych do pliku:

    void save_to_file(Bookstore *store);

    Odczytywanie danych z pliku:

    void load_from_file(Bookstore *store);

Funkcje GTK+

    Inicjalizacja interfejsu graficznego:

    c

    int main(int argc, char *argv[]);

    Obsługa przycisków:
        Dodawanie książki: void add_book_clicked(GtkButton *button, GuiData *data);
        Usuwanie książki: void remove_book_clicked(GtkButton *button, GuiData *data);
        Wyszukiwanie książki: void find_book_clicked(GtkButton *button, GuiData *data);
        Wyświetlanie listy książek: void show_book_list(GtkButton *button, GuiData *data);
    Zamykanie okna: void on_window_closed(GtkWidget *widget, gpointer data);

Inne
Aplikacja została stworzona jako przykład użycia języka C i biblioteki GTK+ do zarządzania magazynem książek.
