#include <bits/stdc++.h>
using namespace std;

struct MNT {
    string name;
    int pp, kp, mdtp, kpdptr, pntabptr;
};

int main() {
    ifstream mnt("mnt.txt"), kpd("kpdtab.txt"), mdt("mdt.txt"), in("intermediate.txt");
    if(!mnt || !kpd || !mdt || !in) {
        cout << "Error: Missing one or more input files from Pass1\n";
        return 0;
    }

    // Load MNT
    vector<MNT> MNTTAB;
    vector<pair<string,string>> KPDTAB;
    vector<string> MDT;

    string temp;

    // getline(mnt, temp);
    while(getline(mnt, temp)) {
        stringstream ss(temp);
        MNT m;
        ss >> m.name >> m.pp >> m.kp >> m.mdtp >> m.kpdptr >> m.pntabptr;
        MNTTAB.push_back(m);
    }

    // Load KPDTAB
    while(getline(kpd, temp)) {
        stringstream ss(temp);
        string idx, name, def;
        ss >> idx >> name >> def;
        KPDTAB.push_back({name, def});
    }

    // Load MDT
    while(getline(mdt, temp)) {
        stringstream ss(temp);
        string idx, line;
        getline(ss, idx, '\t');
        getline(ss, line);
        if(!line.empty() && line[0]=='\t') line.erase(0,1);
        MDT.push_back(line);
    }

    ofstream out("output.txt");
    string line;

    while(getline(in, line)) {
        stringstream ss(line);
        string macro;
        ss >> macro;
        bool isMacro = false;

        for(auto &m : MNTTAB) {
            if(m.name == macro) {
                isMacro = true;

                // parse arguments
                vector<string> args;
                string tok;
                while(getline(ss, tok, ',')) {
                    tok.erase(remove(tok.begin(), tok.end(), ' '), tok.end());
                    if(!tok.empty()) args.push_back(tok);
                }

                // build APTAB
                vector<string> APTAB(m.pp + m.kp + 1, "");
                for(int i=0; i<m.pp && i<args.size(); i++)
                    APTAB[i+1] = args[i];
                for(int i=0; i<m.kp; i++)
                    APTAB[m.pp + i + 1] = KPDTAB[m.kpdptr - 1 + i].second;

                // overwrite keyword args
                for(int i=m.pp; i<args.size(); i++) {
                    int eq = args[i].find('=');
                    if(eq != string::npos) {
                        string pname = args[i].substr(0, eq);
                        string val = args[i].substr(eq + 1);
                        for(int j=0; j<KPDTAB.size(); j++)
                            if(KPDTAB[j].first == pname)
                                APTAB[m.pp + j + 1] = val;
                    }
                }

                // expand
                int ptr = m.mdtp - 1;
                while(MDT[ptr] != "MEND") {
                    string expLine = MDT[ptr];
                    for(int i=1; i<=m.pp+m.kp; i++) {
                        string key = "#" + to_string(i);
                        size_t pos;
                        while((pos = expLine.find(key)) != string::npos)
                            expLine.replace(pos, key.size(), APTAB[i]);
                    }
                    out << expLine << "\n";
                    ptr++;
                }
                break;
            }
        }

        if(!isMacro && macro != "MACRO" && macro != "MEND")
            out << line << "\n";
    }

    cout << "Pass 2 completed. Final output written to output.txt\n";
    return 0;
}