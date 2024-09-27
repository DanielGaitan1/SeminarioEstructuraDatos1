#include <iostream>
#include <string>

using namespace std;
const int TAM = 5;

class persona {
private:
    string nombre;
    string carrera;
    int materias;
    float promedio;

public:
    persona();
    persona(string n, string c, int m, float p);
    void operator=(const persona& x);
    string obtenerNombre() const {
        return nombre;
    }
    friend std::ostream& operator<<(std::ostream&, const persona&);
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
    int buscar(string nombre);
    friend std::ostream& operator<<(std::ostream& o, Cola& L);
    void enqueue(persona& elem);
    persona dequeue();
    void buscarSolicitud();
};

persona::persona() {
    nombre = "juanito";
    carrera = "Computacion";
    materias = 6;
    promedio = 9.5;
}

persona::persona(string n, string c, int m, float p) : nombre(n), carrera(c), materias(m), promedio(p) {}

void persona::operator=(const persona& x) {
    nombre = x.nombre;
    carrera = x.carrera;
    materias = x.materias;
    promedio = x.promedio;
}

std::ostream& operator<<(std::ostream& o, const persona& p) {
    o << "nombre: " << p.nombre << "\t carrera: " << p.carrera << "\t materias: " << p.materias << "\t promedio: " << p.promedio << endl;
    return o;
}

std::istream& operator>>(std::istream& o, persona& p) {
    std::cout << "\nInserta nombre: ";
    o >> p.nombre;
    std::cout << "\nInserta carrera: ";
    o.ignore();
    o >> p.carrera;
    std::cout << "\nInserta la cantidad de materias que se aprobaron: ";
    o >> p.materias;
    std::cout << "\nInserta promedio general: ";
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

std::ostream& operator<<(std::ostream& o, Cola& L) {
    int i = 0;
    std::cout << "\n";
    while (i <= L.ultimo()) {
        o << L.datos[i];
        i++;
    }
    return o;
}

int Cola::buscar(string nombreBuscado) {
    for (int i = 0; i <= ult; ++i) {
        if (datos[i].obtenerNombre() == nombreBuscado) {
            return i;
        }
    }
    return -1;
}

void Cola::enqueue(persona& elem) {
    inserta(elem, ult + 1); // Insertar al final de la cola
}

persona Cola::dequeue() {
    if (vacia()) {
        std::cout << "\nLa cola está vacía" << std::endl;

    }
    persona temp = datos[0];
    elimina(0);
    return temp;
}

bool Cola::elimina(int pos) {
    if (vacia() || pos < 0 || pos > ult) {
        std::cout << "\nError de eliminación";
        return true;
    }
    for (int i = pos; i < ult; i++) {
        datos[i] = datos[i + 1];
    }
    ult--;
    return false;
}

int Cola::inserta(persona& elem, int pos) {
    if (llena() || pos < 0 || pos > ult + 1) {
        std::cout << "\n\t La Cola está llena, no se guardó la solicitud" << endl;
        return 0;
    }
    for (int i = ult + 1; i > pos; i--) {
        datos[i] = datos[i - 1];
    }
    datos[pos] = elem;
    ult++;
    return 1;
}

void Cola::buscarSolicitud() {
    string nombre;
    cout << "\n Ingrese el nombre del alumno para buscar la solicitud: ";
    cin >> nombre;
    int posicion = buscar(nombre);
    if (posicion != -1) {
        cout << "\n La solicitud se encuentra en la posicion " << posicion + 1 << " de la cola." << endl;
        cout << "Cantidad de constancias a elaborar antes de esta solicitud: " << posicion << endl;
    } else {
        cout << "\n La solicitud de " << nombre << " no se encuentra en la cola. Debe dar de alta una solicitud." << endl;
    }
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
        cout << "3. Buscar solicitud" << endl;
        cout << "4. Salir\n" << endl;

        cin >> opcion;

        switch (opcion) {
            case 1:
                cin >> x;
                MiCola.enqueue(x);
                break;

            case 2:
                if (!MiCola.vacia()) {
                    cout << MiCola.dequeue();
                } else {
                    cout << "No hay elementos en la cola." << endl;
                }
                break;

            case 3:
                MiCola.buscarSolicitud();
                break;

            case 4:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion no valida. Por favor, elija una opcion valida." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
