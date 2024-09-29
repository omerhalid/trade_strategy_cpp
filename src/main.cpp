#include <iostream>
#include <string>
#include <vector>
#include "../inc/utils.hpp"
#include "../inc/strategy.hpp"

int main()
{
    // Load environment variables from .env file
    loadEnv();

    // Display the menu
    loadMenu();

    return 0;
}