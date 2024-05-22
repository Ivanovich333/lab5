#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class Student {
public:
    string FIO;
    string group;
    int ccnumber;
    int score[4];

    Student() {}
    Student(string f, string g, int c, int* s) : FIO(f), group(g), ccnumber(c) {
        for (int i = 0; i < 4; i++) {
            this->score[i] = s[i];
        }
    }
    Student(const Student& other) : FIO(other.FIO), group(other.group), ccnumber(other.ccnumber) {
        for (int i = 0; i < 4; i++) {
            this->score[i] = other.score[i];
        }
    }
    Student(Student&& move) {
        FIO = move.FIO;
        group = move.group;
        ccnumber = move.ccnumber;
        for (int i = 0; i < 4; i++) {
            this->score[i] = move.score[i];
        }
    }
    Student& operator=(Student&& moved) noexcept {
        if (this != &moved) {
            FIO = std::move(moved.FIO);
            group = std::move(moved.group);
            ccnumber = moved.ccnumber;
            for (int i = 0; i < 4; i++) {
                this->score[i] = moved.score[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& os, const Student& w) {
        os << w.FIO << ": " << w.group << "," << w.ccnumber << ", Score: ";
        for (int i = 0; i < 3; i++) {
            os << w.score[i] << ", ";
        }
        os << w.score[3];
        return os;
    }
    bool operator<(const Student& other) const {
        return FIO < other.FIO;
    }
    bool operator==(const Student& other) const {
        return FIO == other.FIO && group == other.group && ccnumber == other.ccnumber &&
               equal(begin(score), end(score), begin(other.score));
    }
};

struct StudentHash {
    size_t operator()(const Student& s) const {
        size_t h1 = hash<string>{}(s.FIO);
        size_t h2 = hash<string>{}(s.group);
        size_t h3 = hash<int>{}(s.ccnumber);
        size_t h4 = 0;
        for (int i = 0; i < 4; i++) {
            h4 ^= hash<int>{}(s.score[i]);
        }
        return h1 ^ h2 ^ h3 ^ h4;
    }
};

int main() {
    vector<Student> students;
    ifstream inputFile("input.txt");
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string fio, group;
        int ccnumber;
        int scores[4];
        getline(iss, fio, ',');
        getline(iss, group, ',');
        iss >> ccnumber;
        char comma;
        iss >> comma;
        for (int i = 0; i < 4; i++) {
            iss >> scores[i];
        }
        Student student(fio, group, ccnumber, scores);
        students.push_back(student);
    }
    inputFile.close();

    ofstream outputFile("output.txt");
    outputFile << "Source container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }

    sort(students.begin(), students.end());

    outputFile << endl << "Sorted container:" << endl;
    for (const auto& student : students) {
        outputFile << student << endl;
    }

    set<Student> studentSet(students.begin(), students.end());
    outputFile << endl << "Set container:" << endl;
    for (const auto& student : studentSet) {
        outputFile << student << endl;
    }

    unordered_set<Student, StudentHash> studentUnorderedSet(students.begin(), students.end());
    outputFile << endl << "Unordered Set container:" << endl;
    for (const auto& student : studentUnorderedSet) {
        outputFile << student << endl;
    }

    outputFile.close();

    return 0;
}
