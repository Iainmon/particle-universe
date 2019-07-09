#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>

namespace graphics {

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

            Frame* frame = new Frame();
            Stroke stroke = Stroke(frame);

            std::clock_t lastTime = std::clock();
            Universe::Universe* universe;

        public:
            GraphicHandler(Universe::Universe* _universe) {
                universe = _universe;
            }
            void setup() {
                const unsigned int width = glutGet(GLUT_WINDOW_WIDTH);
                const unsigned int height = glutGet(GLUT_WINDOW_HEIGHT);
                util::init();
            }

            void loop() {

                const unsigned int width = glutGet(GLUT_WINDOW_WIDTH);
                const unsigned int height = glutGet(GLUT_WINDOW_HEIGHT);

                frame->width = width;
                frame->height = height;

                universe->GetFrame(&stroke);

                //frame->clear();


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
                        //glColor3f(255, 255, 0);
                        const sf::Color pixel = frame->getPixel(x, y);
                        glColor3f(pixel.r, pixel.g, pixel.b);
                        glVertex2i(x, y);
                    }
                }

                glEnd();

                const std::clock_t now = std::clock();
                stroke.deltaTime = 0.01f;//= float( now - lastTime );
                lastTime = now;
                std::cout << stroke.deltaTime << std::endl;

                glFlush();  // Render now
            }

    };
}