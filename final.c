#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Struktura do przechowywania informacji o książce
typedef struct {
    char *autor;    // Autor książki
    char *tytul;    // Tytuł książki
    double cena;    // Cena książki
    int ilosc;      // Ilość dostępnych egzemplarzy
} Book;

// Struktura do przechowywania magazynu książek (lista dynamiczna)
typedef struct {
    Book *books;    // Tablica struktur przechowujących informacje o książkach
    int size;       // Aktualny rozmiar magazynu
} Bookstore;

// Funkcja do dodawania nowej książki do magazynu
void add_book(Bookstore *store, const char *autor, const char *tytul, double cena, int ilosc) {
    store->size++;  // Zwiększamy rozmiar magazynu o 1
    store->books = realloc(store->books, store->size * sizeof(Book));  // Realokujemy pamięć dla nowego rozmiaru magazynu

    // Przypisujemy informacje o nowej książce do ostatniego elementu magazynu
    store->books[store->size - 1].autor = strdup(autor);
    store->books[store->size - 1].tytul = strdup(tytul);
    store->books[store->size - 1].cena = cena;
    store->books[store->size - 1].ilosc = ilosc;
}

// Funkcja do usuwania książki z magazynu
void remove_book(Bookstore *store, int id) {
    if (id < 0 || id >= store->size) {  // Sprawdzamy poprawność identyfikatora książki
        g_print("Błędne id\n");  		// Wyświetlamy komunikat o błędnym identyfikatorze
        return;
    }

    free(store->books[id].autor);  // Zwalniamy pamięć dla autora książki
    free(store->books[id].tytul);  // Zwalniamy pamięć dla tytułu książki

    // Przesuwamy wszystkie elementy magazynu od usuwanej książki w lewo, aby zapełnić lukę
    for (int i = id; i < store->size - 1; i++) {
        store->books[i] = store->books[i + 1];
    }

    store->size--;  // Zmniejszamy rozmiar magazynu o 1
    store->books = realloc(store->books, store->size * sizeof(Book));  // Realokujemy pamięć dla nowego rozmiaru magazynu
}


// Funkcja do wyszukiwania książki w magazynie
int find_book(Bookstore *store, const char *tytul) {
    for (int i = 0; i < store->size; i++) {
        // Używamy strcasecmp do porównywania tytułów bez względu na wielkość liter
        if (strcasecmp(store->books[i].tytul, tytul) == 0) {
            return i; // Zwracamy indeks, jeśli tytuł zawiera podaną frazę
        }
    }

    return -1; // Zwracamy -1, jeśli książka nie została znaleziona
}

// Funkcja do wyszukiwania książek w magazynie
int find_books(Bookstore *store, const char *tytul, int *indeksy, int max_id) {
    int count = 0;

    // Konwertujemy wszystkie znaki tytułu na małe
    char low_tytul[100];
    for (int i = 0; i < strlen(tytul); i++) {
        low_tytul[i] = tolower(tytul[i]);
    }
    low_tytul[strlen(tytul)] = '\0';


    for (int i = 0; i < store->size; i++) {
        char low_szuk_tytul[100];

        // Konwertujemy wszystkie znaki tytułu książki w magazynie na małe
        for (int j = 0; j < strlen(store->books[i].tytul); j++) {
            low_szuk_tytul[j] = tolower(store->books[i].tytul[j]);
        }
        low_szuk_tytul[strlen(store->books[i].tytul)] = '\0';

        // Używamy strstr do sprawdzenia, czy tytuł zawiera podaną frazę
        if (strstr(low_szuk_tytul, low_tytul) != NULL) {
            if (count < max_id) {
                indeksy[count] = i; // Zapisujemy indeks do tablicy indeks
            }
            count++;
        }
    }

    return count;
}

// Struktura przechowująca dane dla interfejsu graficznego
typedef struct {
    GtkWidget *autor_entry;      // Pole tekstowe dla autora
    GtkWidget *tytul_entry;      // Pole tekstowe dla tytułu
    GtkWidget *cena_entry;       // Pole tekstowe dla ceny
    GtkWidget *ilosc_entry;      // Pole tekstowe dla ilości
    GtkWidget *wynik;     		 // Etykieta dla wyników operacji
    Bookstore *store;            // Wskaźnik na magazyn książek
} GuiData;

//GuiData gui_data;               // Globalna struktura przechowująca dane interfejsu graficznego


