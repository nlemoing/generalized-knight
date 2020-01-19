# Generalized Knights

This is the code that originally served as the inspiration for [this article](https://lemoing.ca/blog/knight.html)! Discussion on [Hacker News](https://news.ycombinator.com/item?id=21914566).

> The idea is this: we replace the normal two-then-one pattern knights have with an a-then-b pattern, 
> where a and b can be any whole number. From now on, when we refer to an (a,b)-knight, we’re referring
> to a knight that takes a steps in any direction and then b steps in a perpendicular direction. Using
> this definition, the original knight is a (2,1)-knight.

This repository contains explorations into what happens when you generalize the movement of knights.

The repo is divided into three sections: `python`, `cpp`, and `web`. 

`python` was the language I used, along with Jupyter notebooks, to quickly prototype and explore different
movement patterns that knights exhibit. Simple BFS and random walk algorithms are implemented and plots are
generated to map the path of the knight.

`cpp` was used to build more customizable, comprehensive maps of the movement. Since I was working with the
C++ OpenCV library for another project, I decided to implement this portion in C++. The program exposes several
options for examining knight walk behaviour by customizing board size, knight type, path type (breadth first or
random) as well as stylistic properties like color and square size. The program can generate either finalized
static images or images at each step of the walk.

`web` contains a web interface that sat in front of the `cpp` program that made using the CLI a bit less tedious.
The original plan was to include this interface as part of the article I was writing, but since my blog is a
static site, I wasn't able to generate images dynamically using a server. This also contains Javascript code for
playing an interactive game with generalized knights which also didn't make it into the final article. I ended up
going a different direction by focusing more on making insightful and good-looking visuals instead. This folder 
also contains an early draft of the article.
