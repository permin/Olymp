#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {o << "[";O__(o, v);o << "]";return o;}

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

const int UNDEFINED = 1 << 30;

class NamedHashPrivider {
public:
    static NamedHashPrivider& instance() {
        static NamedHashPrivider instance_;
        return instance_;
    }
    ll hash(int x, int y) {
        if (data_[x][y])
            return data_[x][y];
        return data_[x][y] = std::uniform_int_distribution<unsigned long long> (0, numeric_limits<unsigned long long>::max())(randomGenerator_);
    }
private:
    NamedHashPrivider() {
        data_.assign(8, vector<ll>(8, 0));
    }
    NamedHashPrivider(const NamedHashPrivider&);
    NamedHashPrivider& operator=(const NamedHashPrivider&);

    vector<vector<ll>> data_;
    std::default_random_engine randomGenerator_;
};

class Position{
public:
    Position():
        x_(UNDEFINED), y_(UNDEFINED) {}
    Position(int x, int y):
        x_(x), y_(y) {}
    int x() const {
        return x_;
    }
    int y() const {
        return y_;
    }
    void setX(int x) {
        x_ = x;
    }
    void setY(int y) {
        y_ = y;
    }
    ll hash() const {
        if (x() == UNDEFINED || y() == UNDEFINED)
            return 0;
        return NamedHashPrivider::instance().hash(x_, y_);
    }
    bool operator<(const Position& pos) const {
        return x() == pos.x() ?
                    y() < pos.y():
                    x() < pos.x();
    }
    bool operator == (const Position& pos) const {
        if (hash() == pos.hash())
            return x() == pos.x() && y() == pos.y();
        return false;
    }
    string debugString() const {
        stringstream o;
        o << "Position (" << x_ << ", " << y_ << ")";
        return o.str();
    }
private:
    int x_, y_;
};

Position checkerMove(const Position& checker, const Position& enemy) {
    return Position(2 * enemy.x() - checker.x(),
                    2 * enemy.y() - checker.y());
}

vector<Position> neighbours(const Position& p) {
    static int dx[] = {-1,+1,0,0};
    static int dy[] = {0,0,-1,+1};
    vector<Position> res(4);
    for (int d = 0; d < 4; ++d)
        res[d] = Position(p.x() + dx[d], p.y() + dy[d]);
    return res;
}

bool defined(const Position& position) {
    return position.x() != UNDEFINED && position.y() != UNDEFINED;
}

class ContainerPositions {
public:
    static ContainerPositions makeContainerPositions(const vector<string>& plan) {
        vector<Position> pos;
        for (int i = 0; i < plan.size(); ++i)
            for (int j = 0; j < plan.size(); ++j)
                if (plan[i][j] == '$' || plan[i][j] == '*') {
                    pos.push_back(Position(i, j));
                }
        return ContainerPositions(pos);
    }
    explicit ContainerPositions(const vector<Position>& positions):
        positions_(positions) {calcHash(); calcField();}
    ll hash() const {
        return hash_;
    }
    const Position& position(int i) const {
        return positions_[i];
    }
    void setPosition(int i, const Position& pos) {
        hash_ ^= positions_[i].hash();
        field_ ^= 1LL << index(positions_[i]);
        positions_[i] = pos;
        field_ ^= 1LL << index(positions_[i]);
        hash_ ^= positions_[i].hash();
    }
    vector<Position>::const_iterator begin() const {
        return positions_.begin();
    }
    size_t indexOf(const Position& pos) const {
        for (size_t i = 0; i < positions_.size(); ++i)
            if (positions_[i] == pos)
                return i;
        return UNDEFINED;
    }
    vector<Position>::const_iterator end() const {
        return positions_.end();
    }
    int x(int i) const {
        return positions_[i].x();
    }
    int y(int i) const {
        return positions_[i].y();
    }
    void set(int i, int x) {
        hash_ ^= positions_[i].hash();
        field_ ^= 1LL << index(positions_[i]);
        positions_[i].setX(x);
        field_ ^= 1LL << index(positions_[i]);
        hash_ ^= positions_[i].hash();
    }
    void setY(int i, int y) {
        hash_ ^= positions_[i].hash();
        field_ ^= 1LL << index(positions_[i]);
        positions_[i].setY(y);
        field_ ^= 1LL << index(positions_[i]);
        hash_ ^= positions_[i].hash();
    }
    bool operator == (const ContainerPositions& containerPositions) const {
        if (hash() == containerPositions.hash())
            return positions_ == containerPositions.positions_;
        return false;
    }
    bool isOccupied(const Position& p) const {
        return field_ & (1LL << index(p));
    }
    string debugString() const {
        stringstream o;
        o << "ContainerPositions {" << positions_.size() << ", [";
        bool f = 1;
        for (auto x: positions_) {
            if (!f)
                o << ", ";
            o << x.debugString();
            f = 0;
        }
        o << "] (hash = " << hash() << ")}";
        return o.str();
    }
private:
    static int index(const Position& p) {
        return p.x() * 8 + p.y();
    }
    void calcHash() {
        hash_ = 0;
        for (int i = 0; i < positions_.size(); ++i) {
            hash_ ^= positions_[i].hash();
        }
    }
    void calcField() {
        for (const auto& p: positions_) {
            field_ ^= 1LL << index(p);
        }
    }
    vector<Position> positions_;
    ll field_;
    ll hash_;
};

