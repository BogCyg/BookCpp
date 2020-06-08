
This project depends on sources from the projects Complex & QuadEq.
The tree structure looks as follows:

+ Complex
----src
----include
+ ComplexQuadEq (this one)
----src
----include
+ QuadEq
----src
----include

You do not need to build the Complex & QuadEq. They just need to
be at the same directory level.




To build a project do as follows:

1. Depending on your OS change directory to the one:
build_win
build_linux
build_mac

2. Open terminal and set current directory to the above one.

3. type 
cmake ..

4. Go to the build_xxx directory and launch your project.




