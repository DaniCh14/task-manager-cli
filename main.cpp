
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string text;
    bool done;
};

int main() {
    vector<Task> tasks;

    ifstream in("tasks.txt");
    string line;

    // Load saved tasks
    while (getline(in, line)) {
        if (line.size() > 2 && line[1] == '|') {
            tasks.push_back({
                line.substr(2),
                line[0] == '1'
            });
        }
    }

    while (true) {
        cout << "\n1. Add"
             << "  2. List"
             << "  3. Complete"
             << "  4. Delete"
             << "  0. Exit\n> ";

        int choice;

        if (!(cin >> choice)) {
            break;
        }

        cin.ignore(10000, '\n');

        if (choice == 0) {
            break;
        }

        // Add a new task
        if (choice == 1) {
            cout << "Task: ";
            getline(cin, line);

            if (!line.empty()) {
                tasks.push_back({line, false});
            }
        }

        // Display all tasks
        else if (choice == 2) {
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << i + 1 << ". ["
                     << (tasks[i].done ? 'x' : ' ')
                     << "] " << tasks[i].text << '\n';
            }
        }

        // Complete or delete a task
        else if (choice == 3 || choice == 4) {
            cout << "Number: ";

            size_t n;
            cin >> n;
            cin.ignore(10000, '\n');

            if (n > 0 && n <= tasks.size()) {
                if (choice == 3) {
                    tasks[n - 1].done = true;
                } else {
                    tasks.erase(tasks.begin() + n - 1);
                }
            } else {
                cout << "Invalid number\n";
            }
        }

        // Save tasks to file
        ofstream out("tasks.txt");

        for (const auto& t : tasks) {
            out << (t.done ? '1' : '0')
                << '|'
                << t.text
                << '\n';
        }
    }

    return 0;
}
