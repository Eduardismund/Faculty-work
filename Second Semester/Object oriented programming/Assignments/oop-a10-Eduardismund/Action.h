#include "Dog.h"
#pragma once
#include <memory>
#include "RepoShelterDogs.h"


class Action {
public:

    virtual void executeUndo()=0;
    virtual void executeRedo()=0;
};

class ActionAdd: public Action{
private:
    std::unique_ptr<Dog> addedDog;
    RepoShelterDogs* repo;
public:
    ActionAdd(std::unique_ptr<Dog> addedDog, RepoShelterDogs *repo): addedDog{std::move(addedDog)}, repo{repo} {}
     void executeUndo() override {
        Dog dog=*addedDog;
        repo->deleteDog(dog.getName());
    }
     void executeRedo() override{
         repo->addDog(*addedDog);
    }
};

class ActionRemove: public Action{
private:
    std::unique_ptr<Dog> deletedDog;
    RepoShelterDogs* repo;
public:
    ActionRemove(std::unique_ptr<Dog> deletedDog, RepoShelterDogs* repo): deletedDog{std::move(deletedDog)}, repo{repo} {}
    void executeUndo() override{
        repo->addDog(*deletedDog);
    }
    void executeRedo() override{
        Dog dog=*deletedDog;
        repo->deleteDog(dog.getName());
    }
};

class ActionUpdate : public Action {
private:
    std::unique_ptr<Dog> oldDog;
    std::unique_ptr<Dog> newDog;
    RepoShelterDogs* repo;

public:
    ActionUpdate(std::unique_ptr<Dog> oldDog, std::unique_ptr<Dog> newDog, RepoShelterDogs* repo)
            : oldDog(std::move(oldDog)), newDog(std::move(newDog)), repo(repo) {}

    void executeUndo() override {
        repo->updateDog(*oldDog);
    }

    void executeRedo() override {
        repo->updateDog(*newDog);
    }
};