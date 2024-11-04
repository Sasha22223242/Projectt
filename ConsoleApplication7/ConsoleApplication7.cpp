#include <iostream>
#include <Windows.h>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Contact {
    string name;
    string phone;
};

void addContact(vector<Contact>& contacts);
void modifyContact(vector<Contact>& contacts);
void searchContact(const vector<Contact>& contacts);
void loadContacts(vector<Contact>& contacts);
void saveContacts(const vector<Contact>& contacts);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Contact> contacts;
    loadContacts(contacts);

    srand(static_cast<unsigned int>(time(nullptr)));
    cout << "\t\tШВИДКІСТЬ ДРУКУ\n\n Cуть гри: потрібно швидко надрукувати випадкове слово на ПК\n\tДля початку гри натисніть ENTER";
    cin.ignore();
    string rnd_words[]{ "journey", "word", "send", "apple", "lime", "love" };
    int size = sizeof(rnd_words) / sizeof(rnd_words[0]);
    string word = rnd_words[rand() % size];
    cout << "Введіть слово: \033[45m " << word << "\033[0m\n";
    auto startPlayer = chrono::steady_clock::now();
    string user = "";
    while (user != word) {
        cout << "-->";
        cin >> user;
        if (user != word) {
            cout << "Не правильно. Час плине...\n";
        }
    }
    auto endPlayer = chrono::steady_clock::now();
    double timePlayer = chrono::duration<double>(endPlayer - startPlayer).count();
    cout << "\n\t\tВаш результат: " << round(timePlayer) << " sec\n";

    Sleep(3000);
    auto startPC = chrono::steady_clock::now();
    Sleep(rand() % 3000 + 1000);
    auto endPC = chrono::steady_clock::now();
    double timePC = chrono::duration<double>(endPC - startPC).count();
    cout << "\n\t\tЧас комп'ютера: " << round(timePC) << " sec.\n";

    cout << (timePlayer < timePC ? "\033[32mГравець\033[0m\n" : "\033[32mPC\033[0m\n");

    char choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Додати контакт\n";
        cout << "2. Змінити контакт\n";
        cout << "3. Пошук контакту\n";
        cout << "4. Вихід\n";
        cout << "Введіть вибір: ";
        cin >> choice;

        switch (choice) {
        case '1':
            addContact(contacts);
            break;
        case '2':
            modifyContact(contacts);
            break;
        case '3':
            searchContact(contacts);
            break;
        case '4':
            saveContacts(contacts);
            cout << "Вихід...\n";
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != '4');

    return 0;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Введіть ім'я: ";
    cin >> newContact.name;
    cout << "Введіть номер телефону: ";
    cin >> newContact.phone;
    contacts.push_back(newContact);
    cout << "Контакт додано.\n";
}

void modifyContact(vector<Contact>& contacts) {
    string name;
    cout << "Введіть ім'я для зміни: ";
    cin >> name;
    for (auto& contact : contacts) {
        if (contact.name == name) {
            cout << "Нові дані:\n";
            cout << "Введіть нове ім'я: ";
            cin >> contact.name;
            cout << "Введіть новий номер телефону: ";
            cin >> contact.phone;
            cout << "Контакт змінено.\n";
            return;
        }
    }
    cout << "Контакт не знайдено.\n";
}

void searchContact(const vector<Contact>& contacts) {
    string name;
    cout << "Введіть ім'я для пошуку: ";
    cin >> name;
    for (const auto& contact : contacts) {
        if (contact.name == name) {
            cout << "Знайдено: " << contact.name << " - " << contact.phone << endl;
            return;
        }
    }
    cout << "Контакт не знайдено.\n";
}

void loadContacts(vector<Contact>& contacts) {
    ifstream file("contacts.txt");
    if (file.is_open()) {
        Contact contact;
        while (file >> contact.name >> contact.phone) {
            contacts.push_back(contact);
        }
        file.close();
    }
}

void saveContacts(const vector<Contact>& contacts) {
    ofstream file("contacts.txt");
    for (const auto& contact : contacts) {
        file << contact.name << " " << contact.phone << endl;
    }
    file.close();
}
