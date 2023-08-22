#include "BitcoinExchange.hpp"

Bitcoin::Bitcoin(){}

Bitcoin::Bitcoin(const std::string& inp_fname)
{
    takeDatabase();
    _fname = inp_fname;
}

Bitcoin::Bitcoin(const Bitcoin& other)
{
    *this = other;
}

Bitcoin& Bitcoin::operator=(const Bitcoin& rhs)
{
    if (this != &rhs)
    {
        _database = rhs._database;
        _fname = rhs._fname;
    }
    return *this;
}

Bitcoin::~Bitcoin() {}

void Bitcoin::takeDatabase()
{
    std::string strtmp;
    std::ifstream file("data.csv");
    if (!file)
    {
        std::cout << "Error: data.csv file not found\n";
    }
    std::getline(file, strtmp);
    while (std::getline(file, strtmp))
    {
        if (!file.eof())
        {
            parseDataBase(strtmp);
        }
        else
            break;
    }
}

int Bitcoin::toInt(std::istringstream& str)
{
    int result = 0;
    std::string year;
    std::string month;
    std::string day;
    std::getline(str, year, '-');
    std::getline(str, month, '-');
    std::getline(str, day, '-');
    int iyear = atoi(year.c_str());
    int imonth = atoi(month.c_str());
    int iday = atoi(day.c_str());
    if (!IsValidDate(iyear, imonth, iday))
        return (0);
    result = iyear * 10000 + imonth * 100 + iday;
    return result;
}

void Bitcoin::parseDataBase(std::string &inp_str)
{
    std::string part1;
    int tmp = 0;
    float part2;

    std::istringstream stream(inp_str);
    
    std::getline(stream, part1, ',');
    stream >> part2;
    if (stream.fail())
        throw ConvertFailedException(); 

    std::istringstream tmp_stream(part1);

    tmp = toInt(tmp_stream);
    if (tmp == 0)
        std::cout << "Error: bad database => " << inp_str; 
    _database.insert(std::make_pair(tmp, part2));
}

bool Bitcoin::isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool Bitcoin::IsValidDate(int year, int month, int day)
{
    if (year < 2009 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    static const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDays = daysInMonth[month];
    
    if (month == 2 && isLeapYear(year)) {
        maxDays = 29;
    }

    if (day > maxDays) {
        return false;
    }
    return true;
}

void Bitcoin::change_one_elem(const std::pair<int, float> &elem, const std::string &org_date)
{  
    float res_val = 1.0f;
    std::string res_str = "";

    if (elem.first == 0.0f)
    {
        std::cout << "Error: bad input => " << org_date << std::endl;
        return ;
    }
    else if (elem.second < 0)
    {
        std::cout << "Error: not a positive number. " << std::endl;
        return ;
    }
    else if (elem.second > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return ;
    }
    else
    {
        std::pair<int, float> closest = checkLow(elem);
        res_str = closest.first;
        res_val = closest.second * elem.second;
        std::cout << org_date << " => " << elem.second << " = "<< res_val << std::endl;
    }
}

void Bitcoin::takeInputData(const std::string& fname)
{
    std::string strtmp;
    std::ifstream file(fname);
    if (!file)
    {
        std::cout << "Error: " << fname << " file not found\n";
    }
    std::getline(file, strtmp);
    while (std::getline(file, strtmp))
    {
        parseInputData(strtmp);
        if (file.eof())
            break;
    }
}

void Bitcoin::parseInputData(std::string &inp_str)
{
    std::string part1;
    std::string tmp_str;
    std::string tmp_part2;
    float part2 = 0.0;
    int idate;
    if (inp_str.find("|") == std::string::npos)
    {
        std::cout << "Error: bad input => " << inp_str << std::endl;
    }
    else
    {
        std::istringstream stream(inp_str);

        if(std::getline(stream, part1, '|'))
        {
            stream >> tmp_part2;
            part2 = static_cast<float>(atof(tmp_part2.c_str()));
        }
        std::istringstream tmp_stream(part1);

        idate = toInt(tmp_stream);

        change_one_elem(std::make_pair(idate, part2), part1);
    }
}

void Bitcoin::change()
{
    takeInputData(_fname);

}

std::pair<int, float> Bitcoin::checkLow(const std::pair<int, float> &elem)
{
    std::map<int, float>::reverse_iterator it;
    for(it = _database.rbegin(); it != _database.rend(); ++it)
    {
        if (it->first <= elem.first)
        {
            return std::make_pair(it->first, it->second);
        }
    }
    return std::make_pair(_database.begin()->first, _database.begin()->second);
}

const char* Bitcoin::ConvertFailedException::what() const throw()
{
    return ("Exception: Conversion failed");
}