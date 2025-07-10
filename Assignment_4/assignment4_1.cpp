#include <iostream>
#include<iomanip>

#define NOT_LOGIN -1

/*define the rank of user*/
typedef enum  {
	Begineer,
	Professional,
	Expert
}Rank;

/*define the match result*/
typedef enum {
	Lose,
	Win
}MatchResult;

/*define the user class*/
class User_Prof {
private:
	std::string name_;
	int loginTimes_;
	int playedMatches_;
	int wonMatches_;
	double wonRatio_;
	Rank rank_;
	bool loggedIn_;
public:
	User_Prof() : name_("guest"), loginTimes_(1), playedMatches_(0), wonMatches_(0), wonRatio_(0.0), rank_(Begineer), loggedIn_(false) {}
	User_Prof(std::string name) : name_(name), loginTimes_(1), playedMatches_(0), wonMatches_(0), wonRatio_(0.0), rank_(Begineer), loggedIn_(false) {}
	void login();
	void logout();
	bool testEquivalence(const User_Prof* other)const;
	bool testNotEquivalence(const User_Prof* other)const;
	void printUserInfo();
	void updateMatchResults(User_Prof& other,bool win);
};

/*
 * Function name	: login
 * Function			: the function to login the user
 * Input parameters	: void
 * Return value		: void
 */
void User_Prof::login() {
	if (loggedIn_) {
		std::cerr << "Error: the user has logged!" << std::endl;
		exit(NOT_LOGIN);
	}
	loggedIn_ = true;
	loginTimes_++;
	std::cout << name_ << " logged in. Login times: " << loginTimes_ << std::endl;
}

/*
 * Function name	: logout
 * Function			: the function to logout the user
 * Input parameters	: void
 * Return value		: void
 */
void User_Prof::logout() {
	if (!this->loggedIn_) {
		std::cerr << "Error: the user has not logged!" << std::endl;
		exit(NOT_LOGIN);
	}
	loggedIn_ = false;
	std::cout << name_ << " logged out." << std::endl;
}

/*
 * Function name	: testEquivalence
 * Function			: the function to test if two users are equivalent
 * Input parameters	: const User_Prof* other
 * Return value		: true / false
 */
bool User_Prof::testEquivalence(const User_Prof* other)const {
	if (!this->loggedIn_) {
		std::cerr << "Error: the user has not logged!" << std::endl;
		exit(NOT_LOGIN);
	}
	return this == other;
}


/*
 * Function name	: testNotEquivalence
 * Function			: the function to test if two users are not equivalent
 * Input parameters	: const User_Prof* other	
 * Return value		: true / false
 */
bool User_Prof::testNotEquivalence(const User_Prof* other)const {
	if (!this->loggedIn_) {
		std::cerr << "Error: the user has not logged!" << std::endl;
		exit(NOT_LOGIN);
	}
	return !testEquivalence(other);
}

/*
 * Function name	: printUserInfo
 * Function			: the function to print the user information
 * Input parameters	: void
 * Return value		: void
 */
void User_Prof::printUserInfo() {
	if (!this->loggedIn_) {
		std::cerr << "Error: the user has not logged!" << std::endl;
		exit(NOT_LOGIN);
	}
	std::cout << ">>> Name: " << name_ << std::endl
		<< "	Rank: " << rank_ << std::endl
		<< "	Login Times: " << loginTimes_ << std::endl
		<< "	Played Matches: " << playedMatches_ << std::endl
		<< "	Won Matches: " << wonMatches_ << std::endl
		<< "	Won Ratio: " << std::fixed << std::setprecision(2) << wonRatio_ * 100 << "%" << std::endl << std::endl;
}

/*
 * Function name	: updateMatchResults
 * Function			: the function to update the match results
 * Input parameters	: User_Prof& other, bool win
 * Return value		: void
 */
void User_Prof::updateMatchResults(User_Prof& other,bool win){
	playedMatches_++;
	other.playedMatches_++;
	if (win)
		wonMatches_++;
	else
		other.wonMatches_++;
	wonRatio_ = static_cast<double>(wonMatches_) / playedMatches_;
	other.wonRatio_ = static_cast<double>(other.wonMatches_) / other.playedMatches_;
}

/*
 * Function name	: main
 * Function			: the main function
 * Input parameters	: void
 * Return value		: 0
 */
int main() {
	/*create two users and update their match results*/
	User_Prof user1("ycc"), user2;
	user1.login();
	user2.login();
	user1.updateMatchResults(user2, Win);

	/*print the user information*/
	user1.printUserInfo();
	user2.printUserInfo();

	/*test the equivalence of two users*/
	User_Prof user3;
	if (user2.testEquivalence(&user3)) {
		std::cout << "Users are equivalent." << std::endl;
	}
	else {
		std::cout << "Users are not equivalent." << std::endl;
	}

	User_Prof* user4 = &user1;
	if (user1.testEquivalence(user4)) {
		std::cout << "Users are equivalent." << std::endl;
	}
	else {
		std::cout << "Users are not equivalent." << std::endl;
	}
	return 0;
};
