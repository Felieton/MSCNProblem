cmake_minimum_required(VERSION 3.15)
project(MSCNProblem)

set(CMAKE_CXX_STANDARD 14)

add_executable(MSCNProblem src/main.cpp include/MscnProblem.h src/MscnProblem.cpp include/Matrix.h include/Table.h include/ProblemFileReader.h include/ProblemFileWriter.h include/Random.h src/Random.cpp include/RandomSearch.h src/RandomSearch.cpp include/Const.h include/Individual.h src/Individual.cpp include/DiffEvol.h src/DiffEvol.cpp include/Optimizer.h include/Problem.h include/Timer.h)