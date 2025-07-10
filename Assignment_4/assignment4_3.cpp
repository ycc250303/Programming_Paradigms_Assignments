#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

/*define a traveler class*/
class Traveler {
private:
    std::string name;
public:
    /*default constructor*/
    Traveler(const std::string& name) : name(name) {}

    /*copy constructor*/
    Traveler(const Traveler& other) : name(other.name) {}

    /*define the assignment operator*/
    Traveler& operator=(const Traveler& other) {
        if (this != &other) {
            name = other.name;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Traveler& traveler) {
        os << "Name: " << traveler.name << std::endl;
        return os;
    }
};

/*define a pager class*/
class Pager {
private:
    std::string number;
public:
    Pager(const std::string& number) : number(number) {}

    Pager(const Pager& other) : number(other.number) {}

    /*define the assignment operator*/
    Pager& operator=(const Pager& other) {
        if (this != &other) {
            number = other.number;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pager& pager) {
        os << "Pager Number: " << pager.number << std::endl;
        return os;
    }
};

/*define a business traveler class*/
class BusinessTraveler : public Traveler {
private:
    Pager pager;
public:
    BusinessTraveler() : Traveler(""), pager("") {}

    BusinessTraveler(const std::string& name, const std::string& pagerNumber)
        : Traveler(name), pager(pagerNumber) {}

    BusinessTraveler(const BusinessTraveler& other)
        : Traveler(other), pager(other.pager) {}

    /*define the assignment operator*/
    BusinessTraveler& operator=(const BusinessTraveler& other) {
        if (this != &other) {
            Traveler::operator=(other);
            pager = other.pager;
        }
        return *this;
    }

    /*define the output operator*/
    friend std::ostream& operator<<(std::ostream& os, const BusinessTraveler& businessTraveler) {
        os << "Business Traveler: " << std::endl;
        os << businessTraveler.pager << std::endl;
        return os;
    }
};

int main() {
    BusinessTraveler bt1("2351279", "ycc");
    BusinessTraveler bt2 = bt1; // Calls copy constructor
    BusinessTraveler bt3;
    bt3 = bt1;  // Calls assignment operator

    std::cout << bt1 << std::endl;
    std::cout << bt2 << std::endl;
    std::cout << bt3 << std::endl;

    return 0;
}