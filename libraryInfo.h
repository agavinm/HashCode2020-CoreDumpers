#include <vector>

class libraryInfo {
public:
    libraryInfo() = default;
    ~libraryInfo() = default;

    libraryInfo(int a, int b, int c, int d)
            : nBooks(a), signupTime(b), shipsPerDay(c), ID(d) {
    }

    void addBook(int id)    {
        books.push_back(id);
    }
    int nBooks, signupTime, shipsPerDay, ID;
    std::vector<int> books;
};