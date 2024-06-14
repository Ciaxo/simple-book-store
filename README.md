# Bookstore - GTK Application for Book Management

## Project Description

"Bookstore" is an application written in C using the GTK library, which allows managing a book collection. It enables adding, removing, searching, and displaying a list of books stored in the repository. Book data is saved to and read from a text file.

## Requirements

- GTK+ 3.0
- C Compiler (e.g., gcc)

## Compilation and Execution

1. Install GTK+ 3.0:

    On Ubuntu:
    ```bash
    sudo apt-get update
    sudo apt-get install libgtk-3-dev
    ```

2. Clone the repository and navigate to the project directory:
    ```bash
    git clone https://github.com/twoj-uzytkownik/magazyn-ksiazek.git
    cd magazyn-ksiazek
    ```

3. Compile the code:
    ```bash
    gcc -o magazyn_ksiazek magazyn_ksiazek.c `pkg-config --cflags --libs gtk+-3.0`
    ```

4. Run the application:
    ```bash
    ./magazyn_ksiazek
    ```

## Features

### Adding a Book

To add a new book to the repository, click the "Add Book" button and enter the details (author, title, price, quantity) in the displayed dialog box. After confirming, the book will be added to the repository and saved to the `magazyn.txt` file.

### Removing a Book

To remove a book, click the "Remove Book" button, enter the book's title in the dialog box, and confirm. The book will be removed from the repository, and the `magazyn.txt` file will be updated.

### Searching for a Book

Click "Find Book", enter the full title or a fragment of it in the dialog box, and confirm. Information about all books matching the provided title will be displayed.

### Displaying the List of Books

To display the list of all books in the repository, click the "Show List" button. A new window will show the full list with information about the author, title, price, and quantity of each book.

## Code Structure

### Data Structures

- `Book`: Stores information about a book (author, title, price, quantity).
- `Bookstore`: Stores a dynamic list of books and their current count.
- `GuiData`: Stores GTK widgets and a pointer to the bookstore.

### Functions

- `add_book(Bookstore *store, const char *autor, const char *tytul, double cena, int ilosc)`: Adds a new book to the bookstore.
- `remove_book(Bookstore *store, int id)`: Removes a book from the bookstore based on its index.
- `find_book(Bookstore *store, const char *tytul)`: Searches for a book in the bookstore by title.
- `find_books(Bookstore *store, const char *tytul, int *indeksy, int max_id)`: Searches for books matching the given title and returns their indices.
- `save_to_file(Bookstore *store)`: Saves the bookstore data to the `magazyn.txt` file.
- `load_from_file(Bookstore *store)`: Loads data from the `magazyn.txt` file into the bookstore.
- `add_book_clicked(GtkButton *button, GuiData *data)`: Handles the "Add Book" button click event.
- `remove_book_clicked(GtkButton *button, GuiData *data)`: Handles the "Remove Book" button click event.
- `find_book_clicked(GtkButton *button, GuiData *data)`: Handles the "Find Book" button click event.
- `show_book_list(GtkButton *button, GuiData *data)`: Displays the book list in a new window.
- `on_window_closed(GtkWidget *widget, gpointer data)`: Handles the main window close event.

## Application Purpose

The application was created as an example of using the C language and the GTK+ library to manage a bookstore.

