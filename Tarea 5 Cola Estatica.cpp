#include <iostream>
#include <string>

using namespace std;
const int TAM=5;

class persona {
private:
    string nombre;
    string carrera;
    int materias;
    float promedio;

public:
    persona();
    void operator=(persona& x);
    persona(string n, string c, int m, float p);
    friend std::ostream& operator<<(std::ostream&, persona&);
    friend std::istream& operator>>(std::istream&, persona&);
};

class Cola {
private:
    persona datos[TAM];
    int ult;
    bool elimina(int pos);
    int inserta(persona& elem, int pos);

public:
    Cola() : ult(-1) {}
    bool vacia() const;
    bool llena() const;
    int ultimo() const;
    friend std::ostream& operator<<(std::ostream & o, Cola& L);
    void enqueue(persona& elem);
    persona& dequeue();
};

persona::persona() {
    nombre = "juanito";
    carrera = "Computacion";
    materias = 6;
    promedio = 9.5;
}

persona::persona(string n, string c, int m, float p) : nombre(n), carrera(c), materias(m), promedio(p) {}

void persona::operator=(persona& x) {
    nombre = x.nombre;
    carrera = x.carrera;
    materias = x.materias;
    promedio = x.promedio;
}

std::ostream& operator<<(std::ostream& o, persona& p) {
    o << "nombre: " << p.nombre << "\t carrera: " << p.carrera << "\t materias: " << p.materias << "\t promedio: " << p.promedio << endl;
    return o;
}

std::istream& operator>>(std::istream& o, persona& p) {
    std::cout << "\nInserta nombre: ";
    o >> p.nombre;
    std::cout << "\nInserta carrera: ";
    std::cin.ignore();
    o >> p.carrera;
    std::cout << "\nInserta la cantidad de materias que se aprobaron: ";
    std::cin.ignore();
    o >> p.materias;
    std::cout << "\nInserta promedio general: ";
    std::cin.ignore();
    o >> p.promedio;

    return o;
}


bool Cola::vacia() const {
    return (ult == -1);
}

bool Cola::llena() const {
    return (ult == TAM - 1);
}

int Cola::ultimo() const {
    return ult;
}

std::ostream& operator<<(std::ostream & o, Cola& L) {
    int i = 0;
    std::cout << "\n";
    while (i <= L.ultimo()) {
        o << L.datos[i];
        i++;
    }
    return o;
}

void Cola::enqueue(persona& elem) {
    inserta(elem, 0);
}

persona& Cola::dequeue() {
    if (vacia()) {
        std::cout << "\nLa cola está vacía" << std::endl;
    } else {
        ult--;
        return datos[ult + 1];
    }
}

bool Cola::elimina(int pos) {
    if (vacia() || pos < 0 || pos > ult) {
        std::cout << "\nError de eliminación";
        return true;
    }
    int i = pos;
    while (i < ult) {
        datos[i] = datos[i + 1];
        i++;
    }
    ult--;
    return false;
}

int Cola::inserta(persona& elem, int pos) {
    if (llena() || pos < 0 || pos > ult + 1) {
        std::cout << "\n\t La Cola esta llena, no se guardó la solicitud"<<endl;
        return 0;
    }
    int i = ult + 1;
    while (i > pos) {
        datos[i] = datos[i - 1];
        i--;
    }
    datos[pos] = elem;
    ult++;
    return 1;
}

int main() {
    Cola MiCola;
    int opcion;
    persona x;

     do {
        cout << "<><><><><><><><><><><><><><><><><><>" << endl;
        cout << "\t Menu\n" << endl;
        cout << "1. Dar de alta solicitud" << endl;
        cout << "2. Elaborar constancia" << endl;
        cout << "3. Salir\n" << endl;

        cin >> opcion;

        switch (opcion) {
            case 1:
                cin>>x;
                MiCola.enqueue(x);

                break;

            case 2:
                if(!MiCola.vacia()){
                    cout<<MiCola.dequeue();
                } else {
                    cout<<"No hay elementos en la cola."<<endl;
                }
                break;

            case 3:

                break;

            default:
                cout << "Opcion no valida. Por favor, elija una opción valida." << endl;
                break;
        }
    }

     while (opcion != 3);

    return 0;
}


