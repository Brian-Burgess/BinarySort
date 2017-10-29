/**
 * Driver for BrianarySort.
 *
 * @author Brian Burgess
 */

#include <iostream>
#include <algorithm>
#include <stdlib.h>

unsigned long binarySearch(unsigned long * const data, unsigned long const key, unsigned long const indexOfKey, unsigned long const size);
bool isAtEndOFArray(unsigned long * const data, unsigned long const low, unsigned long const high, unsigned long const key);
unsigned long returnIndex(unsigned long * const data, unsigned long const middle, unsigned long const key, unsigned long const indexOfKey, unsigned long const size);

int main(int argc, char * argv[]){

    unsigned long size = (unsigned long) strtol(argv[1], NULL, 10);
    unsigned long * array = new unsigned long[size]; //makes array of size "size"

    for(unsigned long i = 0, x = size-1; i<size; i++, x--){//populates array
        array[i] = x; //Assigns values to array
    }//for

    std::random_shuffle(array, &array[size]); //shuffles the array

    std::cout<<"Unsorted: ";
    for(long i = 0; i<size; i++){
        std::cout<<array[i]<<", "; //prints unsorted values
    } //for

    std::cout<<std::endl<<std::endl;

    unsigned long currentPos = 0; //the place we're currently moving
    unsigned long insertionPoint;
    while(currentPos < size ){ //iterates while no greater than 2 higher than the midpoint of the array
        // (technically just needs to be the ceil of (high+low /2) but I'm lazy sooo

        insertionPoint = binarySearch(array, array[currentPos], currentPos, size);
        //std::cout<<insertionPoint<<std::endl;
            //modified binary search to find where to insert element

        if(insertionPoint == currentPos){ //if it tells us to insert where we already are, we increment where we're looking
            currentPos++;
        }else{ //otherwise, we swap the vals where it told us to insert
            unsigned long tmp = array[currentPos];
            array[currentPos] = array[insertionPoint];
            array[insertionPoint] = tmp;
        } // if else

    } // while

    std::cout<<"Sorted Array: ";
    for(long i = 0;i< size; i++){
        std::cout<<array[i]<<", ";
    }//for

    std::cout<<std::endl;
}

/**
 * Modified binary search. Searches on an unsorted array.
 * Calls: isAtEndOfArray (tests whether we should stop searching)
 *        returnIndex (if isAtEndOfArray is true, we return the returned index)
 *
 * @param data The array we're searching
 * @param key The value at currentPos (the value we're searching for)
 * @param indexOfKey Alias for currentPos
 * @param size Size of our array
 * @return Returns the location we should swap
 */
unsigned long binarySearch(unsigned long * const data, unsigned long const key, unsigned long const indexOfKey, unsigned long const size){

    unsigned long low = 0;
    unsigned long high = size - 1;

    while(true) {
        unsigned long middle = (low + high) / 2; //calcs mid point of low and high

        if(isAtEndOFArray(data, low, high, key)) {

            return returnIndex(data, middle, key, indexOfKey, size);
                //calcs the appropriate index to swap

        } else { //traditional binary search

            if (data[middle] < key) {
                low = middle + 1;
            }//if
            if (data[middle] >= key) {
                high = middle - 1;
            } //if
        } // if else
    }// while
} // binarySearch

/**
 * Returns true if we should stop searching. Else, returns false.
 *
 * @param data Array we're searching
 * @param low Lower bound of search on data
 * @param high Upper bound of search on data
 * @param key Value we're searching for
 * @return Returns whether we should stop searching (true) or not (false)
 */
bool isAtEndOFArray(unsigned long * const data, unsigned long const low, unsigned long const high, unsigned long const key){

    if(low == high){ //no more to search
        return true;

    } else if( high - low == 1 && key <= data[low]){ //means we've reached the end
        return true;

    } else {

        return false; //keep it going
    } // if else

} //isAtEndOfArray

/**
 * The heart of the algorithm. If we're at the end of the search bounds, we determine the location to swap.
 *
 * @param data Array to search.
 * @param middle Current middle of lower and upper bounds of searchable array (not the overall middle)
 * @param key The value at currentPos and indexOfKey
 * @param indexOfKey Alias for currentPos
 * @param size Size of the overall array.
 * @return The index to insert
 */
unsigned long returnIndex(unsigned long * const data, unsigned long const middle, unsigned long const key, unsigned long const indexOfKey, unsigned long const size){

    if (middle == indexOfKey) { //means we increment currentPos because the middle index is the same as the current index of Key
        return indexOfKey;
    } //if

    if (data[middle] < key) {

        if (middle == size-1 || indexOfKey < middle){
            //if middle == size-1, then we're at the right end of the array and need to insert at end (middle index).
            //OR if the indexOfKey is less than where we should insert, then we should swap with middle because that sorts those 2 values
            return middle;
        } else if (key < data[middle+1] && indexOfKey > middle+1){
            //if key is less than the right of middle AND the index of key is higher than the middle+1, we should swap as it sorts those 2 vals
            return middle+1;
        } else{
            //if all else fails, we need to change the currentPos to start sorting again
            return indexOfKey;
        } // if else

    } //if

    if (data[middle] > key) {

        if (middle == 0 || indexOfKey > middle){
            //if middle == 0, then we're at the left end of the array and need to insert at beginning (middle index).
            //OR if the indexOfKey is greater than where we should insert, then we should swap with middle because that sorts those 2 values
            return middle;
        } else if (key > data[middle-1] && indexOfKey < middle-1){
            //if key is greater than the left of middle AND the index of key is less than the middle-1, we should swap as it sorts those 2 vals
            return middle-1;
        } else{
            //if all else fails, we need to change the currentPos to start sorting again
            return indexOfKey;
        } //if else

    } // if

} // returnIndex
