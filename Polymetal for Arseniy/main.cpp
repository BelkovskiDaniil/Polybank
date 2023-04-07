#include <iostream>
#include "sqlite-amalgamation-3410200/sqlite3.h"


int main() {
    char * err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("person.db", &db);

    int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS person("
                              "person_id INT PRIMARY KEY,"
                              " first_name varchar(100),"
                              " second_name varchar(100),"
                              " passport INT, address varchar(100),"
                              " verification INT);"
                              NULL, NULL, &err)

    if (rc != SQLITE_OK) {
        std::cout << "BD error" << err;
    }

    for (int i = 0; i < 10; i++) {
        std::string query = "insert into algolancer VALUES ("+std::to_string(i)+", "+std::to_string(i + 5)+", 'Arsenyi have sex with Polymetal');";
        std::cout << query << "\n";
        rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);

        if (rc != SQLITE_OK) {
            std::cout << "Fuck u asshole" << err;
        }
    }

    /*std::cout << "Hello, World!" << std::endl;*/
    return 0;
}
