Trash Simulator 9000000
=======================  
An interactive game with a trash can and throwable trash.

***by Team Girafficks*** *(aka Daniel Smith, Jake Shepard, and Tyler Goffinet)*

```
           A--A
       .-./   #\.-.
      '--;d    b;--'
         \# \/  /
          \'--'/
           |==|
           | #|
           |# |
          /   #\
         ;   #  ;
         | #    |
        /|  ,, #|\
       /#|  ||  | \
   .-.'  |# ||  |# '.-.
  (.=.),'|  ||# |',(.=.)
   '-'  /  #)(   \  '-'
    jgs `""`  `""`
 ```

Overview
--------

As a mentally drained, run-down, depressed, dreary, severity bored office worker you must, in order to save your sanity, shoot some sweet crumpled trash shots.

Taking advantage of the power of **OpenGL, SDL, Assimp, and Bullet Physics**, our team created an interactive game where the user must throw a crumpled piece of paper into a trash can. The setting of the game takes place in a run-of-the-mill office setup with cubicles and dull colors.

**Ambient lighting** implemented by custom shader programs fill the environment. In addition, textures provide the drab emotions of the typical office worker. **Physics collisions** with the crumpled ball of paper (e.g. rolls off desk, bounces off trash can, etc.) provide a realistic representation of desk objects and allow the goal of the game to be visualized.

![Screenshot](https://github.com/qubytes/TrashSim9M/blob/Actual/pics/screenshot_overview.png)

How to Run (Linux)
------------------
* Install cmake
* Install dependencies
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev imagemagick libassimp-dev libbullet-dev
```
* Create new 'build' directory
```bash
mkdir build
cd build
```
* Compile
```bash
cmake ..
make
```
* Run
```bash
./TrashSim9M
```
* Enjoy! *(Use control scheme below)*

How to Run (Mac)
----------------
* Install dependencies with [Brew](https://brew.sh/)
```bash
brew install glew glm sdl2 imagemagick assimp bullet
```
* Create build directory
```bash
mkdir build
cd build
```
* Make Xcode project
```bash
cmake -G Xcode ..
cp -R ../models .
cp -R ../shaders .
cp -R ../textures .
```
* Open [Xcode](https://developer.apple.com/xcode/) project
```bash
open TrashSim9M.xcodeproj
```
* Edit Working Directory
  - Go to Product > Scheme and tick 'TrashSim9M'
  - Go to Product > Scheme > Edit Scheme... > Run *(side tab)* > Options *(top tab)* and select 'Use custom working directory' and browse to the build directory for this project
* Run with Play arrow
* Enjoy! *(Use control scheme below)*

Control Scheme
--------------
### Window controls ###
<kbd>Esc</kbd> Exit program

### Game controls ###
Use the mouse to throw the ball! Click and hold the left mouse button while swinging the mouse in the direction you want to throw. Release the left mouse button to launch the ball!

<kbd>P</kbd> Pause game  
<kbd>R</kbd> Reset the ball in case it gets stuck  
<kbd>\\</kbd> Toggles cheats. Allows you to adjust the ball mid air in the same way you throw the ball.

#### Pro Tip! ####
> The faster you throw the ball, the farther it goes!
#### Extreme Tip! ####
> If the front screen is stuck. Restart game and wait 2 *whole* seconds before clicking.

### Lighting controls ###
<kbd>V</kbd> Toggle between lighting-per-vertex and lighting-per-fragment

<kbd>Q</kbd> Increase ambient lighting  
<kbd>A</kbd> Decrease ambient lighting  
<kbd>W</kbd> Increase specular lighting  
<kbd>S</kbd> Decrease specular lighting

<kbd>↑</kbd> Move light up  
<kbd>↓</kbd> Move light down  
<kbd>←</kbd> Move light left  
<kbd>→</kbd> Move light right
