#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <stdlib.h> 

enum TheLabel     { Label };
enum TreeChlidren { Yes, No, NumOfChildren };

class DTree
{
	private:
		class Question
		{
			public:
				std::string Q;
				
				inline Question() noexcept;                                       // Def Constructor
				inline Question(const std::string &newQ) noexcept;                // Constructor
				inline const Question &operator=(const Question &other) noexcept; // operator = 
		};	// Question

		class Node
		{
			public:
				bool                                  Leaf;
				std::vector<std::vector<std::string>> Data;
				std::vector<Node *>                   Children;
				float                                 Impurity;
				Question                              Qst;

				inline Node(const std::vector<std::vector<std::string>> &newData, 
					bool isLeaf, float newImpurity) noexcept; // Constructor
				inline void Write() const noexcept;               // Write
		};	// Node

		//---Private Methods---//
		inline std::pair<std::string, int> 
			FindTheRightQuestion(const std::vector<std::vector<std::string>> &Set) const noexcept;      // FindTheRightQuestion
		inline float 
			CaclulateImpurity(const std::vector<std::vector<std::string>> &DataSet) const noexcept;     // CaclulateImpurity
		inline void BuildTree(Node *Tree) noexcept;                                                         // BuildTree
		inline void Deallocate(Node *Tree) noexcept;                                                        // Deallocate
		inline void PrintModel(Node *Tree) const noexcept;                                                  // PrintModel
		inline bool IsNumber(const std::string &S) const noexcept;                                          // IsNumber
		inline double 
			CalculateAvg(const std::vector<std::vector<std::string>> &DataSet, int Col) const noexcept; // CalculateAvg

		//---Private Data--//
		const std::vector<std::vector<std::string>> *TrainSet;
		Node                                        *Root;
		const std::vector<std::string>              &Attributes;

	public:
		inline DTree(const std::vector<std::vector<std::string>> &Set, 
			const std::vector<std::string> &Attrs) noexcept;       // Constructor
		inline ~DTree() noexcept;                                      // Destructor
		inline void BuildTree() noexcept;                              // Train-Build Model
		inline void PrintModel() const noexcept;                       // Print Model
		inline std::vector<std::string> Predict() const noexcept;      // Answer Questions
};	// DTree

//-------Question Class, public Section-------//
inline DTree::Question::Question() noexcept
	: Q("")
{}	// Def Constructor

inline DTree::Question::Question(const std::string &newQ) noexcept
	: Q(newQ)
{}	// Constructor

inline const DTree::Question &DTree::Question::operator=(const Question &other) noexcept
{
	if (this != &other) this->Q = other.Q;
	return *this;
}	// operator = 

//-------Node Class, public Section-------//
inline DTree::Node::Node(const std::vector<std::vector<std::string>> &newData,
	bool isLeaf, float newImpurity) noexcept
	: Leaf(isLeaf), Data(newData), Impurity(newImpurity), Children(NumOfChildren)
{}	// Constructor

