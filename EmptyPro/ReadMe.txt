
The purpose of this project is to provide a template project
for user's own projects. 
Assuming your project is named "MyPro", proceed as follows:

1. Make a directory named "MyPro" and copy to it all files 
and folders from the "EmptyPro".

2. In the ./MyPro/CMakeLists.txt find the line
set( PROJECT_NAME EmptyPro )
and change "EmptyPro" to the name of your project, i.e. "MyPro" in our example
set( PROJECT_NAME MyPro )

3. Copy/create ALL your source files to the ./MyPro/src
and ALL headers to the ./MyPro/include

4. Build your project in accordance with the common scheme (below).

=================================
To build a project do as follows:

1. Depending on your OS change directory to the one:
build_win
build_linux
build_mac

2. Open terminal and set current directory to the above one.

3. type 
cmake ..

4. Go to the build_xxx directory and launch your project.




