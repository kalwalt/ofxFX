#ifndef OFXWIREWORLD
#define OFXWIREWORLD

#include "ofxFXObject.h"


class ofxWireworld : public ofxFXObject
{
    public:

        ofxWireworld();

        void allocate(int _width, int _height);

    	ofTexture& getTextureReference() { return pingPong[1].getTextureReference(); };

        void begin();

    	void end(bool drawIt = false);

    	void update();

    	void draw(int x = 0, int y = 0){ pingPong.dst->draw(x, y);};


    private:

        void loadShaders();

    	ofShader	shader;
        swapBuffer	pingPong;

        int         iterations;

};

#endif // OFXWIREWORLD_H
