#include <iostream>
#include <fstream>
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

    ifstream file("GCF_049169615.1_ASM4916961v1_genomic.fna");
    string line, genome = "";
    while (getline(file, line))
        if (line[0] != '>')
            genome += line;


    for (int i = 0; i < genome.length(); i++)
        if (genome[i] == 'T')
            genome[i] = 'U';


    map<string, int> freq;
    for (int i = 0; i + 3 <= genome.length(); i++)
        freq[genome.substr(i, 3)]++;


    string letters = "ACGU";
    for (int k = 1; k <= 10; k++)
    {
        string best = "";
        int bestCount = 0;

        for (int a = 0; a < 4; a++)
            for (int b = 0; b < 4; b++)
                for (int c = 0; c < 4; c++)
                {
                    string codon = "";
                    codon = codon + letters[a] + letters[b] + letters[c];
                    if (freq[codon] > bestCount)
                    {
                        bestCount = freq[codon];
                        best = codon;
                    }
                }

        cout << k << ". " << best << " -> " << code[best] << " (" << bestCount << " times)" << endl;
        freq[best] = 0;
    }

    return 0;
}
