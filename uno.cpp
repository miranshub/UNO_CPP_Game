// completely playable UNO game made by Miran
// comments deleted

#include <bits/stdc++.h>
using namespace std;

typedef struct card
{
    bool type;
    int num;
    char color;
} cd;

vector<cd> cards;
vector<int> deck;
vector<vector<int>> players = {{0}, {0}, {0}, {0}};

vector<int> decko_chamber;

int turn = 0;

int debt = 0;
bool rotation = true;
bool skip_player = false;
bool wild_card = false;
bool uno_call = false;
bool games_played = false;
bool game_ended = false;

bool deck_print = false;

void cards_init();
void cards_distribute();


void print_stack_front();
void print_player_cards(int, int);
void print_card(int, bool);
void color_print(char);

bool check_deck(int);
void turn_modify();
void wild_color(int);

void penalty();
void waiting();

void game();
void gameplay();
bool not_game_end();
void game_end();

int main()
{
    system("cls");
    srand(time(0));

    game();

    return 0;
}

void game()
{
    do
    {
        game_ended = false;

        cards_init();
        gameplay();

        string trash;
        cout << "to exit press 'e'\nto play again press any key";
        char ch = 't';
        cin >> ch;
        getline(cin, trash);

        if (ch == 'e')
        {
            break;
        }

    } while (true);

    cout << "\nbye bye, have a good day";
}

void gameplay()
{
    while (not_game_end() && !game_ended)
    {
        uno_call = false;
        bool putting = false;
        wild_card = false;
        int pointer = 0;
        char movement = 'w';
        int count = 0;
        while (movement != 's')
        {
            system("cls");

            print_stack_front();
            print_player_cards(turn, pointer);

            cout << endl
                 << ": ";
            cin >> movement;

            string trash;
            getline(cin, trash);

            switch (movement)
            {
            case 'a':
                if (pointer > 0)
                {
                    pointer--;
                }
                else
                {
                    pointer = players[turn].size() - 1;
                }
                break;
            case 'd':
                if (pointer < players[turn].size() - 1)
                {
                    pointer++;
                }
                else
                {
                    pointer = 0;
                }
                break;
            case 's':
                if (check_deck(pointer))
                {
                    putting = true;
                }
                else if (count < 1)
                {
                    
                    if(!((cards[deck.front()].type == false) && (cards[deck.front()].num == 4)) && !((cards[deck.front()].type == false) && (cards[deck.front()].num == 2))) {
                    // if(!((cards[deck.front()].type == false) && (cards[deck.front()].num == 4))) {
                        cout << "+2/+4\n";
                        // waiting();
                        debt++;
                    }
                    // waiting();
                    penalty();
                    pointer = players[turn].size() - 1;
                    count++;
                    movement = 'w';
                }
                break;
            case 'u':
                uno_call = !uno_call;
                break;
            case 'e':
                game_ended = !game_ended;
                break;
            default:
                break;
            }
        }

        if (!game_ended)
        {
            int card_id = players[turn][pointer];
            if (putting)
            {
                if ((uno_call && players[turn].size() != 2) || (!uno_call && players[turn].size() == 2))
                {
                    debt += 4;
                    penalty();
                }

                if (!cards[card_id].type)
                {
                    switch (cards[card_id].num)
                    {
                    case 0:
                        rotation = !rotation;
                        penalty();
                        break;
                    case 1:
                        skip_player = true;
                        penalty();
                        break;
                    case 2:
                        if (cards[deck.front()].num == 4 && cards[deck.front()].type == false)
                        {
                            penalty();
                        }
                        debt += 2;
                        break;

                    case 4:

                        if (cards[deck.front()].num == 2 && cards[deck.front()].type == false)
                        {
                            penalty();
                        }
                        debt += 4;

                        wild_color(card_id);
                        break;
                    case 5:
                        penalty();
                        wild_color(card_id);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    penalty();
                }

                deck.insert(deck.begin(), card_id);
                players[turn].erase(players[turn].begin() + pointer);
            }

            else
            {
                if (uno_call)
                {
                    debt += 4;
                    penalty();
                }
            }

            if (skip_player)
            {
                turn_modify();
                skip_player = false;
            }

            turn_modify();
        }
    }

    game_end();

    return;
}

bool check_deck(int pointer)
{
    int itr = 0;
    if (cards[players[turn][pointer]].type == false)
    {
        if (cards[players[turn][pointer]].num > 3)
        {
            itr = 1;
            return true;
        }
        else
        {
            itr = 2;
            return (cards[players[turn][pointer]].color == cards[deck.front()].color || cards[players[turn][pointer]].num == cards[deck.front()].num);
        }
    }
    else
    {
        itr = 3;
        if (cards[deck.front()].type == false)
        {
            return (cards[players[turn][pointer]].color == cards[deck.front()].color);
        }
        else
        {
            return ((cards[players[turn][pointer]].color == cards[deck.front()].color) || (cards[players[turn][pointer]].num == cards[deck.front()].num));
        }
    }
}

void turn_modify()
{
    if (rotation)
    {
        turn = ++turn % 4;
    }
    else
    {
        turn = (--turn + 4) % 4;
    }
}

void wild_color(int card_id)
{
    cout << "change color to\n";
    char cholor = 'x';
    while (cholor != 'r' && cholor != 'g' && cholor != 'b' && cholor != 'y')
    {
        string trash;
        cout << ": ";
        cin >> cholor;
        getline(cin, trash);
    }
    cards[card_id].color = cholor;
}

void penalty()
{
    while (debt--)
    {
        players[turn].push_back(deck.back());
        deck.pop_back();
    }
    debt = 0;
}

void cards_init()
{
    if (!games_played)
    {
        cards.clear();
        string colors = "rgby";
        int id_number = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 1; j < 20; j++)
            {
                cd *card_x = new cd;
                card_x->type = true;
                card_x->num = j / 2;
                card_x->color = colors[i];

                cards.push_back(*card_x);
            }

            for (int j = 0; j < 6; j++)
            {
                cd *card_x = new cd;
                card_x->type = false;
                card_x->num = j / 2;
                card_x->color = colors[i];

                cards.push_back(*card_x);
            }
        }

        for (int i = 0; i < 8; i++)
        {
            cd *card_x = new cd;
            card_x->type = false;
            card_x->num = (i / 4) + 4;
            card_x->color = colors[0];

            cards.push_back(*card_x);
        }
    }

    cards_distribute();

    while (!cards[deck[0]].type)
    {
        deck.push_back(deck.front());
        deck.erase(deck.begin());
    }

    return;
}

