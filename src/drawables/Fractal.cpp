#include <complex>

namespace drawables {

    class Fractal: public graphics::Drawable {

    public:

        void setup() override {

        }
        sf::Color getColorForPixel(unsigned int x, unsigned int y) {
            return f1(x, y);
        }
        void draw(graphics::Stroke *stroke) override {
            for (unsigned int x = 0; x < width; x++) {
                for (unsigned int y = 0; y < height; y++) {
                    stroke->dot(x, y, getColorForPixel(x, y));
                }
            }
        }
        sf::Color f1(int px, int py, double zoom = 200){
            double x = (px - 300) / zoom;
            double y = (py - 300) / zoom;

            std::complex<double> z(x, y);
            std::complex<double> a(2, 0);

            int iter = 0;
            int maxIter = 300;

            while(abs(z) > 0 && iter < maxIter){
                std::complex<double> b = 7.0*z;
                std::complex<double> c = 2.0 + 5.0*z;
                std::complex<double> d = cos(M_PI * z);
                
                z = (0.25 * (a + b - c * d));

                iter++;
            }

            float ratio = pow((double)(iter * 500) / maxIter, 3);

            sf::Color filledColor = sf::Color::White;
            sf::Color emptyColor = sf::Color::Black;

            sf::Color colorDif = filledColor - emptyColor;
            sf::Color actualColor = emptyColor + (colorDif * sf::Color(ratio * 255, ratio * 255, ratio * 255));
            return actualColor;
        }
    };
    
}
