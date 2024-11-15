#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi; // rellenar tabla.

vvi sus(26, vector<int>(26));
vvi trans(26, vector<int>(26));
vector<int> ins(26);
vector<int> del(26);

void leerMatrizCosto(string txtName, vvi &matriz){
    ifstream archivo(txtName);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << txtName << endl;
        return;
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            archivo >> matriz[i][j];
        }
    }
    
    if (archivo.fail()) {
        cerr << "Error al leer el archivo: " << txtName << endl;
    }

    archivo.close();
}

int costo_sub(char c1, char c2) {
    int val1 = c1 - 'a';
    int val2 = c2 - 'a';
    return sus[val1][val2]; // Costo de sustitución
}

int costo_ins(char c1) {
    int val = c1 - 'a';
    return ins[val]; // Costo de inserción
}

int costo_del(char c1) {
    int val = c1 - 'a';
    return del[val]; // Costo de eliminación
}

int costo_trans(char c1, char c2) {
    int val1 = c1 - 'a';
    int val2 = c2 - 'a';
    return trans[val1][val2]; // Costo de transposición
}

int recursion(string s1, string s2, int i, int j, vvi &cache) {
    if (i == s1.length()){
        int costo = 0;
        for(int w = j; w < s2.length(); w++){
            costo += costo_ins(s2[w]);
        } 
        return costo; // Si s1 está vacío, solo hay que insertar (s2.length() - j) * costo_ins();
    }
    if (j == s2.length()){
        int costo = 0;
        for(int w = i; w < s1.length(); w++){
            costo += costo_del(s1[w]);
        }
        return costo; 
    }             
                                                                                                        
    if (s1[i] == s2[j]) {
        return recursion(s1, s2, i + 1, j + 1, cache); // No hay costo, avanzar ambos
    }
    if(cache[i + 1][j + 1] != -1){
        return cache[i + 1][j + 1];
    }
    // Costo de las operaciones
    int c1 = costo_sub(s1[i], s2[j]) + recursion(s1, s2, i + 1, j + 1, cache); // Sustitución
    int c2 = costo_ins(s2[j]) + recursion(s1, s2, i, j + 1, cache); // Inserción
    int c3 = costo_del(s1[i]) + recursion(s1, s2, i + 1, j, cache); // Eliminación
    // Costo de transposición
    int c4 = INT_MAX;
    if (i + 1 < s1.length() && j + 1 < s2.length() && s1[i] == s2[j + 1] && s1[i + 1] == s2[j]) {
        c4 = costo_trans(s1[i], s2[j]) + recursion(s1, s2, i + 2, j + 2, cache); // Transposición
    }
    int minimo = min({c1, c2, c3, c4});
    cache[i + 1][j + 1] = minimo;
    return minimo;// Retornar el costo mínimo
}

int edicion_ext(string s1, string s2) {
    vvi cache(s1.length() + 1, vector<int>(s2.length() + 1, -1));
    cache[0][0] = 0;
    for(int i = 1; i < s1.length() + 1; i++){
        cache[i][0] = cache[i - 1][0] + costo_del(s1[i - 1]);
    }
    for(int j = 1; j < s2.length() + 1; j++){
        cache[0][j] = cache[0][j - 1] + costo_ins(s2[j - 1]);
    }
    return recursion(s1, s2, 0, 0, cache);
}


void leerLineaCosto(string txtName, vector<int> &lista){
    ifstream archivo(txtName);
    if (!archivo.is_open()) {
        cerr<< "Error al abrir el archivo." <<endl;
        return;
    }
    for(int i = 0; i < 26; ++i){
        archivo >> lista[i];
    }
    archivo.close();
}

int main() {
    string s1, s2;

    leerMatrizCosto("cost_replace.txt", sus);
    leerLineaCosto("cost_insert.txt", ins);
    leerLineaCosto("cost_delete.txt", del);
    leerMatrizCosto("cost_transpose.txt", trans);
    cout << "Inserte la primera palabra: \n";
    getline(cin, s1);
    cout << "Inserte la segunda palabra: \n";
    getline(cin, s2);
    int costo = edicion_ext(s1, s2);
    cout << "El costo mínimo de edición es: " << costo << endl;

    /*
    int casos;
    cout<<"inserte cantidad de casos: ";
    cin>>casos;
    ifstream archivo("pruebasX.txt");
    ofstream salida("out_testdinX.txt");
    for(int i = 0; i < casos; i++){
        archivo >> s1;
        archivo >> s2;
        cout<<s1<<" "<<s2<<"\n";
        auto inicio = chrono::high_resolution_clock::now();    
        int costo = edicion_ext(s1, s2);
        cout << "El costo mínimo de edición es: " << costo << endl;
        auto fin = chrono::high_resolution_clock::now();

        auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        salida << s1.length() << " " << s2.length() << " " << duracion.count() << "\n";
        cout << "Tiempo de ejecución: " << duracion.count() << " ms" << endl;
    }
    archivo.close();
    salida.close();
    */
    return 0;
}



