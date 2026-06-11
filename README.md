# Movie Streaming Database 🎬

C++ program that manages a movie streaming service database, processing movies, users, and viewing history using arrays of structs and a command-driven interface.

## Features
- Reads and stores movies, users, and view history from data files
- Find movies and users by ID or username
- Display user viewing history with dates and ratings
- Identifies most watched and unwatched movies
- Filters movies by genre
- Calculates average ratings per movie and per user
- Command-driven execution via a commands file

## Tech Stack
C++ · File I/O · Structs · Arrays

## 🚀 Run
```bash
g++ main.cpp -o streaming
./streaming
```

Ensure `Movies.txt`, `Users.txt`, `ViewHistory.txt`, and `Commands.txt` are in the same directory.
