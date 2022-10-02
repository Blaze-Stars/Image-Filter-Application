# Image-Filter-Application
### `An Application to apply different Filters to different BMPs Images`
## Table of Contents

1) [An overview](#project)
2) [Building Image-Filter-Application](#building)
3) [Running Image-Filter-Application](#running)
4) [Contribution Guide](https://github.com/Blaze-Stars/Image-Filter-Application/blob/main/CONTRIBUTING.md)

## Project

This project is associated with the Department of Integrated MCA, Utkal University, Bhubaneshwar, Odisha.<br>
This is a command line application.<br>

## Pre-requisite

To build `Image-Filter-App` make sure To install `make` in your System and `g++` compiler.<br>
`make` installation in windows -> [link](https://www.technewstoday.com/install-and-use-make-in-windows/)<br>
`make` installation in Ubuntu -> [link](https://askubuntu.com/questions/161104/how-do-i-install-make) 
## Building

To build `Image-Filter-App`, go to your project directory and open your `Terminal` and type.
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
./filter
```
## License
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.
