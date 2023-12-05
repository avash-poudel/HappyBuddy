#include "Countries.h"
#include <wx/wx.h>
#include <fstream>
#include <sstream>
#include <iostream>

CountryList::CountryList(std::string filepath)
{
	noMatch.name = "This country was not found";
	noMatch.happiness = 0.0;
	noMatch.ranking = 0;

	std::ifstream csv(filepath);
	if (!csv.is_open())
	{
		wxLogMessage("Could not open CSV file stated");
	}
	else
	{
		std::string line;
		getline(csv, line);
		while (getline(csv, line))
		{
			Country newCountry;
			std::istringstream stream(line);

			getline(stream, newCountry.name, ',');
			//Name of country in lower case

			std::string happiness_str;
			getline(stream, happiness_str, ',');
			newCountry.happiness = stod(happiness_str);
			//Turns happiness string into int input for country

			std::string ranking_str;
			getline(stream, ranking_str, ',');
			newCountry.ranking = stoi(ranking_str);

			countryHappinessList.push_back(newCountry);
		}
		csv.close();
	}
}

Country CountryList::searchCountries(std::string countryName)
{
	for (Country curr_country : countryHappinessList)
	{
		std::string lowercurrCountry = "";
		std::string lowersearchCountry = "";
		for (char letter : curr_country.name)
		{
			lowercurrCountry.push_back(tolower(letter));
		}
		for (char letter : countryName)
		{
			lowersearchCountry.push_back(tolower(letter));
		}

		if (lowercurrCountry == lowersearchCountry)
		{
			return curr_country;
		}
	}
	return noMatch;
}

void CountryList::displayList()
{
	for (Country curr_country : countryHappinessList)
	{
		std::cout << curr_country.name << " Happiness: " << curr_country.happiness << " Ranking " << curr_country.ranking << std::endl;
	}

}
