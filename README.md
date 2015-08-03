# Opulence Graphics Engine

## Dependencies ##
* CMake 2.8
* Google Test 1.7.0
* SDL 2.0
* OpenGL 3.3
* GLSL 1.3
* OpenGL Extension Wrangler Library 1.6 (GLEW)
* OpenGL Mathematics Library 0.9.6 (GLM)

## Usage

###Google Test Installation
#### Ubuntu
* cd /test/gtest-(version number)
* sudo cmake .
* sudo make
* sudo mv libg* /usr/lib
* sudo apt-get install libgtest-dev

```c++
#include "opulence/opulence.cpp"

int main()
{
	Opulence opulence;
	opulence.start();

    // responsible for memory management
	ModelFactory *mf = opulence.getModelFactory();
	CameraFactory *cf = opulence.getCameraFactory();

	mf->setObjSource(/*** obj models path relative to the opulence folder ***/);
	mf->addObj(/*** obj file name without file extension (eg: hello.obj => hello) ***/);
	mf->makeModel(0, 0, 0, /*** obj file name without the file extension ***/);

    // the only available camera is RtsCamera currently
    RtsCamera *camera;
    cf->setMainCamera(cf->makeCamera(glm::vec3(0.0, 3.0, 10.0), camera));

    // main loop
    while (!quit) {
        // get input

        // do whatever else

        opulence.render();

    }

    // to run all of opulence's unit tests
    if (you want to run tests) {
        // run all them tests
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        // return as usual
        return 0;
    }
}
```

In the file CMakeLists.txt in your opulence folder
```CMake
// change the line with this
set_source_files_properties(../main.c opulence.cpp PROPERTIES LANGUAGE CXX )

// put the main file that you are using when including opulence by replacing yourMainFile.c
set_source_files_properties(../yourMainFile.c opulence.c PROPERTIES LANGUAGE CXX)

// also change the line
set(SOURCE_FILES
	../main.c
	opulence.c)

// do the same change again
set(SOURCE_FILES
	../youMainFile.c
	opulence.c)
```

###### Please note that this engine is changing fast; thus, this 'usage' section will change frequently
