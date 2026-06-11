//816044402 
//DILLON GANPAT 
//COMP 1602- ASSIGNMENT #1
//DR. MOHAN'S GROUP 


#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// Maximum number of records
const int MAX_MOVIES = 100;
const int MAX_USERS = 100;
const int MAX_HISTORY = 500;


// Struct Definitions
struct Date {
    int day;
    int month;
    int year;
};



struct Movie {
    string movieID;
    string title;
    string genre;
    string director;
};



struct User {
    int userID;
    string userName;
    string subscriptionType;
};



struct ViewHistory {
    int userID;
    string movieID;
    Date viewDate;
    int rating;
    
    
};




//Functions required
void displayDate(Date date) {
    cout << date.day << "/" << date.month << "/" << date.year;
}







void displayMovie(Movie movie) {
    cout << "Movie ID: " << movie.movieID << endl;
    cout << "Movie Title: " << movie.title << endl;
    cout << "Movie Genre: " << movie.genre << endl;
    cout << "Director: " << movie.director << endl << endl;
}








void displayUser(User user) {
    cout << "User ID: " << user.userID << endl;
    cout << "Username: " << user.userName << endl;
    cout << "Subscription: " << user.subscriptionType << endl << endl;
}









int readMovies(Movie movies[]) {
    ifstream inputFile("Movies.txt");
    if (!inputFile.is_open()) {
    	cout << "Error opening movies file. Aborting ...";
        return 0;
    }

	    cout << "Reading data from Movies file... " << endl;


	int count=0; 
    string movieTitle, movieGenre, movieID,  movieDirector;

    inputFile >> movieID;
    
	    
	    while (movieID != "END") {
	        inputFile >> movieTitle >> movieGenre >> movieDirector;
	
	        movies[count].movieID = movieID;
	        movies[count].title = movieTitle;
	        movies[count].genre = movieGenre;
	        movies[count].director = movieDirector;
	
	        count= count +1; 
	        inputFile >> movieID;
	    }
	    
    cout << "-> Data for " << count << " movie(s) read."<< endl;
    cout << endl; 

    inputFile.close();
    
    return count;
}








int readUsers(User users[]) {
    ifstream inputFile("Users.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening users file. Aborting ...";
        return 0;
    }
    
        cout << "Reading data from Users file..." << endl;


    int count, userID;
    
    count=0; 
    
    string username;
	string subscriptionType;

	    inputFile >> userID;
	    while (userID != 0) {
	        inputFile >> username >> subscriptionType;
	
	        users[count].userID = userID;
	        users[count].userName = username;
	        users[count].subscriptionType = subscriptionType;
			count= count +1; 
			
	        inputFile >> userID;
	    }


    cout << "-> Data for " << count << " user(s) read." << endl;
    cout << endl; 
    inputFile.close();
    return count;
}





int readViewHistory(ViewHistory history[]) {
    ifstream inputFile("ViewHistory.txt");
    
    if (!inputFile.is_open()) {
        cout << "Error opening input file. Aborting... " << endl;
        return 0; 
    }
	    cout << "Reading data from ViewHistory file..." << endl;


    int count = 0;
	
	char slash; 
	
    inputFile >> history[count].userID;
    
    while (history[count].userID != 0) {
    	
        inputFile >> history[count].movieID;
        inputFile >> history[count].viewDate.day;
        
   		inputFile >> slash;
    
        inputFile >> history[count].viewDate.month;
        
    	inputFile >> slash; 
    
        inputFile >> history[count].viewDate.year;
        
        inputFile >> history[count].rating;

        count= count +1; 
        inputFile >> history[count].userID;
    }

    cout << "-> Data for " << count << " view histories read." << endl;
    cout << endl; 

    inputFile.close();
    return count;
}




int findMovie(Movie movies[], int numMovies, string movieID) {
    for (int i = 0; i < numMovies; i=i+1) {
        if (movies[i].movieID == movieID)
            return i;
    }

    cout << endl << "[Error] Movie " << movieID << " does not exist." << endl; 
	cout << endl; 
	
    return -1;
}









