#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>

namespace graphics {


    struct Frame {
        
        unsigned int width = WIDTH;
        unsigned int height = HEIGHT;

        sf::Color pixels[WIDTH][HEIGHT];

        void setPixel(unsigned int x, unsigned int y, const sf::Color color) {
            pixels[x][y] = color;
        }
        sf::Color getPixel(unsigned int x, unsigned int y) {
            return pixels[x][y];
        }
    };

    class Stroke {
        private:

            Frame *frame;

            void drawCircle( int xc,  int yc,  int x,  int y, sf::Color color) {
                dot(xc+x, yc+y, color);
                dot(xc-x, yc+y, color);
                dot(xc+x, yc-y, color);
                dot(xc-x, yc-y, color);
                dot(xc+y, yc+x, color);
                dot(xc-y, yc+x, color);
                dot(xc+y, yc-x, color);
                dot(xc-y, yc-x, color);
            }
            
        public:

            float deltaTime = 0.0f;

            Stroke(Frame *drawingFrame) {
                this->frame = drawingFrame;
            }
            bool isInBounds(const int x, const int y) {
                return ( x <= WIDTH && y <= HEIGHT && x >= 0 && y >= 0 );
            }
            void dot(const int x, const int y, sf::Color color) {
                if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0) {
                    this->frame->pixels[x][y] = color;
                }
            }
            void unsafe_dot(const int x, const int y, sf::Color color) {
                this->frame->pixels[x][y] = color;
            }
            sf::Color pix(const int x, const int y) {
                if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0) {
                    return this->frame->pixels[x][y];
                }
            }
            sf::Color unsafe_pix(const int x, const int y) {
                return this->frame->pixels[x][y];
            }

            void line( int x1, int y1, int x2, int y2, const sf::Color& color ){
                // Bresenham's line algorithm
                const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
                if(steep)
                {
                    swap(x1, y1);
                    swap(x2, y2);
                }
                
                if(x1 > x2)
                {
                    swap(x1, x2);
                    swap(y1, y2);
                }
                
                const float dx = x2 - x1;
                const float dy = fabs(y2 - y1);
                
                float error = dx / 2.0f;
                const int ystep = (y1 < y2) ? 1 : -1;
                int y = (int)y1;
                
                const int maxX = (int)x2;
                
                for(int x=(int)x1; x<maxX; x++)
                {
                    if(steep)
                    {
                        dot(y,x, color);
                    }
                    else
                    {
                        dot(x,y, color);
                    }
                
                    error -= dy;
                    if(error < 0)
                    {
                        y += ystep;
                        error += dx;
                    }
                }
            }
 
            void lr_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                const int dx = x2 - x1;
                const int dy = y2 - y1;

                int z1 = x1;
                int z2 = x2;
                int w1 = y1;
                int w2 = y2;

                if (dx < 0) {
                    swap(z1, z2);
                }
                if (dy < 0) {
                    swap(w1, w2);
                }

                unsigned_lr_line(z1, w1, z2, w2, color);

            }
            void ud_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                const int dx = x2 - x1;
                const int dy = y2 - y1;

                int z1 = x1;
                int z2 = x2;
                int w1 = y1;
                int w2 = y2;

                if (dx < 0) {
                    swap(z1, z2);
                }
                if (dy < 0) {
                    swap(w1, w2);
                }

                unsigned_ud_line(z1, w1, z2, w2, color);

            }
            void swap(int& x, int& y) {
                int tmp = x;
                x = y;
                y = tmp;
            }


            void unsigned_ud_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                int dx = x2 - x1;
                int dy = y2 - y1;
                int D = 2 * dy - dx;
                int x = x1;
                
                for (int y = y1; y <= y2; y++) {
                    dot(x, y, color);

                    if (D > 0) {
                        x++;
                        D -= dy * 2;
                    }
                    D += dx * 2;
                }
            }

            void unsigned_lr_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                int dx = x2 - x1;
                int dy = y2 - y1;
                int D = 2 * dy - dx;
                int y = y1;
                
                for (int x = x1; x <= x2; x++) {
                    dot(x, y, color);

                    if (D > 0) {
                        y++;
                        D -= dx * 2;
                    }
                    D += dy * 2;
                }
            }
            void rect(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                for (int x = x1; x < x2; x++) {
                    for (int y = y1; y < y2; y++) {
                        this->frame->pixels[x][y] = color;
                    }
                }
            }
            void background(sf::Color color = sf::Color::Black) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    for (unsigned int y = 0; y < HEIGHT; y++) {
                        this->frame->pixels[x][y] = color;
                    }
                }
            }
            
            void circle( int xc,  int yc,  int r, sf::Color color) 
            {
                 int x = 0, y = r;
                 int d = 3 - 2 * r;
                drawCircle(xc, yc, x, y, color);
                while (y >= x)
                {
                    // for each pixel we will 
                    // draw all eight pixels 
                    
                    x++; 
            
                    // check for decision parameter 
                    // and correspondingly  
                    // update d, x, y 
                    if (d > 0) 
                    { 
                        y--;  
                        d = d + 4 * (x - y) + 10; 
                    } 
                    else
                        d = d + 4 * x + 6; 
                    drawCircle(xc, yc, x, y, color); 
                } 
            }
    };

    class Drawable {

        public:

            static const unsigned int width = WIDTH;
            static const unsigned int height = HEIGHT;

            int raidius;

            physics::Vector v;

            virtual void setup() = 0;
            virtual void draw(Stroke *stroke) = 0;
            virtual physics::Position* getPosition() = 0;
            virtual void setRaidius(const int x) = 0;
    };

    class Processor {
        private:
            Frame frame;
            //bool ran = false;
        public:
            std::vector<Drawable*> drawables;
            void loadDrawable(Drawable* drawable) {
                drawables.push_back(drawable);
            }
            void setup(unsigned int w, unsigned int h) {
                frame.width = w;
                frame.height = h;
                
                for (unsigned int i = 0; i < drawables.size(); i++) {
                    (*drawables[i]).setup();
                }
            }
            Frame loop() {
                //if (!ran) {
                    Stroke stroke(&frame);
                    stroke.background();
                    for (unsigned int i = 0; i < drawables.size(); i++) {
                        (*drawables[i]).draw(&stroke);
                    }
                //}

                return frame;
            }
    };

    class GraphicHandler {
        private:

            bool shouldUpdateFrame = true;
            bool paused = false;
            Processor processor;

            sf::RenderWindow *window;
            sf::Clock clock;
            float framerate = 60.0f;

            sf::Image image;
            sf::Texture texture;
            sf::Sprite sprite;

        public:
            GraphicHandler(/*Universe _universe*/) {
                //universe = _universe;
            }
            void setup() {
                const unsigned int width = glutGet(GLUT_WINDOW_WIDTH);
                const unsigned int height = glutGet(GLUT_WINDOW_HEIGHT);
                util::init();
            }

            void loop() {

                const unsigned int width = glutGet(GLUT_WINDOW_WIDTH);
                const unsigned int height = glutGet(GLUT_WINDOW_HEIGHT);

                Frame frame;
                frame.width = width;
                frame.height = height;

                Stroke stroke = Stroke(&frame);
                //universe.Step(&stroke);


                glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque 

                glClear( GL_COLOR_BUFFER_BIT );
                glMatrixMode( GL_PROJECTION );
                glLoadIdentity();
                gluOrtho2D(0, width, height, 0);

                glBegin(GL_POINTS);
                for (unsigned int x = 0; x < width; x++)
                {
                    for (unsigned int y = 0; y < height; y++)
                    {
                        glColor3f(255, 255, 0);
                        //glColor3f(frame.pixels[x, y].r, frame.pixels[x, y].g, frame.pixels[x, y].b);
                        glVertex2i(x, y);
                    }
                }

                glEnd();
            
                glFlush();  // Render now
            }

    };
}