#include <iostream>
#include <memory>

#include "StandardSeat.hpp"

int main() {
    std::shared_ptr<Seat> seat = std::make_shared<StandardSeat>(123, false);
    std::cout << std::boolalpha << seat->isTaken() << '\n';
    std::cout << seat->getID() << '\n';

    return 0;
}
