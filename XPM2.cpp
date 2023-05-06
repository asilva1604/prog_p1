#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "XPM2.hpp"
#include "Image.hpp"
#include "Color.hpp"

using namespace std;

namespace prog {

    bool operator<(const Color &first, const Color &second) {
        return (first.red() < second.red() || (first.red() == second.red() && first.green() < second.green()) || (first.red() == second.red() && first.green() == second.green() && first.blue() < second.blue()));
    }

    string intToHex(int num) {
        const char lookup[] = "0123456789ABCDEF";
        string res(2, '0');
        res[0] = lookup[(num >> 4) & 0xF];
        res[1] = lookup[num & 0xF];
        return res;
    }
    string rgbToHex(const Color &c) {
        ostringstream oss;
        oss << "#" << intToHex(c.red()) << intToHex(c.green()) << intToHex(c.blue());
        return oss.str();
    }

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
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
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
        ofstream ofs;
        ofs.open(file);
        int w = image->width();
        int h = image->height();
        map<Color, char> colors;
        char first = 'a';
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                Color current = image->at(j, i);
                if (colors.find(current) == colors.end()) {
                    colors[current] = first;
                    first++;
                }
            }
        }
        ofs << "! XMP 2" << "\n" << w << " " << h << " " << colors.size() << " 1\n";
        for (const auto &m : colors) {
            ofs << m.second << " c " << rgbToHex(m.first) << "\n";
        }

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                ofs << colors[image->at(x,y)];
            }
            ofs << "\n";
        }

        ofs << "\n";
        ofs.close();
    }
}
