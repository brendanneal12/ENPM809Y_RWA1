#include <iostream>
//Brendan Neal
//ENPM809Y RWA1
//Directory ID: bneal12
//Due: 01 October 2023



// ----------------------------------------------------------
// Main Function
// ----------------------------------------------------------

int main() {

    // ----------------------------------------------------------
    // User Interface Code
    // ----------------------------------------------------------

    //Declare variables to store user-entered information (number of parts and boxes).
    int sm_boxes{0}; 
    int med_boxes{0}; 
    int large_boxes{0}; 
    int number_of_parts{0};

    //Prompt and assign user inputs to box variables.
    std::cout << "How many boxes are available for small, medium, and large? ";
    std::cin >> sm_boxes >> med_boxes >> large_boxes; 

    //Check if any box information is invalid (negative) and reprompt the user to enter valid parameters.
    while ( (sm_boxes < 0) || (med_boxes < 0) || (large_boxes < 0) ){
        std::cout << "Please enter positive integers for box information. \n";
        std::cout << "How many boxes are available for small, medium, and large? ";
        std::cin >> sm_boxes >> med_boxes >> large_boxes; 
    }

    std::cout << "-------------------------------------------------------- \n";

    //Prompt and assign user inputs to parts variables.
    std::cout << "How many parts are available? ";
    std::cin >> number_of_parts; 

    //Check if part information is invalid (negative) and reprompt the user to enter valid parameters.
    while (number_of_parts < 0){
        std::cout << "Please enter positive integers for part information. \n";
        std::cout << "How many parts are available? ";
        std::cin >> number_of_parts; 
    }

    std::cout << "\n******************************************************** \n";
    std::cout << "Computing part distribution to minimize leftover parts. \n";
    std::cout << "******************************************************** \n";

    // ----------------------------------------------------------
    // Part Sorting Code
    // ----------------------------------------------------------

    //Initialize Box Capacity Variables.
    int sm_cap{7}; 
    int med_cap{12}; 
    int large_cap{25}; 

    //Initialize Variables to Keep Track of Boxes Used.
    int sm_used{0};
    int med_used{0}; 
    int large_used{0}; 

    //Initialize while loop assuming that parts can be sorted down to < 7. 
    //There are other exit conditions at the end of the loop to account for other cases.
    while(number_of_parts > sm_cap){

        //***Prioritize filling boxes with parts that distribute perfectly evenly.***

        //If you haven't filled all large boxes available
        if(large_used < large_boxes){ 
            //If the parts will distribute evenly into large boxes without using more large boxes than available.
            if ((number_of_parts % large_cap == 0) && (number_of_parts/large_cap <= large_boxes-large_used)){ 
                large_used += 1; //Add another large box to the count.
                number_of_parts -= large_cap; //Subtract sorted parts from total.
                continue;
            }
        }

        //If you haven't filled all medium boxes available
        if(med_used < med_boxes){ 
            //If the parts will distribute evenly into medium boxes without using more medium boxes than available.
            if ((number_of_parts % med_cap == 0) && (number_of_parts/med_cap <= med_boxes-med_used)){ 
                med_used += 1; //Add another medium box to count.
                number_of_parts -= med_cap; //Subtract sorted parts from total.
                continue;
            }
        }

        //If you haven't filled all small boxes available
        if(sm_used < sm_boxes){ 
            //If the parts will distribute evenly into small boxes without using more small boxes than available.
            if ((number_of_parts % sm_cap == 0) && (number_of_parts/sm_cap <= sm_boxes-sm_used)){
                sm_used += 1; //Add another small box to count.
                number_of_parts -= sm_cap; //Subtract sorted parts from total.
                continue;
            }
        }

        //***If the number of boxes and parts won't distribute perfectly evenly, begin to iteratively distribute them to minimize remaining parts.***
        //Aim to fill large boxes first. 
        //Then, selectively choose if a medium or small box would be "better" otherwise.

        if(large_used < large_boxes){ //If you haven't filled all large boxes available.
            if(number_of_parts / large_cap != 0){ //And you are able to fully fill a single large box in this iteration.
                large_used += 1; //Add another large box to the count.
                number_of_parts -= large_cap; //Subtract sorted parts from total.
                continue;
            }
        }

        if(med_used < med_boxes){ //If you haven't filled all medium boxes available.
            if(number_of_parts / med_cap != 0){ //If you can fully fill a medium box in this iteration
                //If the number of remaining parts from filling medium boxes is less than or equal to filling small boxes.
                if(number_of_parts % med_cap <= number_of_parts % sm_cap){ 
                    med_used += 1; //Add another medium box to the count.
                    number_of_parts -= med_cap; //Subtract sorted parts from total.
                    continue;
                }

                //If there are no more small boxes.
                if(sm_used == sm_boxes){ 
                    med_used += 1; //Add another medium box to the count.
                    number_of_parts -= med_cap; //Subtract sorted parts from total.
                    continue;
                }

                //If there aren't enough small boxes left to minimize parts (even if it is the iteration's best option), fill a medium box.
                //This condintion was implemented to fix some cases I found in testing.
                if(number_of_parts/sm_cap > sm_boxes-sm_used){ 
                    med_used += 1; //Add another medium box to the count.
                    number_of_parts -= med_cap; //Subtract sorted parts from total.
                    continue;
                }
            }
        }

        if(sm_used < sm_boxes){ //If you haven't filled all small boxes available.
            if(number_of_parts / sm_cap != 0){ //If you can fully fill a small box in this iteration
                //If the number of remaining parts from filling small boxes is less than or equal to filling medium boxes.
                if(number_of_parts % sm_cap <= number_of_parts % med_cap){ 
                    sm_used += 1; //Add another small box to the count.
                    number_of_parts -= sm_cap; //Subtract sorted parts from total.
                    continue;
                }

                //If there are no medium boxes left.
                if(med_used == med_boxes){ 
                    sm_used += 1; //Add another small box to the count.
                    number_of_parts -= sm_cap; //Subtract sorted parts from total.
                    continue;
                } 
            }    
                   
        }

        //Break the loop if all available boxes have been used.
        if((sm_used == sm_boxes) && (med_used == med_boxes) && (large_used == large_boxes)){
            break;
        }

        //Break the loop if all small and medium boxes have been used, and the remaining parts don't fit in a large box.
        if((sm_used == sm_boxes) && (med_used == med_boxes) && (number_of_parts < large_cap)){
            break;
        }

        //Break the loop if all small and large boxes have been used, and the remaining parts don't fit in a medium box.
        if((sm_used == sm_boxes) && (number_of_parts < med_cap) && (large_used == large_boxes)){
            break;
        }
        
        //Break the loop if all medium and large boxes have been used, and the remaining parts don't fit in a small box.
        if((number_of_parts < sm_cap) && (med_used == med_boxes) && (large_used == large_boxes)){
            break;
        }

    }

    //Capture and evaluate the loop's "edge case" where the number of remaining parts is 7 and there is at least 1 remaining small box.
    if(sm_used < sm_boxes){
        if(number_of_parts == 7){
            sm_used += 1; //Add another small box to the count.
            number_of_parts -= sm_cap; //Subtract sorted parts from total.
        }
    }
   
    //Print Results to Terminal
    std::cout << "You have used: \n";
    std::cout << sm_used << " Small Box(es),\n";
    std::cout << med_used << " Medium Box(es),\n";
    std::cout << large_used << " Large Box(es),\n";
    std::cout << "With " << number_of_parts << " Part(s) leftover.\n";
    return 0;
}