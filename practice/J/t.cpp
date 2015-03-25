#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>


struct TrieNode {
    std::vector<size_t> string_ids;
    std::map<char, TrieNode> children;
};

void AddString(TrieNode* const root, size_t string_id, const std::string& string)
{
    TrieNode* node = root;
    for (char character : string) {
        node = &node->children[character];
    }
    node->string_ids.push_back(string_id);
}


class AhoCorasickAutomaton {
public:
    struct State {
        std::vector<size_t> matched_string_ids;
        std::map<char, State> links;
        const State* suffix_link;
        const State* terminal_link;
    };

    AhoCorasickAutomaton()
    { }

    void Init(const TrieNode& trie)
    {
        CreateState(trie, &root_);
        InitStates();
    }

    const State* Root() const
    {
        return &root_;
    }

    const State* NextState(const State* state, char character) const
    {
        auto it = state->links.find(character);
        while (state != &root_ && it == state->links.end()) {
            state = state->suffix_link;
            it = state->links.find(character);
        }
        if (it == state->links.end()) {
            return &root_;
        } else {
            return &it->second;
        }
    }

    template <class Callback>
    void GenerateMatches(const State* state, Callback on_match) const
    {
        while (state) {
            for (size_t string_id : state->matched_string_ids) {
                on_match(string_id);
            }
            state = state->terminal_link;
        }
    }

private:
    void CreateState(const TrieNode& node, State* state)
    {
        state->matched_string_ids = node.string_ids;
        state->links.clear();
        for (const auto& child : node.children) {
            CreateState(child.second, &state->links[child.first]);
        }
    }

    void InitState(const State& parent, char character, State* const child)
    {
        if (&parent == &root_) {
            child->suffix_link = &root_;
        } else {
            child->suffix_link = NextState(parent.suffix_link, character);
        }
        if (child->suffix_link->matched_string_ids.empty()) {
            child->terminal_link = child->suffix_link->terminal_link;
        } else {
            child->terminal_link = child->suffix_link;
        }
    }

    void InitStates()
    {
        root_.suffix_link = &root_;
        root_.terminal_link = nullptr;
        std::queue<State*> queue({&root_});
        while (!queue.empty()) {
            State& state = *queue.front();
            for (auto& link : state.links) {
                InitState(state, link.first, &link.second);
                queue.push(&link.second);
            }
            queue.pop();
        }
    }

    State root_;

    AhoCorasickAutomaton(const AhoCorasickAutomaton&) = delete;
    AhoCorasickAutomaton& operator= (const AhoCorasickAutomaton&) = delete;
};


template <class Predicate>
std::vector<std::string> Split(const std::string& string, const Predicate& is_delimiter)
{
    std::vector<std::string> result;
    auto split_begin = string.begin();
    while (split_begin != string.end()) {
        const auto split_end = std::find_if(split_begin, string.end(), is_delimiter);
        result.emplace_back(split_begin, split_end);
        if (split_end == string.end()) {
            return result;
        }
        split_begin = std::next(split_end);
    }
    result.emplace_back();
    return result;
}


class WildcardMatcher {
public:
    void Init(const std::string& pattern)
    {
        static const auto IS_WILDCARD = [] (char character) {
            return character == '?';
        };
        TrieNode trie;
        size_t word_end_offset = -1;
        const auto& words = Split(pattern, IS_WILDCARD);
        for (const auto& word : words) {
            word_end_offset += 1 + word.size();
            AddString(&trie, word_end_offset, word);
        }
        number_of_words_ = words.size();
        aho_corasick_automaton_.Init(trie);
    }

    template <class Callback>
    void FindAll(const std::string& string, Callback on_match) const
    {
        std::vector<size_t> counter(string.size() + 1, 0);
        const auto *state = aho_corasick_automaton_.Root();
        for (size_t offset = 0; offset < string.size(); ++offset) {
            aho_corasick_automaton_.GenerateMatches(state, [&] (size_t word_end_offset) {
                if (offset >= word_end_offset) {
                    ++counter.at(offset - word_end_offset);
                }
            });
            state = aho_corasick_automaton_.NextState(state, string[offset]);
        }
        aho_corasick_automaton_.GenerateMatches(state, [&] (size_t word_end_offset) {
            if (string.size() >= word_end_offset) {
                ++counter.at(string.size() - word_end_offset);
            }
        });
        for (size_t offset = 0; offset < counter.size(); ++offset) {
            if (counter[offset] == number_of_words_) {
                on_match(offset);
            }
        }
    }

private:
    size_t number_of_words_;
    AhoCorasickAutomaton aho_corasick_automaton_;
};


std::string ReadString()
{
    std::string result;
    std::getline(std::cin, result);
    return result;
}


std::vector<size_t> FindAll(const std::string& pattern, const std::string& text)
{
    WildcardMatcher matcher;
    matcher.Init(pattern);
    std::vector<size_t> result;
    matcher.FindAll(text, [&] (size_t offset) {
        result.push_back(offset);
    });
    return result;
}


void Print(const std::vector<size_t>& sequence)
{
    std::cout << sequence.size() << '\n';
    for (const auto& item : sequence) {
        std::cout << item << ' ';
    }
    std::cout << '\n';
}


int main()
{
    const std::string pattern = ReadString();
    const std::string text = ReadString();
    Print(FindAll(pattern, text));
    return 0;
}
