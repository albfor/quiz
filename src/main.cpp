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
        set<string> topics = cs.get_all_topics();
        crow::mustache::context topic_ctx;

        string content = "<h1>Topics</h1>";
        for (const string& t : topics)
        {
            crow::mustache::context ctx;
            ctx["topic"] = t;
            content += crow::mustache::load("topic.html").render_string(ctx);
        }

        crow::mustache::context base_ctx;
        base_ctx["content"] = content;
        return crow::mustache::load("index.html").render(base_ctx);
    });

    CROW_ROUTE(app, "/<string>/card")([&cs](string topic){
        if (topic.find("%20") != string::npos)
        {
            topic.replace(topic.find("%20"), 3, " ");
        }
        cout << topic << endl;
        auto card = cs.get_random_card(cs.filter_cards_on_topic(topic));
        auto content_ctx = load_card_context(card);
        return crow::mustache::load("card.html").render(content_ctx);
    });

    app.port(18080).multithreaded().run();

    return 0;
}
