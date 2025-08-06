// Chimdubem Duruji
// "none"
// 022
// 04/05/2025

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// c269759b-5ea7-4702-bff4-ebc05443d45d
//------------------------------------------------------



// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <fstream>
#include <vector>

// This #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main(){


    // TODO: implement the main program

    //defining some variables
    vector <string> keywords;
    vector <double> weights;
    ifstream keywordsIn("keywordWeights.txt");

    //reading in the keywords and their weights
    if(!keywordsIn.is_open()){
        cout << "Error: keywordWeights.txt could not be opened." << endl;
        return 1;
    } else readKeywordWeights(keywordsIn, keywords, weights);

    string reviewFilename; //name of a review
    vector <string> reviewString; //vector for containing the file names
    vector <double> scores; // vector containing the review scores for each review
    vector <string> categories; // a vector that contains the categories of each score
    int index_of_max = 0; //index of the highest scoring review
    int index_of_min = 0; // index of the lowest scoring review
    int i=0;

    //loop adding the scores and categories for each review to respective vectors as long as there are files to read
    while(true){
        reviewFilename = makeReviewFilename(i);
        ifstream reviewName(reviewFilename);

        if(!reviewName.is_open()){
            break;
        }

        reviewString.clear();
        readReview(reviewName, reviewString);
        double score = reviewScore(reviewString, keywords, weights);

        string category;
        if (score > SCORE_LIMIT_TRUTHFUL){
            category = "truthful";
        } else if(score < SCORE_LIMIT_DECEPTIVE){
            category = "deceptive";
        } else {
            category = "uncategorized";
        }
        scores.push_back(score);
        categories.push_back(category);
        ++i;
    }

    // loop finding the index of the best review
    for(int j = 0; j<scores.size(); ++j){
        if(scores.at(j)>scores.at(index_of_max)){
            index_of_max = j;
        }
    }


    //loop finding the index of the worst review
    for(int k = 0; k<scores.size(); ++k){
        if(scores.at(k)<scores.at(index_of_min)){
            index_of_min = k;
        }
    }
    
    //making the summary file
    ofstream reportOut("report.txt");
    reportOut << "review score category" << endl;

    //loop adding the reviews and their respective scores and categories to the output file
    for(int x=0; x<scores.size(); ++x){
        reportOut << x << " " << scores.at(x) << " " << categories.at(x) << endl;
    }

    reportOut << endl; 

    reportOut << "Number of reviews: " << scores.size() << endl;
    int truthfulReviews = 0; //number of truthful reviews
    int deceptiveReviews = 0; //number of deceptive reviews
    int uncatReviews = 0; // number of uncategorized reviews
    for(int y=0; y<categories.size(); ++y){
        if(categories.at(y) == "truthful"){
            truthfulReviews +=1;
        } else if(categories.at(y) == "uncategorized"){
            uncatReviews += 1;
        } else deceptiveReviews +=1;
    }

    reportOut << "Number of truthful reviews: " << truthfulReviews << endl;
    reportOut << "Number of deceptive reviews: " << deceptiveReviews << endl;
    reportOut << "Number of uncategorized reviews: " << uncatReviews << endl;
    reportOut << endl;
    reportOut << "Review with highest score: " << index_of_max <<  endl;
    reportOut << "Review with lowest score: " << index_of_min << endl;
    reportOut.close(); // close the file

    cout << "Program complete.  Check report.txt file for summary." << endl; //end the program
}



