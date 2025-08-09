#include <iostream>
#include <string>
#include "blockchain/Blockchain.h"

int main() {
    blockchain::Blockchain myBlockchain(3); // ✅ Added namespace

    std::cout << "============================\n";
    std::cout << "     Simple C++ Blockchain  \n";
    std::cout << "============================\n\n";

    std::cout << "Genesis block is being created...\n";

    char choice = 'y';
    int blockCount = 1;

    while (choice == 'y' || choice == 'Y') {
        std::cout << "\n--- Block #" << blockCount << " ---\n";
        std::cout << "💡 Example transaction data format:\n";
        std::cout << "    Sender:Receiver:Amount\n";
        std::cout << "    e.g., Alice:Bob:10\n\n";

        std::string data;
        std::cout << "Enter transaction data: ";
        std::getline(std::cin, data);

        if (data.empty()) {
            data = "Alice:Bob:10";
            std::cout << "(No input detected, using demo data: " << data << ")\n";
        }

        myBlockchain.add_block(data);
        std::cout << "\n✅ Block added successfully!\n";

        std::cout << "Do you want to add another block? (y/n): ";
        std::cin >> choice;
        std::cin.ignore();

        blockCount++;
    }

    std::cout << "\n============================\n";
    std::cout << "       Blockchain Data      \n";
    std::cout << "============================\n";
    const auto& chain = myBlockchain.chain();
    for (const auto& b : chain) {
        std::cout << "----------------------------\n";
        std::cout << "Index    : " << b.index() << "\n";
        std::cout << "Timestamp: " << b.timestamp() << "\n";
        std::cout << "Data     : " << b.data() << "\n";
        std::cout << "PrevHash : " << b.previous_hash() << "\n";
        std::cout << "Hash     : " << b.hash() << "\n";
        std::cout << "Nonce    : " << b.nonce() << "\n";
    }
    std::cout << "----------------------------\n";
    std::cout << "Valid chain? " << (myBlockchain.is_chain_valid() ? "Yes" : "No") << std::endl;

    return 0;
}
