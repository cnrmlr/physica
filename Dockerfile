FROM ubuntu:20.04

# tzdata confirmation override
ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && apt-get -y upgrade

# we need git to run as dev container
RUN apt-get -y install git 

# install compiler and build stuff
RUN apt-get -y install build-essential cmake clang-tidy clang-format clang 

# install documentation stuff
RUN apt-get -y install doxygen plantuml graphviz 

# other 
RUN apt-get -y install lcov iwyu

# Install gdb
RUN apt-get -y install gdb

# Install conan
RUN apt-get -y install python3 python3-pip && pip install conan

# Clean up to reduce image size
RUN apt-get clean && rm -rf /var/lib/apt/lists/*
