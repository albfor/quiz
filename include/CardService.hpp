#pragma once

#include "nlohmann/json.hpp"
#include <vector>
#include <set>

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
    std::vector<card::card_t> cards;
public:
    CardService(std::string file_name);

    auto get_random_card(const std::vector<card::card_t>& deck) -> card::card_t;
    auto filter_cards_on_topic(std::string topic) -> std::vector<card::card_t>;
    auto get_cards() -> std::vector<card::card_t>;
    auto get_all_topics() -> std::set<std::string>;
};
