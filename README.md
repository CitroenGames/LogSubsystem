# UE5 Logging Subsystem

This project provides a custom logging subsystem for Unreal Engine 5 that allows developers to log messages to a file during runtime. The logging can be enabled or disabled dynamically through a function that's callable from Blueprints, or it can be changed in the game's settings.

## Features
- Dynamically enable or disable logging at runtime via both code and game settings.
- Append messages to a log file in the user's platform directory under the project's name.
- Blueprint-callable functions for logging and setting the logging state.
- Log files are named based on the project name and the Unix timestamp of the game startup.

## Setup
- Clone this repository into your Plugins folder in your Unreal Engine 5 project.
- Re-generate project files by right-clicking on your .uproject file and selecting "Generate Visual Studio project files".
- Build the project in your preferred IDE (e.g., Visual Studio).

## Usage
To log a message to the file:

```cpp
GetSubsystem<ULoggingSubsystem>()->LogToFile("Your log message");
```

Or, from Blueprint:

```
GetSubsystem -> LogToFile
```

To enable or disable logging at runtime:

```cpp
GetSubsystem<ULoggingSubsystem>()->SetLoggingEnabled(true);
```

Or, from Blueprint:

```
GetSubsystem -> SetLoggingEnabled
```

To check if logging is enabled:

```cpp
bool bIsLoggingEnabled = GetSubsystem<ULoggingSubsystem>()->IsLoggingEnabled();
```

Or, from Blueprint:

```
GetSubsystem -> IsLoggingEnabled
```

Note: Logging is disabled by default and can be changed in the game's settings.

## Contributions
Contributions are welcomed! To contribute:

- Fork the project.
- Create your feature branch: `git checkout -b feature/my-new-feature`
- Commit your changes: `git commit -am 'Add some feature'`
- Push to the branch: `git push origin feature/my-new-feature`
- Submit a pull request.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
