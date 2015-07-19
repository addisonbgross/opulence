# Opulence Graphics Engine

## Dependencies:
* OpenGL 3.3
* GLSL 1.3
* OpenGL Extension Wrangler Library 1.6 (GLEW)
* OpenGL Mathematics Library 0.9.6 (GLM)

## Usage:

```c++
#include "opulence/opulence.cpp"

// wherever you decide to begin
Opulence opulence;
opulence.start();

ModelFactory *mf = opulence.getModelFactory();
mf->setObjSource(/*** the directory where you store obj models, relative to the opulence folder ***/);
mf->addObj(/*** the obj filename without the file extension (eg: hello.obj => hello) ***/);
mf->makeModel(0, 0, 0, /*** obj filename without the file extension ***/);

opulence.loop();
```

Please note that this engine is changing fast; thus, this 'usage' section will change frequently
