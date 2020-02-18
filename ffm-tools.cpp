#include <fstream>
#include <iostream>
#include <string>

#include "ffm.h"

using namespace std;
using namespace ffm;

int convert_model_to_txt(const string& bin_path, const string& txt_path) {
    ffm_model model = ffm_load_model(bin_path);
    ofstream output_fp(txt_path.c_str());
    if (!output_fp.is_open()) {
        cerr << "open txt_path failed: " << txt_path << endl;
        return 1;
    }
    output_fp << model.n << " " << model.m << " " << model.k << endl;
    for (ffm_int nid = 0; nid < model.n; nid ++) {
        for (ffm_int mid = 0; mid < model.m; mid ++) {
            vector<ffm_float> w = get_w(nid, mid, model);
            output_fp << nid << " " << mid;
            for (ffm_int kid = 0; kid < model.k; kid ++) {
                output_fp << " " << w[kid];
            }
            output_fp << endl;
        }
    }
    output_fp.close();
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Usage: ffm-tools <task> [args]" << endl;
        return 1;
    }
    string task(argv[1]);
    if (task == "model2txt") {
        if (argc < 4) {
            cerr << "Usage: ffm-tools model2txt <bin_path> <txt_path>" << endl;
            return 1;
        }
        return convert_model_to_txt(argv[2], argv[3]);
    } else {
        cerr << "Unknown task: " << task << endl;
        return 1;
    }
    return 0;
}
