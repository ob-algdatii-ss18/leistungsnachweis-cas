//
// Created by chris on 27.04.18.
//

#include "RecursiveBacktracker.h"


//print maze to terminal
void RecursiveBacktracker::drawMaze( )
{
    int k=0;
    for ( auto &cell : newcells)
    {
        cout << cell->image;
        k++;
        if(k >= width)
        {
            cout << endl;
            k=0;
        }
    }
}
//large grid of cells, each cell starting with four walls
int RecursiveBacktracker::initMaze( )
{
    newcells.reserve(height * width);

    int i, j;
    Cell *current;

    //Setup crucial cells
    for ( i = 0; i < width; i++ )
    {
        for ( j = 0; j < height; j++ )
        {
            current = dummy + i + j * width;
            //each cell starting with four walls
            // -> every other cell is a 'path' cell
            if ( i * j % 2 )
            {
                current->x = i;
                current->y = j;
                current->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
                current->image = path;
                current->up = true;
                current->down = true;
                current->left = true;
                current->right = true;
                newcells.push_back(current);
            }
            else{
                current->x = i;
                current->y = j;
                current->image = wall;
                newcells.push_back(current);
            }
        }
    }
    return 0;
}

/* removes the wall between the two cells and marks the new cell as visited.
 * this continues until a cell that has no unvisited neighbours is reached
 */
Cell * RecursiveBacktracker::backtracking( Cell *n )
{
    int x, y, direction;
    Cell *dest;

    if ( n == nullptr ) return nullptr;

    //While there are directions still unexplored
    while ( n->up || n->down || n->left || n->right /*n->dirs*/ )
    {
        //Randomly pick one direction
        direction = (rand() % 4);

        switch(direction)
        {
            case 0:
                if(!n->up)
                    continue;
                else if ( n->y - 2 >= 0 )
                {
                    x = n->x;
                    y = n->y - 2;
                    n->up = false;
                }
                else continue;
                break;
            case 1:
                if(!n->down)
                    continue;
                else if ( n->y + 2 < height )
                {
                    x = n->x;
                    y = n->y + 2;
                    n->down = false;
                }
                else continue;
                break;
            case 2:
                if(!n->left)
                    continue;
                else if ( n->x - 2 >= 0 )
                {
                    x = n->x - 2;
                    y = n->y;
                    n->left = false;
                }
                else continue;
                break;
            case 3:
                if(!n->right)
                    continue;
                else if ( n->x + 2 < width )
                {
                    x = n->x + 2;
                    y = n->y;
                    n->right = false;
                }
                else continue;
                break;
        }

        //Get destination node into pointer
        dest = newcells.front() + x + y * width;

        //Make sure that destination node is not a wall
        if ( dest->image == path )
        {
            //If destination is a linked node already - abort
            if ( dest->parentCell != nullptr ) continue;

            //Otherwise, adopt node
            dest->parentCell = n;

            //Remove wall between cells
            newcells.at(n->x + ( x - n->x ) / 2 + ( n->y + ( y - n->y ) / 2 ) * width)->image = path;

            //Return address of the child node
            return dest;
        }
    }
    //return parent's address
    return (Cell *) n->parentCell;
}



//width, height,
int RecursiveBacktracker::startMaze( )
{
    Cell *start, *end;

    string input;
    cout << "What's the maze width? " ;
    getline (cin, input);
    width = stoi(input);
    cout << "What's the maze height " ;
    getline (cin, input);
    height = stoi(input);

    //Do not allow negative dimensions
    if ( width <= 0 || height <= 0 )
    {
        cerr << " maze dimensions must be greater than 0!\n" << endl;
        exit( 1 );
    }

    //Allow only odd dimensions
    if ( !( width % 2 ) || !( height % 2 ) )
    {
        cerr << " maze dimensions must be odd!\n" << endl;
        exit( 1 );
    }

    //It seeds the pseudo random number generator that rand() uses
    srand( time( nullptr ) );

    //Initialize maze
    int answer = initMaze();
    if ( answer != 0 )
    {
        cerr << " maze : out of memory!\n" << endl;
        exit( 1 );
    }

    //Setup start node
    start = newcells.front() + 1 + width;
    start->parentCell = start;
    end = start;

    //Connect cells until start node is reached
    while ( (end = backtracking(end)) != start );
    drawMaze( );

    return 0;
}



