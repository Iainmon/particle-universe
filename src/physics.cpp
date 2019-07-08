#include <SFML/Graphics.hpp>


namespace physics {

    class Bucket {
    private:
        float value; // 0 to 1 on how much liquid
        sf::Color emptyColor;
        sf::Color filledColor;

    public:
        Bucket(){
            value = 0;
            emptyColor = sf::Color::Black;
            filledColor = sf::Color::White;
        }

        Bucket(float _value, sf::Color _emptyColor, sf::Color _filledColor){
            value = _value;
            emptyColor = _emptyColor;
            filledColor = _filledColor;
        }

        sf::Color getColor(){
            sf::Color colorDif = filledColor - emptyColor;
            sf::Color actualColor = emptyColor + (colorDif * sf::Color(value, value, value));
            return actualColor;
        }

        float getValue(){
            return value;
        }
    };



    class FluidSim {
        private:
            int width, height;
            sf::Color floorColor, fluidColor;
            Bucket **buckets;

        public:
        
        FluidSim(int _width, int _height, sf::Color _floorColor, sf::Color _fluidColor){
            width = _width;
            height = _height;
            floorColor = _floorColor;
            fluidColor = _fluidColor;
            
            // Init bucket array
            buckets = new Bucket*[width];
            for(int i = 0; i < height; i++){
                buckets[i] = new Bucket[height];
            }
            for(int x = 0; x < width; x++){
                for(int y = 0; y < height; y++){
                    buckets[x][y] = Bucket(0, floorColor, fluidColor);
                }
            }
        }

        sf::Color getBucketColor(int x, int y){
            return buckets[x][y].getColor();
        }

        float getBucketValue(int x, int y){
            return buckets[x][y].getValue();
        }

        void setBucket(int x, int y, int targetValue){
            buckets[x][y] = Bucket(targetValue, floorColor, fluidColor);
        }

        void step(){
            
            // Init cache for future buckets
            Bucket **newBuckets = new Bucket*[width];
            for(int i = 0; i < height; i++){
                newBuckets[i] = new Bucket[height];
            }

            for(int x = 0; x < width; x++){
                for(int y = 0; y < height; y++){
                    buckets[x][y] = Bucket(0, floorColor, fluidColor);
                }
            }

            buckets = newBuckets;
        }
    };
}

