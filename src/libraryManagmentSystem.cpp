//1.Create a system where users can borrow, return, and search for books. 
//Store information like book title, author, and availability in files. 
//Implement features such as searching and sorting books.

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

// Book class to hold book details
class Book {
    string title;
    string author;
    int bookID;
    bool availability;

public:
    // Constructor to initialize book details
    Book(string title, string author, int bookID, bool availability = true)
        : title(title), author(author), bookID(bookID), availability(availability) {}

    // Getter methods
    string getTitle() const 
    { 
        return title; 
    }
    string getAuthor() const 
    { 
        return author; 
    }
    int getBookID() const 
    { 
        return bookID; 
    }
    bool isAvailable() const 
    { 
        return availability; 
    }

    // Method to change the availability status
    void setAvailability(bool status) 
    { 
        availability = status; 
    }

    // Display book info
    void displayInfo() const 
    {
        cout << "Title: " << title << "\nAuthor: " << author
             << "\nBook ID: " << bookID
             << "\nAvailable: " << (availability ? "Yes" : "No") << endl;
    }
};

// Member class to hold member details
class Member {
    string name;
    int memberID;
    vector<int> issuedBooks;

public:
    Member(string name = "", int memberID = 0) : name(name), memberID(memberID) {}

    // Getter methods
    string getName() const { return name; }
    int getMemberID() const { return memberID; }
    const vector<int>& getIssuedBooks() const { return issuedBooks; }

    // Method to add an issued book
    void issueBook(int bookID, vector<Book>& books) {
        for (auto& book : books) 
        {
            if (book.getBookID() == bookID) 
            {
                if (!book.isAvailable())
                {
                    cout << "Book is already issued" << endl;
                    return;
                }
                issuedBooks.push_back(bookID);
                book.setAvailability(true);
                cout << "Book issued successfully" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Method to return a book
    void returnBook(int bookID, vector<Book>& books) {
        auto it = find(issuedBooks.begin(), issuedBooks.end(), bookID);
        if (it != issuedBooks.end()) 
        {
            issuedBooks.erase(it); // Removes the specific book
            for (auto& book : books) 
            {
                if (book.getBookID() == bookID) 
                {
                    book.setAvailability(true);
                    cout << "Book returned successfully!" << endl;
                    return;
                }
            }
        }
        cout << "Book was not issued to this member" << endl;
    }

    // Display member info
    void displayMemberInfo() const {
        cout << "Name: " << name << "\nMember ID: " << memberID
             << "\nIssued Books: ";
        if (issuedBooks.empty()) 
        {
            cout << "None" << endl;
        } 
        else 
        {
            for (const auto& bookID : issuedBooks) 
            {
                cout << bookID << " ";
            }
            cout << endl;
        }
    }
};

// Librarian class to manage books
class Librarian {
    vector<Book>& books;

public:
    Librarian(vector<Book>& books) : books(books) {}

    void addBook(const Book& newBook) {
        for(const auto& book : books)
        {
            if(book.getBookID() == newBook.getBookID())
            {
                cout << "A book with this ID already exists!" <<endl;
                return;
            }
        }
        books.push_back(newBook);
        cout << "Book added successfully" <<endl;
    }

    void removeBook(int bookID) {
        auto it = remove_if(books.begin(), books.end(), [bookID](const Book& book) {
            return book.getBookID() == bookID;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book removed successfully!" << endl;
        } else {
            cout << "Book not found!" << endl;
        }
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
            cout << "----------------------" << endl;
        }
    }

    void searchBook(const string& title) const {
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                book.displayInfo();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to sort books by title
    void sortBooksByTitle() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getTitle() < b.getTitle();
        });
        cout << "Books sorted by title!" << endl;
    }

    // Function to sort books by author
    void sortBooksByAuthor() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getAuthor() < b.getAuthor();
        });
        cout << "Books sorted by author!" << endl;
    }

    // Function to sort books by book ID
    void sortBooksById() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getBookID() < b.getBookID();
        });
        cout << "Books sorted by ID!" << endl;
    }

    // Function to display sorted books (remove the const qualifier)
    void displaySortedBooks() {
        int choice;
        cout << "Sort Books by: " << endl;
        cout << "1. Title" << endl;
        cout << "2. Author" << endl;
        cout << "3. ID" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                sortBooksByTitle();
                break;
            case 2:
                sortBooksByAuthor();
                break;
            case 3:
                sortBooksById();
                break;
            default:
                cout << "Invalid choice!" << endl;
                return;
        }

    displayAllBooks(); // Show the sorted list of books
    }
};

