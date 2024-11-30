#include "okx_client.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h> // For getcwd()

void loadEnvFile(const std::string& filename) {
    // Check and print the current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << std::endl;
    } else {
        std::cerr << "Error: Unable to get current working directory." << std::endl;
    }

    // Attempt to open the .env file
    std::ifstream envFile(filename);
    if (!envFile.is_open()) {
        std::cerr << "Error: Could not open .env file at " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(envFile, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            // Set the environment variable on macOS/Linux
            if (setenv(key.c_str(), value.c_str(), 1) != 0) {
                std::cerr << "Error: Could not set environment variable " << key << std::endl;
            }
        }
    }

    envFile.close();
    std::cout << "Environment variables loaded successfully." << std::endl;
}

int main() {
    // Load environment variables from the .env file
    loadEnvFile(".env");

    // Retrieve the environment variables
    const char* apiKey = getenv("OKX_API_KEY");
    const char* secretKey = getenv("OKX_SECRET_KEY");
    const char* passphrase = getenv("OKX_PASSPHRASE");

    // Check if all required environment variables are set
    if (!apiKey || !secretKey || !passphrase) {
        std::cerr << "Error: API key, secret key, or passphrase environment variable is not set." << std::endl;
        return 1;
    }

    // Initialize the OKXClient with the loaded environment variables
    OKXClient client(apiKey, secretKey, passphrase);

    // Example usage of OKXClient methods
    client.placeOrder("MAGIC-USDT-SWAP", "buy", "limit", 1, 0.3); // works for open order
    // client.placeOrder("MAGIC-USDT-SWAP", "buy", "limit", 1, 0.345); // works for filled order
    // client.getPendingOrders("limit", "SWAP"); // works
    // client.getOrderHistory("MAGIC-USDT-SWAP", "SWAP");
    // client.cancelOrder("MAGIC-USDT-SWAP", "1704069961901199360"); // works
    // client.getOpenOrders("MAGIC-USDT-SWAP", "SWAP"); // works
    // client.modifyOrder("1704076679599149056", "MAGIC-USDT-SWAP", "2", "0.352"); // works
    // client.getOpenOrders("MAGIC-USDT-SWAP", "SWAP"); // works

    // Output examples of client methods
    std::cout << client.getOrderBook("MAGIC-USDT-SWAP") << std::endl;
    std::cout << client.getCurrentPositions() << std::endl;

    return 0;
}