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
        auto page = crow::mustache::load("card.html");
        crow::mustache::context ctx;
        ctx["topic"] = card.topic;
        ctx["question"] = card.question;
        ctx["answer"] = card.answer;
        return page.render(ctx);
    });

    app.port(18080).multithreaded().run();

    return 0;
}
