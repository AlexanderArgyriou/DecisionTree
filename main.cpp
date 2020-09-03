#include "DTree.h"
#include "DataSet.h"

inline void TrainModel(const char *FileName) noexcept;

int main()
{
	TrainModel("DataSets\\NBA_Players_2015.txt");
	return 0;
}	// main

inline void TrainModel(const char *FileName) noexcept
{
	DTree  *Model;
	VecStr	Answer;
	DataSet D(FileName);

	D.LoadSet();
	Model = new DTree(D.GetDataSet(), D.GetAtt());
	Model->BuildTree();	// Train Model based on the set
	Model->PrintModel();
	Answer = Model->Predict();
	std::cout << "Decision Made: ";
	for (const auto& i : Answer)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;
	delete Model;
}	// TrainModel


