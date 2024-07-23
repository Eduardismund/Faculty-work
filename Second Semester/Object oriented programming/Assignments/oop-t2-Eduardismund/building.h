#include <string>

class Building{
protected:
    std::string address;
    int constructionYear;
public:
    explicit Building(std::string address="", int constructionYear=0): address{std::move(address)}, constructionYear{constructionYear} {};
    virtual ~Building()=default;
    virtual bool mustBeRestored() {return false;};
    virtual bool canBeDemolished() {return false;};
    virtual std::string toString();
    int getYear() const{return this->constructionYear;};

};

class Block: public Building{
private:
    int totalApartments;
    int occupiedApartments;
public:
    explicit Block(std::string address="", int constructionYear=0, int totalApartments=0, int occupiedApartments=0): Building{std::move(address), constructionYear}, totalApartments{totalApartments}, occupiedApartments{occupiedApartments} {};
    bool mustBeRestored() override;
    bool canBeDemolished() override;
    std::string toString() override;
};