// Funkcja do zapisywania informacji o książkach do pliku
void save_to_file(Bookstore *store) {
    FILE *file = fopen("magazyn.txt", "w");

    if (file == NULL) {
        g_print("Nie można otworzyć pliku do zapisu, tworzę nowy...\n");
        return;
    }
    
    // Iterujemy przez książki w magazynie i zapisujemu ich dane do pliku
    for (int i = 0; i < store->size; i++) {
        fprintf(file, "Autor: %s\nTytuł: %s\nCena: %.2f\nIlość: %d\n\n",
                store->books[i].autor, store->books[i].tytul,
                store->books[i].cena, store->books[i].ilosc);
    }

    fclose(file);
}

// Funkcja do odczytu informacji o książkach z pliku
void load_from_file(Bookstore *store) {
    FILE *file = fopen("magazyn.txt", "r");

    if (file == NULL) {
        g_print("Nie można otworzyć pliku do odczytu.\n");
        return;
    }
    
    // Odczytujemy dane o książkach z pliku i dodajemy ich do magazynu
    while (!feof(file)) {
        Book book;
        char autor[100], tytul[100];
        double cena;
        int ilosc;

        if (fscanf(file, "Autor: %99[^\n]\n", autor) != 1 ||
            fscanf(file, "Tytuł: %99[^\n]\n", tytul) != 1 ||
            fscanf(file, "Cena: %lf\n", &cena) != 1 ||
            fscanf(file, "Ilość: %d\n\n", &ilosc) != 1) {
            break; // Przerywujemy czytanie, jeśli którekolwiek z oczekiwanych pól brakuje.
        }

        // Definiujemy książki danymi z pliku
        book.autor = strdup(autor);
        book.tytul = strdup(tytul);
        book.cena = cena;
        book.ilosc = ilosc;

        // Dodajemy książki do magazynu
        add_book(store, book.autor, book.tytul, book.cena, book.ilosc);
    }
    
    fclose(file);
}

// Funkcja obsługująca dodanie książki
void add_book_clicked(GtkButton *button, GuiData *data) {
    GtkWidget *dialog;
    GtkWidget *autor_label, *tytul_label, *cena_label, *ilosc_label;
    GtkWidget *autor_entry, *tytul_entry, *cena_entry, *ilosc_entry;
    GtkWidget *content_area;
    gint result;

    // Tworzymy okno dialogowe
    dialog = gtk_dialog_new_with_buttons("Dodaj książkę", GTK_WINDOW(data->wynik),
                                         GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_OK,
                                         "Anuluj", GTK_RESPONSE_CANCEL, NULL);

    // Tworzymy treść okna dialogowego
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    autor_label = gtk_label_new("Autor:");
    autor_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), autor_label);
    gtk_container_add(GTK_CONTAINER(content_area), autor_entry);

    tytul_label = gtk_label_new("Tytuł:");
    tytul_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), tytul_label);
    gtk_container_add(GTK_CONTAINER(content_area), tytul_entry);

    cena_label = gtk_label_new("Cena:");
    cena_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), cena_label);
    gtk_container_add(GTK_CONTAINER(content_area), cena_entry);

    ilosc_label = gtk_label_new("Ilość:");
    ilosc_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), ilosc_label);
    gtk_container_add(GTK_CONTAINER(content_area), ilosc_entry);

    gtk_widget_show_all(dialog);

    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_OK) {
        const char *autor = gtk_entry_get_text(GTK_ENTRY(autor_entry));
        const char *tytul = gtk_entry_get_text(GTK_ENTRY(tytul_entry));
        const char *cena_str = gtk_entry_get_text(GTK_ENTRY(cena_entry));
        const char *ilosc_str = gtk_entry_get_text(GTK_ENTRY(ilosc_entry));

        if (strlen(autor) == 0 || strlen(tytul) == 0 || strlen(cena_str) == 0 || strlen(ilosc_str) == 0) {
            gtk_label_set_text(GTK_LABEL(data->wynik), "Wypełnij wszystkie pola!");
            gtk_widget_destroy(dialog);
            return;
        }

        double cena = atof(cena_str);
        int ilosc = atoi(ilosc_str);

        // Dodajemy książkę do magazynu
        add_book(data->store, autor, tytul, cena, ilosc);
        gtk_label_set_text(GTK_LABEL(data->wynik), "Książka dodana do magazynu!");
        
        // Zapisujemy dane do pliku po dodaniu książki
        save_to_file(data->store);
    } else {
        gtk_label_set_text(GTK_LABEL(data->wynik), "Dodawanie książki anulowane.");
    }

    gtk_widget_destroy(dialog);
}

