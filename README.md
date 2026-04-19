# Unix Shell Implementation (C)

Welcome to my custom Unix shell project! This isn't just a simple command-line interface; it’s a functional terminal environment built from the ground up in C. It handles the "heavy lifting" of the operating system—things like process lifecycles, inter-process communication, and system signals—just like the shells you use every day.

## How It Works (The Workflow)

My shell follows a continuous **REPL (Read-Eval-Print Loop)** cycle to keep things running smoothly:

1.  **Read**: It waits for your input, capturing your commands via `fgets`.
2.  **Parse**: 
    * It breaks your input into manageable "tokens" (commands and arguments).
    * **Smart Expansion**: It automatically spots symbols like `$USER` or `$PATH` and swaps them for actual system values using `getenv`.
3.  **Execute**:
    * **Speed First**: It checks for "Built-ins" like `cd`, `pwd`, or `exit` and runs them instantly without the overhead of forking.
    * **Process Magic**: For everything else, it uses `fork()` to spawn a new process. 
    * **I/O Routing**: It handles the plumbing—managing file descriptors to make sure redirections (`>`) and pipes (`|`) flow exactly where they should.
4.  **Wait**: The shell stays in control, waiting for a task to finish before asking for your next command—unless you send it to the background with `&`.

## Advanced Features

* **Multi-Stage Piping**: Chain as many commands as you want (e.g., `cat file | grep "error" | sort | uniq`). The pipe logic is built to be "infinite."
* **Safety Net (Signal Handling)**: Ever accidentally closed your shell with `Ctrl+C`? Not here. Custom `SIGINT` handling ensures `Ctrl+C` only stops the running task, not the shell itself.
* **Pro I/O Redirection**: Full support for overwriting (`>`), appending (`>>`), and reading from files (`<`).
* **Environment Aware**: It knows your system. It expands environment variables on the fly so your scripts work perfectly.
* **Multitasking**: Use the `&` suffix to run long tasks in the background so you can keep working.

## Inside the Project

* `src/main.c`: The "brain" of the shell—handles the main loop and signal setup.
* `src/parser.c`: The "translator"—turns your text into actionable tokens and expands variables.
* `src/executor.c`: The "engine"—manages process forking and command execution.
* `src/advanced.c`: The "plumber"—where the complex pipe and redirection logic lives.
* `src/builtin.c`: Quick-access logic for internal shell commands.
* `src/shell.h`: The "blueprint"—where all prototypes and definitions are kept.

## Getting Started

Ready to try it out? It’s as simple as:

1.  **Build it**:
    ```bash
    make
    ```
2.  **Fire it up**:
    ```bash
    ./myshell
    ```
3.  **Clean up**:
    ```bash
    make clean
    ```

## Give It a Spin
Try these commands to see the shell in action:

```bash
# Check who you are
echo "Current user is: $USER"

# Pipe some data and save it
cat /etc/passwd | grep "/bin/bash" > bash_users.txt

# Test the signal safety
# Press Ctrl+C while this is running—the shell won't die!
sleep 10
