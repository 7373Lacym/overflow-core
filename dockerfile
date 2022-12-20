FROM alpine:latest

# Install build tools and libraries needed for the C TCP server
RUN apk add --update build-base libc-dev

# Copy the source code for the C TCP server into the Docker image
COPY server.c .

# Compile the C TCP server
RUN gcc -o server server.c

# Expose port 8080
EXPOSE 8080

# Run the C TCP server when the Docker container starts
CMD ["./server"]
