#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

// Function prototypes
void init_ui();
void cleanup_ui();
void draw_main_menu();
void draw_add_book_form();
void draw_borrow_book_form();
void draw_return_book_form();
void draw_student_list();
void draw_waiting_list();
void draw_status_bar(const char *message);
void handle_input();

// Global variables
WINDOW *main_win;
WINDOW *status_win;

int main() {
    init_ui();
    
    // Main loop
    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case '1':
                draw_add_book_form();
                break;
            case '2':
                draw_borrow_book_form();
                break;
            case '3':
                draw_return_book_form();
                break;
            case '4':
                draw_student_list();
                break;
            case '5':
                draw_waiting_list();
                break;
            default:
                draw_main_menu();
                break;
        }
    }
    
    cleanup_ui();
    return 0;
}

void init_ui() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Initialize colors if supported
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_BLACK, COLOR_WHITE);
    }
    
    // Create main window
    main_win = newwin(LINES-3, COLS, 0, 0);
    status_win = newwin(3, COLS, LINES-3, 0);
    
    // Draw initial screen
    draw_main_menu();
}

void cleanup_ui() {
    delwin(main_win);
    delwin(status_win);
    endwin();
}

void draw_main_menu() {
    wclear(main_win);
    wbkgd(main_win, COLOR_PAIR(1));
    
    // Draw title
    mvwprintw(main_win, 2, (COLS-20)/2, "LIBRARY MANAGER");
    
    // Draw menu options
    mvwprintw(main_win, 5, 10, "1. Add a new book");
    mvwprintw(main_win, 6, 10, "2. Borrow a book");
    mvwprintw(main_win, 7, 10, "3. Return a book");
    mvwprintw(main_win, 8, 10, "4. View student list");
    mvwprintw(main_win, 9, 10, "5. View waiting list");
    mvwprintw(main_win, 11, 10, "Press 'q' to quit");
    
    wrefresh(main_win);
    draw_status_bar("Ready. Select an option from the menu.");
}

void draw_add_book_form() {
    wclear(main_win);
    wbkgd(main_win, COLOR_PAIR(1));
    
    mvwprintw(main_win, 2, (COLS-15)/2, "ADD NEW BOOK");
    
    // Form fields
    mvwprintw(main_win, 5, 10, "Title: ");
    mvwprintw(main_win, 6, 10, "Author: ");
    mvwprintw(main_win, 7, 10, "ISBN: ");
    mvwprintw(main_win, 8, 10, "Quantity: ");
    
    // Draw input fields (just placeholders in this UI)
    mvwprintw(main_win, 5, 18, "[input field]");
    mvwprintw(main_win, 6, 18, "[input field]");
    mvwprintw(main_win, 7, 18, "[input field]");
    mvwprintw(main_win, 8, 18, "[input field]");
    
    mvwprintw(main_win, 10, 10, "Press Enter to submit or ESC to cancel");
    
    wrefresh(main_win);
    draw_status_bar("Adding a new book to the library.");
}

void draw_borrow_book_form() {
    wclear(main_win);
    wbkgd(main_win, COLOR_PAIR(1));
    
    mvwprintw(main_win, 2, (COLS-16)/2, "BORROW A BOOK");
    
    // Form fields
    mvwprintw(main_win, 5, 10, "Student ID: ");
    mvwprintw(main_win, 6, 10, "Book ISBN: ");
    mvwprintw(main_win, 7, 10, "Due Date: ");
    
    // Draw input fields (just placeholders in this UI)
    mvwprintw(main_win, 5, 22, "[input field]");
    mvwprintw(main_win, 6, 22, "[input field]");
    mvwprintw(main_win, 7, 22, "[input field]");
    
    mvwprintw(main_win, 9, 10, "Press Enter to submit or ESC to cancel");
    
    wrefresh(main_win);
    draw_status_bar("Borrowing a book from the library.");
}

void draw_return_book_form() {
    wclear(main_win);
    wbkgd(main_win, COLOR_PAIR(1));
    
    mvwprintw(main_win, 2, (COLS-15)/2, "RETURN A BOOK");
    
    // Form fields
    mvwprintw(main_win, 5, 10, "Student ID: ");
    mvwprintw(main_win, 6, 10, "Book ISBN: ");
    
    // Draw input fields (just placeholders in this UI)
    mvwprintw(main_win, 5, 22, "[input field]");
    mvwprintw(main_win, 6, 22, "[input field]");
    
    mvwprintw(main_win, 8, 10, "Press Enter to submit or ESC to cancel");
    
    wrefresh(main_win);
    draw_status_bar("Returning a book to the library.");
}

void draw_student_list() {
    wclear(main_win);
    wbkgd(main_win, COLOR_PAIR(1));
    
    mvwprintw(main_win, 2, (COLS-15)/2, "STUDENT LIST");
    
    // Column headers
    mvwprintw(main_win, 5, 5, "ID");
    mvwprintw(main_win, 5, 15, "Name");
    mvwprintw(main_win, 5, 40, "Books Borrowed");
    
    // Sample data (in a real app, this would come from your data structure)
    mvwprintw(main_win, 7, 5, "1001");
    mvwprintw(main_win, 7, 15, "John Doe");
    mvwprintw(main_win, 7, 40, "3");
    
    mvwprintw(main_win, 8, 5, "1002");
    mvwprintw(main_win, 8, 15, "Jane Smith");
    mvwprintw(main_win, 8, 40, "1");
    
    mvwprintw(main_win, 10, 10, "Press any key to return to main menu");
    
    wrefresh(main_win);
    draw_status_bar("Viewing student list.");
}

void draw_waiting_list() {
    wclear(main_win);
    wbkgd(main_win, COLOR_PAIR(1));
    
    mvwprintw(main_win, 2, (COLS-15)/2, "WAITING LIST");
    
    // Column headers
    mvwprintw(main_win, 5, 5, "Position");
    mvwprintw(main_win, 5, 20, "Student ID");
    mvwprintw(main_win, 5, 35, "Book ISBN");
    mvwprintw(main_win, 5, 50, "Request Date");
    
    // Sample data (in a real app, this would come from your data structure)
    mvwprintw(main_win, 7, 5, "1");
    mvwprintw(main_win, 7, 20, "1003");
    mvwprintw(main_win, 7, 35, "978-1234567890");
    mvwprintw(main_win, 7, 50, "2023-05-15");
    
    mvwprintw(main_win, 8, 5, "2");
    mvwprintw(main_win, 8, 20, "1004");
    mvwprintw(main_win, 8, 35, "978-0987654321");
    mvwprintw(main_win, 8, 50, "2023-05-16");
    
    mvwprintw(main_win, 10, 10, "Press any key to return to main menu");
    
    wrefresh(main_win);
    draw_status_bar("Viewing waiting list for popular books.");
}

void draw_status_bar(const char *message) {
    wbkgd(status_win, COLOR_PAIR(2));
    wclear(status_win);
    
    mvwprintw(status_win, 1, 1, "%s", message);
    
    wrefresh(status_win);
}