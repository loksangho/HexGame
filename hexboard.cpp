#include "hexboard.h"
#include <iostream>
#include <random>
#include <chrono>

// Gets the colour of the node 'x' on the board
Colour HexBoard::get_colour(int x){
    return board_graph->get_node_value(x);
}

Colour HexBoard::get_colour_trial(int x) {
    return trial_nodes[x];
}

// Attempts to make move if legal, also increments num of moves made
int HexBoard::make_move(int i, int j, Colour c) {
    if(is_legal(i,j,c)) {
        place_colour(i,j,c);
        return ++num_of_moves_made;
    }
    return num_of_moves_made;

}

void HexBoard::reset_game() {
    num_of_moves_made=0;
    delete board_graph;
    board_graph= new Graph(length);
}


int HexBoard::get_length() { return length;}

// Make node QVector for trialing Monte Carlo
void HexBoard::make_trial_node_vec() {
    trial_nodes = QVector<Colour>();
    for(Colour node : board_graph->get_node_values()) {
        trial_nodes.push_back(node);
    }
}

int HexBoard::convert_location_to_index(int i, int j) {
    return j*length + i;
}

QPair<int,int> HexBoard::convert_index_to_location(int x, int length) {
    return qMakePair(x%length, x/length);
}

// Converts colour to status of game
QString HexBoard::winner_string(Colour winner) {
    switch(winner) {
        case Colour::BLUE:
            return "Blue Wins";
        case Colour::RED:
            return "Red Wins";
        case Colour::EMPTY:
            return "Still Playing";
        default:
            return "ERROR string";
    }
    return "";
}


int HexBoard::best_move_AI(Colour AI_colour, int num_of_MC_trials) {

    QVector<double> probability_of_winning;
    for(int j=0; j < length; j++) {
        for(int k=0; k< length; k++) {
            double cur_prob = 0.0;
            int cur_sum = 0;
            if(is_legal(k,j,AI_colour)) {
                //If legal, then test this move using Monte Carlo
                for(int n=0; n< num_of_MC_trials; n++) {
                    make_trial_node_vec();
                    trial_nodes[convert_location_to_index(k,j)] = AI_colour;
                    int remaining_nodes_size = length*length-num_of_moves_made-1;
                    QVector<Colour> remaining_nodes;
                    for(int i=0; i< remaining_nodes_size; i++) {
                        if(i%2 == 0) { // fill BLUE first because if size of QVector is odd then it's always BLUE's turn (BLUE starts)
                            remaining_nodes.push_back(Colour::BLUE);
                        }
                        else {
                            remaining_nodes.push_back(Colour::RED);
                        }
                    }

                    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

                    shuffle (remaining_nodes.begin(), remaining_nodes.end(), std::default_random_engine(seed));


                    for(int m=0; m< trial_nodes.size(); m++) {
                        if(trial_nodes[m] == Colour::EMPTY) {
                            trial_nodes[m] = remaining_nodes.back();
                            remaining_nodes.pop_back();
                        }
                    }

                    if(has_winner(true) == AI_colour) {
                        cur_sum++;
                    }
                }
            }
            else {
                cur_sum = -1;
            }
            cur_prob = (1.0*cur_sum)/num_of_MC_trials;
            probability_of_winning.push_back(cur_prob);
        }
    }
    return std::max_element(probability_of_winning.begin(), probability_of_winning.end()) - probability_of_winning.begin();

}

void HexBoard::insert_unique(QVector<int>& vec, int x) {
    if(std::find(vec.begin(), vec.end(), x) == vec.end()) {
        vec.push_back(x);
    }
}

bool HexBoard::contains(QVector<int>vec, int x) {
    return std::find(vec.begin(), vec.end(), x) != vec.end();
}

QVector<Node>::iterator HexBoard::contains_id(QVector<Node>& vec, int x) {
    return std::find_if(vec.begin(), vec.end(), [x](Node& n){
        return n.get_id() == x;
    });

/*    for(auto it=vec.begin(); it!=vec.end(); it++) {
        if((*it).get_id() == x) {
            return it;
        }
    }
    return vec.end();
*/
}


