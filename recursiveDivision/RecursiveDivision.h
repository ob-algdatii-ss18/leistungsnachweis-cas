#ifndef LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
#define LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H

#include <iostream>
#include "../prims/LabGraph.h"

/**
 * Class with recursive division algorithm.
 *
 * Creates a NxM empty maze field surrounded by a wall.
 * Each time this field will be separated by a wall with a passage into two smaller fields.
 * These new small field will be separated in another two smaller fields and so on.
 *
 * After each field have the minimum size of 2x2 a start opening and a end opening will be calculated.
 */
class RecursiveDivision {
public:
    /**
     * For UI printing;
     */
    LabGraph *labPrinter;
    /**
     * Var to print maze after every division on console.
     */
    bool debugMode = false;

    /**
     * Method which generate the empty maze field.
     *
     * Field is surrounded by a wall.
     *
     * The generated field is a 2D - boolean array.
     * @param width Absolute width of the maze.
     * @param height Absolute height of the maze.
     * @return The generated maze field as 2D bool array.
     */
    bool **initMaze(int width, int height);

    /**
     * Start method of this class with console.
     *
     * It ask for cols and rows of the maze. Theses are the relative sizes of the maze, because of the walls.
     * A maze with 2 cols have an absolute width of 6. Two for the walls on the left and on the right, two for the
     * given col amount and 2 for walls between them.
     * @param is input-stream for reading input params.
     * @return 0 if no exception occurs.
     */
    int generateMaze(std::istream &is);

    /**
     * Arbitrator method for the recursive division.
     *
     * It consumes the maze and the current coordinates of the field. These coordinates are the four directions.
     * This method choose by the width and height if the field will be divided and in which direction.
     * @param field The complete maze field.
     * @param left The column index of the left column.
     * @param right The column index of the right column.
     * @param top The row index of the top row.
     * @param bottom The row index of the bottom row.
     */
    void divideField(bool **field, int left, int right, int top, int bottom);

    /**
     * Divide the sub-field with a vertical wall.
     *
     * It choose a random number for the row index where the wall will be placed. After that the wall will be added and
     * a random row index is calculated to open the passage. After that, this method calls the generateMaze() Method
     * again with the new two, smaller fields.
     * @param field The complete maze field.
     * @param left The column index of the left column.
     * @param right The column index of the right column.
     * @param top The row index of the top row.
     * @param bottom The row index of the bottom row.
     */
    void divideVertical(bool **field, int left, int right, int top, int bottom);

    /**
     * Divide the sub-field with a horizontal wall.
     *
     * It choose a random number for the column index where the wall will be placed. After that the wall will be added
     * and a random column index is calculated to open the passage. After that, this method calls the generateMaze() Method
     * again with the new two, smaller fields.
     * @param field The complete maze field.
     * @param left The column index of the left column.
     * @param right The column index of the right column.
     * @param top The row index of the top row.
     * @param bottom The row index of the bottom row.
     */
    void divideHorizontal(bool **field, int left, int right, int top, int bottom);

    /**
     * Make the start and end opening of the maze.
     *
     * It consumes the absolute width and the relative rows to calculate a random opening and closing passage.
     * @param field The complete maze field.
     * @param rows The relative row count.
     * @param cols The absolute width.
     */
    void makeMazeOpening(bool **field, int rows, int cols);

    /**
     * Consumes the maze field and draw it at the console output.
     * @param field Maze field.
     * @param output output stream (only for testing purpose).
     */
    void drawMaze(bool **field, std::ostream &output);

    /**
     * Generate a random integer value between the lower and the upper boundary.
     * @param lower Lower bound.
     * @param upper Upper bound.
     * @return random value.
     */
    int generateRandomInt(int lower, int upper);

    /**
     * Generate a random boolean value.
     * @return random true or false.
     */
    bool generateRandomBoolean();
};


#endif //LEISTUNGSNACHWEIS_CAS_RECURSIVEDIVISION_H