// Funkcja obsługująca usunięcie książki
void remove_book_clicked(GtkButton *button, GuiData *data) {
    GtkWidget *usun_dialog;     			// Okno dialogowe do usunięcia książki
    GtkWidget *tytul_label, *tytul_entry;   // Etykieta i pole tekstowe dla tytułu książki
    GtkWidget *content_area;      			// Obszar treści okna dialogowego
    gint result;                  			// Wynik działania okna dialogowego

    // Tworzymy okno dialogowe do usunięcia książki
    usun_dialog = gtk_dialog_new_with_buttons("Usuń książkę", GTK_WINDOW(data->wynik),
                                                GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_OK,
                                                "Anuluj", GTK_RESPONSE_CANCEL, NULL);

    // Tworzymy treść okna dialogowego
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(usun_dialog));

    tytul_label = gtk_label_new("Tytuł:");
    tytul_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), tytul_label);
    gtk_container_add(GTK_CONTAINER(content_area), tytul_entry);

    gtk_widget_show_all(usun_dialog);

    result = gtk_dialog_run(GTK_DIALOG(usun_dialog));

    if (result == GTK_RESPONSE_OK) {
        const char *tytul = gtk_entry_get_text(GTK_ENTRY(tytul_entry));

        if (strlen(tytul) == 0) {
            gtk_label_set_text(GTK_LABEL(data->wynik), "Wprowadź tytuł do usunięcia!");
            gtk_widget_destroy(usun_dialog);
            return;
        }

        // Znajdujemy indeks książki w magazynie
        int id = find_book(data->store, tytul);

        if (id != -1) {
            // Usuwamy książkę z magazynu
            remove_book(data->store, id);
            gtk_label_set_text(GTK_LABEL(data->wynik), "Książka usunięta z magazynu!");

            // Zapisujemy do pliku po usunięciu książki
            save_to_file(data->store);
        } else {
            gtk_label_set_text(GTK_LABEL(data->wynik), "Książka nie znaleziona w magazynie!");
        }
    } else {
        gtk_label_set_text(GTK_LABEL(data->wynik), "Usuwanie książki anulowane.");
    }

    gtk_widget_destroy(usun_dialog);
}

// Funkcja obsługująca wyszukiwanie książki
void find_book_clicked(GtkButton *button, GuiData *data) {
    GtkWidget *search_dialog;     			// Okno dialogowe do wyszukiwania książki
    GtkWidget *tytul_label, *tytul_entry;   // Etykieta i pole tekstowe dla tytułu książki
    GtkWidget *content_area;      			// Obszar treści okna dialogowego
    gint result;                  			// Wynik działania okna dialogowego

    // Tworzymy okno dialogowe do wyszukiwania książki
    search_dialog = gtk_dialog_new_with_buttons("Znajdź książkę", GTK_WINDOW(data->wynik),
                                                GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_OK,
                                                "Anuluj", GTK_RESPONSE_CANCEL, NULL);

    // Tworzymy treść okna dialogowego
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(search_dialog));

    tytul_label = gtk_label_new("Tytuł:");
    tytul_entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(content_area), tytul_label);
    gtk_container_add(GTK_CONTAINER(content_area), tytul_entry);

    gtk_widget_show_all(search_dialog);

    result = gtk_dialog_run(GTK_DIALOG(search_dialog));

    if (result == GTK_RESPONSE_OK) {
        const char *tytul = gtk_entry_get_text(GTK_ENTRY(tytul_entry));

        if (strlen(tytul) == 0) {
            gtk_label_set_text(GTK_LABEL(data->wynik), "Wprowadź tytuł do wyszukania!");
        } else {
            int indeksy[100];  // Maksymalna liczba indeksów, które chcemy przechować
            int count = find_books(data->store, tytul, indeksy, sizeof(indeksy) / sizeof(indeksy[0]));

            if (count > 0) {
                char result_text[500];  // Zwiększamy rozmiar bufora wynikowego (na wszelki wypadek)
                snprintf(result_text, sizeof(result_text), "Znaleziono %d książek:\n", count);

                // Tworzymy tekst wynikowy z infem o znalezionych książkach
                for (int i = 0; i < count; i++) {
                    int id = indeksy[i];
                    snprintf(result_text + strlen(result_text), sizeof(result_text) - strlen(result_text),
                             "Autor: %s, Tytuł: %s, Cena: %.2f, Ilość: %d\n",
                             data->store->books[id].autor,
                             data->store->books[id].tytul,
                             data->store->books[id].cena,
                             data->store->books[id].ilosc);
                }

                // Wyświetlamy wyniki w nowym oknie dialogowym
                GtkWidget *result_dialog = gtk_dialog_new_with_buttons("Wyniki wyszukiwania", NULL,
                                                                       GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_OK, NULL);
                GtkWidget *result_content_area = gtk_dialog_get_content_area(GTK_DIALOG(result_dialog));
                GtkWidget *wynik = gtk_label_new(result_text);
                gtk_container_add(GTK_CONTAINER(result_content_area), wynik);
                gtk_widget_show_all(result_dialog);

                // Uruchamiamy nowe okno dialogowe z wynikami
                gtk_dialog_run(GTK_DIALOG(result_dialog));
                gtk_widget_destroy(result_dialog);
            } else {
                gtk_label_set_text(GTK_LABEL(data->wynik), "Książka nie znaleziona w magazynie!");
            }
        }
    } else {
        gtk_label_set_text(GTK_LABEL(data->wynik), "Wyszukiwanie książki anulowane.");
    }

    gtk_widget_destroy(search_dialog);
}


