#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

typedef std::vector<std::vector<std::string>> Set;
typedef std::vector<std::string>              VecStr;

class DataSet
{
	private:
		Set           Data;
		VecStr        Attributes;
		std::ifstream File;
		std::string   Filename;

	public:
		inline DataSet(const char *newFileName) noexcept
			: Filename(newFileName)
		{}	// Constructor

		inline ~DataSet() noexcept
		{
			Data.clear();
			Attributes.clear();
			Filename = "";
		}	// Destructor

		inline void LoadSet() noexcept
		{
			File.open(Filename.c_str());
			if (!File)
			{
				std::cout << "Invalid FileName";
				exit(1);
			}	// if

			std::string        Line;
			std::string        Token;
			std::getline(File, Line);
			std::istringstream iss(Line);
			while (std::getline(iss, Token, '\t'))
				Attributes.push_back(Token);
			Attributes.erase(Attributes.begin());	// erase Label

			while (std::getline(File, Line))
			{     
				std::istringstream iss(Line);
				std::string		   Token;
				VecStr			   Add;
				while (std::getline(iss, Token, '\t'))   
					Add.push_back(Token);
				Data.push_back(Add);
			}	// while

			Data.shrink_to_fit();
			for (auto &D : Data) D.shrink_to_fit();
			Attributes.shrink_to_fit();

			File.close();
		}	// LoadSet

		inline void Write() const noexcept
		{
			for (auto &A : Attributes)
				std::cout << A << " ";
			std::cout << "\n";

			for (const auto &i : Data)
			{
				for (const auto &j : i)
					std::cout << j << " ";
				
				std::cout << "\n";
			}
		}	// Write

		inline const Set &GetDataSet() const noexcept { return Data; }        // GetDataSet
		inline const VecStr &GetAtt() const noexcept { return Attributes; }   // GetAtt
};	//	DataSet
