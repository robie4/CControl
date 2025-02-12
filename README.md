# CControl

CControl is a library written in 100% C code. No external libraries and 100% platform independent.
The purpose with this library is to fit advanced tools for really small embedded systems or desktop as well.
Here I have focused on practical numerical methods and selected the methods that works best in practice. It has
been a lot of work finding the best methods and best algorithms.

Many examples can be found in the scr folder.

- Artificial Intelligence
  - Astar algorithm for quick path finding
  - Point-in-polygon algorithm for checking if a point is inside the area
  
- Control Engineering
  - Kalman filter update
  - Linear Quadratic Integral regulator
  - Model predictive Control
  - Model Reference Adaptive Control
  - Transfer function to state space
  - Stability check
  - Continuous to discrete
  - Comming soon: Nonlinear Model Predictive Control

- Filtering
  - Monte Carlo Simulation
  - Comming soon: Particle filter
  - Filtfilt 
  - Square Root Unscented Kalman Filter
  
- Linear Algebra
  - Balance matrix
  - Cholesky decomposition
  - Cholesky update
  - QR decomposition
  - LUP decomposition
  - Determinant
  - Discrete Lyapunov solver
  - Eigenvalues symmetric + Eigenvectors
  - Random real eigenvalues and random imaginary eigenvalues
  - Hankel matrix
  - Inverse
  - Pseudo inverse
  - Linear solver
  - Nonlinear solver
  - Multiplication
  - Singular Value Decomposition Golup Reinsch
  - Singular Value Decomposition Jacobi One Sided
  - Transpose
  - Matrix sum
  - Norm
  - Matrix exponential

- Miscellaneous
  - Concatenate
  - Cut matrix
  - Insert sub matrix into matrix
  - Print matrix or vector
  - Saturation
  - Sign
  - Randn
  - Mean
  - Standard deviation
  - Value min
  - Value max
  
- Optimization
  - Linear programming maximization
  - Linear programming minimization

- System Identification
  - Observer Kalman Filter identification
  - Eigensystem Realization Algorithm
  - Recursive Least Square with forgetting factor and kalman filter identification
  - Square Root Unscented Kalman Filter for parameter estimation

### How the project is structured

This project is structured as

 - No malloc, calloc or free - No dynamic memory allocation in other words
 - Use pointers as much as you can
 - Use "valgrind --tool=exp-sgcheck ./CControl" to check if your output in Debug folder is correct. For windows users, `Dr.Memory` works too
 - Main focusing on: Control engineering, linear algebra, optimization, AI algorithms, system identification and classification

# How to help to build on this library

Find a good pratical function that always comes in handy. An algorithm for example. When you writing your code, remember these steps:

 - `1D` arrays are only allowed. When you are indexing an `1D`, then you using `my_array[i*column_length + j]` where `i` is row index and `j` is column index and `column_length` is column length of `my_array`
 - Only `floats` are allowed because some processors don't have `double` implemented
 - `C99` standard is only allowed because I want it to follow `MISRA C` standard
 - Your code must come with an example
 - Write `clean code`, that means no slack variables, don't try to compute everything in one single functions, minimize input arguments if it's possible, focus on practical implementation, focus on memory

# Fan Controller with Linear Quadratic Integral Control

I have created a controller for a fan. The controller works as it read the temperature sensor and it compare the temperature sensor with the potentiometer, which is the reference set point. If the error is large between the temperature sensor and the potentiometer, then the fan is going to turn on high, or low, depending on if the error is negative or positive. 

The goal with this system is that I'm going to implement this on a heat source. The fan is going to blow warm air onto a object and the object is holding the temperature sensor. If the fan is blowing to much warm air, then the controller is going to turn down the speed of the fan so the temperature of the object meets the reference

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Fan%20Controller/System.jpg)

I have been using Matavecontrol and Mataveid to estimate and creating the kalman gain matrix and the LQR control law with integral action. I'm the author of both Matavecontrol and Mataveid.

Identification process. Here I have using the Observer Kalman Filter Identification and Eigen System Realization methods.

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Fan%20Controller/Identification%20and%20simulation/Identification.png)

Simulation process:

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Fan%20Controller/Identification%20and%20simulation/Simulation.png)


# Model Predictive Integral Temperature Controller

This is a Model Predictive Controller, with integral action. It uses linear programming instead of quadratic programming for the optimization. This controller works well.

This predictive controller have a wiring diagram if you want to build the same controller for your temperature project.

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Temperature%20Controller/IMPC.jpg)

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Temperature%20Controller/IMPC2.jpg)

Step answer of first order model.

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Temperature%20Controller/Step%20answer%20-%20First%20order.png)

# Model Reference Adaptive CAN-bus controller

This is a MRAC project, Model Reference Adaptive Controller. This controls the a Sonceboz stepper motor with CAN-bus J1939-21 protocol. The purpose is to control a big wheel with two multivariable hydraulical valves.

See the movie in the project folder. 

Library for SAE J1939 https://github.com/DanielMartensson/Open-SAE-J1939

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/Stepper%20Motor%20Controller/Picture%20CAN-bus.jpg)


# Square Root Uncented Kalman Filter for state estimation and parameter estimation

This is the latest Uncented Kalman Filter. MATLAB is using the same algorithm. A `.m` file is available at the `SR-UKF` folder.

For state estimation

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/SR-UKF/sr-ukf-state-estimation.png)

For parameter estimation

![a](https://raw.githubusercontent.com/DanielMartensson/CControl/master/Projects/SR-UKF/sr-ukf-parameter-estimation.png)