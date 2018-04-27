# Plan

## Summary 

Since Herodotus' account of the Egyptian Labyrinth in the 5th century BC mazes have been a recurring aesthetic theme in both architecture and design.
But I believe mazes to be so much more than aesthetic, they so neatly encapsulate the human spirit for adventure, providing a microcosm in which to explore the manor in which we move through, and interact with, space.
I wanted to investigate how this translates into cyber-space, that is the intersection between a physical maze and the virtual.
If the physical maze is a microcosm for our material experience, then this most basic and historic structure in cyber-space could surely be a reflection our computing experience.

In the seemingly endless turmoil of modernity and it's vast and oddly inconsequential complexity we seek, possibly in vein, to find meaning, purpose and truth.
These very human traits don't necessarily translate into the binary, the indifferent nature of the machine, but regardless we are compelled to strive for the machine to grant us meaning, purpose and truth.

A higher understanding of our position in relation to this, our daunting new world, is greatly important in the quest for meaning.
To this end I have created a maze, In it's apparent simplicity it provides a complex allegory for our modern transcendent existence.
It is left to the user to fine meaning and purpose in the maze's desolate and isolating environment, to reflect on the existential immaterial nature of our virtual lives.

The trapped perspective and construction of the maze is a design to enable the user to experience the trapping confines of our highly interconnected presence.
It's meaninglessness, a ploy to empower the user into realising their subconscious entrenchment in this brave new world of youtube and facebook.

In summary, I hope to inspire self reflection and introspection as the user navigates my world, created at random, and try to understand their dependence on the machine.

---------------------

I chose to do the SDL task in order to learn more about the OpenGL.
Within this I decided to go for a more interactive artistic project than actual game.

The plan is to make a maze, rendered in 3D. It's an exercise in OpenGL and an artistic project.
The final plan is to have a maze with the ability to move within the maze using wasd.

## Large Scale

On a large scale this software requires three major components.

1. First is a maze generator and associative data structures

2. Second is the renderer, that is a system to render the maze in 3D

3. Third is the necessary SDL code to create windows and create the OpenGL context.

## Medium Scale

On the medium scale, I plan to implement the maze generator using a recursive back tracking algorithm.
This is as a result of reading a blog post from this chap: http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking who wrote a similar maze generator in ruby.

1. Choose a starting point in the field.

2. Randomly choose a wall at that point and carve a passage through to the adjacent cell, but only if the adjacent cell has not been visited yet. This becomes the new current cell.

3. If all adjacent cells have been visited, back up to the last cell that has uncarved walls and repeat.

4.  The algorithm ends when the process has backed all the way up to the starting point.

To test that this works I wrote a simple render of the maze using SDLs built in 2D renderer.
This is arguably the simplest implementation of my maze.

Next I'll implement the 3D renderer for the maze and test this.

I will then proceed to add two perspectives for my maze, a first person one and third person one.
The test for this is, again, to run the program and check it all looks OK.

Next I will implement keyboard input and ensure this works properly.

Finally I will implement a system to add 'rooms' to my maze.
These open areas make the maze significantly more interesting.

# Testing

In order to test this I will run and analyse the multiple iterations of the code. `test_maze.c` was written to test the maze generator without the 3D aspect.
The simplest test for this, and the subsequent 3D graphics is to simply run it and ensure that it looks correct.
Thus this was done as the program was iteratively improved

# Schedule

The schedule was a little messy for this project, this is primarily due to it being set so late and family events which prohibited me from really sinking my teeth into it. Thus I only had around 3-4 full days to complete it.

## Day 1:

Get the maze generation working
This was tested using the 2D SDL renderer.

## Day 2:

Begin to learn how OpenGL works and write some initial experimental code to get used to the API.
My OpenGL was tested in the 3D objects and animation I was able to render.

## Day 3:

Render the maze in OpenGL.
Which was tested through looking at what was being rendered.

## Day 4:

Make a moveable camera incorporating first person and 3rd person modes and WASD controls.
Which was tested by interacting with the model.

# Test outcomes

All of my tests were fairly successful and came back without too many errors or bugs.
Any bugs found were corrected.
For visual demonstration of what the tests looked like please compile and view the render and interact with it using WASD and F5 to change perspective.

Here is a breakdown of the functionality needing testing:

## pressing W:

When W is pressed the render does appear to, if the player position isn't against a wall in the forward direction, progress forward.

## pressing A:

When A is pressed the camera does appear to move to the players left. This indicates that the `pos[2]` rotational position is working and properly translating to the change in camera.

## pressing S:

When S is pressed the render does appear to, if the player position isn't backing a wall, progress backward.

## pressing D:

When D is pressed the camera does appear to move to the players left. This indicates that the `pos[2]` rotational position is working and properly translating to the change in camera.

## pressing F5:

Upon the pressing of F5 the perspective will change, it will switch between a top down perspective and a first person perspective.
This, when tested, also worked perfectly and successfully.

## The render

The maze successfully renders and displays the requisite walls and spaces to lead me to believe that the software works in full.
The SDL window is successfully created and the SDL keystroke events are clearly recognised.

Little went wrong during the making of this project and the development went smoothly and quickly and other than one or two cases in which one could walk through walls it all went quite well.
I utilised git to allow me to experiment with my code safe in the knowledge that I can roll back my commits to a working version.

# Reflection

To reflect on my project, I feel it went well.
I learned a significant amount about liner algebra, matrices and Xorg (arguably all three necessary as openGL and SDL manages a significant amount of this for me).
Before I discovered the gluLookAt function creating the view port matrix was rather tricky as I was unfamiliar with this area in mathematics).

I will admit, time management was a little bit of a problem.
None of the set tasks really engaged me particularly, with their annoying (and I would argue unnecessary) limitations, and thus finding the motivation to get the job done was rather hard.

I really love C programming because, unlike the child friendly languages of today such as Java and python, I feel far more as if I am programming a computer rather than programming another program.
It's closeness to the physical machine and lack of unnecessary verbosity really lends to an experience similar to writing assembly without the ridiculous amount of time it takes to do menial tasks.
The unsafeness of C I think is seen by my colleges as an annoyance, but to me I see it as a great asset.
The gloves are off and I am able to manage memory in the way I want to manage memory and not have some garbage garbage collector parasite running along side my program.
