#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <Grid.hpp>
# include <fstream>

class GenerateGrid {
public:

    static Grid* const      from(int const &size) const;
    static Grid* const      from(std::string const &src) const;

private:

    Parser();
    virtual ~Parser();

};

#endif