typedef Position PlayerPosition;
PlayerPosition makePlayerPosition(const vector<string>& plan) {
    for (int i = 0; i < plan.size(); ++i)
        for (int j = 0; j < plan.size(); ++j)
            if (plan[i][j] == '@' || plan[i][j] == '+')
                return Position(i, j);
    return Position();
}

bool defined(const ContainerPositions& containerPositions) {
    for (const auto& x: containerPositions) {
        if (!defined(x))
            return false;
    }
    return true;
    // return all_of(all(containerPositions), defined);
}

class Board {
public:
    enum Type{FLOOR, MARKED, WALL};
    static Board makeBoard(const vector<string>& plan) {
        Board b;
        b.board_.assign(plan.size(), vector<Type>(plan[0].size()));
        for (size_t i = 0; i < plan.size(); ++i)
            for (int j = 0; j < plan.size(); ++j) {
                char ch = plan[i][j];
                if (ch == '.' || ch == '+' || ch == '*') {
                    b.board_[i][j] = MARKED;
                } else if (ch == '#') {
                    b.board_[i][j] = WALL;
                } else {
                    b.board_[i][j] = FLOOR;
                }
            }
        return b;
    }
    size_t height() const {
        return board_.size();
    }
    size_t width() const {
        return board_.back().size();
    }
    Type get(int x, int y) const {
        return board_[x][y];
    }
private:
    vector<vector<Type>> board_;
};

bool canBeOccupied(const Position& pos, const Board& board) {
    return board.get(pos.x(), pos.y()) != Board::WALL;
}

bool inHalfInterval(int x, int a, int b) {
    return a <= x && x < b;
}

bool inside(const Position& pos, const Board& board) {
    return defined(pos) && inHalfInterval(pos.x(), 0, board.height()) &&
                           inHalfInterval(pos.y(), 0, board.width());
}

class State {
public:
    State(const Board& board,
          const PlayerPosition& playerPosition,
          const ContainerPositions& containerPositions):
        board_(board),
        playerPosition_(playerPosition),
        containerPositions_(containerPositions) {}

    const Board& board() const {
        return board_;
    }
    const PlayerPosition& playerPosition() const {
        return playerPosition_;
    }
    const ContainerPositions& containerPositions() const {
        return containerPositions_;
    }
    ll hash() const {
        return playerPosition_.hash() + containerPositions_.hash();
    }
private:
    const Board& board_;
    PlayerPosition playerPosition_;
    ContainerPositions containerPositions_;
};

bool areAllDifferent(vector<Position> pos) {
    sort(all(pos));
    return unique(all(pos)) == pos.end();
}

bool areAllDifferent(vector<Position> pos, const PlayerPosition& plpos) {
    return areAllDifferent(pos) && none_of(all(pos), [&](const Position& p) {
                return p == plpos;
            });
}

bool areAllDifferent(const ContainerPositions& containerPositions, const PlayerPosition& plpos) {
    vector<Position> pos(all(containerPositions));
    return areAllDifferent(pos, plpos);
}

bool isConsistent(const State& state) {
    return all_of(all(state.containerPositions()), [&state](const Position& pos) {return canBeOccupied(pos, state.board());}) &&
           areAllDifferent(state.containerPositions(), state.playerPosition());
}

std::vector<State> getTransitions(const State& state) {
    vector<State> res;
    res.reserve(4);
    for (const auto& nexPlayerPosition: neighbours(state.playerPosition())) {
        if (canBeOccupied(nexPlayerPosition, state.board())) {
            res.push_back(State(state.board(), nexPlayerPosition, state.containerPositions()));
        } else {
            if (state.containerPositions().isOccupied(nexPlayerPosition)) {
                const Position& nextPosition = checkerMove(state.playerPosition(), nexPlayerPosition);
                if (!state.containerPositions().isOccupied(nextPosition) &&
                        canBeOccupied(nextPosition, state.board())) {
                    size_t i = state.containerPositions().indexOf(nexPlayerPosition);
                    assert(i != UNDEFINED);
                    ContainerPositions newContainerPostions = state.containerPositions();
                    newContainerPostions.setPosition(i, nextPosition);
                    res.push_back(State(state.board(), nextPosition, newContainerPostions));
                }
            }
        }
    }
}

template<class T, class S = std::ptr_fun(swap<T>)>
struct C {

};

int main() {
    C<int> cc;
    vector<string> plan;
    string s;
    while (cin >> s) {
        plan.push_back(s);
    }
    Board board = Board::makeBoard(plan);
    PlayerPosition position(makePlayerPosition(plan));
    ContainerPositions containerPositions = ContainerPositions::makeContainerPositions(plan);
    debug(containerPositions.debugString());
    debug(position.debugString());
    debug(isConsistent(State(board, position, containerPositions)));

    return 0;
}
