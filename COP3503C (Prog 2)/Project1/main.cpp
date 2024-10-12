#include "LinkedList.h"

using namespace std;

void TestOtherRemoval()
{
    cout << "=====Testing RemoveAt() and clearing with RemoveHead()/RemoveTail() functionality=====" << endl;
    LinkedList<string> data;
    data.AddTail("Batman");
    data.AddTail("RemoveMe");
    data.AddTail("Superman");
    data.AddTail("RemoveMe");
    data.AddTail("Wonder Woman");
    data.AddTail("RemoveMe");
    data.AddTail("The Flash");

    cout << "Initial list: " << endl;
    data.PrintForward();
    cout << "\nRemoving using RemoveAt()..." << endl;
    data.RemoveAt(1);
    data.RemoveAt(2);
    data.RemoveAt(3);

    data.PrintForward();
    
    cout << "\nAttempting to remove out of range using RemoveAt()..." << endl;
    if (!data.RemoveAt(100))
        cout << "Attempt to RemoveAt(100) failed." << endl;
    else
        cout << "Successfully removed node 100? Weird, there are only 4 nodes..." << endl;

    cout << "\nClearing list using RemoveHead()..." << endl;
    while (data.RemoveHead()){}

    if (data.NodeCount() == 0)
        cout << "List is empty!" << endl;
    else
        cout << "List not empty!" << endl;

    cout << "Adding additional nodes..." << endl;
    data.AddTail("Robin");
    data.AddTail("Batgirl");
    data.AddTail("Nightwing");
    data.AddTail("Red Hood");
    data.AddTail("Bluebird");

    data.PrintForward();

    cout << "Clearing list using RemoveTail()..." << endl;
    while (data.RemoveTail()) {}

	data.PrintForward();
    if (data.NodeCount() == 0)
        cout << "List is empty!" << endl;
    else
        cout << "List not empty!" << endl;
}
int main() {
	TestOtherRemoval();
	return 0;
}
