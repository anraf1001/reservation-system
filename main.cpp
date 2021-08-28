#include <iostream>
#include <memory>
#include <vector>

#include "DisabledSeat.hpp"
#include "Person.hpp"
#include "StandardSeat.hpp"
#include "VIPSeat.hpp"

int main() {
    using Seats = std::vector<std::shared_ptr<Seat>>;
    Seats vec{std::make_shared<StandardSeat>(123),
              std::make_shared<VIPSeat>(345),
              std::make_shared<DisabledSeat>(678)};

    for (const auto& seat : vec) {
        std::cout << "Seat " << seat->getID() << " Type: " << seat->getSymbol() << " Price: " << seat->getPrice() << '\n';
    }
    for (const auto& seat : vec) {
        std::cout << *seat << ' ';
    }
    std::cout << '\n';

    Person person{"Jan", "Kowalski", "123456789", "email@email.com", "20271854937"};
    std::cout << person.getAge() << '\n';

    vec[1]->take(std::make_shared<Person>("Jan", "Kowalski", "123456789", "email@email.com", "20271854937"));
    for (const auto& seat : vec) {
        std::cout << *seat << ' ';
    }
    std::cout << '\n';

    return 0;
}
