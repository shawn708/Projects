#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX_BOOKS 5000
#define MAX_BORROWED_BOOKS 3
#define MAX_STUDENTS 1000

typedef struct{
   int book_id;
   char title[50];
   char author[50];
   char field_of_study[50];
   int copies_available;
}Book;

typedef struct{
    int student_id;
    char name[50];
    int borrowed_books[MAX_BORROWED_BOOKS];  // array to hold the IDs of the borrowed books
    int num_borrowed_books;  // number of books borrowed by the student
} Student;

Book library[100];			// global array to store books
Student students[MAX_STUDENTS];		// array to hold student records
int num_students = 0;


void add_book(int book_id, char title[], char author[], char field_of_study[], int copies_available);
void remove_book(int book_id);
void search_book();
void add_student(int student_id);
void borrow_book(int student_id, int book_id);
void return_book(int student_id, int book_id);

int main() {
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add new book\n");
        printf("2. Remove a book\n");
        printf("3. Search a book\n");
        printf("4. Add a student\n");
        printf("5. Borrow a book\n");
        printf("6. Return a book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                {
                    int book_id, copies_available;
                    char title[50], author[50], field_of_study[50];
                    printf("Enter book ID: ");
                    scanf("%d", &book_id);
                    printf("Enter book title: ");
                    scanf("%s",&title);
                    printf("Enter book author: ");
                    scanf("%s", &author);
                    printf("Enter field of study: ");
                    scanf("%s", &field_of_study);
                    printf("Enter number of copies available: ");
                    scanf("%d", &copies_available);
                    add_book(book_id, title, author, field_of_study, copies_available);
                    break;
                }
            case 2:
					{
					int book_id;
					printf("Enter book ID: ");
					scanf("%d", &book_id);
					remove_book(book_id);
					break;
					}
            case 3:
           			{
           			search_book();
           			break;
					}
           
            case 4:
	            	{
	            	int student_id;
	            	add_student(student_id);
	                break;
					}
            case 5:
                	{
                	int student_id, book_id;
                	borrow_book(student_id, book_id);
                	break;
					}
            case 6:
            		{
            		int student_id, book_id;
            		return_book(student_id, book_id);
                	break;
					}
                
            case 0:{
					printf("Exiting...\n");
                	break;
					}
                
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);
    
    return 0;
}


void add_book(int book_id, char title[], char author[], char field_of_study[], int copies_available) 

{
	int get_book_count();
    if (get_book_count() == MAX_BOOKS) {
        printf("Error: Library is full.\n");
        return;
    }
    for (int i = 0; i < get_book_count(); i++) 		// Check if book with the same ID already exists
	{
        if (library[i].book_id == book_id) {
            printf("Error: Book with the same ID already exists.\n");
            return;
        }
    }

    Book new_book ;
    new_book.book_id = book_id;
    strcpy(new_book.title, title);
    strcpy(new_book.author, author);
    strcpy(new_book.field_of_study, field_of_study);
    new_book.copies_available = copies_available;

    library[get_book_count()] = new_book;
    
    printf("Book added successfully.\n");
}
void remove_book(int book_id) 			// function to remove a book from the library
{
   int i, index = -1;
   int get_book_count();
   for (i = 0; i < get_book_count(); i++) {
      if (library[i].book_id == book_id) {
         index = i;
         break;
      }
   }
   if (index != -1) {
      for (i = index; i < get_book_count()-1; i++) {
         library[i] = library[i+1];
      }
   printf("Book with ID %d has been removed from the library.\n", book_id);
        (get_book_count()-1); 
	} else {
        printf("Book with ID %d was not found in the library.\n", book_id);
    }
}

void search_book()
{              
   char search_term[50];
   int found_books = 0;
   int get_book_count();
   printf("Enter the author or title of the book you're searching for: ");
   scanf("%s", search_term);
   printf("Search results for \"%s\":\n\n", search_term);
   for (int i = 0; i < get_book_count(); i++) {
      if (strcmp(library[i].title, search_term) == 0 || strcmp(library[i].author, search_term) == 0) {
         printf("Book ID: %d\nTitle: %s\nAuthor: %s\nField of study: %s\nCopies available: %d\n\n",
            library[i].book_id, library[i].title, library[i].author, library[i].field_of_study, library[i].copies_available);
         found_books++;
      }
   }
   if (found_books == 0) {
      printf("No books found.\n");
   }
}


int get_book_count()		// function to get the total number of books in the library
{
   int i;
   for (i = 0; i < 100; i++) {
      if (library[i].book_id == 0) {
         return i;
      }
   }
   return i;
}



void add_student(int student_id) 		// function to add a new student
{
    if (num_students == MAX_STUDENTS) {
        printf("Error: Maximum number of students reached.\n");
        return;
    }
    Student new_student;
    printf("Enter student ID: ");
    scanf("%d", &new_student.student_id);
    printf("Enter student name: ");
    scanf("%s", new_student.name);
    new_student.num_borrowed_books = 0;
    num_students++;
    students[num_students - 1] = new_student;
    printf("Student added successfully.\n");
}

void borrow_book(int student_id, int book_id) 			// function to borrow a book
{
    printf("Enter student ID: ");
    scanf("%d", &student_id);
    int student_index = -1;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].student_id == student_id) {
            student_index = i;
            break;
        }
    }
    if (student_index == -1) {
        printf("Error: Student not found.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int book_index = -1;
    for (int i = 0; i < get_book_count(); i++) {
        if (library[i].book_id == book_id) {
            book_index = i;
            break;
        }
    }
    if (book_index == -1) {
        printf("Error: Book not found.\n");
        return;
    }
    if (students[student_index].num_borrowed_books == MAX_BORROWED_BOOKS) {
        printf("Error: Maximum number of borrowed books reached for this student.\n");
        return;
    }
    if (library[book_index].copies_available == 0) {
        printf("Error: Book not available.\n");
        return;
    }
    library[book_index].copies_available--;
    students[student_index].borrowed_books[students[student_index].num_borrowed_books] = book_id;
    students[student_index].num_borrowed_books++;
    printf("Book borrowed successfully.\n");
}

void return_book(int student_id, int book_id) 					//function to return a book
{
     printf("Enter student ID: ");
    scanf("%d", &student_id);
    int student_index = -1;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].student_id == student_id) {
            student_index = i;
            break;
        }
    }
     if (student_index == -1) {
        printf("Error: Student not found.\n");
        return;
    }  
    printf("Enter book ID: ");
    scanf("%d", &book_id);
    int book_index = -1; 
    for (int i = 0; i <get_book_count() ; i++) {
        if (library[i].book_id == book_id) {
            book_index = i;
            break;
        }
    }
     if (book_index == -1) {
        printf("Error: Book not found.\n");
        return;
    }
    int found = 0;																			 // Search for the borrowed book in the student's borrowed_books array
    for (int i = 0; i < students[student_index].num_borrowed_books; i++) {
        if (students[student_index].borrowed_books[i] == book_id) {
            found = 1;
            for (int j = i; j < students[student_index].num_borrowed_books - 1; j++)			 // Remove the returned book from the borrowed_books array by shifting all subsequent books left
			{
                students[student_index].borrowed_books[j] = students[student_index].borrowed_books[j + 1];
            }
            students[student_index].num_borrowed_books--;
            break;
        }
    }
    if (!found) {
        printf("Error: This book is not currently borrowed by the specified student.\n");
        return;
    }
    library[book_index].copies_available++;		// Increase the number of available copies of the book

    printf("Book returned successfully.\n");
}