QVector<Node>::iterator HexBoard::contains_value(QVector<Node>& vec, int val) {
    return std::find_if(vec.begin(), vec.end(), [val](Node& n){
        return n.get_value() == val;
    });
/*    for(auto it=vec.begin(); it!=vec.end(); it++) {
        if((*it).get_value() == val) {
            return it;
        }
    }
    return vec.end();
*/
}

void HexBoard::check_node(QVector<Node>& unvisited,int x){
    auto contains_id_index = contains_id(unvisited, x);
    if(get_colour_trial(x) == Colour::BLUE && contains_id_index != unvisited.end())
        (*contains_id_index).set_value(1);
}

// When board is full, check if path for BLUE exists. If not, RED path exists.
bool HexBoard::check_blue_path_exists_trial(int node ) {
    Colour c = Colour::BLUE;
    //PriorityQueue unvisited;
    QVector<Node> unvisited;
    QVector<int> visited;
    for(int i=0; i< length*length; i++) {
        if(i!=node && get_colour_trial(i) == c) {
            unvisited.push_back(Node(i,2));
        }
    }

    Node cur_node= Node(node,1);
    int x = cur_node.get_id();
    while(!(is_right_boundary(x) || is_top_obtuse_corner(x) || is_bottom_acute_corner(x)) && unvisited.size() != 0 && cur_node.get_value() != 2) {
        visited.push_back(x);

        if(is_left_boundary(x)) {
            check_node(unvisited, x-length);
            check_node(unvisited, x+length);
            check_node(unvisited, x+1);
            check_node(unvisited, x-length+1);
        }
        else if(is_top_acute_corner(x)){
            check_node(unvisited, x+length);
            check_node(unvisited, x+1);
        }
        else if(is_bottom_obtuse_corner(x)) {
            check_node(unvisited, x-length);
            check_node(unvisited, x+1);
            check_node(unvisited, x-length+1);
        }
        else if(is_top_boundary(x)) {
            check_node(unvisited, x+1);
            check_node(unvisited, x-1);
            check_node(unvisited, x+length);
            check_node(unvisited, x+length-1);
        }
        else if(is_bottom_boundary(x)) {
            check_node(unvisited, x+1);
            check_node(unvisited, x-1);
            check_node(unvisited, x-length);
            check_node(unvisited, x-length+1);
        }
        else if(is_middle(x)) {
            check_node(unvisited, x+1);
            check_node(unvisited, x-1);
            check_node(unvisited, x-length);
            check_node(unvisited, x-length+1);
            check_node(unvisited, x+length);
            check_node(unvisited, x+length-1);
        }

        auto priority_1_node = contains_value(unvisited,1);
        if(priority_1_node != unvisited.end()) {
            cur_node = *priority_1_node;
            unvisited.erase(priority_1_node);
            x=cur_node.get_id();
        }
        else {
            break;
        }
    }
    if ((is_right_boundary(x) || is_top_obtuse_corner(x) || is_bottom_acute_corner(x))) return true;
    else return false;
}


// (Inefficient) Recursive method to determine whether there is a winner or not
void HexBoard::check_adjacent(int x, Colour c, QVector<int> visited, bool& winner, bool trial) {
    if(c == Colour::BLUE) {
        if(is_right_boundary(x) || is_top_obtuse_corner(x) || is_bottom_acute_corner(x)) {
            winner = true;
            //return true;
            return;
        };
        QVector<int> nodes_to_check; // these are the neighbouring nodes to check for adjacency
        if(is_left_boundary(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-length+1);
        }
        else if(is_top_acute_corner(x)){
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+1);
        }
        else if(is_bottom_obtuse_corner(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-length+1);
        }
        else if(is_top_boundary(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+length-1);
        }
        else if(is_bottom_boundary(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x-length+1);
        }
        else if(is_middle(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x-length+1);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+length-1);
        }
        visited.push_back(x);
        for(int cur_node: nodes_to_check) {
            Colour cur_colour = trial?get_colour_trial(cur_node):get_colour(cur_node);
            if(!contains(visited,cur_node) && cur_colour == Colour::BLUE) {
                visited.push_back(cur_node);
                check_adjacent(cur_node,c,visited,winner, trial);
                if(winner) return;
            }
        }

        return;
    }
    else if(c == Colour::RED) {
        if(is_bottom_boundary(x) || is_bottom_obtuse_corner(x) || is_bottom_acute_corner(x)) {
            winner = true;
            return;
        };
        QVector<int> nodes_to_check;
        if(is_left_boundary(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-length+1);
        }
        if(is_right_boundary(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x+length-1);
        }
        else if(is_top_acute_corner(x)){
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+1);
        }
        else if(is_top_obtuse_corner(x)){
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x+length-1);
        }
        else if(is_top_boundary(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+length-1);
        }
        else if(is_middle(x)) {
            //nodes_to_check.erase(nodes_to_check.begin(), nodes_to_check.end());
            nodes_to_check.push_back(x+1);
            nodes_to_check.push_back(x-1);
            nodes_to_check.push_back(x-length);
            nodes_to_check.push_back(x-length+1);
            nodes_to_check.push_back(x+length);
            nodes_to_check.push_back(x+length-1);
        }
        visited.push_back(x);
        for(int cur_node: nodes_to_check) {
            Colour cur_colour = trial?get_colour_trial(cur_node):get_colour(cur_node);
            if(!contains(visited,cur_node) && cur_colour == Colour::RED) {
                visited.push_back(cur_node);
                check_adjacent(cur_node,c,visited,winner,trial);
                if(winner) return;
            }
        }

        return;
    }
    return;
}

