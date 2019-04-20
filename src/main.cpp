/***************************************************************************
 * Copyright 2019 HYUNWOO O
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************/

#include <iostream>

#include "tableIndexer.hpp"
#include "tableSearcher.hpp"

#define MAX_QUERY_SIZE 1000

int main() {
    HashMap hashMap;
    
    TableIndexer tableIndexer;
    tableIndexer.createIndex("../resources/amazon_jobs.csv", hashMap);
    
    TableSearcher tableSearcher;
    
    while (true) {
        std::cout << "Input queries: (type 'exitsearch' to exit) ";
        
        char temp[MAX_QUERY_SIZE];
        std::cin.getline(temp, MAX_QUERY_SIZE, '\n');
        std::string searchQuery(temp);
        
        if (searchQuery == "exitsearch") {
            std::cout << "\n>>>>> Shut down search engine...\n";
            break;
        }
        
        tableSearcher.search(searchQuery, hashMap);
    }
    
    return 0;
}
