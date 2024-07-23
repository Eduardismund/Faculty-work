#pragma once
#include "Idea.h"
#include "Researcher.h"
#include <vector>
#include <algorithm>

class Controller
{
private:
	std::vector<Idea> ideas;
	std::vector<Researcher> researchers;
public:
	Controller() : ideas(), researchers() 
	{
		readIdeas();
		readResearchers();
	}

	std::vector<Idea> getIdeas()
    { std::vector<Idea> all = this->ideas;
        std::sort(all.begin(), all.end(), [](Idea a, Idea b){
            return a.getDuration() < b.getDuration();
        });
    return all; }
	std::vector<Researcher> getResearchers() { return researchers; }

	void addIdea(Idea& idea);
	void acceptIdea(int indexOfIdea);

	void readIdeas();
	void readResearchers();

	void writeIdeas();
};

