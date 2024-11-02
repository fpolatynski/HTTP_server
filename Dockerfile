# Use an official Linux distribution with GCC installed
FROM gcc:latest

EXPOSE 9002

# Set working directory inside the container
WORKDIR /app

# Copy the project files into the container
COPY . .

# Install any additional dependencies if required
# RUN apt-get update && apt-get install -y <dependencies>

# Compile the project using the Makefile
RUN make

# Set the default command to execute the compiled program
CMD ["./build/main"]