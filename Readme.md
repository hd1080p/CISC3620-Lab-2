# Lab 2: Draw a house

## Due date: Thurs. 2/16

Like last time, 1 point extra credit will be awarded for completed assignment or pull request fixing error before Thurs. 2/9

Extra credit will also be given for opening and especially answering issues on the original repository.

## Summary

The startup code for this lab follows the learnopengl tutorial and draws a triangle. You will change the code to draw a 2d shape (such as a house) made of at least three triangles.

## Getting started

The steps here will be the same as [last time](https://cisc3620.github.io/docs/submissions.html). 

1. Clone this repository to make a local copy on your machine.

2. Run cmake from the Build directory to generate a project file for your platform.

3. Compile and run.
   You should see an orange triangle with a gray background.

## Modify

Open main.cpp for editing. 

* Instead of a triangle, draw a shape (such as a house) made of at least three triangles.

* Instead of setting a single uniform color in the fragment shader, specify a color for each vertex and pass it to the fragment shader.

## Submit

[Same as last time.](https://cisc3620.github.io/docs/submissions.html)

**In addition**, execute the program, save the image that's created (using a screenshot tool), and move the image into the top level of your repository.

Your add command will be 

```git add main.cpp img.png```

I will look at the code you've changed in main and your generated image.
