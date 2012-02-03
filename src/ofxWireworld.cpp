#include "ofxWireworld.h"

ofxWireworld::ofxWireworld()
{


     iterations = 6;

             string wireworldFragmentShader="#version 120\n \
            #extension GL_ARB_texture_rectangle : enable\n \
             uniform sampler2DRect texture_A; \
             int sum; \
             vec4 blank = vec4(0.0,0.0,0.0,1.0); \
             vec4 copper = vec4(1.0,0.5,0.0,1.0); \
             vec4 head = vec4(1.0,1.0,1.0,1.0); \
             vec4 tail = vec4(0.0,1.0,1.0,1.0); \
             void main(void) {  \
                 vec4 y = texture2DRect(texture_A, gl_TexCoord[0].st); \
                    \
                 if(y==blank) gl_FragColor = blank; \
                 else if(y==head) gl_FragColor = tail; \
                 else if(y==tail) gl_FragColor = copper; \
                 else { \
                     sum=0; \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(-1.0, -1.0))==head) ++sum; \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(0.0, -1.0))==head) ++sum; \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(1.0, -1.0))==head) ++sum; \
                            \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(-1.0, 0.0))==head) ++sum; \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(1.0, 0.0))==head) ++sum; \
                            \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(-1.0, 1.0))==head) ++sum; \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(0.0, 1.0))==head) ++sum; \
                     if (texture2DRect(texture_A, gl_TexCoord[0].st + vec2(1.0, 1.0))==head) ++sum; \
                            \
                     if (sum==1||sum==2) gl_FragColor = head; \
                     else gl_FragColor = copper; \
                 } \
             }";

               shader.setupShaderFromSource(GL_FRAGMENT_SHADER, wireworldFragmentShader);
            shader.linkProgram();

    //ctor
}

void ofxWireworld::allocate(int _width, int _height){

            width = _width;
            height = _height;

            pingPong.allocate(width, height,GL_RGBA);

}

void ofxWireworld::begin(){


            pingPong[0].begin();


}

void ofxWireworld::end(bool drawIt){


            pingPong[0].end();
            update();

            if (drawIt)
            draw();

}

void ofxWireworld::update(){

    for( int i = 0; i < iterations ; i++ ){

            pingPong.dst->begin();
            ofClear(0,0,0,255);


            shader.begin();

            shader.setUniformTexture("texture_A", pingPong.src->getTextureReference(), 0 );


            renderFrame();
            shader.end();

            pingPong.dst->end();

            pingPong.swap();

	}

}