int findUser(User users[], int numUsers, string userName) {
    for (int i = 0; i < numUsers; i= i+1) {
        if (users[i].userName == userName)
            return i;
    }

    cout << endl << "[Error] User " << userName << " does not exist." << endl << endl;
    return -1;
}








bool findMovieView(ViewHistory history[], int numViews, string movieID) {
    for (int i = 0; i < numViews; i=i+1) {
    	
        if (history[i].movieID == movieID)
            return true;
    }
    return false;
}





int totalMovieViews(ViewHistory history[], int numViews, string movieID) {
    int movieviews = 0;
    for (int i = 0; i < numViews; i=i+1) {
        if (history[i].movieID == movieID) {
            movieviews= movieviews +1;
        }
    }
    

   if (movieviews == 0) {
    cout << "Movie was not watched." << endl;
        return -1;
    }
    return movieviews;
}





void displayAllUnwatchedMovies(Movie movies[], int numMovies, ViewHistory history[], int numViews) {
    for (int i = 0; i < numMovies; i=i+1) {
    	
    	
    	//for this part, if a movie doesnt have views, i called the display movie function instead of having to write the 4 cout statements and redeclare stuff
        if (!findMovieView(history, numViews, movies[i].movieID)) {
            displayMovie(movies[i]);     
            
        }
    }
}





void displayUserHistory(ViewHistory history[], int numViews, int userID) {
    bool found = false;
    
    
    for (int i = 0; i < numViews; i=i+1) {
        if (history[i].userID == userID) {
            cout << "- " << history[i].movieID << " on ";
            displayDate(history[i].viewDate); 
            cout << ", Rated: " << history[i].rating << endl;
            
            
            //if rating=0 then the person didnt rate the movie
            if (history[i].rating== 0) {
            	cout << "(Not Rated)" << endl; 
			}
            found = true;
        }
    }
    if (!found) {
        cout << "No viewing history found for user ID " << userID << "." << endl;
    }
}







void displayMostWatchedMovie(ViewHistory history[], int numViews, Movie movies[], int numMovies) {
    int highestWatchCount = 0;
    int highestWatchedIndex = -1;

    for (int i = 0; i < numMovies; i=i+1) {
        int watchCount = 0;
        for (int a = 0; a < numViews; a=a+1) {
            if (history[a].movieID == movies[i].movieID) {
                watchCount= watchCount +1;
            }
        }
        if (watchCount > highestWatchCount) {
            highestWatchCount = watchCount;
            highestWatchedIndex = i;
        }
    }

    if (highestWatchedIndex != -1) {
        cout << "The most watched movie is: " << endl;
        cout << "Movie ID: " << movies[highestWatchedIndex].movieID << endl;
        cout << "Title: " << movies[highestWatchedIndex].title << endl;
        cout << "Genre: " << movies[highestWatchedIndex].genre << endl;
        cout << "Director: " << movies[highestWatchedIndex].director << endl;
    } else {
        cout << "No movies have been watched yet." << endl;
    }
}




void displayMoviesGenre(Movie movies[], int numMovies, string genre) {
    int count = 0;
    for (int i = 0; i < numMovies; i=i+1) {
        if (movies[i].genre == genre) {
            cout << movies[i].title << endl;
            count= count +1; 
        }
    }
    
    
    if (count!=0) {
       
        cout << "There are " << count << " movies in the " << genre << " genre." << endl;
    }
    
    else {
    	cout << "No movies in the selected genre." << endl; 
	}
	}





void displayMovieRatings(ViewHistory history[], int numViews, string movieID) {
    double totalRating = 0;
    int count = 0;

	cout << endl; 
	 cout << "Movie Ratings and Average Rating for " << movieID << endl; 

    for (int i = 0; i < numViews; i++) {
        if (history[i].movieID == movieID) {
            cout << "Date: " << history[i].viewDate.day << "/"<< history[i].viewDate.month << "/"<< history[i].viewDate.year << " - Rated: " << history[i].rating << endl;
            totalRating += history[i].rating;
            count= count +1; 
        }
    }
	
	
    if (count > 0) {
        double averageRating = totalRating / count;
        cout << endl; 
        cout << "Average Rating: " << averageRating << endl;
        
    } else {
        cout << "[Error] " << movieID << " does not exist." << endl;
    }
}


