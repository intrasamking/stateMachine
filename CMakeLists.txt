cmake_minimum_required(VERSION 3.24.2)

project(stateMachine C)

include_directories( include )

set( SOURCES src/main.c src/sensorStateFunctions.c)

add_executable( stateMachine ${SOURCES} )