// Library class to manage library functionalities
class Library {
    vector<Book> books;
    vector<Member> members;

public:
    vector<Book>& getBooks() { return books; } // Provide access to books

    void addMember(const Member& newMember) {
        members.push_back(newMember);
        cout << "Member added successfully!" << endl;
    }

    void displayAllMembers() const {
        for (const auto& member : members) {
            member.displayMemberInfo();
        }
    }

    void addBook(const string& title, const string& author, int bookID) {
        books.emplace_back(title, author, bookID);
        cout << "Book added successfully!" << endl;
    }

    void issueBook(int bookID, int memberID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) {
                for (auto& member : members) {
                    if (member.getMemberID() == memberID) {
                        member.issueBook(bookID, books);
                        return;
                    }
                }
            }
        }
        cout << "Book not available or Member not found" << endl;
    }

    void returnBook(int bookID, int memberID) {
        for (auto& member : members) {
            if (member.getMemberID() == memberID) {
                member.returnBook(bookID, books);
                return;
            }
        }
        cout << "Member not found!" << endl;
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
            cout << "---------------------" << endl;
        }
    }

    void saveToFile() const {
        ofstream file("books.txt");
        if (!file.is_open()) {
            cerr << "Unable to open the file." << endl;
            return;
        }
        for (const auto& book : books) {
            file << book.getBookID() << "\n" << book.getTitle() << "\n" << book.getAuthor() << "\n" << book.isAvailable() << endl;
        }
        file.close();
        cout << "Data saved to file successfully!" << endl;
    }

    void loadBooksFromFile() {
        ifstream file("books.txt");
        if (!file.is_open()) {
            cerr << "Unable to open the file." << endl;
            return;
        }

        int id;
        string title, author;
        bool availability;

        // Read books from file
        while (file >> id >> ws) {
            getline(file, title);
            getline(file, author);
            file >> availability;
            books.emplace_back(title, author, id, availability);
        }

        file.close();
        cout << "Data loaded from file successfully!" << endl;
    }
};

int main() {
    Library library;
    library.loadBooksFromFile();
    Librarian librarian(library.getBooks());

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Display All Books\n";
        cout << "7. Add Member\n";
        cout << "8. Display All Members\n";
        cout << "9. Save to File\n";
        cout << "10. Sort and Display Books\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(); // To avoid newline issues before using getline

        switch (choice) {
            case 1: {
                string title, author;
                int id;
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter book ID: ";
                cin >> id;
                librarian.addBook(Book(title, author, id));
                break;
            }
            case 2: {
                int id;
                cout << "Enter book ID to remove: ";
                cin >> id;
                librarian.removeBook(id);
                break;
            }
            case 3: {
                string title;
                cout << "Enter book title to search: ";
                cin.ignore();
                getline(cin, title);
                librarian.searchBook(title);
                break;
            }
            case 4: {
                int bookID, memberID;
                cout << "Enter book ID to issue: ";
                cin >> bookID;
                cout << "Enter member ID: ";
                cin >> memberID;
                library.issueBook(bookID, memberID);
                break;
            }
            case 5: {
                int bookID, memberID;
                cout << "Enter book ID to return: ";
                cin >> bookID;
                cout << "Enter member ID: ";
                cin >> memberID;
                library.returnBook(bookID, memberID);
                break;
            }
            case 6:{
                librarian.displayAllBooks();
                break;
            }
            case 7: {
                string name;
                int memberID;
                cout << "Enter member name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter member ID: ";
                cin >> memberID;
                library.addMember(Member(name, memberID));
                break;
            }
            case 8:{
                library.displayAllMembers();
                break;
            }
            case 9:{
                library.saveToFile();
                break;
            }
            case 10:{
                librarian.displaySortedBooks();
                break;
            }
            case 11: {
                cout << "Exiting the system..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 11);

    return 0; // Ensure this return statement is present
}