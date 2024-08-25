#include <cstdlib>
#include <ctime>
#include <iostream>

#include "CardService.hpp"
#include "inja.hpp"

using namespace std;
using namespace inja;

int main() {
    CardService cs(string(ASSETS_DIR) + "/cards.json");
    json card = cs.get_random_card();

    Environment env;
    Template temp = env.parse_template(string(TEMPLATES_DIR) + "/card.html");

    env.render_to(cout, temp, card);

    return 0;
}
