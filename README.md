# Magazyn Książek - Aplikacja GTK do Zarządzania Książkami

## Opis Projektu

"Magazyn Książek" to aplikacja stworzona w języku C z użyciem biblioteki GTK, która pozwala na zarządzanie kolekcją książek. Umożliwia dodawanie, usuwanie, wyszukiwanie oraz wyświetlanie listy książek przechowywanych w magazynie. Dane o książkach są zapisywane i odczytywane z pliku tekstowego.

## Wymagania

- GTK+ 3.0
- Kompilator C (np. `gcc`)

## Kompilacja i Uruchomienie

1. Zainstaluj GTK+ 3.0:

    Na Ubuntu:
    ```bash
    sudo apt-get update
    sudo apt-get install libgtk-3-dev
    ```

2. Sklonuj repozytorium i przejdź do katalogu projektu:
    ```bash
    git clone https://github.com/twoj-uzytkownik/magazyn-ksiazek.git
    cd magazyn-ksiazek
    ```

3. Skompiluj kod:
    ```bash
    gcc -o magazyn_ksiazek magazyn_ksiazek.c `pkg-config --cflags --libs gtk+-3.0`
    ```

4. Uruchom aplikację:
    ```bash
    ./magazyn_ksiazek
    ```

## Funkcjonalności

### Dodawanie Książki

Aby dodać nową książkę do magazynu, kliknij przycisk "Dodaj książkę" i wprowadź dane (autor, tytuł, cena, ilość) w wyświetlonym oknie dialogowym. Po zatwierdzeniu książka zostanie dodana do magazynu i zapisana w pliku `magazyn.txt`.

### Usuwanie Książki

Aby usunąć książkę, kliknij przycisk "Usuń książkę", wprowadź tytuł książki w oknie dialogowym i zatwierdź. Książka zostanie usunięta z magazynu, a plik `magazyn.txt` zostanie zaktualizowany.

### Wyszukiwanie Książki

Kliknij "Znajdź książkę", wprowadź tytuł lub jego fragment w oknie dialogowym i zatwierdź. Wyświetlone zostaną informacje o wszystkich książkach, które pasują do podanego tytułu.

### Wyświetlanie Listy Książek

Aby wyświetlić listę wszystkich książek w magazynie, kliknij przycisk "Wyświetl listę". W nowym oknie zobaczysz pełną listę z informacjami o autorze, tytule, cenie i ilości każdej książki.

## Struktura Kodów

### Struktury Danych

- `Book`: Przechowuje informacje o książce (autor, tytuł, cena, ilość).
- `Bookstore`: Przechowuje dynamiczną listę książek oraz ich aktualną liczbę.
- `GuiData`: Przechowuje widgety GTK oraz wskaźnik na magazyn książek.

### Funkcje

- `add_book(Bookstore *store, const char *autor, const char *tytul, double cena, int ilosc)`: Dodaje nową książkę do magazynu.
- `remove_book(Bookstore *store, int id)`: Usuwa książkę z magazynu na podstawie jej indeksu.
- `find_book(Bookstore *store, const char *tytul)`: Wyszukuje książkę w magazynie na podstawie tytułu.
- `find_books(Bookstore *store, const char *tytul, int *indeksy, int max_id)`: Wyszukuje książki pasujące do podanego tytułu i zwraca ich indeksy.
- `save_to_file(Bookstore *store)`: Zapisuje dane magazynu do pliku `magazyn.txt`.
- `load_from_file(Bookstore *store)`: Odczytuje dane z pliku `magazyn.txt` i ładuje je do magazynu.
- `add_book_clicked(GtkButton *button, GuiData *data)`: Obsługuje zdarzenie kliknięcia przycisku "Dodaj książkę".
- `remove_book_clicked(GtkButton *button, GuiData *data)`: Obsługuje zdarzenie kliknięcia przycisku "Usuń książkę".
- `find_book_clicked(GtkButton *button, GuiData *data)`: Obsługuje zdarzenie kliknięcia przycisku "Znajdź książkę".
- `show_book_list(GtkButton *button, GuiData *data)`: Wyświetla listę książek w nowym oknie.
- `on_window_closed(GtkWidget *widget, gpointer data)`: Obsługuje zamknięcie głównego okna.

## Cel Aplikacji

Aplikacja została stworzona jako przykład użycia języka C i biblioteki GTK+ do zarządzania magazynem książek.