inline void DTree::Node::Write() const noexcept
{
	for (const auto &i : Data)
	{
		for (const auto &j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}	// for
	std::cout << "Impurity: " << Impurity << std::endl;
	std::cout << std::endl;
}	// Write

//-------DTree Class, private Section-------//
inline double DTree::CalculateAvg(const std::vector<std::vector<std::string>> &DataSet, int Col) const noexcept
{
	double Sum = 0.0;
	std::string::size_type sz;

	for(std::size_t i = 0; i < DataSet.size(); i++)
		Sum += std::stod(DataSet[i][Col], &sz);

	return Sum / (double)DataSet.size();
}	// CalculateAvg

inline bool DTree::IsNumber(const std::string &S) const noexcept
{
	char *p;
	double val = strtod(S.c_str(), &p);
	return !*p;
}	// IsNumber

inline void DTree::PrintModel(Node *Tree) const noexcept
{
	if (Tree)
	{
		if (Tree->Leaf)
			Tree->Write();
		PrintModel(Tree->Children[Yes]);
		PrintModel(Tree->Children[No]);
	}	// if
}

inline void DTree::Deallocate(Node *Tree) noexcept
{
	if (Tree)
	{
		Deallocate(Tree->Children[Yes]);
		Deallocate(Tree->Children[No]);
		delete Tree;
	}	// if
}	// Deallocate

inline void DTree::BuildTree(Node *Tree) noexcept
{
	auto Qst = FindTheRightQuestion(Tree->Data);
	if (Qst.first != "" && Qst.second != -1)
	{
		std::vector<std::vector<std::string>> DataSetYes;
		std::vector<std::vector<std::string>> DataSetNo;
		std::vector<int> Y;
		std::vector<int> N;

		if (IsNumber(Qst.first))
		{
			double Avg = CalculateAvg(Tree->Data, Qst.second);
			std::string::size_type sz;
			Tree->Qst = DTree::Question("Is " + Attributes[Qst.second - 1] + " >= " + std::to_string(Avg) + "?");
			for (std::size_t i = 0; i < Tree->Data.size(); ++i)
			{
				if (Avg <= std::stod(Tree->Data[i][Qst.second], &sz)) Y.push_back(i);
				else N.push_back(i);
			}
		}	// number
		else
		{
			Tree->Qst = DTree::Question("Is " + Attributes[Qst.second - 1] + " " + Qst.first + "?");
			for (std::size_t i = 0; i < Tree->Data.size(); ++i)
				if (Qst.first == Tree->Data[i][Qst.second]) Y.push_back(i);
				else N.push_back(i);
		}	// not a number

		for (std::size_t i = 0; i < Y.size(); ++i)
		{
			std::vector<std::string> Add;
			for (std::size_t j = 0; j < Tree->Data[0].size(); j++)
				Add.push_back(Tree->Data[Y[i]][j]);
			DataSetYes.push_back(Add);
		}	// for

		for (std::size_t i = 0; i < N.size(); ++i)
		{
			std::vector<std::string> Add;
			for (std::size_t j = 0; j < Tree->Data[0].size(); j++)
				Add.push_back(Tree->Data[N[i]][j]);
			DataSetNo.push_back(Add);
		}	// for 

		Tree->Children[Yes] = new(std::nothrow) Node(DataSetYes, false, CaclulateImpurity(DataSetYes));
		if (!Tree->Children[Yes])
		{
			std::cerr << "Out of mem!";
			exit(1);
		}	// if
		BuildTree(Tree->Children[Yes]);

		Tree->Children[No] = new(std::nothrow) Node(DataSetNo, false, CaclulateImpurity(DataSetNo));
		if (!Tree->Children[No])
		{
			std::cerr << "Out of mem!";
			exit(1);
		}	// if
		BuildTree(Tree->Children[No]);
	}	// if
	else
	{
		Tree->Leaf = true;
		Tree->Qst = DTree::Question("No Question, Leaf Node");
	}	// else
}	// BuildTree

inline std::pair<std::string, int> 
DTree::FindTheRightQuestion(const std::vector<std::vector<std::string>> &Set) const noexcept
{
	// Right Question is the one with the lowest impurity, if such question does not exist, we have a leaf.
	std::unordered_map<std::string, std::size_t>             Occ;
	std::vector<std::pair<std::pair<std::string, int>, int>> Impurities;
	//< <"orange", 3>, 2 > that means , orange is the question, with lowest occurrences 3, at position 2(col) on set.

	for (std::size_t j = 1; j < Set[0].size(); ++j)
	{
		for (std::size_t i = 0; i < Set.size(); ++i) Occ[Set[i][j]]++;
		if (Occ.size() > 1)
		{
			auto min = *std::min_element(Occ.begin(), Occ.end(),
				[](const std::pair<std::string, int> op1, const std::pair<std::string, int> op2) -> bool
			{
				return op1.second < op2.second;
			});	// lamda
			Impurities.push_back({ min, j });
		}	// if
		Occ.clear();
	}	// for

	// Impurity == Lowest possible
	if(!Impurities.size())
		return { "", -1 };

	// Impurity != Lowest possible
	auto min_pos = std::min_element(Impurities.begin(), Impurities.end(),
		[](auto op1, auto op2) -> bool
		{
			return op1.first.second < op2.first.second;
		}) - Impurities.begin();	// lamda

		return { Impurities[min_pos].first.first, Impurities[min_pos].second };
}	// FindTheRightQuestion

inline float 
DTree::CaclulateImpurity(const std::vector<std::vector<std::string>> &DataSet) const noexcept
{
	std::set<std::string> Unq;
	for (std::size_t i = 0; i < DataSet.size(); ++i)
		Unq.insert(DataSet[i][0]);

	return (float)(1) - ( (float)(1) / (float)Unq.size() );
}	// CaclulateImpurity

//-------DTree Class, public Section-------//
inline DTree::DTree(const std::vector<std::vector<std::string>> &Set, 
	const std::vector<std::string> &Attrs) noexcept
	: TrainSet(&Set), Root(nullptr), Attributes(Attrs)
{
	if (!Set.size())
	{
		std::cerr << "Empty set!";
		exit(1);
	}	// if

	std::set<int> Check;
	for (std::size_t i = 0; i < Set.size(); ++i)
		Check.insert(Set[i].size());

	if (Check.size() > 1 || *Check.begin() < 2)
	{
		std::cerr << "Wrong set, in terms of size or number of attributes!";
		exit(1);
	}	// if

	if (Attributes.size() != (*TrainSet)[0].size() - 1)
	{
		std::cerr << "Atrributes missmatch";
		exit(1);
	}	// if

	Root = new(std::nothrow) Node(Set, false, CaclulateImpurity(Set));
	if (!Root)
	{
		std::cerr << "Out of memory!";
		exit(1);
	}	// if
}	// Constructor

inline DTree::~DTree() noexcept
{
	Deallocate(Root);
	Root = nullptr;
	TrainSet = nullptr;
}	// Destructor

inline void DTree::BuildTree() noexcept
{
	BuildTree(Root);
}	// Train-Build Model

inline std::vector<std::string> DTree::Predict() const noexcept
{
	Node *Tree = Root;
	std::vector<std::string> Ans;
	char C;

	while (true)
	{
		if (Tree->Qst.Q == "No Question, Leaf Node")
		{
			for (std::size_t i = 0; i < Tree->Data.size(); i++)
				Ans.push_back(Tree->Data[i][Label]);
			return Ans;
		}	// if

		std::cout << Tree->Qst.Q << " (y/n)" << std::endl;
		std::cin >> C;
		if (C == 'y') Tree = Tree->Children[Yes];
		if (C == 'n') Tree = Tree->Children[No];
	}	// while

	return Ans;	// impossible
}	// Question

inline void DTree::PrintModel() const noexcept
{
	PrintModel(Root);
}	// PrintModel
