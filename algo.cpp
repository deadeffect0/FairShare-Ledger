#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
    int transactions, num_friends;
    cin >> transactions >> num_friends;

    string payer, payee;
    int amount;

    map<string, int> balanceSheet;

    int originalTransactions = transactions;
    while (transactions--) {
        cin >> payer >> payee >> amount;

        // Initialize balance for new participants
        if (!balanceSheet.count(payer)) {
            balanceSheet[payer] = 0;
        }
        if (!balanceSheet.count(payee)) {
            balanceSheet[payee] = 0;
        }

        // Update balances
        balanceSheet[payer] -= amount;
        balanceSheet[payee] += amount;
    }

    // Create a multiset to store participants with non-zero balances
    multiset<pair<int, string>> balances;
    for (const auto& entry : balanceSheet) {
        if (entry.second != 0) {
            balances.insert({entry.second, entry.first});
        }
    }

    int optimizedTransactions = 0;
    while (!balances.empty()) {
        auto lowest = balances.begin(); // Smallest balance (debtor)
        auto highest = prev(balances.end()); // Largest balance (creditor)

        int debit = lowest->first;
        string debtor = lowest->second;

        int credit = highest->first;
        string creditor = highest->second;

        balances.erase(lowest);
        balances.erase(highest);

        // Settle the minimum amount between debtor and creditor
        int settleAmount = min(-debit, credit);
        debit += settleAmount;
        credit -= settleAmount;

        cout << debtor << " pays " << settleAmount << " to " << creditor << "." << endl;

        // Reinsert updated balances if non-zero
        if (debit != 0) {
            balances.insert({debit, debtor});
        }
        if (credit != 0) {
            balances.insert({credit, creditor});
        }

        optimizedTransactions++;
    }

    cout << endl;
    cout << "Summary of Transactions:" << endl;
    cout << "-------------------------" << endl;
    cout << "Initial number of transactions: " << originalTransactions << endl;
    cout << "Optimized number of transactions: " << optimizedTransactions << endl;
    cout << "Reduction in transactions: " << (originalTransactions - optimizedTransactions) << endl;

    return 0;
}
