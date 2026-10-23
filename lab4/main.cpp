#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string samples[25000];
bool used[25000];

int main() {


    string fileName = "GCF_023617405.1_ASM2361740v1_genomic.fna";
    ifstream fin(fileName);
    if (!fin) {
        cout << "Could not open the genome file: " << fileName << endl;
        return 1;
    }
    ofstream fout("samples.fasta");
    string genome, line;

    while (getline(fin, line)) {
        if (line.empty() || line[0] == '>')
            continue;
        genome += line;
    }

    cout << "Genome length: " << genome.length() << endl;

    if (genome.length() < 150) {
        cout << "The genome is too short or empty!" << endl;
        return 1;
    }

    int n = 25000;
    srand(time(0));

    for (int i = 0; i < n; i++) {
        long start = i * (genome.length() - 150) / (n - 1);
        int len = 100 + rand() % 51;

        if (i == n - 1)
            len = genome.length() - start;

        string sample = genome.substr(start, len);

        fout << ">sample" << i + 1 << " pos=" << start << " len=" << len << endl;
        fout << sample << endl;
    }

    cout << n << " samples were saved in samples.fasta" << endl;

    int originalLength = genome.length();
    fin.close();
    fout.close();
    genome = "";
    line = "";
    n = 0;

    fin.clear();
    fin.open("samples.fasta");
    if (!fin) {
        cout << "Could not open samples.fasta" << endl;
        return 1;
    }

    while (getline(fin, line) && n < 25000) {
        if (line.empty() || line[0] == '>')
            continue;
        samples[n] = line;
        n++;
    }
    fin.close();
    cout << "\nSamples read: " << n << endl;
    genome = samples[0];
    used[0] = true;

    bool added = true;
    while (added) {
        added = false;

        for (int i = 1; i < n; i++) {
            if (used[i])
                continue;

            string s = samples[i];

            for (int ov = s.length() - 1; ov >= 50; ov--) {
                if (ov > genome.length())
                    continue;

                if (genome.substr(genome.length() - ov) == s.substr(0, ov)) {
                    genome += s.substr(ov);
                    used[i] = true;
                    added = true;
                    break;
                }
            }
        }
    }

    cout << "Reconstructed genome length: " << genome.length() << endl;
    cout << "Original genome length: " << originalLength << endl;

    fout.open("reconstructed.fasta");
    fout << ">reconstructed_genome" << endl;
    fout << genome << endl;
    fout.close();

    cout << "Saved in reconstructed.fasta" << endl;
    return 0;
}
