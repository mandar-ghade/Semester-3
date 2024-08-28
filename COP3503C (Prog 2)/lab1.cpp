#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void print_you_entered(string text) {
  cout << "You entered: ";
  cout << text;
  cout << "\n" << endl;
}

string get_title() {
    string title;
    cout << "Enter a title for the data:" << endl;
    getline(cin, title);
    print_you_entered(title);
}

string get_column(int num) {
    string column_header;
    cout << "Enter the column ";
    cout << num;
    cout << " header:" << endl;
    getline(cin, column_header);
    print_you_entered(column_header);
}

int main()
{
   
   /* Overall flow of the program:
   Get some input for the title
   Get some input for column header #1
   Get some input for column header #2
   
   Until the user types "-1":
   Get input for a string
   Validate input
   If valid...
      Split
      Validate second half of input
      If also valid...
         Store separate pieces
   
   Print out data in table format
   
   Print out data in chart format
   */
// WRITE YOUR CODE HERE
    int i = 0;
    for (; i < 10; i++) {
        cout << i << endl;
    }

    while (i < 20) {
        cout << i << endl;
        i++;
    }
    
    string title = get_title();
    string column_1 = get_column(1);
    string column_2 = get_column(2);
}