// Funkcja obsługująca wyświetlanie listy książek
void show_book_list(GtkButton *button, GuiData *data) {
    GtkWidget *list_window;          // Okno do wyświetlenia listy książek
    GtkWidget *text_view;            // Interfejs? do wyświetlania tekstu
    GtkTextBuffer *text_buffer;      // Bufor tekstu

    // Tworzymy nowe okno
    list_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(list_window), "Lista Książek w Magazynie");
    gtk_window_set_default_size(GTK_WINDOW(list_window), 400, 300);

    // Tworzymy interfejs do wyświetlania tekstu
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);

    // Pobieramy bufor tekstu
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Wprowadzamy info o książkach do bufora tekstu
    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(text_buffer, &iter);

    for (int i = 0; i < data->store->size; i++) {
        gchar *info = g_strdup_printf("Autor: %s\nTytuł: %s\nCena: %.2f\nIlość: %d\n\n",
                                      data->store->books[i].autor, data->store->books[i].tytul,
                                      data->store->books[i].cena, data->store->books[i].ilosc);
        gtk_text_buffer_insert(text_buffer, &iter, info, -1);
        g_free(info);
    }

    // Dodajemy interfejs do okna
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_container_add(GTK_CONTAINER(list_window), scrolled_window);

    // Wyświetlamy okno
    gtk_widget_show_all(list_window);
}

// Funkcja obsługująca zamknięcie okna
void on_window_closed(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    // Inicjalizujemy GTK
    gtk_init(&argc, &argv);

    // Tworzymy okno główne
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Magazyn Książek");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 100, 100);
    g_signal_connect(main_window, "destroy", G_CALLBACK(on_window_closed), NULL);

    // Tworzymy interfejs graficzny
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(main_window), grid);

    // Tworzymy etykiety
    GtkWidget *autor_entry = gtk_entry_new();
    GtkWidget *tytul_entry = gtk_entry_new();
    GtkWidget *cena_entry = gtk_entry_new();
    GtkWidget *ilosc_entry = gtk_entry_new();

    // Tworzymy przyciski
    GtkWidget *add_button = gtk_button_new_with_label("Dodaj książkę");
    GtkWidget *remove_button = gtk_button_new_with_label("Usuń książkę");
    GtkWidget *find_button = gtk_button_new_with_label("Znajdź książkę");
    GtkWidget *show_list_button = gtk_button_new_with_label("Wyświetl listę");

    // Tworzymy etykietę wynikową
    GtkWidget *wynik = gtk_label_new("");

    // Dodajemy elementy do siatki
    gtk_grid_attach(GTK_GRID(grid), add_button, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), remove_button, 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), find_button, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), show_list_button, 0, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), wynik, 0, 4, 2, 1);

    // Inicjalizujemy strukturę do przechowywania danych dla GUI
    GuiData gui_data;
    gui_data.autor_entry = autor_entry;
    gui_data.tytul_entry = tytul_entry;
    gui_data.cena_entry = cena_entry;
    gui_data.ilosc_entry = ilosc_entry;
    gui_data.wynik = wynik;

    // Inicjalizujemy strukturę magazynu
    gui_data.store = malloc(sizeof(Bookstore));
    gui_data.store->books = NULL;
    gui_data.store->size = 0;

    // Wczytujemy dane z pliku podczas uruchamiania programu
    load_from_file(gui_data.store);

    // Łączymy funkcje obsługi przycisków
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_book_clicked), &gui_data);
    g_signal_connect(remove_button, "clicked", G_CALLBACK(remove_book_clicked), &gui_data);
    g_signal_connect(find_button, "clicked", G_CALLBACK(find_book_clicked), &gui_data);
    g_signal_connect(show_list_button, "clicked", G_CALLBACK(show_book_list), &gui_data);

    // Wyświetlamy okno główne
    gtk_widget_show_all(main_window);

    // Uruchamiamy pętlę GTK
    gtk_main();

    // Czyszcimy pamięć
    for (int i = 0; i < gui_data.store->size; i++) {
        free(gui_data.store->books[i].autor);
        free(gui_data.store->books[i].tytul);
    }
    free(gui_data.store->books);
    free(gui_data.store);

    return 0;
}
