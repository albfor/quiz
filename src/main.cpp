#include <crow/app.h>
#include <crow/mustache.h>
#include <cstdlib>
#include <ctime>
#include <crow.h>

#include "CardService.hpp"

using namespace std;

crow::mustache::context load_card_context(card::card_t& card)
{
    crow::mustache::context card_ctx;
    card_ctx["topic"] = card.topic;
    card_ctx["question"] = card.question;
    card_ctx["answer"] = card.answer;
    return card_ctx;
}

int main() {
    crow::SimpleApp app;
    CardService cs(string(ASSETS_DIR) + "/cards.json");

    CROW_ROUTE(app, "/")([&cs](){
        auto card = cs.get_random_card();
        auto content_ctx = load_card_context(card);
        auto content = crow::mustache::load("card.html").render_string(content_ctx);
        crow::mustache::context base_ctx;
        base_ctx["content"] = content;
        return crow::mustache::load("index.html").render(base_ctx);
    });

    CROW_ROUTE(app, "/science")([&cs](){
        auto cards = cs.filter_cards_on_topic("Science");
        auto card = cs.get_random_card(cards);
        auto content_ctx = load_card_context(card);
        auto content = crow::mustache::load("card.html").render_string(content_ctx);
        crow::mustache::context base_ctx;
        base_ctx["content"] = content;
        return crow::mustache::load("index.html").render(base_ctx);
    });


    app.port(18080).multithreaded().run();

    return 0;
}
