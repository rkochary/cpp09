#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>

class Bitcoin
{
    public:
        Bitcoin();
        Bitcoin(const std::string& );
        Bitcoin(const Bitcoin& );
        Bitcoin& operator=(const Bitcoin& );
        ~Bitcoin();
        void change();

    private:
        std::map<int, float> _database;
        std::string _fname; 

    private:
        void takeInputData(const std::string& );
        void takeDatabase();
        void parseInputData(std::string& );
        void parseDataBase(std::string& );
        bool IsValidDate(int year, int month, int day);
        bool isLeapYear(int year);
        std::pair<int, float> checkLow(const std::pair<int, float> & );
        int toInt(std::istringstream& );
        void change_one_elem(const std::pair<int, float> &, const std::string& );

        class ConvertFailedException : std::exception
        {
            public:
                const char * what() const throw();
        };
};

#endif