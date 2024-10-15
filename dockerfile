# Use an official GCC image as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/app

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Install CMake
RUN apt-get update && apt-get install -y cmake

# Create a build directory
RUN mkdir -p build

# Set the working directory to the build directory
WORKDIR /usr/src/app/build

# Run CMake to configure the project
RUN cmake ..

# Build the project
RUN make

# Expose the port the app runs on
EXPOSE 18080

# Run the application
CMD ["./hotel"]