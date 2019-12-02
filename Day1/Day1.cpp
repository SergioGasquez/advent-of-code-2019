
#include <fstream>
#include <iostream>
#include <string>

void computeFuel (int number, int & result) 
{
    number = number/3 -2;
    if (number  >= 0)
    {
        result += number;
        computeFuel(number, result);
    }   
}

auto computeMassFromFile (const std::string& filename) -> int
{
    int result = 0;
    int number = 0;
    std::ifstream inputFile (filename);
    if (inputFile.is_open())
    {
        while (inputFile >> number) 
        {
            computeFuel(number, result);
        }
    }
    inputFile.close();
    return result;
}

auto main() -> int 
{
    int result = 0;
    auto res = computeMassFromFile("Input.txt");
    std::cout << res << std::endl;

    return 0;
}
