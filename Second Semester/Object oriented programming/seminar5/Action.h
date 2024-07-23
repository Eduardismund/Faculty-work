#include "Song.h"
#include <memory>
#include "Repository.h"

#ifndef SEMINAR5_ACTION_H
#define SEMINAR5_ACTION_H


class Action {
public:

    virtual void executeUndo()=0;
    virtual void executeRedo()=0;
};

class ActionAdd: public Action{
private:
    std::unique_ptr<Song> addedSong;
    Repository& repo;
public:
    ActionAdd(std::unique_ptr<Song> addedSong, Repository& repo): addedSong{std::move(addedSong)}, repo{repo} {}
     void executeUndo() override {
        repo.removeSong(*addedSong);
    }
     void executeRedo() override{
         repo.addSong(*addedSong);
    }
};

class ActionRemove: public Action{
private:
    std::unique_ptr<Song> deletedSong;
    Repository& repo;
public:
    ActionRemove(std::unique_ptr<Song> deletedSong, Repository& repo): deletedSong{std::move(deletedSong)}, repo{repo} {}
    void executeUndo() override{
        repo.addSong(*deletedSong);
    }
    void executeRedo() override{
        repo.removeSong(*deletedSong);
    }
};

class ActionUpdate : public Action {
private:
    std::unique_ptr<Song> oldSong;
    std::unique_ptr<Song> newSong;
    Repository& repo;

public:
    ActionUpdate(std::unique_ptr<Song> oldSong, std::unique_ptr<Song> newSong, Repository& repo)
            : oldSong(std::move(oldSong)), newSong(std::move(newSong)), repo(repo) {}

    void executeUndo() override {
        repo.updateSong(*newSong, *oldSong);
    }

    void executeRedo() override {
        repo.updateSong(*oldSong, *newSong);
    }
};
#endif //SEMINAR5_ACTION_H
