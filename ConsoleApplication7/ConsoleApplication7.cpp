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
    cout << "\t\t����ʲ��� �����\n\n C��� ���: ������� ������ ����������� ��������� ����� �� ��\n\t��� ������� ��� �������� ENTER";
    cin.ignore();
    string rnd_words[]{ "journey", "word", "send", "apple", "lime", "love" };
    int size = sizeof(rnd_words) / sizeof(rnd_words[0]);
    string word = rnd_words[rand() % size];
    cout << "������ �����: \033[45m " << word << "\033[0m\n";
    auto startPlayer = chrono::steady_clock::now();
    string user = "";
    while (user != word) {
        cout << "-->";
        cin >> user;
        if (user != word) {
            cout << "�� ���������. ��� �����...\n";
        }
    }
    auto endPlayer = chrono::steady_clock::now();
    double timePlayer = chrono::duration<double>(endPlayer - startPlayer).count();
    cout << "\n\t\t��� ���������: " << round(timePlayer) << " sec\n";

    Sleep(3000);
    auto startPC = chrono::steady_clock::now();
    Sleep(rand() % 3000 + 1000);
    auto endPC = chrono::steady_clock::now();
    double timePC = chrono::duration<double>(endPC - startPC).count();
    cout << "\n\t\t��� ����'�����: " << round(timePC) << " sec.\n";

    cout << (timePlayer < timePC ? "\033[32m�������\033[0m\n" : "\033[32mPC\033[0m\n");

    char choice;
    do {
        cout << "\n����:\n";
        cout << "1. ������ �������\n";
        cout << "2. ������ �������\n";
        cout << "3. ����� ��������\n";
        cout << "4. �����\n";
        cout << "������ ����: ";
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
            cout << "�����...\n";
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (choice != '4');

    return 0;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "������ ��'�: ";
    cin >> newContact.name;
    cout << "������ ����� ��������: ";
    cin >> newContact.phone;
    contacts.push_back(newContact);
    cout << "������� ������.\n";
}

void modifyContact(vector<Contact>& contacts) {
    string name;
    cout << "������ ��'� ��� ����: ";
    cin >> name;
    for (auto& contact : contacts) {
        if (contact.name == name) {
            cout << "��� ���:\n";
            cout << "������ ���� ��'�: ";
            cin >> contact.name;
            cout << "������ ����� ����� ��������: ";
            cin >> contact.phone;
            cout << "������� ������.\n";
            return;
        }
    }
    cout << "������� �� ��������.\n";
}

void searchContact(const vector<Contact>& contacts) {
    string name;
    cout << "������ ��'� ��� ������: ";
    cin >> name;
    for (const auto& contact : contacts) {
        if (contact.name == name) {
            cout << "��������: " << contact.name << " - " << contact.phone << endl;
            return;
        }
    }
    cout << "������� �� ��������.\n";
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
