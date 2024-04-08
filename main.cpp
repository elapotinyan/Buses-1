#include "newCity.h"
#include <iostream>
#include <string>
#include <limits.h>

const int inf = INT_MAX;

int main() {
    int n, m;
    std::cin >> n >> m;
    newCity city(n);
    std::vector<std::vector<int>> graph(n, std::vector<int>(n, inf));
    for (int i = 0; i < m; ++i) {
        city.constructStreet();
    }

    int busID = 0;
    while (true) {
        std::string operation;
        std::cin >> operation;
        if (operation == "add_bus") {
            city.addBus();
            busID++;
        }  else if (operation == "construct_street") { 
            city.constructStreet();
        }
        else if (operation == "detail") {
            city.detail();
        } else if (operation == "end") {
            break;
        }
    }
    return 0;
}
