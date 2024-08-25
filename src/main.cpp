#include <crow/app.h>
#include <crow/mustache.h>
#include <cstdlib>
#include <ctime>
#include <crow.h>

#include "CardService.hpp"

using namespace std;

int main() {
    crow::SimpleApp app;
    CardService cs(string(ASSETS_DIR) + "/cards.json");

    CROW_ROUTE(app, "/")([&cs](){
        auto card = cs.get_random_card();

        crow::mustache::context content_ctx;
        content_ctx["topic"] = card.topic;
        content_ctx["question"] = card.question;
        content_ctx["answer"] = card.answer;

        auto content = crow::mustache::load("card.html").render_string(content_ctx);

        crow::mustache::context base_ctx;
        base_ctx["content"] = content;

        return crow::mustache::load("index.html").render(base_ctx);
    });

    CROW_ROUTE(app, "/science")([&cs](){
        auto cards = cs.get_cards_on_topic("Science");
        auto card = cs.get_random_card(cards);

        crow::mustache::context content_ctx;
        content_ctx["topic"] = card.topic;
        content_ctx["question"] = card.question;
        content_ctx["answer"] = card.answer;

        auto content = crow::mustache::load("card.html").render_string(content_ctx);

        crow::mustache::context base_ctx;
        base_ctx["content"] = content;

        return crow::mustache::load("index.html").render(base_ctx);
    });


    app.port(18080).multithreaded().run();

    return 0;
}
