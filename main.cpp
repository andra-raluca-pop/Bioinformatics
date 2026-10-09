
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
   
    map<string, string> code = {
        {"UUU","Phe"}, {"UUC","Phe"}, {"UUA","Leu"}, {"UUG","Leu"},
        {"UCU","Ser"}, {"UCC","Ser"}, {"UCA","Ser"}, {"UCG","Ser"},
        {"UAU","Tyr"}, {"UAC","Tyr"}, {"UAA","Stop"}, {"UAG","Stop"},
        {"UGU","Cys"}, {"UGC","Cys"}, {"UGA","Stop"}, {"UGG","Trp"},
        {"CUU","Leu"}, {"CUC","Leu"}, {"CUA","Leu"}, {"CUG","Leu"},
        {"CCU","Pro"}, {"CCC","Pro"}, {"CCA","Pro"}, {"CCG","Pro"},
        {"CAU","His"}, {"CAC","His"}, {"CAA","Gln"}, {"CAG","Gln"},
        {"CGU","Arg"}, {"CGC","Arg"}, {"CGA","Arg"}, {"CGG","Arg"},
        {"AUU","Ile"}, {"AUC","Ile"}, {"AUA","Ile"}, {"AUG","Met"},
        {"ACU","Thr"}, {"ACC","Thr"}, {"ACA","Thr"}, {"ACG","Thr"},
        {"AAU","Asn"}, {"AAC","Asn"}, {"AAA","Lys"}, {"AAG","Lys"},
        {"AGU","Ser"}, {"AGC","Ser"}, {"AGA","Arg"}, {"AGG","Arg"},
        {"GUU","Val"}, {"GUC","Val"}, {"GUA","Val"}, {"GUG","Val"},
        {"GCU","Ala"}, {"GCC","Ala"}, {"GCA","Ala"}, {"GCG","Ala"},
        {"GAU","Asp"}, {"GAC","Asp"}, {"GAA","Glu"}, {"GAG","Glu"},
        {"GGU","Gly"}, {"GGC","Gly"}, {"GGA","Gly"}, {"GGG","Gly"}
    };

        map<string, string> letter = {
        {"Ala","A"}, {"Arg","R"}, {"Asn","N"}, {"Asp","D"}, {"Cys","C"},
        {"Glu","E"}, {"Gln","Q"}, {"Gly","G"}, {"His","H"}, {"Ile","I"},
        {"Leu","L"}, {"Lys","K"}, {"Met","M"}, {"Phe","F"}, {"Pro","P"},
        {"Ser","S"}, {"Thr","T"}, {"Trp","W"}, {"Tyr","Y"}, {"Val","V"}
    };

    string gene = "ATGGCCATTGTAATGGGCCGCTGAAAGGGTGCCCGATAG";

    for (int i = 0; i < gene.length(); i++)
        if (gene[i] == 'T')
            gene[i] = 'U';

    cout << "Phase1 -> mRNA: " << gene << endl;
    cout << "Phase2 -> Protein: ";

    string abbreviated = "";

  
    for (int i = 0; i + 3 <= gene.length(); i += 3)
    {
        string group = code[gene.substr(i, 3)];
        if (group == "Stop")
            break;
        cout << group << " ";
        abbreviated += letter[group];
    }

    cout << endl;
    cout << "Phase3 -> One-letter abbreviation: " << abbreviated << endl;
    
    int start = gene.find("AUG");

    cout << "Phase4 -> From first AUG: ";

    if (start == -1)
    {
        cout << "no AUG found" << endl;
    }
    else
    {
        string fromStart = "";

        for (int i = start; i + 3 <= gene.length(); i += 3)
        {
            string group = code[gene.substr(i, 3)];
            if (group == "Stop")
                break;
            cout << group << " ";
            fromStart += letter[group];
        }

        cout << "(" << fromStart << ")" << endl;
    }


    return 0;
}
