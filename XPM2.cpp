#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "XPM2.hpp"
#include "Image.hpp"
#include "Color.hpp"

using namespace std;

namespace prog {
    Image* loadFromXPM2(const std::string& file) {
        ifstream ifs;
        ifs.open(file);
        string line, hex;
        getline(ifs, line);
        int w,h,nColors,colorSize;
        char colorSymbol, aux;
        map<char, Color> colors;
        ifs >> w >> h >> nColors >> colorSize;
        Image *img = new Image(w,h);
        for (int i = 0; i < nColors; i++) {
            ifs >> colorSymbol >> aux >> hex;
            unsigned char r, g, b;
            string hexAux;
            r = stoi(hex.substr(1,2), nullptr, 16);
            g = stoi(hex.substr(3,2), nullptr, 16);
            b = stoi(hex.substr(5, 2), nullptr, 16);
            colors[colorSymbol] = {r,g,b};
        }
        char current;
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                ifs >> current;
                if (current != ' ') {
                    img->at(x, y) = colors[current];
                }
            }
        }
        ifs.close();
        return img;
    }

    void saveToXPM2(const std::string& file, const Image* image) {

    }
}