void displayUserRatings(ViewHistory history[], int numViews, string userName, User users[], int numUsers) {
	
	//reused the finduser function call 
    int userIndex = findUser(users, numUsers, userName); 


    int userID = users[userIndex].userID; 


   double totalRating = 0;
   
    int ratingCount = 0;

	cout << endl;
    cout << "Ratings given by User " << userName << ":" << endl;
    
    
	int i; 
    for (i = 0; i < numViews; i++) {
        if (history[i].userID == userID) {
            cout << "Movie: " << history[i].movieID << " rated: " << history[i].rating << endl;
            totalRating += history[i].rating;
            ratingCount= ratingCount+1; 
        }
    }



    if (ratingCount > 0) {
        double averageRating = totalRating / ratingCount;
        cout << endl; 
        cout << "Average: " << averageRating << endl;
    }
}





int main() {
	
    Movie movies[MAX_MOVIES];
    User users[MAX_USERS];
    ViewHistory history[MAX_HISTORY];



    int numMovies = readMovies(movies);
    int numUsers = readUsers(users);
    int numViews = readViewHistory(history);



    
    
    ifstream inputFile("Commands.txt");
    
    if (!inputFile) {
        cout << "Error opening file. Aborting..." << endl;            
        return 1;
    }

		int command=0; 

    cout << "Processing commands from Command file..." << endl << endl;

    while (inputFile >> command) {
        if (command == 99) {
            cout << "End of Program." << endl;
            return 0;
            
            
        } else if (command == 11) {
            cout << "--> Processing Command: 11- Movie Details... "  << endl;
            string movieID;
            inputFile >> movieID;
            int index = findMovie(movies, numMovies, movieID);
            if (index != -1) {
                displayMovie(movies[index]);
                cout << endl; 
            }
            
            
        } else if (command == 12) {
            cout << "--> Processing Command 12- User details..."  << endl;
            string userName;
            inputFile >> userName;
            int index = findUser(users, numUsers, userName);
            if (index != -1) {
                displayUser(users[index]);
                cout << endl; 
            }
            
            
        } else if (command == 21) {
            cout << "--> Processing Command 21 - User's Watched Movies ..."  << endl;
            string userName;
            inputFile >> userName;
            int userIndex = findUser(users, numUsers, userName);
            if (userIndex != -1) {
                cout << "Movies watched by User " << userName << ":" << endl;
                displayUserHistory(history, numViews, users[userIndex].userID);
            cout << endl; 
			}
			
			

			
			
        } else if (command == 22) {
            cout << "--> Processing Command: 22- Most Watched Movie... " << endl;
            displayMostWatchedMovie(history, numViews, movies, numMovies);
            cout << endl; 
            
            
            
            
            
        } else if (command == 23) {
            cout << "--> Processing Command: 23- All Unwatched Movies..." <<  endl;
            displayAllUnwatchedMovies(movies, numMovies, history, numViews);
            cout << endl; 
            
            
            

            
            
            
        } else if (command == 24) {
            cout << "--> Processing Command: 24- Movies in a Certain Genre..." <<  endl;
            string genre;
            inputFile >> genre;
            displayMoviesGenre(movies, numMovies, genre);
            cout << endl;
            
            
            
            

        } else if (command == 31) {
            cout << "--> Processing Command: 31- All Ratings for Movie..." << endl;
            string movieID;
            inputFile >> movieID;
            displayMovieRatings(history, numViews, movieID);
            cout << endl; 
        }
        
        
	    else if (command == 32) {
	   	 cout << "--> Processing Command: 32- All Ratings By User..." << endl;
	    string userName;
	    inputFile >> userName;
	    displayUserRatings(history, numViews, userName, users, numUsers); 
	    cout << endl;
	}
            
            
        else {
            cout << "[Error] --> Command " << command << " does not exist." << endl;
            cout << endl; 
        }
    }


    inputFile.close();
    return 0;
}
