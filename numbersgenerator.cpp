#include <iostream>
#include <fstream>
#include <random>

int main() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(2, 100);

    int num_numbers = dist(gen);

    std::ofstream file("numbers.txt");
    if (!file.is_open()) 
    {
        std::cerr << "Cannot open file" << std::endl;
        return 1;
    }

    for (int i = 0; i < num_numbers; ++i) 
    {
        int number = dist(gen);
        file << number;
        if (i < num_numbers - 1) 
        {
            file << ", ";
        }
    }

    file.close();
    return 0;
}