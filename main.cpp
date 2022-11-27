// #include<boost/algorithm/string.hpp>
#include <bits/stdc++.h>

// using namespace boost::algorithm;
using namespace std;

int main()
{


    // taking the number of production rules
    int production_rules_count;
    cout << "Enter the number of production rules : ";
    cin >> production_rules_count;
    cin.ignore();



    // declaring and taking the grammars as input
    string grammars_left[production_rules_count], grammars_right[production_rules_count];
    for (int i=0; i<production_rules_count; i++) {

        // taking input
        string grammar_input;
        cout << "** (if grammar) E -> a+b || (input should be) E = a+b **" << endl;
        cout << "Enter the production rule " << i+1 << " : ";
        getline(cin, grammar_input);
        cout << endl;

        // checking if a valid grammar or not
        int points_for_input_grammar = 0;
        bool left_part = true;
        for (int j=0; j<grammar_input.length(); j++) {
            if (left_part) {
                if (grammar_input[j] == '=') {
                    points_for_input_grammar++;
                    left_part = false;
                } else if (grammar_input[j] == ' ') {
                    continue;
                } else {
                    if(points_for_input_grammar == 0) {
                        points_for_input_grammar++;
                    }
                }
            } else {
                if (grammar_input[j] == ' ') {
                    continue;
                } else {
                    if(points_for_input_grammar == 2) {
                        points_for_input_grammar++;
                        break;
                    }
                }
            }
        }
        // checking for validity
        if (points_for_input_grammar != 3) {
            cout << "Invalid Grammar! Insert once more" << endl;
            i--;
            continue;
        }

        // assigning the grammars to the proper arrays based on the direction
        // left-part -> right-part
        left_part = true;
        for (int j=0; j<grammar_input.length(); j++) {
            if (grammar_input[j] == ' ') {
                continue;
            } else if (grammar_input[j] == '=') {
                left_part = false;
            } else {
                if (left_part) {
                    grammars_left[i].push_back(grammar_input[j]);
                } else {
                    grammars_right[i].push_back(grammar_input[j]);
                }
            }
        }
    }




    // displaying all the grammars
    cout << endl;
    cout << "Grammar :";
    cout << endl;

    for (int i=0; i<production_rules_count; i++) {
        cout << grammars_left[i] << " -> " << grammars_right[i] << endl;
    }
    cout << endl;



    // take input string
    string input_buffer;
    cout << "Enter an Input String : ";
    getline(cin, input_buffer);

    // trimming the input string
    string trimmed_input;
    for(int i=0; i<input_buffer.length(); i++) {
        if(input_buffer[i] == ' ') {
            continue;
        } else {
            trimmed_input.push_back(input_buffer[i]);
        }
    }

    // setting the new trimmed string
    input_buffer = trimmed_input;

    // setting the buffer and the input
    string stack_buffer = "$";
    input_buffer.push_back('$');


    // we want to shift and reduce to match it
    while(input_buffer != "$") {
        stack_buffer.push_back(input_buffer[0]);
        input_buffer.erase(input_buffer.begin());
        cout << "Stack : " << stack_buffer << endl;
        cout << "Input Buffer : " << input_buffer << endl;
        cout << "SHIFT " << endl << endl;

        for (int i=0; i<production_rules_count; i++) {
            bool reduce = false;
            if(stack_buffer.find(grammars_right[i]) < stack_buffer.length()) {
                stack_buffer.erase(stack_buffer.find(grammars_right[i]), stack_buffer.length());
                stack_buffer += grammars_left[i];

                cout << "Stack : " << stack_buffer << endl;
                cout << "Input Buffer : " << input_buffer << endl;
                cout << "REDUCE : " << grammars_left[i] << " -> " << grammars_right[i] << endl << endl;
                reduce = true;
            }

            if (reduce) {
                i=-1;
            }

        }

    }

    input_buffer += grammars_left[0];



    // if matched then okay else not
    if(stack_buffer == input_buffer) {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;

}
