/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 4: Priority Queue – Hospital Emergency System
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A04_PriorityQueue.cpp -o a04 && ./a04
 *
 * INPUT  : No input needed – patients are hardcoded.
 *
 * EXPECTED OUTPUT:
 *   === Admitting Patients ===
 *   Admitted: Raj Kumar      [Priority: 9]
 *   Admitted: Anita Desai    [Priority: 5]
 *   Admitted: Mohan Tiwari   [Priority: 9]
 *   Admitted: Sunita Rao     [Priority: 7]
 *   Admitted: Vikram Nair    [Priority: 3]
 *
 *   === Treating in Priority Order ===
 *   Slot 1 : Raj Kumar      [Priority: 9]
 *   Slot 2 : Mohan Tiwari   [Priority: 9]
 *   Slot 3 : Sunita Rao     [Priority: 7]
 *   Slot 4 : Anita Desai    [Priority: 5]
 *   Slot 5 : Vikram Nair    [Priority: 3]
 * ============================================================
 */

#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;

struct Patient {
    string name;
    int    priority;
    int    arrivalTime;

    // Higher priority first; equal priority -> earlier arrival first
    bool operator<(const Patient& o) const {
        if (priority != o.priority) return priority < o.priority;
        return arrivalTime > o.arrivalTime;
    }
};

int main() {
    priority_queue<Patient> pq;

    // Admit patients
    vector<Patient> incoming = {
        {"Raj Kumar",    9, 1},
        {"Anita Desai",  5, 2},
        {"Mohan Tiwari", 9, 3},
        {"Sunita Rao",   7, 4},
        {"Vikram Nair",  3, 5}
    };

    cout << "=== Admitting Patients ===" << endl;
    for (auto& p : incoming) {
        pq.push(p);
        cout << "Admitted: " << left << setw(16) << p.name
             << "[Priority: " << p.priority << "]" << endl;
    }

    cout << "\n=== Treating in Priority Order ===" << endl;
    int slot = 1;
    while (!pq.empty()) {
        Patient cur = pq.top(); pq.pop();
        cout << "Slot " << slot++ << " : "
             << left << setw(16) << cur.name
             << "[Priority: " << cur.priority << "]" << endl;
    }

    return 0;
}
