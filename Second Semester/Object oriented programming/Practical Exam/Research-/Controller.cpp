#include "Controller.h"
#include <fstream>

void Controller::addIdea(Idea& idea)
{
	if (idea.getDuration() > 4 || idea.getDuration() < 0)
		throw std::runtime_error("Invalid duration!");
	if(idea.getTitle() == "" || idea.getDescription() == "")
		throw std::runtime_error("Invalid title or description!");
	this->ideas.push_back(idea);
}

void Controller::acceptIdea(int indexOfIdea)
{
    std::vector<Researcher> allResearchers=this->researchers;
    std::vector<Idea>allIdeas=this->ideas;
    std::string status="accepted";
    if(indexOfIdea <=-1 or indexOfIdea >= ideas.size())
        throw std::runtime_error("The given index is not valid!");
//    if(ideas[indexOfIdea].getStatus() == status)
//        throw std::runtime_error("The idea has already been accepted!");
    ideas[indexOfIdea].accept();
//    ideas[indexOfIdea].status="accepted";
}

void Controller::readIdeas()
{
	std::ifstream inputFile{ "ideas.txt" };
	Idea idea;
	while(inputFile >> idea)
		ideas.push_back(idea);
	inputFile.close();
}

void Controller::readResearchers()
{
	std::ifstream inputFile{ "researchers.txt" };
	Researcher researcher;
	while(inputFile >> researcher)
		researchers.push_back(researcher);
	inputFile.close();
}

void Controller::writeIdeas()
{
	std::ofstream outputFile{ "ideas.txt" };
	if(!outputFile.is_open())
		throw std::runtime_error("File could not be opened!");
	for(auto idea : ideas)
		outputFile << idea.toString() << std::endl;
	outputFile.close();
}
