#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#define pb push_back
#define mp make_pair
#define ll long long
using namespace std;

vector <int> failure_function(string &s)
{
    int n = (int)s.size();
    vector <int> ff(n, 0);
    for(int i = 1; i < n; i++)
    {
        int j = ff[i - 1];
        while(j > 0 && s[i] != s[j])
            j = ff[j - 1];
        ff[i] = j + (s[i] == s[j]);
    }
    return ff;
}

string t, s;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int tests;

    cin >> tests;
    for(int current_case = 1; current_case <= tests; current_case++)
    {
        cin >> t >> s;

        string conc = s + "#" + t;
        vector <int> ff = failure_function(conc);
        vector <int> ans;
        for(int i = (int)s.size() + 1; i < (int)ff.size(); i++)
        {
            if(ff[i] == (int)s.size())
                ans.pb(i - 2 * (int)s.size() + 1);
        }

        if((int)ans.size() == 0)
        {
            cout << "Not Found" << endl;
            continue;
        }

        cout << (int)ans.size() << endl;
        for(auto i: ans)
            cout << i << " ";
        cout << endl;
    }


    return 0;
}
