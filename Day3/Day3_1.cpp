#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

// Starting poing
constexpr int STARTING_X  = 10000;
constexpr int STARTING_Y  = 10000;

// Dimensions
constexpr int ROWS_MATRIX  = 20001;
constexpr int COLS_MATRIX  = 20001;

template<class type>
class Matrix{
    int rows_;
    int cols_;
    std::vector<type> data_;
    int x_ = STARTING_X;
    int y_ = STARTING_Y;
public:
    // Consturctor
    Matrix(int row, int col):rows_(row), cols_(col), data_(rows_*cols_)
    {
    }
    // Operator overload
    auto operator()(size_t row, size_t col) -> type &
    {
        return data_[row*cols_+col];
    } 
    auto operator()(size_t row, size_t col) const -> type
    {
        return data_[row*cols_+col];
    } 
    // Draws the wire line
    void drawLine(const std::string& sense, int length)
    {
      if(sense == "R") 
      {
        for (int i = 0; i <= length; i ++)
        {
          data_[x_*cols_+(y_+i)] = 1;
        }
        y_ += length;
      }
      else if (sense == "L" )
      {
        for (int i = 0; i <= length; i ++)
        {
          data_[x_*cols_+(y_-i)] = 1;
        }
        y_ -= length;
      }  
      else if (sense == "U" )
      {
        for (int i = 0; i <= length; i ++)
        {
          data_[(x_-i)*cols_+y_] = 1;
        }
        x_ -= length;
      }
      else if (sense == "D" )
      {
        for (int i = 0; i <= length; i ++)
        {
          data_[(x_+i)*cols_+y_] = 1;
        }
        x_ += length;
      }
      else
      {
        std::cout << "Wrong direction :(" << std::endl;
      }  
    }

    // Prints the map
    void printMap()
    {
      for (int i = 0; i < rows_; i ++)
      {
        std::cout << std::endl;
        for (int j = 0; j < cols_; j ++)
        {
          std::cout << data_[i*cols_+j] << " ";
        }
      }
    }
};


// Parses the input string and saves it into a vector of pairs (sense and length to move)
void parseString(std::string & wire, std::vector< std::pair<std::string, int>> & directions)
{
  std::istringstream buffer(wire);
  std::string cell;
  while(std::getline(buffer, cell, ','))
  {   
      std::string sense = cell.substr(0, 1);
      int length = stoi(cell.substr(1,cell.size()));
      directions.push_back(make_pair(sense,length));
  }
}

// Adds two matrixs
void addMaps(const Matrix<int> &a, const Matrix<int> &b, Matrix<int> & result) 
{
    for (int i = 0; i < ROWS_MATRIX ; i ++)
    {
      for (int j = 0; j < COLS_MATRIX; j ++)
      {
        result(i,j) = a(i,j) + b(i,j);
      }
    }
}

// Method that parses and draws the lines for a map
void processWire(std::string & wire, Matrix<int> & map)
{
  std::vector< std::pair<std::string, int>>  directions;
  parseString(wire, directions);
  for(const auto& elem : directions)
  {
    std::string sense = elem.first;
    int length = elem.second;
    map.drawLine(sense, length);
    //std::cout << sense << " " << length << std::endl;
  }
  //map.printMap();
}

