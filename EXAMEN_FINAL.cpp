#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <sstream>
using namespace std;

//clases

class Rating {
public:
	int user_id;
	int book_id;
	int rating;
	Rating(int user_id, int book_id, int rating);
};
class Book {
public:
	int book_id;
	string title;
	Book(int id, string title);
	int calificaciones;
};

//definiciones de clases
Book::Book(int id, string title) {
	this->book_id = id;
	this->title = title;

}
Rating::Rating(int user_id, int book_id, int rating) {
	this->user_id = user_id;
	this->book_id = book_id;
	this->rating = rating;
}

// funciones utiliarias
void calificaciones(Book& book, vector<Rating>& ratings) {
	int tempCont = 0;
	for (Rating rating : ratings) {
		if (book.book_id == rating.book_id) {
			tempCont++;
		}
	}
	book.calificaciones = tempCont;
}

void lecturaBookCsv(vector<Book>& books, vector<Rating>& ratings) {
	fstream booksFile("C:\\Users\\emili\\Downloads\\libros.csv", ios::in);
	if (!booksFile) {
		cerr << "El archivo no se pudo abrir, favor de intentarlo nuevamente" << endl;
		exit(EXIT_FAILURE);
	}
	string linea;
	getline(booksFile, linea);
	while (getline(booksFile, linea, ',')) {
		int tempBook_id = stoi(linea);
		getline(booksFile, linea);
		string tempTitle = linea;
		Book tempBook(tempBook_id, tempTitle);
		calificaciones(tempBook, ratings);
		books.push_back(tempBook);
	}
}

void lecturaRatingCsv(vector<Rating>& ratings) {
	fstream ratingsFile("C:\\Users\\emili\\Downloads\\opiniones.csv", ios::in);
	if (!ratingsFile) {
		cerr << "El archivo no se pudo abrir, favor de intentarlo nuevamente" << endl;
		exit(EXIT_FAILURE);
	}
	string linea;
	getline(ratingsFile, linea);
	while (getline(ratingsFile, linea, ',')) {
		int tempUser_id = stoi(linea);
		getline(ratingsFile, linea, ',');
		int tempBook_id = stoi(linea);
		getline(ratingsFile, linea);
		int tempRating = stoi(linea);
		Rating tempR(tempUser_id, tempBook_id, tempRating);
		ratings.push_back(tempR);
	}
}

void crearNuevoCsv(vector< Book>& books, vector<Rating>& ratings) {
	std::ofstream newCsv("C:\\Users\\emili\\Downloads\\resultados.csv", std::ios::out);
	if (!newCsv) {
		std::cerr << "Error al abrir el archivo para escribir." << std::endl;
		return;
	}

	// Escribir encabezados en el nuevo archivo CSV
	newCsv << "book_id,evaluaciones,titulo" << std::endl;

	for (Book book:books) {
		newCsv << book.book_id << "," << book.calificaciones <<"," << book.title << endl;
	}

	std::cout << "Nuevo archivo CSV creado correctamente." << std::endl;
}
// main
int main() {
	vector<Book> libros;
	vector<Rating> ratings;
	lecturaRatingCsv(ratings);
	cout << "Opiniones leidas correctamente" << endl;
	lecturaBookCsv(libros, ratings);
	cout << "Libros leidos correctamente" << endl;
	crearNuevoCsv(libros, ratings);
	return 0;
}