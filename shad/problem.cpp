#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using std::endl;
using std::cout;
using std::cin;
using std::cout;
using std::vector;
using std::string;


class EntriesSampleInText
{
public:
    EntriesSampleInText (const string& sample, const string& text):
        sample_(sample), text_(text), separator_('#'), question_('?') {}

    void init ()
    {
        foundQuestions ();
        calculateZFunction();
    }

    vector<int> getEntries () const
    {
        vector<int> allEntryes;
        for (int i = sample_.size() + 1; i < zFunction_.size(); ++i)
        {
            if (zFunction_[i] == sample_.size())
            {
                allEntryes.push_back(i - sample_.size() - 1);
            }
        }
        return allEntryes;
    }

private:
    const string sample_;
    const string text_;
    vector<int> indexesQuestion_;
    vector<int> zFunction_;
    char separator_;
    char question_;

    void foundQuestions ()
    {
        indexesQuestion_.empty();
        for (int i = 0; i < sample_.size(); ++i)
        {
            if (sample_[i] == question_)
            {
                indexesQuestion_.push_back(i);
            }
        }
    }

    bool compare (char first, char second) const
    {
        if (first == separator_ || second == separator_)
        {
            return false;
        }
        return (first == second) || (first == question_) || (second == question_);
    }

    void calculateZFunction ()
    {
        string code = sample_ + separator_ + text_;

        zFunction_.empty();
        zFunction_.resize(code.size());

        int left = 0, right = 0;
        for (int index = 1; index < code.size(); ++index)
        {
            if (index <= right)
            {
                int coincidence = predictCoincidence(index, left, right, code);
                int nextIndex = index + coincidence;
                while (nextIndex + 1 <= right && code[nextIndex] == question_)
                {
                    coincidence += predictCoincidence(nextIndex + 1, left, right, code) + 1;
                    nextIndex = index + coincidence;
                }
                zFunction_[index] = coincidence;
            }
            increaseZFunction(index, code);
            if (index + zFunction_[index] - 1 > right)
            {
                left = index;
                right = index + zFunction_[index] - 1;
            }
        }
    }
    int predictCoincidence (int index,
                            int left,
                            int right,
                            const string& text)
    {
        int lowerBoundCoincidence = std::min(right - index + 1, zFunction_[index - left]);
        for (int j = 0; j < indexesQuestion_.size(); ++j)
        {
            int id = indexesQuestion_[j] - (index - left);
            if (id >= 0 && id < lowerBoundCoincidence)
            {
                if (!compare(text[id], text[index + id]))
                {
                    lowerBoundCoincidence = id;
                    break;
                }
            }
        }
        return lowerBoundCoincidence;
    }

    void increaseZFunction (int index, const string& text)
    {
        while (index + zFunction_[index] < text.size() &&
            compare(text[zFunction_[index]], text[index + zFunction_[index]]))
        {
            ++zFunction_[index];
        }
    }
};

vector<int> foundEntries (const string& sample, const string& text)
{
    EntriesSampleInText entriesSampleInText(sample, text);
    entriesSampleInText.init();
    return entriesSampleInText.getEntries();
}

template<class T>
void print (const vector<T>& allEntryes)
{
    cout << allEntryes.size() << endl;
    for (int i = 0; i < allEntryes.size(); ++i)
    {
       printf("%d ", allEntryes[i]);
    }
    cout << endl;
}

vector<int> solve(string sample,  string text) {
    return foundEntries(sample, text);
}

vector<int> stSolve(string sample, string text) {
    vector<int> res;
    for (int i = 0; i + sample.size() <= text.size(); ++i)  {
        bool ok = 1;
        for (int j = 0; j < sample.size(); ++j) {
            ok = ok && (sample[j] == '?' || sample[j] == text[i+j]);
        }
        if (ok)
            res.push_back(i);
    }
    return res;
}

string gen(int len, string alpha) {
    string s = "";
    for (int i = 0; i < len; ++i) {
        s += alpha[rand() % alpha.size()];
    }
    return s;
}

int main() {
    srand(1);
    while (true) {
        string s, t;
        s = gen(5, "abc?");
        t = gen(9, "acb");
        std::cerr << s << " " << t << "\n";
        vector<int> a,b;
        a = solve(s, t);
        b = stSolve(s, t);
        if (a != b) {
            print(a);
            print(b);
            break;
        }
    }
}