// Determines if there is a winner, returns EMPTY if there is none
Colour HexBoard::has_winner(bool trial=false) {

    if(trial) {

        for(int i=0; i< length; i++) {
            int x = i*length;
            Colour colour_x = trial?get_colour_trial(x):get_colour(x);
            if(colour_x == Colour::BLUE) {
                if(check_blue_path_exists_trial(x)) {
                    return Colour::BLUE;
                }
            }
        }
        return Colour::RED;
    }

    //Check BLUE first
    for(int i=0; i< length; i++) {
        int x = i*length;
        bool winner = false;
        QVector<int> visited;
        Colour colour_x = trial?get_colour_trial(x):get_colour(x);
        if(colour_x == Colour::BLUE) {
            check_adjacent(x, Colour::BLUE, visited, winner, trial);
            if(winner) {
                return Colour::BLUE;
            }
        }
    }

    //Check RED
    for(int i=0; i< length; i++) {
        int x = i;
        bool winner = false;
        QVector<int> visited;
        Colour colour_x = trial?get_colour_trial(x):get_colour(x);
        //std::cout << colour_x << std::endl;
        if(colour_x == Colour::RED) {
            //std::cout << "HERE" << std::endl;
            check_adjacent(x, Colour::RED, visited, winner, trial);
            if(winner) {
                return Colour::RED;
            }
        }
    }
    return Colour::EMPTY;

}



bool HexBoard::on_valid_boundary(int i, int j, Colour c) {
    assert(c == Colour::RED || c== Colour::BLUE);
    int x = j*length + i;
    // X (Blue) should be left-right boundaries, O (Red) should be top-bottom boundaries
    if(c == Colour::BLUE) {
        return is_left_boundary(x) || is_right_boundary(x) || is_top_acute_corner(x) || is_top_obtuse_corner(x) || is_bottom_acute_corner(x) || is_bottom_obtuse_corner(x);
    }
    else if(c== Colour::RED) {
        return is_top_boundary(x) || is_bottom_boundary(x) || is_top_acute_corner(x) || is_top_obtuse_corner(x) || is_bottom_acute_corner(x) || is_bottom_obtuse_corner(x);
    }
    else {
        std::cout << "ERROR: wrong colour" << std::endl;
        return false;
    }
}

