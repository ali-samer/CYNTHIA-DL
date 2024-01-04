# Cynthia-DL (CYDL)

Welcome to the CYDL library, a powerful tool for your C++ developments in the Cynthia-DL project. Let's dive into how you can get started.

## Installation

To get started with CYDL, clone the repository and set up your environment:
```bash
git clone https://github.com/your-repository/Cynthia-DL.git
cd Cynthia-DL
```
***

> **Note:** It's best to build the documentation when you install the software to learn how to use the API's. We used Sphinx to make it look pretty and easy to navigate.

## Building the Documentation
all you have to do here is build the software like you usually do using cmake:
````bash
mkdir build; cd build
cmake ..
make sphinx-doc
````
that's it, now you can access the documentation through the build dir. 
````bash
open Cynhtia-DL/build/doc/html/index.html
````
