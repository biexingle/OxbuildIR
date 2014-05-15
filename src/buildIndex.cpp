#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
namespace fs = boost::filesystem;
namespace po = boost::program_options;

using namespace std;

vector<int> readDescriptors(string fpath) {
    vector<int> descs;
    ifstream fin(fpath.c_str());
    if (!fin.is_open()) {
        cerr << "Unable to open file: " << fpath << endl;
        return vector<int>();
    }
    float temp;
    fin >> temp >> temp;
    int desc;
    while (fin >> desc >> temp >> temp >> temp >> temp >> temp) {
        descs.push_back(desc);
    }
    fin.close();
    return descs;
}

string fpathToIdx(string fpath) {
    return fpath.substr(0, fpath.size() - 4); 
}

void addToIndex(vector<int> descs, string img_idx, map<int, vector<string> > &invIdx) {
    for (int i = 0; i < descs.size(); i++) {
        if (invIdx.count(descs[i]) <= 0) {
            // not exists
            invIdx[descs[i]] = vector<string>();
        }
        invIdx[descs[i]].push_back(img_idx);
    }
}

void dumpToFile(string output_fpath, map<int, vector<string> > invIdx) {
    ofstream fout;
    fout.open(output_fpath.c_str(), ios::out);
    for (auto iter = invIdx.begin();
            iter != invIdx.end(); ++iter) {
        fout << iter->first << " ";
        for (auto iter2 = iter->second.begin(); 
                iter2 != iter->second.end(); ++iter2) {
            fout << *iter2 << " "; 
        }
        fout << endl;
    }
    fout.close();
}

int main(int argc, char *argv[]) {
    po::options_description desc("Allowed Options");
    desc.add_options()
        ("help", "produce this help message")
        ("dir,d", po::value<string>()->required(), "directory with oxc1 files")
        ("output,o", po::value<string>()->required(), "Output file")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return -1;
    }
    string dir = vm["dir"].as<string>();
    
    map<int, vector<string> >invIdx;
    fs::recursive_directory_iterator rdi(dir), end;
    string img_fpath, img_fname;
    int count = 0;
    while (rdi != end) {
        img_fpath = (*rdi).path().string();
        img_fname = (*rdi).path().filename().string();
        vector<int> descs = readDescriptors(img_fpath);
        string img_idx = fpathToIdx(img_fname);
        addToIndex(descs, img_idx, invIdx);
        rdi++; count++;
        cout << "Done for " << img_fname << " (" << count << ")"<< endl;
    }
    dumpToFile(vm["output"].as<string>(), invIdx);
    return 0;
}
