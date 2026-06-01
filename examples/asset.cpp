#include <finam-api-manager/client.h>

#include <iostream>

int main() {
    std::cout << "It's finam-api-manager!\n";
    FinamSession fns("key");
    std::vector<Exchange> exchanges = fns.asset.Exchanges();
}