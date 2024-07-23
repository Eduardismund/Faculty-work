#include "RepoShelterDogs.h"
#include "Exception.h"


using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
    auto* records = static_cast<Records*>(p_data);
    try {
        records->emplace_back(p_fields, p_fields + num_fields);
    }
    catch (...) {

        return 1;
    }
    return 0;
}


Records select_stmt(sqlite3 *db, const char* stmt)
{
    Records records;
    char *errmsg;
    int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
    if (ret != SQLITE_OK) {
        std::string stmt_str(stmt);
        std::string errmsg_str(errmsg);
        std::string error_msg = "Error in select statement " + stmt_str + "[" + errmsg_str + "]\n";
        throw Exception(error_msg);
        //std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
    }
    else {
        // std::cerr << records.size() << " records returned.\n";
    }
    return records;
}

DBRepository::DBRepository() {
    int errorCode = sqlite3_open("ShelterDogs5.db", &this->databaseWithDogs);

    if (errorCode != SQLITE_OK)
        throw Exception("Could not open database");

    std::string createTableStatement = "CREATE TABLE IF NOT EXISTS Dogs (Name TEXT PRIMARY KEY, Breed TEXT, Age INTEGER, Photograph TEXT);";
    if(sqlite3_exec(this->databaseWithDogs, createTableStatement.c_str(),nullptr, nullptr,nullptr)!=SQLITE_OK)
        throw Exception("\nError: Could not create SQL table.\n");
}

DBRepository::~DBRepository() {
    sqlite3_close(this->databaseWithDogs);
}


void DBRepository::addDog(const Dog &dog)
{
    std::string insertStatement = "INSERT INTO Dogs VALUES ('" + dog.getName() + "', '" + dog.getBreed() + "', " + std::to_string(dog.getAge())+ ", '" + dog.getPhotograph() + "');";
    if(sqlite3_exec(this->databaseWithDogs, insertStatement.c_str(),nullptr, nullptr,nullptr)!=SQLITE_OK)
        throw Exception("\nError: Could not add. Dog Already in there!\n");
}

void DBRepository::deleteDog(const std::string &name)
{
    Dog dog=this->getDogByName(name);
    std::string deleteStatement = "DELETE FROM Dogs WHERE Name = '" + dog.getName() +"';";
    if(sqlite3_exec(this->databaseWithDogs, deleteStatement.c_str(),nullptr, nullptr,nullptr)!=SQLITE_OK)
        throw Exception("\nError: Could not delete. Dog doesn't exist!\n");
}

void DBRepository::updateDog(const Dog &dog)
{
    Dog d=this->getDogByName(dog.getName());
    std::string updateStatement = "UPDATE Dogs SET Name = '" + dog.getName() + "', Breed = '" + dog.getBreed() + "', Age = " + std::to_string(dog.getAge()) + ", Photograph = '" + dog.getPhotograph() + "' WHERE Name = '" + d.getName() +"' AND Breed = '" + d.getBreed() + "' AND Age = " + std::to_string(d.getAge()) + " AND Photograph = '" +d.getPhotograph()+"';";
    if(sqlite3_exec(this->databaseWithDogs, updateStatement.c_str(),nullptr, nullptr,nullptr)!=SQLITE_OK)
        throw Exception("\nError: Could not update. Dog doesn't exist!\n");
}


std::vector<Dog> DBRepository::getDogs() const {
    std::vector<Dog> all_dogs;
    Dog d;
    std::string name, breed, link;
    int age;
    Records res = select_stmt(this->databaseWithDogs, "SELECT * FROM Dogs;");
    for (auto &record: res) {
        name = record[0];
        breed = record[1];
        age = std::stoi(record[2]);
        link = record[3];
        d = Dog{breed, name, link, age};
        all_dogs.push_back(d);
    }
    return all_dogs;
}

int DBRepository::getDogPositionByName(const std::string &name) {
    std::string name_from_db;
    int i=0;
    Records res = select_stmt(this->databaseWithDogs, "SELECT * FROM Dogs;");
    for (auto &record: res) {
        name_from_db = record[0];
        if(name==name_from_db)
            return i;
        i++;
    }
    return -1;
}

int DBRepository::getDogPosition(const Dog &dog) {
    Dog d;
    std::string name, breed, link;
    int age;
    int i=0;
    Records res = select_stmt(this->databaseWithDogs, "SELECT * FROM Dogs;");
    for (auto &record: res) {
        name = record[0];
        breed = record[1];
        age = std::stoi(record[2]);
        link = record[3];
        d = Dog{breed, name, link, age};
        if(dog==d)
            return i;
        i++;
    }
    return -1;
}

Dog DBRepository::getDogByName(const std::string &name) {
    Dog d;
    std::string db_name, breed, link;
    int age;
    Records res = select_stmt(this->databaseWithDogs, "SELECT * FROM Dogs;");
    for (auto &record: res) {
        db_name = record[0];
        if(db_name==name) {
            breed = record[1];
            age = std::stoi(record[2]);
            link = record[3];
            d = Dog{breed, name, link, age};
            return d;
        }
    }
    return {};
}