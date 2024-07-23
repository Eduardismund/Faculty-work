#include "Service.h"
#include <algorithm>
#include "FilePlaylist.h"
#include "RepositoryExceptions.h"

using namespace std;

void Service::updateSong(const std::string& old_artist, const std::string& old_title,const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{

    Song oldSong = this->repo.findByArtistAndTitle(old_artist, old_title);
    Song newSong{ artist, title, Duration{minutes, seconds}, source };


    std::unique_ptr<Action> updateAction = std::make_unique<ActionUpdate>(std::make_unique<Song>(oldSong),
                                                                          std::make_unique<Song>(newSong),
                                                                          this->repo);

    addActionToUndoStack(std::move(updateAction));


    this->repo.updateSong(oldSong,newSong);
}

void Service::addSongToRepository(const std::string& artist, const std::string& title, double minutes, double seconds, const std::string& source)
{
	Song s{ artist, title, Duration{minutes, seconds}, source };
    this->validator.validate(s);
    std::unique_ptr<Action> addAction = std::make_unique<ActionAdd>(std::make_unique<Song>(s), this->repo);
    addActionToUndoStack(std::move(addAction));
	this->repo.addSong(s);
}

void Service::removeSongFromRepository(const std::string & artist, const std::string & title)
{
	Song s = this->repo.findByArtistAndTitle(artist, title);
    std::unique_ptr<Action> removeAction = std::make_unique<ActionRemove>(std::make_unique<Song>(s), this->repo);
    addActionToUndoStack(std::move(removeAction));
    this->repo.removeSong(s);
}

void Service::addSongToPlaylist(const Song& song)
{
	if (this->playList == nullptr)
		return;
	this->playList->add(song);
}

void Service::addAllSongsByArtistToPlaylist(const std::string& artist)
{
	vector<Song> songs = this->repo.getSongs();
	int nSongs = static_cast<int>(count_if(songs.begin(), songs.end(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		}));

	vector<Song> songsByArtist(nSongs);
	copy_if(songs.begin(), songs.end(), songsByArtist.begin(),
		[artist](const Song& s)
		{
			return s.getArtist() == artist;
		});

	for (auto s : songsByArtist)
		this->playList->add(s);
}

void Service::startPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->play();
}

void Service::nextSongPlaylist()
{
	if (this->playList == nullptr)
		return;
	this->playList->next();
}

void Service::savePlaylist(const std::string& filename)
{
	if (this->playList == nullptr)
		return;

	this->playList->setFilename(filename);
	this->playList->writeToFile();
}

void Service::openPlaylist() const
{
	if (this->playList == nullptr)
		return;

	this->playList->displayPlaylist();
}

void Service::undo()
{
    if (!undoStack.empty()) {

        std::unique_ptr<Action> action = std::move(undoStack.back());
        undoStack.pop_back();

        action->executeUndo();

        redoStack.push_back(std::move(action));
    }
}

void Service::addActionToUndoStack(std::unique_ptr<Action> action)
{

    undoStack.push_back(std::move(action));


    redoStack.clear();
}

void Service::redo()
{
    if (!redoStack.empty()) {

        std::unique_ptr<Action> action = std::move(redoStack.back());
        redoStack.pop_back();

        action->executeRedo();

        undoStack.push_back(std::move(action));
    }
}