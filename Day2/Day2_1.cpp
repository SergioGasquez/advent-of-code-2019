#include <iostream>
#include <sstream>
#include <string>
#include <vector>


class Command 
{
public:
    Command(int opcode,int position1, int position2, int positionRes):
    opcode_(opcode), position1_(position1), position2_(position2), positionRes_(positionRes)
    {
        //std::cout << "opcode_: "<< opcode_  << " position1_: " << position1_  << " position2_: "<< position2_ << " positionRes_: "<< positionRes_ << std::endl;
    }
    void processComand(std::vector<int> &inputVector) const
    {
        if(opcode_ == 1)
        {
            inputVector[positionRes_] = inputVector[position1_] + inputVector[position2_];
            //std::cout << "Pos " << positionRes_ << " updated with " << (inputVector[position1_] + inputVector[position2_]) << "( " << inputVector[position1_] << " + " << inputVector[position2_]  << ") " << std::endl;
        } 
        else if(opcode_ == 2)
        {
            inputVector[positionRes_] = inputVector[position1_] * inputVector[position2_];
            //std::cout << "Pos " << positionRes_ << " updated with " << (inputVector[position1_] * inputVector[position2_]) << "( " << inputVector[position1_] << " * " << inputVector[position2_]  << ") " << std::endl;

        }
        else
        {
            std::cout << "ERROR: Elfs are going to die" << std::endl;
        }
    }
    auto haltCode() const -> bool const
    {
      return (opcode_ == 99);
    }
    void printCommandInfo() const
    {
      std::cout << "opcode: "<< opcode_  << " position1: " << position1_  << " position2: "<< position2_ << " positionRes: "<< positionRes_ << std::endl;
    }

private:
    int opcode_{0};
    int position1_{0};
    int position2_{0};
    int positionRes_{0};
};


void parseInput (const std::string & input, std::vector<int> & inputVector, std::vector<Command> & inputCommands) 
{
    std::istringstream buffer(input);
    std::string cell;
    while(std::getline(buffer, cell, ','))
    {   
        inputVector.push_back(stoi(cell));
    }

    int i = 0;
    int opcode = 0;
    int position1 = 0;
    int position2 = 0;
    int positionRes = 0;

    std::vector<int> copyVector = inputVector;
    for(i = 0; i < (inputVector.size()/4); i++)
    {
        opcode = copyVector.front();
        copyVector.erase(copyVector.begin());
        position1 = copyVector.front();
        copyVector.erase(copyVector.begin());
        position2 = copyVector.front();
        copyVector.erase(copyVector.begin());
        positionRes = copyVector.front();
        copyVector.erase(copyVector.begin());

        Command command(opcode, position1, position2, positionRes);
        inputCommands.push_back(command);
    }

}

void executeCommands(std::vector<int> & inputVector, std::vector<Command> & inputCommands )
{
  for(auto elem : inputCommands)
  {
    //elem.printCommandInfo();
    if(!elem.haltCode())
    {
      elem.processComand(inputVector);
    }
    else
    {
      break;
    }
  } 
}


auto main() -> int 
{
    const std::string input =  "1,12,2,3"
                               ",1,1,2,3"
                               ",1,3,4,3"
                               ",1,5,0,3"
                               ",2,1,10,19"
                               ",1,19,6,23"
                               ",2,23,13,27"
                               ",1,27,5,31"
                               ",2,31,10,35"
                               ",1,9,35,39"
                               ",1,39,9,43"
                               ",2,9,43,47"
                               ",1,5,47,51"
                               ",2,13,51,55"
                               ",1,55,9,59"
                               ",2,6,59,63"
                               ",1,63,5,67"
                               ",1,10,67,71"
                               ",1,71,10,75"
                               ",2,75,13,79"
                               ",2,79,13,83"
                               ",1,5,83,87"
                               ",1,87,6,91"
                               ",2,91,13,95"
                               ",1,5,95,99"
                               ",1,99,2,103"
                               ",1,103,6,0"
                               ",99,2,14,0,0" ;
                               
                               
    std::vector<int> inputVector; 
    std::vector<Command>  inputCommands;   
    parseInput(input, inputVector, inputCommands); 
    executeCommands(inputVector, inputCommands);
    std::cout << "The value of the position 0 is: " << inputVector[0] << std::endl;
    return 0;
}
