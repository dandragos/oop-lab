#include <iostream>
using namespace std;

//Creem cele doua clase si definim constructorii de initializare, constructorul de copiere, operatorul de atribuire,
// destructorii, supraincarcarea operatorilor << si >> pentru intrari si iesiri de obiecte si metodele get/set.

class Camera {
    private:
        int id;
        int capacitate;
        bool disponibilitate;
    public:
        Camera();
        Camera(int i, int c, bool d);
        Camera(const Camera& camera);
        Camera& operator=(const Camera& camera);
        ~Camera();
        friend ostream& operator<<(ostream& os, const Camera& camera);
        friend istream& operator>>(istream& is, Camera& camera);
        int getId() const;
        int getCapacitate() const;
        bool getDisponibilitate() const;
        void setId(int i);
        void setCapacitate(int c);
        void setDisponibilitate(bool d);
};

class Hotel {
    private:
        Camera* camere;
        int nr_camere;
    public:
        Hotel();
        Hotel(int nr_c);
        Hotel(const Hotel& hotel);
        Hotel& operator=(const Hotel& hotel);
        ~Hotel();
        friend ostream& operator<<(ostream& os, const Hotel& hotel);
        friend istream& operator>>(istream& is, Hotel& hotel);
        int getNrCamere() const;
        Camera getCamera(int i) const;
        void setCamera(int i, const Camera& camera);
        void adaugaCamera();
        void stergeCamera();
        void modificaCamera();
        void afisareCamere() const;
        void cautareCamera() const;
        void meniu();
};

//Constructorii de initializare, constructorul de
// copiere, operatorul de atribuire si destructorii sunt definite astfel:
Camera::Camera() {
    id = 0;
    capacitate = 0;
    disponibilitate = true;
}

Camera::Camera(int i, int c, bool d) {
    id = i;
    capacitate = c;
    disponibilitate = d;
}

Camera::Camera(const Camera& camera) {
    id = camera.id;
    capacitate = camera.capacitate;
    disponibilitate = camera.disponibilitate;
}

Camera& Camera::operator=(const Camera& camera) {
    if (this != &camera) {
        id = camera.id;
        capacitate = camera.capacitate;
        disponibilitate = camera.disponibilitate;
    }
    return *this;
}

Camera::~Camera() {}

//Supraincarcarea operatorilor << si >> este definita astfel:

ostream& operator<<(ostream& os, const Camera& camera) {
    os << "ID: " << camera.id << ", Capacitate: " << camera.capacitate << ", Disponibilitate: " << (camera.disponibilitate ? "Da" : "Nu");
    return os;
}

istream& operator>>(istream& is, Camera& camera) {
    cout << "Introduceti ID-ul camerei: ";
    is >> camera.id;
    cout << "Introduceti capacitatea camerei: ";
    is >> camera.capacitate;
    cout << "Este camera disponibila? (0 - Nu, 1 - Da): ";
    is >> camera.disponibilitate;
    return is;
}

//Metodele get/set pentru variabilele membru sunt definite astfel:

int Camera::getId() const {
    return id;
}

int Camera::getCapacitate() const {
    return capacitate;
}

bool Camera::getDisponibilitate() const {
    return disponibilitate;
}

void Camera::setId(int i) {
    id = i;
}

void Camera::setCapacitate(int c) {
    capacitate = c;
}

void Camera::setDisponibilitate(bool d) {
    disponibilitate = d;
}


//In clasa Hotel, avem variabila membru camere, care este un pointer la o lista de obiecte Camera,
// si variabila membru nr_camere, care reprezinta numarul de camere din hotel.
//
//Constructorii de initializare, constructorul de copiere, operatorul de atribuire si
// destructorii sunt definite astfel:


Hotel::Hotel() {
    camere = nullptr;
    nr_camere = 0;
}

Hotel::Hotel(int nr_c) {
    nr_camere = nr_c;
    camere = new Camera[nr_camere];
}

Hotel::Hotel(const Hotel& hotel) {
    nr_camere = hotel.nr_camere;
    camere = new Camera[nr_camere];
    for (int i = 0; i < nr_camere; i++) {
        camere[i] = hotel.camere[i];
    }
}

Hotel& Hotel::operator=(const Hotel& hotel) {
    if (this != &hotel) {
        nr_camere = hotel.nr_camere;
        delete[] camere;
        camere = new Camera[nr_camere];
        for (int i = 0; i < nr_camere; i++) {
            camere[i] = hotel.camere[i];
        }
    }
    return *this;
}

