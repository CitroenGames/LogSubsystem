# UE5 Logging Subsystem

This project provides a custom logging subsystem for Unreal Engine 5 that allows developers to log messages to a file during runtime. The logging can be enabled or disabled dynamically through a function that's callable from Blueprints.

## Features

- Dynamically enable or disable logging at runtime.
- Append messages to a log file in the user's platform directory under the project's name.
- Blueprint-callable function for logging.
- Log files are named based on the project name and the Unix timestamp of the game startup.

## Setup

1. Clone this repository into your `Plugins` folder in your Unreal Engine 5 project.
2. Re-generate project files by right-clicking on your `.uproject` file and selecting "Generate Visual Studio project files".
3. Build the project in your preferred IDE (e.g., Visual Studio).

## Usage

To log a message to the file:

```cpp
GetSubsystem<ULoggingSubsystem>()->LogToFile("Your log message");
```

Or, from Blueprint:

```plaintext
GetSubsystem -> LogToFile
```

To enable or disable logging at runtime:

```cpp
GetSubsystem<ULoggingSubsystem>()->SetLoggingEnabled(true);
```

Or, from Blueprint:

```plaintext
GetSubsystem -> SetLoggingEnabled
```

Note: Logging is disabled by default for runtime.
