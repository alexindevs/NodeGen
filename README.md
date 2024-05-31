# NodeGen

## Introduction

NodeGen is a command-line tool that simplifies the setup process for Node.js projects by generating boilerplate code for popular frameworks like ExpressJS, ExpressJS with Typescript, and NestJS.

## Inspiration

NodeGen was inspired by the need to streamline the initial setup of Node.js projects. As a passionate software engineer, I often found myself spending valuable time configuring project structures and dependencies. NodeGen aims to automate this process, allowing developers to focus more on building their applications rather than setting up the project environment.

## Features

- Generates boilerplate code for ExpressJS, ExpressJS with Typescript, and NestJS.
- Simplifies the setup process by automating the creation of project directories and configuration files.
- Provides a user-friendly interface for selecting the desired framework.

## Installation

To use NodeGen, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/alexindevs/NodeGen.git
   ```

2. Navigate to the project directory:

   ```bash
   cd NodeGen
   ```

3. Compile the project:

   ```bash
   find . -name "*.c" -exec gcc {} -o NodeGen \;
   ```

4. Add the project directory to your system's PATH to make NodeGen executable from anywhere. Edit your shell configuration file (`~/.bashrc`, `~/.bash_profile`, `~/.zshrc`, etc.) and add the following line:

   ```bash
   export PATH="$PATH:/path/to/NodeGen/"
   ```

   Replace `/path/to/NodeGen/` with the actual path to the NodeGen directory on your computer.

5. Reload the shell configuration:

   - For Bash:

     ```bash
     source ~/.bashrc
     ```

   - For Zsh:

     ```bash
     source ~/.zshrc
     ```

## Usage

After installation, you can use NodeGen by running the `NodeGen` command followed by the desired options. For example:

```bash
NodeGen
```

Follow the on-screen instructions to select the framework and set up your project.

## Feedback

If you have any feedback, suggestions, or issues with NodeGen, feel free to [open an issue](https://github.com/alexindevs/NodeGen/issues) on GitHub.

## About the Author

I'm Alexin, a passionate software engineer with a knack for crafting tools that solve real-world problems. You can find more of my projects and contributions on [GitHub](https://github.com/alexindevs).
