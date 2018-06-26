#include "GenerateGrid.hpp"

Grid*               GenerateRandomGrid(int const &size) {
    std::vector<int>  matrix(size * size);
    unsigned    seed = std::chrono::system_clock::now().time_since_epoch().count();

    if (size < 1)
        throw SyntaxException("Error: size must be higher than zero");
    for (int i = 0; i < size * size; i++) {
        matrix[i] = i;
    }
    std::shuffle(matrix.begin(), matrix.end(), std::default_random_engine(seed));
    return (new Grid(size, matrix));
}

Grid*            GenerateGridFromFile(std::string const &src) {
    std::ifstream   myFile(src);
    Grid*           grid;

    if (myFile.is_open())
        grid = parseFile(myFile);
    else
        throw SyntaxException("Error : This file can not be opened");
    return (grid);
}

Grid*                   parseFile(std::ifstream &ifs) {
    std::string         line;
    std::vector<int>    finalVector;
    std::vector<int>    lineVector;
    size_t              size;

    size = 0;
    while (std::getline(ifs, line)) {
        parseLine(line, lineVector);
        if (size == 0 && lineVector.size() > 1)
            throw SyntaxException("Error : The first line must specify the puzzle size");
        else if (size != 0 && lineVector.size() != size)
            throw SyntaxException("Error : Each line must contain " + std::to_string(size) + " numbers");
        else if (lineVector.size() == 1)
            size = lineVector[0];
        else {
            finalVector.insert(finalVector.end(), lineVector.begin(), lineVector.end());
        }
        lineVector.clear();
    }
    if (finalVector.empty() || size <= 0)
        throw SyntaxException("Error : Unvalid puzzle description");
    else if (finalVector.size() > size * size)
        throw SyntaxException("Error : Unvalid grid description, too much numbers");
    else if (finalVector.size() < size * size)
        throw SyntaxException("Error : Unvalid grid description, not enough numbers");
    checkMatrixNumbers(finalVector, size);
    return (new Grid(size, finalVector));
}

void                    parseLine(std::string &line, std::vector<int> &v) {
    for (std::string::iterator it = line.begin(); it != line.end(); it++) {
        if (*it == '#')
            return ;
        else if (*it == ' ' || *it == '\t')
            ;
        else if (isdigit(*it))
            v.push_back(parseWord(it));
        else {
            throw SyntaxException("Error : Unexpected character found");
        }
    }
}

int                     parseWord(std::string::iterator &it) {
    std::string     str;

    while (isdigit(*it)) {
        str += *it;
        ++it;
    }
    it -= 1;
    return (std::stoi(str));
}

void                    checkMatrixNumbers(std::vector<int> matrix, int const &size) {
    std::sort(matrix.begin(), matrix.end());
    for (int i = 0; i < static_cast<int>(matrix.size()); i++) {
        if (i != matrix[i])
            throw SyntaxException("Error : puzzle must contain every values from 0 to " + std::to_string(size * size - 1));
    }
}

Grid*                    generateSolution(size_t size){
    std::vector<int>    matrix(size * size, 0);
    int                 len = matrix.size();
    int                 x = 0;
    int                 y = 0;
    int                 i = 1;

    while (i < len) {
        while (x < static_cast<int>(size) && matrix[x + y * size] == 0 && i != len) {
            matrix[x++ + y * size] = i++;
        }
        x--;
        y++;
        while (y < static_cast<int>(size) && matrix[x + y * size] == 0 && i != len)
            matrix[x + y++ * size] = i++;
        y--;
        x--;
        while (x >= 0 && matrix[x + y * size] == 0 && i != len)
            matrix[x-- + y * size] = i++;
        x++;
        y--;
        while (y >= 0 && matrix[x + y * size] == 0 && i != len)
            matrix[x + y-- * size] = i++;
        y++;
        x++;
    }
    return (new Grid(size, matrix));
}

Grid*                   generateRegularSolution(size_t size) {
    std::vector<int>    matrix(size * size, 0);
    int                 num = 1;

    for(int y = 0; y < static_cast<int>(size); y++) {
        for(int x = 0; x < static_cast<int>(size); x++) {
            matrix[x + y * size] = num;
            num = (num + 1) % (size * size);
        }
    }
    return new Grid(size, matrix);
}

/*
**                  Exception class
*/

SyntaxException::SyntaxException(std::string msg) :
	_msg(msg)
{}

const char*		SyntaxException::what(void) const throw() {
	return (_msg.c_str());
}
