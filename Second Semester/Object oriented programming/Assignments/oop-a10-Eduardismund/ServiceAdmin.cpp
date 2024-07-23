#include "ServiceAdmin.h"
#include "Exception.h"
#include <utility>
using namespace std;

AdminService::AdminService(RepoShelterDogs *adminRepoDogs, std::string shelterFile_): adminRepo(adminRepoDogs), shelterFile(std::move(shelterFile_)){

}

AdminService::~AdminService() = default;

void AdminService::addDog(const Dog &dog) {
    // validate the dog before adding it - see if the dog already exists
    if (ServiceValidator::validateDogExists(this->adminRepo->getDogs(), dog.getName())) {
        throw ServiceException(
                "A dog with this name already exists and cannot be added! (consider adding a number at the end of the name)");
    }

    std::unique_ptr<Action> addAction = std::make_unique<ActionAdd>(std::make_unique<Dog>(dog), this->adminRepo);
    addActionToUndoStack(std::move(addAction));
    // then simply add the dog
    this->adminRepo->addDog(dog);

}

void AdminService::addDog(const std::string &breed, const std::string &name, const std::string &photograph, int age) {
    if(this->getDogPositionByName(name) != -1)
        throw Exception("A dog with the same name already exists. try another one!");
    Dog dog=Dog(breed, name,photograph, age);
    std::unique_ptr<Action> addAction = std::make_unique<ActionAdd>(std::make_unique<Dog>(dog), this->adminRepo);
    addActionToUndoStack(std::move(addAction));
    this->adminRepo->addDog(dog);

}

void AdminService::deleteDog(const std::string &name) {
    if(this->getDogPositionByName(name) == -1)
        throw Exception("A dog with that name does not exist. try another one!");
    Dog dog=adminRepo->getDogByName(name);
    std::unique_ptr<Action> removeAction = std::make_unique<ActionRemove>(std::make_unique<Dog>(dog), this->adminRepo);
    addActionToUndoStack(std::move(removeAction));
    this->adminRepo->deleteDog(name);

}

void AdminService::updateDog(const std::string &name, const std::string &newBreed, const std::string &newPhotograph,
                             int newAge) {
    if(this->getDogPositionByName(name) == -1)
        throw Exception("A dog with that name does not exist. try another one!");
    Dog oldDog=this->adminRepo->getDogByName(name);
    Dog newDog=Dog(newBreed, name,newPhotograph, newAge);
    std::unique_ptr<Action> updateAction = std::make_unique<ActionUpdate>(std::make_unique<Dog>(oldDog),
                                                                          std::make_unique<Dog>(newDog),
                                                                          this->adminRepo);

    addActionToUndoStack(std::move(updateAction));
    this->adminRepo->updateDog(newDog);

}

std::vector<Dog> AdminService::getDogs() const {
    return this->adminRepo->getDogs();
}

int AdminService::getDogPositionByName(const std::string &name) {
    return this->adminRepo->getDogPositionByName(name);
}

int AdminService::getDogPosition(const Dog &dog) {
    return this->adminRepo->getDogPosition(dog);
}

Dog AdminService::getDogByName(const std::string &name) {
    int position = this->getDogPositionByName(name);
    if(position == -1)
        throw Exception("The dog does not exist!");
    else
        return this->adminRepo->getDogs()[position];
}

bool ServiceValidator::validateDogExists(const vector<Dog> &dogs, const string &name) {
    for (const auto &dog: dogs) {
        if (dog.getName() == name) {
            return true;
        }
    }
    return false;
}

void AdminService::undo()
{
    if (!undoStack.empty()) {

        std::unique_ptr<Action> action = std::move(undoStack.back());
        undoStack.pop_back();

        action->executeUndo();

        redoStack.push_back(std::move(action));
    }
    else
        throw Exception("No more undo's!");
}

void AdminService::addActionToUndoStack(std::unique_ptr<Action> action)
{

    undoStack.push_back(std::move(action));


    redoStack.clear();
}

void AdminService::redo()
{
    if (!redoStack.empty()) {

        std::unique_ptr<Action> action = std::move(redoStack.back());
        redoStack.pop_back();

        action->executeRedo();

        undoStack.push_back(std::move(action));
    }
    else
        throw Exception("No more redo's!");
}