# Use the official Node.js image as the base image
FROM node

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy package.json and package-lock.json to the working directory
COPY package*.json ./

# Install dependencies using npm
RUN npm install

# Copy all files from the current directory to the working directory
COPY . .

# Expose port 8080 for the container
EXPOSE 8080

# Specify the command to run when the container starts
CMD [ "node", "server.js" ]