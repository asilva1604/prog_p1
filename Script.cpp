#include <iostream>
#include <fstream>
#include <algorithm>
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
                opened = true;
                continue;
            }

            if (command == "xpm2_open") {
                xpm2_open();
                opened = true;
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
                    replace();
                    continue;
                }

                if (command == "fill") {
                    fill();
                    continue;   
                }
                
                if (command == "add") {
                    add();
                    continue;
                }

                if (command == "h_mirror") {
                    h_mirror();
                    continue;
                }

                if (command == "v_mirror") {
                    v_mirror();
                    continue;
                }

                if (command == "crop") {
                    crop();
                    continue;
                }

                if (command == "median_filter") {
                    median_filter();
                    continue;
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

    void Script::replace() {
        //Replaces all (r1,  g1, b1) pixels by (r2,  g2, b2).
        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
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

    void Script::fill() {
        int x, y, w, h;
        Color fill; //this is the color that we will use
        input >> x >> y >> w >> h >> fill;
        for (int i = x; i < x+w; i++) {
            for (int j = y; j < y+h; j++) {
                //loop iterating over each single pixel
                image->at(i,j) = fill;  //changes color of pixel
            }
        }
    }

    void Script::h_mirror() {
        int w = image->width();
        int h = image->height();

        for (int i = 0; i < w / 2; i++) {
            for (int j = 0; j < h; j++) {
                //loop iterating over each single pixel
                Color temp = image->at(w - 1 - i, j);   //
                image->at(w - 1 - i, j) = image->at(i,j);
                image->at(i,j) = temp;
            }
        }
    }

    void Script::v_mirror() {
        int w = image->width();
        int h = image->height();

        for (int j = 0; j < h/2; j++) {
            for (int i = 0; i < w; i++) {
                Color temp = image->at(i, j);
                image->at(i, j) = image->at(i, h - 1 -j);
                image->at(i,h-1-j) = temp;
            }
        }
    }

    void Script::add() {
        int r, g, b, x, y;
        string filename;
        input >> filename;
        input >> r >> g >> b >> x >> y;
        Image *img = loadFromPNG(filename);
        for (int i = 0; i < img->width(); i++) {
            for (int j = 0; j < img->height(); j++) {
                //loop iterating over each single pixel
                if (
                    img->at(i,j).red() == r &&
                    img->at(i,j).green() == g &&
                    img->at(i, j).blue() == b
                ){continue;}
                
                image->at(i+x,j+y).red() = img->at(i,j).red();
                image->at(i+x,j+y).green() = img->at(i,j).green();
                image->at(i+x,j+y).blue() = img->at(i,j).blue();

            }
        }
        delete img;
        
    }

    void Script::crop() {
        int x,y,w,h;
        input >> x >> y >> w >> h;
        Image *newImg = new Image(w,h);
        for (int i = x; i < x+w; i++) {
            for (int j = y; j < y+h; j++) {
                newImg->at(i-x,j-y) = image->at(i,j);
            }
        }
        clear_image_if_any();
        image = newImg;
    }

    void Script::median_filter() {
        int ws;
        input >> ws;

        int w = image->width();
        int h = image->height();

        Image *newImg = new Image(w,h);

        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                vector<Color> neighbours;
                //max(0, x - ws / 2) <= nx <= min(width() - 1, x + ws / 2), where ws / 2 denotes integer division, and
                //max(0, y - ws / 2) <= ny <= min(height() - 1, y + ws /2).

                for (int ii = max(0, i - ws/2); ii <= min(w-1, i + ws / 2); ii++) {
                    for (int jj = max(0, j - ws / 2); jj <= min(h-1, j + ws / 2); jj++) {
                        neighbours.push_back(image->at(ii, jj));
                    }
                }

                vector<int> rr,gg,bb;
                for (const auto &c : neighbours) {
                    rr.push_back(c.red());
                    gg.push_back(c.green());
                    bb.push_back(c.blue());
                }
                sort(rr.begin(), rr.end());
                sort(gg.begin(), gg.end());
                sort(bb.begin(), bb.end());
                if (rr.size() % 2 != 0) {
                    newImg->at(i,j).red() = rr.at(rr.size() / 2);
                    newImg->at(i,j).green() = gg.at(gg.size() / 2);
                    newImg->at(i,j).blue() = bb.at(bb.size() / 2);
                } else {
                    newImg->at(i,j).red() = (rr.at(rr.size() / 2 - 1) + rr.at(rr.size() / 2)) / 2;
                    newImg->at(i,j).green() = (gg.at(gg.size() / 2 - 1) + gg.at(gg.size() / 2)) / 2;
                    newImg->at(i,j).blue() = (bb.at(bb.size() / 2 - 1) + bb.at(bb.size() / 2)) / 2;
                }
          
            }
        }

        clear_image_if_any();
        image = newImg;
    }

    void Script::xpm2_open() {
        string ff;
        input >> ff;
        clear_image_if_any();
        image = loadFromXPM2(ff);
    }
}
