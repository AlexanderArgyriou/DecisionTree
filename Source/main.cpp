#include "DTree.h"
#include "DataSet.h"

inline void TrainModel(const char *FileName, 
	const Vec_vec_str &TD) noexcept;

int main() 
{
	/*Vec_vec_str TestingDataAthletesForbes
	{
		{"57.3", "25.3", "32", "Basketball"}, // Kevin Durant
		{"26.9", "19.9", "7", "Soccer"}	      // Luis Suarez
	};
	TrainModel("DataSets\\AtheletesForbes.txt", TestingDataAthletesForbes);
	
	Vec_vec_str TestingDataNFL
	{
		{"CB", "TEN", "69"}, // Logan Ryan
		{"DB", "OAK", "75"}  // Sean Smith
	};
	TrainModel("DataSets\\NFL_Players.txt", TestingDataNFL);

	Vec_vec_str TestingDataNBA
	{
		{"2013", "74.25", "75.25", "78.25", "96.5", 
		"38.5", "135", "32", "128.5", "197", "8.6", 
		"8", "9.5", "13", "11.02", "3.32"} // C.J.McCollum
	};
	TrainModel("DataSets\\NBA_Draft_2013.txt", TestingDataNBA);

	Vec_vec_str TestingDataCountries
	{
		{"Oceania", "NZD"},      // Cook Islands
		{"North America", "CRC"} // Costa Rica	
	};
	TrainModel("DataSets\\Countries.txt", TestingDataCountries);

	Vec_vec_str TestingDataCountriesNobels
	{
		{"2", "66", "0", "2", "0%", "100%" } // Greece
	};
	TrainModel("DataSets\\Countries_By_Nobels.txt", TestingDataCountriesNobels);
	*/
	// --- Toy Set --- //
	/*VecStr Attribute{ "Diam","Color" };
	Set training_data = {
		{"Apple","3","Green"} ,
			{"Apple","3","Yellow"},
			{"Grape","1","Red"},
			{"Grape","1","Red"},
			{"Lemon","3","Yellow"},
	};
	DTree* Model = new DTree(training_data, Attribute);
	Model->BuildTree();
	Model->PrintModel();
	delete Model;*/
	return 0;
}	// main

inline void TrainModel(const char *FileName, 
	const Vec_vec_str &TD) noexcept
{
	DTree  *Model;
	Vec_str	Answer;
	DataSet TrainingData(FileName);

	TrainingData.LoadSet();
	//D.Write();

	Model = new DTree(TrainingData.GetDataSet(), TrainingData.GetAtt());
	Model->BuildTree();	// Train Model based on the set
	Model->Test(TD);
	//Model->PrintModel();
	//std::cout << "Model Height: " << Model->TreeHeight() << std::endl;	// TreeHeight() - 1 worst case
	//std::cout << Model->AvgQuestionsToPredict() << std::endl;
	/*Answer = Model->Predict();
	std::cout << "Decision Made: ";
	for (const auto &i : Answer)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;*/

	delete Model;
}	// TrainModel


