# Contributing

Thank you for your interest in contributing to the University Management System. Contributions of all kinds are welcome, including bug reports, feature suggestions, documentation improvements, accessibility fixes, and code changes.

## Code of Conduct

Be respectful, constructive, and inclusive in all project discussions. Critique code and ideas without attacking people. Harassment, discrimination, and personal attacks are not acceptable.

## Before You Start

- Check the existing issues and pull requests to see whether someone is already working on the same change.
- For a large feature or a change to the data model, open an issue first to discuss the proposed approach.
- Keep each pull request focused on one problem or feature.
- Do not include unrelated changes in a pull request.

## Report a Bug

When reporting a bug, include:

- A clear description of the problem.
- The steps needed to reproduce it.
- What you expected to happen.
- What happened instead.
- Your operating system, compiler, Qt version, and build method.
- Relevant error messages, logs, or screenshots.

Remove personal information, passwords, database contents, and other sensitive information before sharing logs or screenshots.

## Suggest a Feature

When suggesting a feature, describe:

- The problem it would solve.
- Who would use it.
- How you expect it to work.
- Any relevant constraints or examples.

For large features, discuss the design in an issue before starting implementation.

## Development Setup

The application is written in C++17 and uses Qt 6, SQLite, and OpenSSL. CMake is the recommended build system.

### Linux dependencies

On Debian or Ubuntu, install the required packages with:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake qt6-base-dev libsqlite3-dev libssl-dev
Configure and build
Run these commands from the repository root:
cmake -S . -B build
cmake --build build --parallel
Run the application
./build/university_system
Run the Tests
After making a change, run the project tests:
ctest --test-dir build --output-on-failure
If you cannot run a test, explain why in your pull request and describe any other checks you performed.
Code and Documentation Guidelines
- Follow the existing C++17 and Qt patterns in the codebase.
- Use clear names and keep functions focused on one responsibility.
- Validate user input and show actionable error messages.
- Keep the interface usable at different window sizes.
- Consider readability, keyboard navigation, and accessibility when changing the GUI.
- Do not store passwords in plain text.
- Keep authentication and authorization checks in application logic; hiding a button alone is not access control.
- Use prepared statements for database queries.
- Update documentation when changing setup steps, user-visible behavior, or data handling.
- Do not commit build output, generated binaries, local database files, credentials, or personal data.
Pull Requests
Before submitting a pull request:
1. Build the application.
2. Run relevant tests.
3. Review your diff and remove unrelated changes.
4. Update documentation when needed.
In the pull request description, explain:
- What changed.
- Why the change is needed.
- How you verified it.
- Any known limitations or follow-up work.
Use a concise, descriptive pull request title, such as:
- Fix residence room validation
- Improve student registration dialog
- Add account password reset
Use clear commit subjects that describe the change, such as:
- Fix residence room validation
- Add student account login
- Document CMake dependencies
