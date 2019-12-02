#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Instructions
constexpr int SUM_INSTRUCTION  = 1;
constexpr int MULT_INSTRUCTION  = 2;
constexpr int HALT_INSTRUCTION  = 99;

// Max ranges
constexpr int MAX_NOUN  = 99;
constexpr int MAX_VERB  = 99;


// Class to store and process diferents instructions
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
        if(opcode_ == SUM_INSTRUCTION)
        {
            inputVector[positionRes_] = inputVector[position1_] + inputVector[position2_];
            //std::cout << "Pos " << positionRes_ << " updated with " << (inputVector[position1_] + inputVector[position2_]) << "( " << inputVector[position1_] << " + " << inputVector[position2_]  << ") " << std::endl;
        } 
        else if(opcode_ == MULT_INSTRUCTION)
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
      return (opcode_ == HALT_INSTRUCTION);
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

// Saves the input string into a int vector
void parseInput (const std::string & input, std::vector<int> & inputVector) 
{
    std::istringstream buffer(input);
    std::string cell;
    while(std::getline(buffer, cell, ','))
    {   
        inputVector.push_back(stoi(cell));
    }
}

// Saves into vector of commands the differents instructions to be executed
void saveCommands (std::vector<int> inputVector, int numberOfCommands, std::vector<Command> & inputCommands)
{
  int i = 0;
  int opcode = 0;
  int position1 = 0;
  int position2 = 0;
  int positionRes = 0;

  for(i = 0; i < numberOfCommands; i++)
  {
      opcode = inputVector.front();
      inputVector.erase(inputVector.begin());
      position1 = inputVector.front();
      inputVector.erase(inputVector.begin());
      position2 = inputVector.front();
      inputVector.erase(inputVector.begin());
      positionRes = inputVector.front();
      inputVector.erase(inputVector.begin());

      Command command(opcode, position1, position2, positionRes);
      inputCommands.push_back(command);
  }

}

// Executes the instructins in a vector of commands until it encounters a halt instruction or the vector ends
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

// Obtains the noun and verb which give the desired target result at the element 0. Returns true if result is found, false otherwise
auto getNounAndVerb(std::vector<int> & inputVector, std::vector<Command> & inputCommands, int & noun, int & verb,int target) -> bool
{
  bool resultFound = false;
  int numberOfCommands = inputVector.size()/4;
  for (noun = 0; noun <= MAX_NOUN; ++noun)
  {
    inputVector[1] = noun;
    for (verb = 0; verb <= MAX_VERB; ++verb)
    {
      inputVector[2] = verb;

      saveCommands(inputVector, numberOfCommands, inputCommands);
      executeCommands(inputVector, inputCommands);
      if(inputVector[0] == target)
      {
        return true;
      }
    }
  }
  return false;

}



auto main() -> int 
{
    const std::string input =  "1,0,0,3"
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
    parseInput(input, inputVector); 
    int noun = 0;
    int verb = 0;
    constexpr int target  = 19690720;

    auto res = getNounAndVerb(inputVector,inputCommands,noun, verb, target);    
    if(res)
    {
      std::cout << "We did get the magic noun (" <<  noun << ") and verb(" << verb << "). Hurray!" << std::endl;
    }
    else
    {
      std::cout << "Result not Found - Gifts will also be turn to magic smoke";
    }
    return 0;
}