void waiting()
{
    string trash;
    getline(cin, trash);
}

void cards_distribute()
{
    vector<int> arr, arr2;
    for (int i = 0; i < 108; i++)
    {
        arr.push_back(i);
    }

    for (int i = 0; i < 108; i++)
    {
        int idx = rand() % (108 - i);
        arr2.push_back(arr[idx]);
        arr.erase(arr.begin() + idx);
    }
    for (int i = 0; i < 108; i++)
    {
        int idx = rand() % (108 - i);
        arr.push_back(arr2[idx]);
        arr2.erase(arr2.begin() + idx);
    }

    deck.clear();

    for (int i = 0; i < 108; i++)
    {
        int idx = rand() % (108 - i);
        deck.push_back(arr[idx]);
        arr.erase(arr.begin() + idx);
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            players[j].push_back(deck.back());
            deck.pop_back();
        }
    }
    for (int i = 0; i < 4; i++)
    {
        players[i].erase(players[i].begin());
    }
    return;
}

bool not_game_end()
{
    return (players[0].size() && players[1].size() && players[2].size() && players[3].size());
}

void game_end()
{
    game_ended = true;
    games_played = true;
    system("cls");
    int idx = 0;
    bool found_winner = false;
    for (auto player : players)
    {
        idx++;
        if (player.size() == 0)
        {
            cout << "player " << idx << " s winner" << endl;
            found_winner = true;
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        players[i].clear();
    }
    vector<vector<int>> temp_init_arr = {{0}, {0}, {0}, {0}};

    players = temp_init_arr;

    if (!found_winner)
    {
        cout << "no winner..." << endl;
    }
}

void print_stack_front()
{
    deck_print = true;
    cout << "stack: \t";
    print_card(deck.front(), true);
    cout << endl
         << "\t";
    print_card(deck.front(), false);
    cout << "\t\tsizes: " << players[0].size() << " " << players[1].size() << " " << players[2].size() << " " << players[3].size();
    cout << endl;
    cout << "\t\t\t\t       ";
    for (int i = 0; i < turn; i++)
    {
        cout << "  ";
    }

    if (uno_call || game_ended)
    {
        if (uno_call)
        {
            cout << "\bUNO";
        }
        else
        {
            cout << "X";
        }
    }
    else
    {
        cout << "_";
    }

    cout << endl;
    deck_print = false;
}

void print_player_cards(int player, int pointer)
{
    cout << "player " << player + 1 << ": " << players[player].size() << endl;
    for (int card_number : players[player])
    {
        print_card(card_number, true);
    }
    cout << endl;
    for (int card_number : players[player])
    {
        print_card(card_number, false);
    }
    cout << endl;

    for (int i = 0; i < pointer; i++)
    {
        cout << "  \t";
    }
    cout << "-----" << endl;
    return;
}

void print_card(int id, bool line)
{

    if (line)
    {
        if (cards[id].type)
        {
            cout << cards[id].num << "\t";
        }
        else
        {
            switch (cards[id].num)
            {
            case 0:
                cout << "rev\t";
                break;
            case 1:
                cout << "skip\t";
                break;
            case 2:
                cout << "pick2\t";
                break;

            case 4:
                cout << "wild4\t";
                break;
            case 5:
                cout << "wild\t";
                break;

            default:
                break;
            }
        }

        if (deck_print)
        {
            cout << "\t\tdebt: " << debt << "\trotation: " << rotation;
        }
    }

    else if (cards[id].type || (!cards[id].type && (cards[id].num == 0 || cards[id].num == 1 || cards[id].num == 2) || deck_print))
    {
        cout << cards[id].color << "\t";
    }

    else
    {
        cout << "\t";
    }
}

// after everything debugged, I found one bug, +4 Color, if not present color bro had to pick 5 cards proly //bug fixed
// confusion: suppose +2 on deck // reviewed and fixed, just need confirmation