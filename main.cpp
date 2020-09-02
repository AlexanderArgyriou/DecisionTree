#include "DTree.h"

int main()
{
	// Attributes: at least 1.
	// Row: same size for all of them.
	std::vector<std::string> Attributes1{ "Diameter", "Color", "Flavor", "NutritionalQuality", "Texture" };
	std::vector<std::vector<std::string>> DataSet1
	{
		{"Apple", "8", "Red", "Sour", "High", "Smooth"},
		{"Green Apple", "8", "Green", "Extra Sour", "High", "Smooth"},
		{"Banana", "15", "Yellow", "Sweet", "Medium", "Hard Smooth"},
		{"Lemon", "6", "Yellow", "Extra Sour", "Low", "Rough"},
		{"Grape", "15", "Green", "Sweet Sour", "Medium", "Smooth"},
		{"Watermelon", "50", "Green", "Sweet", "Medium", "Smooth"},
		{"Melon", "15", "Yellow", "Sweet", "Medium", "Hard Smooth"},
		{"Orange", "8", "Orange", "Sour", "High", "Rough"},
		{"Ananas", "40", "Green Brown", "Sweet", "High", "Rough"},
		{"Mango", "40", "Yellow", "Sweet", "High", "Smooth"}
	};

	std::vector<std::string> Attributes2{ "Sport", "Height", "Skin Color", "Country", "EyeColor", "Married"};
	std::vector<std::vector<std::string>> DataSet2
	{
		{"C.Ronaldo", "Football", "181cm", "White", "Portugal", "Black", "Yes"},
		{"L.Messi", "Football", "165cm", "White", "Argentina", "Brown", "Yes"},
		{"L.James", "Basketball", "209cm", "Black", "USA", "Black", "Yes"},
		{"T.Woods", "Golf", "175cm", "Light Black", "USA", "Black", "No"},
		{"K.Irving", "Basketball", "198cm", "Black", "USA", "Black", "No"},
		{"S.Gerrard", "Football", "181cm", "White", "UK", "Brown", "Yes"},
		{"S.Vettel", "F1", "176cm", "White", "Germany", "Brown", "Yes"},
		{"V.Rossi", "MotoGp", "176cm", "White", "Italy", "Blue", "Yes"},
		{"Thibaut Pinot", "Cycling", "181cm", "White", "France", "Brown", "Yes"},
		{"M.Phelps", "Swimming","181cm", "White", "USA", "Blue", "Yes"},
		{"R.Federer", "Tennis","187cm", "White", "Switzerland", "Brown", "Yes"},
		{"C.McGregor", "MMA","187cm", "White", "UK", "Brown", "Yes"},
		{"B.Maneff", "Tennis","187cm", "White", "Switzerland", "Brown", "Yes"},
		{"A.Winner", "MMA","187cm", "White", "UK", "Brown", "Yes"}
	};

	std::vector<std::string> Attributes3{ "Sport" };
	std::vector<std::vector<std::string>> DataSet3
	{
		{"C.Ronaldo", "Football"},
		{"L.Messi", "Football"},
		{"L.James", "Basketball"},
		{"T.Woods", "Golf"},
		{"K.Irving", "Basketball"},
		{"S.Gerrard", "Football"},
		{"S.Vettel", "F1"},
		{"V.Rossi", "MotoGp"},
		{"Thibaut Pinot", "Cycling"},
		{"M.Phelps", "Swimming"},
		{"R.Federer", "Tennis"},
		{"B.Maneff", "Tennis"}
	};

	std::vector<std::string> Answer;
	DTree *Model = new DTree(DataSet2, Attributes2);
	Model->BuildTree();	// Train Model based on the set
	//Model->PrintModel();
	Answer = Model->Predict();
	std::cout << "Decision Made: ";
	for (auto &i : Answer)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;
	delete Model;

	return 0;
}	// main


