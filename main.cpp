#include <iostream>
#include <memory>
#include <vector>

#include "DisabledSeat.hpp"
#include "StandardSeat.hpp"
#include "VIPSeat.hpp"

int main() {
    using Seats = std::vector<std::shared_ptr<Seat>>;
    Seats vec{std::make_shared<StandardSeat>(123, false),
              std::make_shared<VIPSeat>(345, true),
              std::make_shared<DisabledSeat>(678, false)};

    for (const auto& seat : vec) {
        std::cout << "Seat " << seat->getID() << " Type: " << seat->getSymbol() << '\n';
    }

    return 0;
}