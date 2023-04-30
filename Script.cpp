#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        bool opened = false;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                opened = true;
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            //added flag to check whether file is opened
            if (opened) {
                if (command == "save") {
                    save();
                    continue;
                }
                if (command == "invert") {
                    invert();
                    continue;
                }
                if (command == "to_gray_scale") {
                    to_gray_scale();
                    continue;
                }

                if (command == "replace") {
                    int r1, g1, b1, r2, g2, b2;
                    input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
                    replace(r1,g1,b1,r2,g2,b2);

                }
            }

            

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert() {
        //Transforms each individual pixel (r, g, b) to (255-r,255-g,255-b).
        int w = image->width();
        int h = image->height();
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                //loop iterating over each single pixel
                image->at(i, j).red() = 255 - image->at(i, j).red();
                image->at(i, j).blue() = 255 - image->at(i, j).blue();
                image->at(i, j).green() = 255 - image->at(i, j).green();
            }
        }
    }

    void Script::to_gray_scale() {
        //Transforms each individual pixel (r, g, b) to (v, v, v) where v = 
        //(r + g + b)/3. You should use integer division without rounding to compute v.
        int w = image->width();
        int h = image->height();
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                //loop iterating over each single pixel
                int v = (image->at(i, j).red() + 
                image->at(i, j).blue() + 
                image->at(i, j).green() ) / 3;

                image->at(i, j).red() = v;
                image->at(i, j).blue() = v;
                image->at(i, j).green() = v;
            }
        }
    }

    void Script::replace(int r1, int g1, int b1, int r2, int g2, int b2) {
        //Replaces all (r1,  g1, b1) pixels by (r2,  g2, b2).
        int w = image->width();
        int h = image->height();
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                //loop iterating over each single pixel
                if (
                    image->at(i,j).red() == r1 &&
                    image->at(i,j).green() == g1 &&
                    image->at(i, j).blue() == b1
                ) 
                //this condition checks if pixel meets criteria
                {
                    //replace old colors with new ones
                    image->at(i, j).red() = r2;
                    image->at(i, j).blue() = b2;
                    image->at(i, j).green() = g2;
                }
            }
        }
    }
}
