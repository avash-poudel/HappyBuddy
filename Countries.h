#pragma once
#pragma warning(disable : 4996)
#include <string>
#include <vector>

struct Country {
	std::string name;
	double happiness = 0;
	int ranking = 0;
};

class CountryList
{
public:
	CountryList(std::string filepath);
	Country searchCountries(std::string countryName);
	void displayList();

private:
	Country noMatch;
	std::vector<Country> countryHappinessList;

};

