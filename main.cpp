#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//We make a structure for the state
typedef struct {
    int n;
    int numEdges;
    bool end;
} State;

//Then we make a structure for all the edges that we are going through
typedef struct {
    char *letter;
    State start;
    State stop;
} Edge;

bool NFA(char *w, State sEdge, Edge **edgeM, int current)
{
    /**
    * We will use the parameter @w as a char to represent the word that we verify
    * The parameter @sEdge will represent the state that we start with
    * The parameter @current will represent the letter that we start with
    * The parameter @edgeM will represent the edge of the matrix that we start with
    * @return  true or false, represents if the word belongs to the alphabet
    */

    if (current == strlen(w) && sEdge.end) return true;

    if (current == strlen(w) && !sEdge.end) return false;

    if (current <= strlen(w) && sEdge.numEdges == 0) return false;

    for (int i = 0; i < sEdge.numEdges; i++)
    {
        if (edgeM[sEdge.n][i].letter[0] == w[current])
            if (NFA(w, edgeM[sEdge.n][i].stop, edgeM, current + 1)) return true;

    }

    return false;

}

// The empty word is "*";

int main()
{
    ifstream f("../datein.txt"); // we use this file for testing the function

    char word[21];
    int nStates;
    //First we read the word that needs to be tested
    f >> word;
    //Then we read the number of states
    f >> nStates;

    // We use the parameter "States" to represent the state
    State States[nStates];
    // We initialize the states;
    for (int i = 0; i < nStates; i++)
    {
        States[i].end = false;
        States[i].n = i;
    }

    //We check if the "i" state is the end
    for (int i = 0; i < nStates; i++)
    {
        int endOrNot;
        f >> endOrNot;
        if (endOrNot == 1) States[i].end = true;
    }

    Edge **edges;
    edges = new Edge *[nStates];

    // Now we read the number of edges that the state "i" has;
    for (int i = 0; i < nStates; i++)
    {
        f >> States[i].numEdges;
        edges[i] = new Edge[States[i].numEdges];
    }


    for (int i = 0; i < nStates; i++)
    {

        for (int j = 0; j < States[i].numEdges; j++)
        {
            char letter[1]; // Used to see what letter brings us to witch state;
            int lastEdgeState; // the state that we ended up into
            edges[i][j].start = States[i];

            //Read the letter
            f >> (*letter);
            edges[i][j].letter = new char[1];
            strcpy(edges[i][j].letter, letter); // save the letter into our matrix;

            // We read the number of the state that we reached with the specific letter;
            f >> lastEdgeState;
            edges[i][j].stop = States[lastEdgeState];
            // We display the states
            cout << edges[i][j].start.n << " " << edges[i][j].letter[0] << " " << edges[i][j].stop.n << "\n";


        }
    }

    cout << "\n";
    if (word == "*")
    {
        if (States[0].end) cout << "The word belongs to the alphabet";
        else cout << "The word doesn't belong to the alphabet";
    } else {
        if (NFA(word, States[0], edges, 0)) cout << "The word belongs to the alphabet";
        else cout << "The word doesn't belong to the alphabet";
    }

    return 0;
}