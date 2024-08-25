#include "CardService.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

CardService::CardService(std::string& file_name)
{
    std::srand(std::time(nullptr));
    json data;
    std::ifstream is(file_name);

    if (!is.is_open())
    {
        std::cerr << "Failed to open file: " << file_name << "\n";
    }
    else
    {
        is >> data;
        for (const auto& c : data["cards"])
        {
            cards.push_back(c);
        }
    }
}

auto CardService::get_random_card(const std::vector<card::card_t>& deck) -> card::card_t
{
    return deck.at(std::rand() % deck.size());
}

auto CardService::filter_cards_on_topic(std::string& topic) -> std::vector<card::card_t>
{
    std::vector<card::card_t> on_topic;
    std::copy_if(cards.begin(), cards.end(), std::back_inserter(on_topic),
         [&topic](card::card_t c) {
            return c.topic == topic;
         });
    return on_topic;
}

void card::to_json(json& j, const card_t& c)
{
    j = json{{"topic", c.topic}, {"question", c.question}, {"answer", c.answer}};
}

void card::from_json(const json& j, card_t& c)
{
    j.at("topic").get_to(c.topic);
    j.at("question").get_to(c.question);
    j.at("answer").get_to(c.answer);
}