Hotel::~Hotel() {
    delete[] camere;
}

//Supraincarcarea operatorilor << si >> este definita astfel:

ostream& operator<<(ostream& os, const Hotel& hotel) {
    os << "Hotelul are " << hotel.nr_camere << " camere: " << endl;
    for (int i = 0; i < hotel.nr_camere; i++) {
        os << hotel.camere[i] << endl;
    }
    return os;
}

istream& operator>>(istream& is, Hotel& hotel) {
    cout << "Introduceti numarul de camere din hotel: ";
    is >> hotel.nr_camere;
    hotel.camere = new Camera[hotel.nr_camere];
    for (int i = 0; i < hotel.nr_camere; i++) {
        cout << "Introduceti datele pentru camera " << i + 1 << ":" << endl;
        is >> hotel.camere[i];
    }
    return is;
}

//Metodele get/set pentru variabilele membru sunt definite astfel:

int Hotel::getNrCamere() const {
    return nr_camere;
}

Camera Hotel::getCamera(int i) const {
    return camere[i];
}

void Hotel::setCamera(int i, const Camera& camera) {
    camere[i] = camera;
}


//Metodele pentru meniul interactiv sunt definite astfel:

void Hotel::adaugaCamera() {
    nr_camere++;
    Camera* temp = new Camera[nr_camere];
    for (int i = 0; i < nr_camere - 1; i++) {
        temp[i] = camere[i];
    }
    delete[] camere;
    camere = temp;
    Camera c;
    cin >> c;
    camere[nr_camere - 1] = c;
}



void Hotel::stergeCamera() {
    int id;
    cout << "Introduceti ID-ul camerei de sters: ";
    cin >> id;
    int pozitie = -1;
    for (int i = 0; i < nr_camere; i++) {
        if (camere[i].getId() == id) {
            pozitie = i;
            break;
        }
    }
    if (pozitie == -1) {
        cout << "Nu exista o camera cu ID-ul dat." << endl;
    }
    else {
        for (int i = pozitie; i < nr_camere - 1; i++) {
            camere[i] = camere[i + 1];
        }
        nr_camere--;
        Camera* temp = new Camera[nr_camere];
        for (int i = 0; i < nr_camere; i++) {
            temp[i] = camere[i];
        }
        delete[] camere;
        camere = temp;
        cout << "Camera a fost stearsa cu succes." << endl;
    }
}

void Hotel::modificaCamera() {
    int id;
    cout << "Introduceti ID-ul camerei de modificat: ";
    cin >> id;
    int pozitie = -1;
    for (int i = 0; i < nr_camere; i++) {
        if (camere[i].getId() == id) {
            pozitie = i;
            break;
        }
    }
    if (pozitie == -1) {
        cout << "Nu exista o camera cu ID-ul dat." << endl;
    }
    else {
        cout << "Introduceti datele noi pentru camera:" << endl;
        cin >> camere[pozitie];
        cout << "Camera a fost modificata cu succes." << endl;
    }
}

void Hotel::afisareCamere() const {
    cout << *this << endl;
}

void Hotel::cautareCamera() const {
    int id;
    cout << "Introduceti ID-ul camerei cautate: ";
    cin >> id;
    int pozitie = -1;
    for (int i = 0; i < nr_camere; i++) {
        if (camere[i].getId() == id) {
            pozitie = i;
            break;
        }
    }
    if (pozitie == -1) {
        cout << "Nu exista o camera cu ID-ul dat." << endl;
    }
    else {
        cout << "Camera cautata este:" << endl;
        cout << camere[pozitie] << endl;
    }
}

void Hotel::meniu() {
    int optiune;
    do {
        cout << "\n----- MENIU -----\n";
        cout << "1. Adaugare camera\n";
        cout << "2. Stergere camera\n";
        cout << "3. Modificare camera\n";
        cout << "4. Afisare camere\n";
        cout << "5. Cautare camera\n";
        cout << "6. Iesire\n";
        cout << "Introduceti optiunea dorita: ";
        cin >> optiune;
        switch (optiune) {
            case 1:
                adaugaCamera();
                break;
            case 2:
                stergeCamera();
                break;
            case 3:
                modificaCamera();
                break;
            case 4:
                afisareCamere();
                break;
            case 5:
                cautareCamera();
                break;
            case 6:
                cout << "La revedere!";
                break;
            default:
                cout << "Optiune invalida. Va rugam sa reintroduceti optiunea." << endl;
        }
    } while (optiune != 6);
}

int main() {
    Hotel hotel;
    hotel.meniu();
    return 0;
}