// Determines if the placement of colour 'C' at (i,j) is next to the colour 'other'
bool HexBoard::is_next_to(int i, int j, Colour c, Colour other) {
    assert(c == Colour::RED || c == Colour::BLUE);
    assert(other == Colour::RED || other == Colour::BLUE);
    int x = j*length + i;
    if(is_top_acute_corner(x)) {
        return get_colour(x+1)==other || get_colour(x+length) == other;
    }
    else if(is_top_obtuse_corner(x)) {
        return get_colour(x-1) == other || get_colour(x+length) == other || get_colour(x+length-1) == other;
    }
    else if(is_bottom_acute_corner(x)) {
        return get_colour(x-length) == other || get_colour(x-1) == other;
    }
    else if(is_bottom_obtuse_corner(x)) {
        return get_colour(x-length) == other || get_colour(x-length+1) == other || get_colour(x+1)==other;
    }
    else if(is_top_boundary(x)) {
        return get_colour(x-1) == other || get_colour(x+1) == other || get_colour(x+length) == other || get_colour(x+length-1) == other;
    }
    else if(is_bottom_boundary(x)) {
        return get_colour(x-1) == other || get_colour(x+1) == other || get_colour(x-length) == other || get_colour(x-length+1) == other;
    }
    else if(is_left_boundary(x)) {
        return get_colour(x-length) == other || get_colour(x+length) == other || get_colour(x-length+1) == other || get_colour(x+1) == other;
    }
    else if(is_right_boundary(x)) {
        return get_colour(x-length) == other || get_colour(x+length) == other || get_colour(x+length-1) == other || get_colour(x-1) == other;
    }
    else if(is_middle(x)) {
        return get_colour(x+1) == other || get_colour(x-1) == other || get_colour(x+length) == other || get_colour(x-length) == other || get_colour(x-length+1) == other || get_colour(x+length-1) == other;
    }
    else {
        std::cout << "ERROR: node does not belong anywhere" << std::endl;
        return false;
    }
}


// Determines if move is legal or not. It is legal if: the cells is empty; it is used to continue an existing chain; it is used to block the opponent's chain; or it is on a valid boundary
bool HexBoard::is_legal(int i, int j, Colour c) {
    assert(c == Colour::RED || c == Colour::BLUE);
    bool is_legal = false;
    if(board_graph->get_node_value(j*length+i) == Colour::EMPTY) { // Old code: && (is_next_to(i,j,c, c==Colour::RED?Colour::BLUE:Colour::RED) || (is_next_to(i,j,c, c)) || on_valid_boundary(i,j,c))
        is_legal = true;
    }
    return is_legal;

}

// place colour on location (i,j)
void HexBoard::place_colour(int i, int j, Colour c) {
    board_graph->set_colour(j*length+i,c);
}

// Determines if node x is in top left corner (acute angle)
bool HexBoard::is_top_acute_corner(int x) {
    return x==0;
}

// Determines if node x is in top right corner (obtuse angle)
bool HexBoard::is_top_obtuse_corner(int x) {
    int length = board_graph->get_length();
    return (x==length-1);
}

// Determines if node x is in bottom right corner (acute angle)
bool HexBoard::is_bottom_acute_corner(int x) {
    int length = board_graph->get_length();
    return x == (length*length)-1;
}

// Determines if node x is in bottom left corner (obtuse angle)
bool HexBoard::is_bottom_obtuse_corner(int x) {
    int length = board_graph->get_length();
    return (x == length*length-length);
}

// Determines if node x is in the top boundary (non-corners)
bool HexBoard::is_top_boundary(int x) {
    int length = board_graph->get_length();

    return (x> 0 && x < length-1);
}

// Determines if node x is in the bottom boundary (non-corners)
bool HexBoard::is_bottom_boundary(int x) {
    int length = board_graph->get_length();
    return (x > length*length-length && x < length*length-1);
}

// Determines if node x is in the left boundary (non-corners)
bool HexBoard::is_left_boundary(int x) {
    int length = board_graph->get_length();
    return (x%length==0 && !is_top_acute_corner(x) && !is_bottom_obtuse_corner(x));
}

// Determines if node x is in the right boundary (non-corners)
bool HexBoard::is_right_boundary(int x) {
    int length = board_graph->get_length();
    return (x%length==length-1 && !is_top_obtuse_corner(x) && !is_bottom_acute_corner(x));
}

// Determines if node x is in the middle
bool HexBoard::is_middle(int x) {
    return !is_top_obtuse_corner(x) && !is_top_acute_corner(x) && !is_bottom_acute_corner(x) && !is_bottom_obtuse_corner(x) && !is_top_boundary(x) && !is_bottom_boundary(x) && !is_left_boundary(x) && !is_right_boundary(x);
}

HexBoard::~HexBoard() {
    if(board_graph) {
        delete board_graph;
    }
}

