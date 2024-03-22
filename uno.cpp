//completely playable UNO game made by Miran
//checking "git push origin main" // attempt 1 failed

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
vector<int> decko_chamber;
vector<vector<int>> players = {{0}, {0}, {0}, {0}};

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

bool not_game_end();

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
            // cout << "\n\n\n"; //this line was added for debugging process

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
                    // cout << "\t\t\t3" << endl; //this line was added for debugging process
                    debt++;
                    penalty();
                    pointer = players[turn].size() - 1;
                    count++;
                    movement = 'w';
                }
                break;
            // cout << "\t\t\t4" << endl; //this line was added for debugging process
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
    // return (cards[players[turn][pointer]].color == cards[deck.front()].color ||  cards[players[turn][pointer]].num == cards[deck.front()].num || (!(cards[players[turn][pointer]].type) && (cards[players[turn][pointer]].num  > 3)));

    // if (!cards[players[turn][pointer]].type && cards[players[turn][pointer]].num > 3)
    // {
    //     return true;
    // }

    // return ((cards[players[turn][pointer]].color == cards[deck.front()].color) || (cards[players[turn][pointer]].num == cards[deck.front()].num));
    int itr = 0;
    // cout << "\t\t\t\t pointer: " << pointer << endl; //this line was added for debugging process
    // cout << "\t\t\t\t turn: " << turn << endl; //this line was added for debugging process
    // cout << "\t\t\t\t players[turn][pointer]: " << players[turn][pointer] << endl; //this line was added for debugging process
    // cout << "\t\t\t\t cards[players[turn][pointer]].type: " << cards[players[turn][pointer]].type << endl; //this line was added for debugging process
    if (cards[players[turn][pointer]].type == false)
    {
        if (cards[players[turn][pointer]].num > 3)
        {
            // cout << "\t\t\t\t cards[players[turn][pointer]].type: false__" << endl; //this line was added for debugging process
            itr = 1;
            // cout << "\t\t\tcond: " << itr << endl; //this line was added for debugging process
            return true;
        }
        else
        {
            // cout << "\t\t\t\t cards[players[turn][pointerd]].type: false__" << endl; //this line was added for debugging process
            itr = 2;
            // cout << "\t\t\tcocnd" << itr << endl; //this line was added for debugging process
            return (cards[players[turn][pointer]].color == cards[deck.front()].color || cards[players[turn][pointer]].num == cards[deck.front()].num);
        }
    }
    else
    {
        itr = 3;
        // cout << "\t\t\tcocnd" << itr << endl; //this line was added for debugging process
        if (cards[deck.front()].type == false)
        {
            return (cards[players[turn][pointer]].color == cards[deck.front()].color);
        }
        else
        {
            return ((cards[players[turn][pointer]].color == cards[deck.front()].color) || (cards[players[turn][pointer]].num == cards[deck.front()].num));
        }
        // if()
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
    // cout << endl;
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
        else {
            cout << "_";

        }
        
        
    // }

    cout << endl;
    deck_print = false;
}

void print_player_cards(int player, int pointer)
{
    // int index = 0;
    // for (auto player_tbp : players)
    // {
    // cout << "player " << index << ": " << players[index].size() << endl;
    cout << "player " << player + 1 << ": " << players[player].size() << endl;
    // for (int card_number : player)
    for (int card_number : players[player])
    {
        print_card(card_number, true);
    }
    cout << endl;
    // for (int card_number : player)
    for (int card_number : players[player])
    {
        print_card(card_number, false);
    }
    cout << endl;

    // if (index == player)
    // {

    // cout << "xx";
    for (int i = 0; i < pointer; i++)
    {
        cout << "  \t";
    }
    cout << "-----" << endl;
    // }
    // cout << endl;
    // index++;
    // }
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
                // reverse
                cout << "rev\t";
                break;
            case 1:
                // skip
                cout << "skip\t";
                break;
            case 2:
                // pick 2
                cout << "pick2\t";
                break;

            case 4:
                // wild +pick 4
                cout << "wild4\t";
                break;
            case 5:
                // wild
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

    // if (cards[id].type)
    // {
    //     cout << cards[id].num;
    //     color_print(cards[id].color);
    // }

    // else
    // {
    //     if (cards[id].num == 4)
    //     {
    //         cout << "wild pick +4";
    //     }

    //     else if (cards[id].num == 5)
    //     {
    //         cout << "wild";
    //     }

    //     else
    //     {
    //         switch (cards[id].num)
    //         {
    //         case 0:
    //             cout << "reverse";
    //             break;
    //         case 1:
    //             cout << "skip";
    //             break;
    //         case 2:
    //             cout << "pick +2";
    //             break;

    //         default:
    //             break;
    //         }
    //         color_print(cards[id].color);
    //     }
    // }
    // cout << "\n";
}

// error debugged
/*
skip: before putting card into stack the turn value is changed henceskip card never poped from the players[turn][pointer]

//error to be debug : debugged
/*
2 for +2d
0 can be putted on reverse, reverse card has number 0 but type 0
5 can be putted on wild
and somewhere debt issue

//debugged
*/