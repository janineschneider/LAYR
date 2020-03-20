cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -O0")

project(layr)

SET(HEADER
##Header files
    ##Additionals
    getworkingdir.h

    ##Stream
    bytecontainer.h

    ##Exceptions
    customexception.h

    ##Basics
    heuristic.h
    parallel.h

    ##Operators
    SequentialOperators/seqcomp.h
    SequentialOperators/or.h
    ParallelOperators/union.h
    ParallelOperators/intersection.h
    ParallelOperators/minus.h

    ##Heuristics
    Heuristics/DOS/dos.h
    Heuristics/Ext3/ext3.h
    Heuristics/Failure/failure.h
    Heuristics/AddResults/addresults.h
    Heuristics/Input/input.h
)

SET(SOURCES
##Source files
    ##Stream
    bytecontainer.cpp

    ##Opertors
    SequentialOperators/seqcomp.cpp
    SequentialOperators/or.cpp
    ParallelOperators/union.cpp
    ParallelOperators/intersection.cpp
    ParallelOperators/minus.cpp

    ##Heuristics
    Heuristics/DOS/dos.cpp
    Heuristics/Ext3/ext3.cpp
    Heuristics/Failure/failure.cpp
    Heuristics/AddResults/addresults.cpp
    Heuristics/Input/input.cpp

    ##Tests
    #Tests/test_dos.cpp
    #Tests/test_ext3.cpp
    #Tests/test_or.cpp
    #Tests/test_seqComp.cpp
    Tests/test_setops.cpp
)

add_executable(${PROJECT_NAME} ${HEADER} ${SOURCES})
