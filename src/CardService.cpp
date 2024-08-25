#include "CardService.hpp"
#include <cstdlib>
#include <ctime>

CardService::CardService(std::string file_name)
{
    std::srand(std::time(nullptr));
    inja::json data;
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

void card::to_json(inja::json& j, const card_t& c)
{
    j = inja::json{{"topic", c.topic}, {"question", c.question}, {"answer", c.answer}};
}

void card::from_json(const inja::json& j, card_t& c)
{
    j.at("topic").get_to(c.topic);
    j.at("question").get_to(c.question);
    j.at("answer").get_to(c.answer);
}
