# Image-Filter-Application

An Application to apply different Filters to different BMPs Images. For now this is limited to gray scale, blur, reflect, edge, sepia.

## Table of Contents

1) [Project Image-Filter-Application overview](#project)
2) [Building Image-Filter-Application](#building)
3) [Running Image-Filter-Application](#usage)
4) [Contribution Guide](https://github.com/Blaze-Stars/Image-Filter-Application/blob/main/CONTRIBUTING.md)

## Project

This project is associated with [Department of Integrated MCA, Utkal University](https://utkaluniversity.ac.in/departments/5-years-integrated-master-in-computer-application/).<br>
Image Filter application is only available in command line application. To know more, here you can read the [whole process](https://drive.google.com/file/d/1GJ7fSOZBK7VxsA8DUD2BaNMYAcl2ceGh/view?usp=share_link) we went through.

## Pre-requisite

1. CMake
2. gcc

## Building

To build `Image-Filter-App`, go to your project directory.

1. Create a build dir
```shell
mkdir build
```
2. Now its time for `cmake` to do configure and generate build files.
```shell
cmake -B build/
```

3. Now its time for `make` to generate executable file. Head inside `build` dir and type.
```shell
make
```
Boom! You have successfully build `Image-Filter-Application`

## Usage

+ Currently `Image-Filter-Application` supports `5 filters`, these filters can be used using the following options below.<br>
+ We have several example Images to test these filters stored in [imgDB](https://github.com/Blaze-Stars/Image-Filter-Application/tree/main/img-db)

| Filters | Flag |
| ------- | ----- |
| GrayScale | g |
| Blur | b |
| Reflect | r |
| Edge | e |
| Sepia | s |

To use any of the filters :
```shell
./filter infile outfile
```
#### Illustration
```
./filter img-db/yard.bmp out.bmp

 FILTER    : OPTION
 ------------------
 Blur        : b
 Edge        : e
 GrayScale   : g
 Reflect     : r
 Sepia       : s

 To QUIT press    : [q]
Enter option :b
Applied Blur filter successfully...
```
You can check out.bmp for Blured Result.

## License
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
