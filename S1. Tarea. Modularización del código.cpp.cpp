#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Estructura para los productos
struct Producto {
    string codigo;
    string nombre;
    int cantidad;
    double precio;
};

// --- FUNCIONES DE AYUDA ---

// Busca un producto y devuelve su posicion (indice)
int buscarProducto(const vector<Producto>& inventario, string codigo) {
    for (int i = 0; i < inventario.size(); i++) {
        if (inventario[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// --- FUNCIONES MODULARES ---

void mostrarMenu() {
    cout << "\n--- SISTEMA GADGETXPRESS ---" << endl;
    cout << "1. Registrar producto" << endl;
    cout << "2. Listar inventario" << endl;
    cout << "3. Actualizar stock" << endl;
    cout << "4. Reporte bajo stock" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione: ";
}

void agregarProducto(vector<Producto>& inventario) {
    string cod;
    cout << "\nCodigo: ";
    cin >> cod;

    if (buscarProducto(inventario, cod) != -1) {
        cout << "Error: El codigo ya existe." << endl;
        return;
    }

    Producto p;
    p.codigo = cod;
    cout << "Nombre: ";
    cin.ignore();
    getline(cin, p.nombre);
    cout << "Cantidad: ";
    cin >> p.cantidad;
    cout << "Precio: ";
    cin >> p.precio;

    inventario.push_back(p);
    cout << "Producto guardado." << endl;
}

void listarProductos(const vector<Producto>& inventario) {
    cout << "\n" << left << setw(10) << "COD" << setw(20) << "NOMBRE" 
         << setw(10) << "STOCK" << setw(10) << "PRECIO" << endl;
    cout << "--------------------------------------------------" << endl;

    for (const auto& p : inventario) {
        cout << left << setw(10) << p.codigo << setw(20) << p.nombre 
             << setw(10) << p.cantidad << fixed << setprecision(2) << setw(10) << p.precio << endl;
    }
}

void actualizarStock(vector<Producto>& inventario) {
    string cod;
    cout << "\nCodigo a buscar: ";
    cin >> cod;

    int idx = buscarProducto(inventario, cod);
    if (idx == -1) {
        cout << "No encontrado." << endl;
    } else {
        cout << "Nueva cantidad para " << inventario[idx].nombre << ": ";
        cin >> inventario[idx].cantidad;
        cout << "Stock actualizado." << endl;
    }
}

void reporteBajoStock(const vector<Producto>& inventario) {
    cout << "\n--- ALERTAS DE STOCK (Menos de 5) ---" << endl;
    for (const auto& p : inventario) {
        if (p.cantidad < 5) {
            cout << "! " << p.nombre << " solo tiene " << p.cantidad << " unidades." << endl;
        }
    }
}

int main() {
    vector<Producto> inventario;
    int opcion;

    do {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1: agregarProducto(inventario); break;
            case 2: listarProductos(inventario); break;
            case 3: actualizarStock(inventario); break;
            case 4: reporteBajoStock(inventario); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);

    return 0;
}