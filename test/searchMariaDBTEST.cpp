#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "mysql_connection.h"

#include "../src/indexer.hpp"

/**
 * Deprecated
 */

void searchMariaDBTest() {
    sql::Driver    * driver = nullptr;
    sql::Connection* conn   = nullptr;
    sql::Statement * stmt   = nullptr;
    sql::ResultSet * result = nullptr;
    
    try {
        driver = get_driver_instance();
        conn   = driver->connect("tcp://127.0.0.1:3306", "root", "");
        conn->setSchema("stackoverflow");
        
        stmt   = conn->createStatement();
        result = stmt->executeQuery("SELECT * FROM answers;");
        
        while (result->next()) {
            std::cout << "ID: " << result->getInt("ID");
            std::cout << ", Body: '" << result->getString("Body") << "'\n\n";
        }
        
    } catch (const sql::SQLException& e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
        std::cout << "# ERR: " << e.what();
        std::cout << " (MariaDB error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << "\n";
    }
    
    delete result;
    delete stmt;
    delete conn;
}
