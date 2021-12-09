# ft_linear_regression

  The aim of this project is to introduce you to the basic concept behind machine learning.
For this project, you will have to create a program that predicts the price of a car by
using a [linear function](https://en.wikipedia.org/wiki/Linear_function) train with a [gradient descent algorithm](https://en.wikipedia.org/wiki/Gradient_descent).

  We will work on a precise example for the project, but once you’re done you will be
able to use the algorithm with any other dataset.

### necessary libraries

[Eigen](https://eigen.tuxfamily.org/)
```
for MAC_OS:  
   brew install eigen
```

[Boost](https://www.boost.org/)
```
for MAC_OS:  
   brew install boost
```

### compilation
```
file the "./CmakeList.txt"  file is needed for indexing the project in Clion

in Clion:

1.  To start training the model
    execute "trainModel" target
    
2.  Predict price
    execut "predict" target
    
in Terminal:

1. 
    mkdir trainModel/build/
    cd trainModel/build
    cmake ../
    make
    ./trainModel

2. 
    mkdir predict/build/
    cd predict/build
    cmake ../
    make
    ./predict
```

### visualiation
```
python3 visualization_in_python/main.py
```