// Constructor for HexBoard
HexBoard::HexBoard(int length) : length(length) {

    board_graph = new Graph(length);

    board_graph->initialise_length(length);

    for(int x=0; x < board_graph->get_length()*board_graph->get_length(); x++) { // Constructs appropriate edges depending on location of node x
        if(is_top_acute_corner(x)) {
            board_graph->add_edge(0,1);
            board_graph->add_edge(0,length);
        }
        else if(is_top_boundary(x)) {
            board_graph->add_edge(x, x-1);
            board_graph->add_edge(x, x+1);
            board_graph->add_edge(x, x+length-1);
            board_graph->add_edge(x, x+length);
        }
        else if(is_top_obtuse_corner(x)) {
            board_graph->add_edge(x, x-1);
            board_graph->add_edge(x, x+length-1);
            board_graph->add_edge(x, x+length);
        }
        else if(is_left_boundary(x)) {
            board_graph->add_edge(x, x-length);
            board_graph->add_edge(x, x+length);
            board_graph->add_edge(x, x+1);
            board_graph->add_edge(x, x-length+1);
        }
        else if(is_right_boundary(x)) {
            board_graph->add_edge(x, x-length);
            board_graph->add_edge(x, x+length);
            board_graph->add_edge(x, x-1);
            board_graph->add_edge(x, x+length-1);
        }
        else if(is_bottom_obtuse_corner(x)) {
            board_graph->add_edge(x, x-length);
            board_graph->add_edge(x, x-length+1);
            board_graph->add_edge(x, x+1);
        }
        else if(is_bottom_boundary(x)) {
            board_graph->add_edge(x, x-1);
            board_graph->add_edge(x, x+1);
            board_graph->add_edge(x, x-length);
            board_graph->add_edge(x, x-length+1);
        }
        else if(is_bottom_acute_corner(x)) {
            board_graph->add_edge(x, x-1);
            board_graph->add_edge(x, x-length);
        }
        else if(is_middle(x)) {
            board_graph->add_edge(x, x-1);
            board_graph->add_edge(x, x+1);
            board_graph->add_edge(x, x-length);
            board_graph->add_edge(x, x-length+1);
            board_graph->add_edge(x, x+length);
            board_graph->add_edge(x, x+length-1);
        }
        else {
            // should not be here
            std::cout << "ERROR: node does not belong anywhere" << std::endl;
        }

    }

    //this->board_graph = graph;
    //delete graph;

}

// Prints the colour to the ostream
std::ostream& operator<<(std::ostream& os, Colour c) {
    if(c == Colour::BLUE) {
        os << "X";
    }
    else if(c == Colour::RED) {
        os << "O";
    }
    else if(c== Colour::EMPTY) {
        os << ".";
    }
    return os;
}


// Prints the HEX board to the ostream
std::ostream& operator<<(std::ostream& os, HexBoard& board) {
    Graph* board_graph = board.board_graph;
    int length = board_graph->get_length();
    QVector<Colour> nodes = board_graph->get_node_values();
    for(int k=0;  k< nodes.size(); k++) {
        os << nodes[k] << " ";
        if (k%length !=length-1) { //not last element of the row, draw edge to the right of this node
            bool has_edge = board_graph->adjacent(k,k+1);
            if(has_edge) {
                os << "-" << " ";
            }
            else {
                os << "~" << " "; // error: no connection
            }
        }
        else { // last element of the row, add new line, then add edge-only row
            os << std::endl;
            if(k!=length*length-1) {
                for(int m=0; m<(k/length)*2+1;m++) { // add appropriate number of spaces to beginning of line
                    os << " ";
                }
                for (int n=0; n< length*2; n++) { // iterate over size to produce the edge-only rows
                    if(board_graph->adjacent(k-length+1+n/2, k+1+n/2)) {
                        if( n % 2 == 0) { //alternate between \ and /
                            os << "\\" << " ";
                        }
                        else {
                            if(n!=length*2-1) {
                                os << "/" << " ";
                            }
                        }
                    }
                    else {
                        if(n!=length*2-1) {
                            os << "{" << " "; // error: no connection
                        }
                    }
                }
                os << std::endl;
                for(int m=0; m<(k/length)+1;m++) { // add appropriate number of spaces to beginning of line
                    os << "  ";
                }
            }
        }

    }

    return os;
}