auto findCloserIntersection(Matrix<int> & map) -> int
{
  int result = -1;
  int distance = 0;
  for (int i = 0; i < ROWS_MATRIX ; i++)
    {
      for (int j = 0; j < COLS_MATRIX; j++)
      {
        if(map(i,j) > 1 && i != STARTING_X && j != STARTING_Y)
        {
          distance = abs(i - STARTING_X) + abs(j - STARTING_Y); 
          if(result == -1 || distance < result)
          {
            result = distance;
          }
        }
      }
    }
    return result;
}
auto main() -> int 
{
  // Inputs
  std::string wire1 = "R998,U494,L814,D519,R407,U983,R307,D745,R64,D29,L935,D919,L272,D473,R689,U560,L942,U264,R816,U745,R209,U227,R241,U111,L653,D108,R823,U254,L263,U987,L368,D76,R665,D646,L759,U425,L581,D826,R829,D388,L234,U33,L48,U598,L708,D764,L414,D75,L163,U802,L183,U893,L486,U947,L393,D694,L454,D600,R377,U312,R89,D178,L652,D751,R402,D946,R213,U985,R994,D336,R573,D105,L442,U965,R603,U508,L17,U191,L37,U678,L506,U823,R878,D709,L348,U167,L355,U314,L164,D672,L309,U895,R358,D769,R869,U598,R63,D68,R105,U133,R357,U588,L154,D631,L939,D235,R506,D885,R958,D896,L195,U292,L952,D616,L824,D497,R99,D121,R387,D155,L70,U580,L890,D368,L910,U645,L786,U977,R9,U781,L454,U783,L382,U321,L195,U196,L239,U764,R18,D71,R97,U77,L803,U963,L704,U94,L511,U747,L798,D905,L679,D135,R455,U650,R947,U14,L722,D245,L490,D183,L276,U559,L901,D767,R827,U522,L380,U494,R402,U70,R589,D582,R206,U756,L989,U427,L704,D864,R885,D9,R872,U454,R912,U752,R197,U304,L728,U879,R456,D410,L141,U473,R246,U498,R443,D297,R333,D123,R12,D665,R684,D531,R601,D13,L260,U60,R302,D514,R416,D496,L562,D334,L608,U74,R451,U251,R961,U166,L368,U146,R962,U973,R120,U808,R480,D536,L690,D958,R292,U333,R656,U305,R46,U831,L756,D907,L638,D969,L445,U541,R784,U148,R338,D264,R72,D637,R759,D709,L611,D34,R99,U305,R143,D191,R673,D753,R387,U994,R720,D896,R95,U703,L499,D453,R96,U808,L485,U127,L856,U357,L543,U382,R411,U969,L532,U64,R303,U457,L412,D140,R146,D67,R147,D681,L1,D994,L876,D504,R46,U683,L992,U640,L663,D681,L327,U840,R543,U97,R988,U792,R36";
  std::string wire2 = "L999,U148,L592,D613,L147,D782,R594,U86,R891,D448,R92,U756,R93,D763,L536,U906,L960,D988,L532,U66,R597,U120,L273,D32,R525,U628,L630,U89,L248,U594,R886,D544,L288,U380,L23,D191,L842,U394,L818,U593,L195,U183,L863,D456,L891,D653,R618,U314,L775,D220,R952,U960,R714,U946,L343,D873,L449,U840,R769,U356,L20,D610,L506,U733,R524,D450,L888,D634,R737,U171,R906,U369,L172,D625,L97,D437,R359,D636,R775,U749,L281,U188,R418,D437,R708,D316,L388,D717,R59,U73,R304,U148,L823,U137,R265,U59,R488,D564,R980,U798,L626,U47,L763,U858,L450,U663,R378,U93,L275,U472,L792,U544,R192,D979,L520,U835,L946,D615,L120,U923,L23,U292,R396,U605,L76,U813,L388,U500,L848,U509,L276,D538,R26,D806,R685,D319,R414,D989,L519,U603,R898,D477,L107,D828,R836,U432,L601,U888,L476,D974,L911,U122,L921,D401,L878,D962,L214,D913,L113,U418,R992,U844,L928,U534,L13,U457,L866,D208,L303,D732,L497,U673,R659,D639,R430,D301,L573,U373,L270,D901,L605,D935,R440,D183,R374,D883,L551,U771,R707,D141,R984,U346,R894,U1,R33,U492,R371,D631,R95,D62,L378,D343,R108,D611,L267,D871,L296,U391,R302,D424,R160,U141,R682,U949,R380,U251,L277,D404,R392,D210,L158,U896,R350,D891,L837,D980,R288,U597,L292,D639,L943,D827,L492,D625,L153,D570,R948,D855,L945,U840,L493,U800,L392,D438,R8,U966,R218,U597,R852,D291,L840,D831,L498,U846,R875,D244,R159,U243,R975,D246,R549,D304,R954,D123,R58,U5,L621,U767,R455,U550,R800,D417,R869,D184,L966,D51,L383,U132,L664,U220,L263,D307,R716,U346,L958,U84,L154,U90,L726,U628,L159,U791,L643,D652,L138,U577,R457,U655,L547,D441,L21";
  
  Matrix<int>  frontPanel(ROWS_MATRIX, COLS_MATRIX); 
  Matrix<int>  mapWire1(ROWS_MATRIX, COLS_MATRIX);
  Matrix<int>  mapWire2(ROWS_MATRIX, COLS_MATRIX);

  processWire(wire1, mapWire1);
  processWire(wire2, mapWire2);

  addMaps(mapWire1,mapWire2,frontPanel);
  //frontPanel.printMap();
  int distance = findCloserIntersection(frontPanel);
  std::cout << "\n Distance: " << distance << std::endl;
}
