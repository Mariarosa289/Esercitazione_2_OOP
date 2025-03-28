#include <iostream>
#include <concepts> // permette i vincolare tipi a cui T può accedere

template <typename T>//dichiaro la classe templete dove T è un tipo generico (int,double,std::string)
requires std::floating_point<T> // Vincola T a essere un tipo floating-point e ciò include float, double,long double
	
	struct ComplexNumber {
		T a;
		T b; //a è la parte reale e b è la parte immaginaria
    	ComplexNumber() : a(0), b(0) {} // Costruttore di default (inizializzo)
    	
		ComplexNumber(T r, T i) : a(r), b(i) {} // Costruttore user-defined che serve per restituire 												r al posto di a e i al posto di b
		
		ComplexNumber coniugate() const { // Metodo per ottenere il coniugato

        return ComplexNumber(a, -b);
    }
    
	// Metodo per inizializzare i valori
    void setValues(T r, T i) {
        a = r;
        b = i;
    }
    
    // Overload di << per la stampa
    std::ostream& print(std::ostream& nc) const {
        nc << a;
        if (b >= 0)
            nc << "+";
        nc << b << "i"; // questo fa si che se b è negativo il meno "non venga visto" e venga 								aggiunto automaticamente a nc
        return nc;
    }
    
    // Overload per l'operatore +=	
    ComplexNumber& operator+=(const ComplexNumber& other) {
    a += other.a;   // Aggiunge la parte reale del numero complesso 'other' alla parte reale 							dell'oggetto corrente.
    b += other.b;   // Aggiunge la parte immaginaria del numero complesso 'other' alla parte 							immaginaria dell'oggetto corrente.
    return *this;   // Restituisce il riferimento all'oggetto corrente (questo permette di 								concatenare altre operazioni con l'operatore +=).
	}
	
	// Overload dell'operatore +
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(a + other.a, b + other.b);
    }		
    
    // Overload dell'operatore *=
    ComplexNumber& operator*=(const ComplexNumber& other) {
        T r = a * other.a - b * other.b;
        T i = a * other.b + b * other.a;
        a = r;
        b = i;
        return *this;
    }
    
    // Overload dell'operatore *
    ComplexNumber operator*(const ComplexNumber& other) const {
        return ComplexNumber(a * other.a - b * other.b,
                             a * other.b + b * other.a);
    }
};

// Funzione globale per l'operatore <<
template <typename T>
std::ostream& operator<<(std::ostream& nc, const ComplexNumber<T>& c) {
    return c.print(nc);
}

int main() {
    ComplexNumber<float> n1(7.0f, 4.0f); // n1: 7+ 4i--> la f indica che il valore è di tipo float
    ComplexNumber<float> n2(1.0f, -5.0f); // n2: 1 - 5i

    std::cout << "n1: " << n1 << "\n"; // Stampa n1
    std::cout << "n2: " << n2 << "\n"; // Stampa n2

    ComplexNumber<float> n3 = n1 + n2; // Somma dei numeri complessi
    std::cout << "n1 + n2: " << n3 << "\n"; // Stampa la somma

    n1 += n2; // Somma con l'operatore +=
    std::cout << "Dopo n1 += n2: " << n1 << "\n";

    ComplexNumber<float> n4 = n1 * n2; // Moltiplicazione dei numeri complessi
    std::cout << "n1 * n2: " << n4 << "\n"; // Stampa il risultato

    n1 *= n2; // Moltiplicazione con l'operatore *=
    std::cout << "Dopo n1 *= n2: " << n1 << "\n";

    std::cout << "Coniugato di n1: " << n1.coniugate() << "\n"; // Stampa il coniugato

    return 0;
}