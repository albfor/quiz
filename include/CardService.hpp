#pragma once

#include "nlohmann/json.hpp"
#include <vector>

using json = nlohmann::json;

namespace card {
struct card_t {
    std::string topic;
    std::string question;
    std::string answer;
};

void to_json(json& j, const card_t& c);
void from_json(const json& j, card_t& c);
}

class CardService {
    std::vector<json> cards;
public:
    CardService(std::string file_name);
    card::card_t get_random_card() {return cards.at(std::rand() % cards.size()); }
};
