#include "RepoAdoptedDogs.h"
#include <fstream>
#include <iostream>
#include "Exception.h"

using namespace std;

void RepoAdoptedDogs::addDog(const string &name, const string &breed, int age, const string &photograph) {
    Dog dog = Dog(breed, name, photograph, age);
    this->vectorWithAdoptedDogs.push_back(dog);
}
std::vector<Dog> RepoAdoptedDogs::getAdoption() {
    return this->vectorWithAdoptedDogs;
}

void RepoAdoptedDogs::addAdoption(const Dog &dog) {
    this->vectorWithAdoptedDogs.push_back(dog);
}

void RepoAdoptedDogsCSV::write() {
    ofstream writeToCSVFile("AdoptedDogs.csv");
    for (auto & i : this->getAdoption()){
        writeToCSVFile << i.getName() << "," << i.getBreed() << "," << i.getAge() << "," << i.getPhotograph() << "\n";
    }
    writeToCSVFile.close();

}

void RepoAdoptedDogsCSV::display() {
    system("start AdoptedDogs.csv");
}

void RepoAdoptedDogsHTML::write() {
    ofstream writeToHTMLFile("AdoptedDogs.html");
    writeToHTMLFile << "<!DOCTYPE html>" << endl;
    writeToHTMLFile << "<html>" << endl;
    writeToHTMLFile << "<head>" << endl;
    writeToHTMLFile << "    <title>Adopted Dogs</title>" << endl;
    writeToHTMLFile << "</head>" << endl;
    writeToHTMLFile << "<body>" << endl;
    writeToHTMLFile << "<table border=\"1\">" << endl;

    writeToHTMLFile << "    <tr>" << endl;
    writeToHTMLFile << "        <td>Name</td>" << endl;
    writeToHTMLFile << "        <td>Breed</td>" << endl;
    writeToHTMLFile << "        <td>Age</td>" << endl;
    writeToHTMLFile << "        <td>Photograph</td>" << endl;
    writeToHTMLFile << "    </tr>" << endl;

    for (auto & i : this->getAdoption()){
        writeToHTMLFile << "    <tr>" << endl;
        writeToHTMLFile << "        <td>"+i.getName()+"</td>" << endl;
        writeToHTMLFile << "        <td>"+i.getBreed()+"</td>" << endl;
        writeToHTMLFile << "        <td>" << i.getAge() << "</td>" << endl;
        writeToHTMLFile << "        <td><img src=\""+i.getPhotograph()+R"(" alt="Image not found"/></td>)" << endl;
        writeToHTMLFile << "    </tr>" << endl;
    }

    writeToHTMLFile << "</table>" << endl;
    writeToHTMLFile << "</body>" << endl;
    writeToHTMLFile << "</html>" << endl;

    writeToHTMLFile.close();
}

void RepoAdoptedDogsHTML::display() {
    system( "start AdoptedDogs.html");
}
