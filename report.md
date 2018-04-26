# Plan

## Summary

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

Here is a breakdown of the funcionality needing testing:

## pressing W:

When w is pressed the render does appear to, if the player position isn't against a wall in the forward direction, progress forward.

## pressing A:

When A is pressed the camera does appear to move to the players left. This indicates that the `pos[2]` rotational position is working and properly translating to the change in camera.

## pressing S:

When w is pressed the render does appear to, if the player position isn't backing a wall, progress backward.

## pressing D:

When A is pressed the camera does appear to move to the players left. This indicates that the `pos[2]` rotational position is working and properly translating to the change in camera.

# Reflection

To reflect on my project, I feel it went well.
I learned a significant amount about liner algebra, matrices and Xorg (arguably all three necessary as openGL and SDL manages a significant amount of this for me).
Before I discovered the gluLookAt function creating the view port matrix was rather tricky as I was unfamiliar with this area in mathematics).


