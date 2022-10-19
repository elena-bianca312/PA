#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <list>
#include <map>
using namespace std;

#define BIGSTRING "ZZZZZZZZZ"

struct Person {
    string name;
    int no;
    set<string> emails;

    Person(string name, int no, set<string> emails)
        : name(name),
          no(no),
          emails(emails)
          {}
};

bool sort_people(Person p1, Person p2) {
    if (p1.no != p2.no)
        return p1.no < p2.no;
    if (p1.name != p2.name)
        return p1.name < p2.name;
}

int main() {
    char inFilename[50] = "adrese.in";
    ifstream fin;
    fin.open(inFilename);
    if (!fin.is_open()) {
        exit(EXIT_FAILURE);
    }

    vector<Person> people;

    int n, i, j, real = 0, count = 0;
    fin >> n;
    string name, email;
    int no, no_email = 0;
    set<string> emails;

    map<string, vector<int>> my_map;

    for (i = 0; i < n; i++) {
        fin >> name;
        fin >> no;
        for (j = 0; j < no; j++) {
            fin >> email;
            no_email++;
            emails.insert(email);
            if (my_map.find(email) == my_map.end()) {
                vector<int> v;
                v.emplace_back(i);
                my_map.emplace(email, v);
            } else {
                my_map.at(email).push_back(i);
            }
        }
        people.emplace_back(name, no, emails);
        emails.clear();
        real++;
        count++;
    }

    for (auto it : my_map) {
        if (it.second.size() > 1) {
            string name = BIGSTRING;
            int id;
            for (auto it2 : it.second) {
                if (people.at(it2).name < name && people.at(it2).no != 0) {
                    name = people.at(it2).name;
                    id = it2;
                }
            }

            for (auto it2 : it.second) {
                if (it2 != id && people.at(it2).no != 0) {
                    for (auto cnt : people.at(it2).emails) {
                        people.at(id).emails.insert(cnt);
                        my_map.at(cnt).push_back(id);
                    }
                    real--;
                    people.at(it2).no = 0;
                    people.at(id).no = people.at(id).emails.size();
                }
            }
        }
    }

    char outFilename[50] = "adrese.out";
    ofstream fout;
    fout.open(outFilename);
    fout << real << endl;
    sort(people.begin(), people.end(), &sort_people);
    for (i = 0; i < count; i++) {
        if (people[i].no != 0) {
            fout << people[i].name << " " << people[i].emails.size() << endl;
            for (auto j : people.at(i).emails) {
                fout << j << endl;
            }
        }
    }
    fout.close();

    return 0;
}
