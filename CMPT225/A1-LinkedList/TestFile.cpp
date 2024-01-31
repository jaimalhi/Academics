#include <iostream>
#include <string>
#include "PlayList.h"
#include "Song.h"

using std::cout;
using std::endl;

// Song Tests

void SongTest1()
{

	cout << endl << "------------------" << "Song Test 1" << "------------------" << endl;

	Song* Song1 = new Song("FakeSong", "FakeArtist", 300);

	cout << Song1->getName() << " " << Song1->getArtist() << " " << Song1->getLength() << endl;

	delete Song1;

	cout << "----------------" << "End Song Test 1" << "----------------" << endl;
}

// Node Tests

void NodeTest1()
{

	cout << endl << "------------------" << "Node Test 1" << "------------------" << endl;	

	Song* Song1 = new Song("FakeSong1", "FakeArtist1", 100);
	Song* Song2 = new Song("FakeSong2", "FakeArtist2", 200);

	cout << "Songs Made" << endl;

	PlayListNode* Node1 = new PlayListNode(*Song1);
	PlayListNode* Node2 = new PlayListNode(*Song2, Node1);

	cout << "Nodes Made" << endl;

	cout << Node2->next->song.getName() << " | " << Node1->song.getName() << endl;

	delete Node1;
	delete Node2;

	cout << "Nodes deleted" << endl;

	delete Song1;
	delete Song2;

	cout << "Songs deleted" << endl;

	cout << "----------------" << "End Node Test 1" << "----------------" << endl;
}

// Playlist Tests

	// Constructor Tests

void PlayListConTest1()
{

	cout << endl << "------------------" << "Constructor Test 1" << "------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);

	cout << "Songs Made" << endl;

	PlayList* pl = new PlayList();

	cout << "Playlist Made" << endl;

	pl->insert(Song1, 0);
	pl->insert(Song2, 0);

	cout << pl->get(0).getName() << ", " << pl->get(1).getName() << endl;

	delete pl;

	cout << "----------------" << "End Constructor Test 1" << "----------------" << endl;	
}

void PlayListConTest2()
{

	cout << endl << "------------------" << "Constructor Test 2" << "------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);
	Song Song4 = Song("FakeSong4", "FakeArtist4", 400);
	Song Song5 = Song("FakeSong5", "FakeArtist5", 500);
	Song Song6 = Song("FakeSong6", "FakeArtist6", 600);

	cout << "Songs Made" << endl;

	PlayList pl;

	cout << "Playlist Made" << endl;

	pl.insert(Song1, 0); // 1
	pl.insert(Song2, 0); // 2, 1
	pl.insert(Song3, 1); // 2, 3, 1
	pl.insert(Song4, 2); // 2, 3, 4, 1
	pl.insert(Song5, 1); // 2, 5, 3, 4, 1
	pl.insert(Song6, 0); // 6, 2, 5, 3, 4, 1

	Song tmp1 = pl.remove(1); // 6, 5, 3, 4, 1
	Song tmp2 = pl.remove(3); // 6, 5, 3, 1

	cout << "Removed: " << tmp1.getName() << " " << tmp2.getName() << endl;

	cout << "Size: " << pl.size() << endl;

	for(int i = 0; i < 4; i++) cout << pl.get(i).getName() << " ";

	cout << endl;

	cout << "----------------" << "End Constructor Test 2" << "----------------" << endl;	
}

void PlayListCopConTest1()
{
	cout << endl << "---------------" << "Copy Constructor Test 1" << "----------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);
	Song Song4 = Song("FakeSong4", "FakeArtist4", 400);
	Song Song5 = Song("FakeSong5", "FakeArtist5", 500);
	Song Song6 = Song("FakeSong6", "FakeArtist6", 600);

	cout << "Songs Made" << endl;

	PlayList* pl1 = new PlayList();

	cout << "Playlist Made" << endl;

	pl1->insert(Song1, 0); // 1
	pl1->insert(Song2, 0); // 2, 1
	pl1->insert(Song3, 0); // 3, 2, 1
	pl1->insert(Song4, 0); // 4, 3, 2, 1
	pl1->insert(Song5, 0); // 5, 4, 3, 2, 1
	pl1->insert(Song6, 0); // 6, 5, 4, 3, 2, 1

	PlayList* pl2 = new PlayList(*pl1);

	cout << pl1->size() << " | " << pl2->size() << endl;

	delete pl1;

	for(unsigned int i = 0; i < pl2->size(); i++){

		cout << pl2->get(i).getName() << endl;

	}

	delete pl2;

	cout << "-------------" << "End Copy Constructor Test 1" << "--------------" << endl;	
}

void OverloadedAssignTest1()
{
	cout << endl << "--------" << "OverLoaded Assignment Operator Test 1" << "---------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);

	cout << "Songs Made" << endl;

	PlayList* pl1 = new PlayList();

	cout << "Playlist 1 Made" << endl;

	pl1->insert(Song1, 0); // 1
	pl1->insert(Song2, 0); // 2, 1
	pl1->insert(Song3, 0); // 3, 2, 1

	for(int i = 0; i < 3; i++) cout << pl1->get(i).getName() << " ";
	
	PlayList* pl2 = new PlayList();
	*pl2 = *pl1;
	cout << endl << "Playlist 2 Made and copied. Size of: " << pl2->size() << endl;

	for(int i = 0; i < 3; i++) cout << pl2->get(i).getName() << " ";
	cout << endl;

	delete pl1;
	cout << "Original deleted;" << endl;
	
	for(int i = 0; i < 3; i++) cout << pl2->get(i).getName() << " ";
	cout << endl;

	delete pl2;

	cout << "------" << "End OverLoaded Assignment Operator Test 1" << "-------" << endl;	
}

	// Method Tests

void SwapTest1()
{
	cout << endl << "---------------------" << "Swap Test 1" << "----------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);

	cout << "Songs Made" << endl;

	PlayList* pl = new PlayList();

	cout << "Playlist Made" << endl;

	pl->insert(Song1, 0); // 1
	pl->insert(Song2, 0); // 2, 1
	pl->insert(Song3, 0); // 3, 2, 1

	cout << "Pre-swap:  ";
	for(int i = 0; i < 3; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	pl->swap(2, 1); // 2, 3, 1

	cout << "Post-swap: ";
	for(int i = 0; i < 3; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	delete pl;

	cout << "-------------------" << "End Swap Test 1" << "--------------------" << endl;	
}

void SwapTest2()
{
	cout << endl << "---------------------" << "Swap Test 2" << "----------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);

	cout << "Songs Made" << endl;

	PlayList* pl = new PlayList();

	cout << "Playlist Made" << endl;

	pl->insert(Song1, 0); // 1
	pl->insert(Song2, 0); // 2, 1
	pl->insert(Song3, 0); // 3, 2, 1

	cout << "Pre-swap:  ";
	for(int i = 0; i < 3; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	pl->swap(0, 1); // 2, 3, 1

	cout << "Post-swap: ";
	for(unsigned int i = 0; i < pl->size(); i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	delete pl;

	cout << "-------------------" << "End Swap Test 2" << "--------------------" << endl;	
}

void SwapTest3()
{
	cout << endl << "---------------------" << "Swap Test 3" << "----------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);
	Song Song4 = Song("FakeSong4", "FakeArtist4", 400);
	Song Song5 = Song("FakeSong5", "FakeArtist5", 500);
	Song Song6 = Song("FakeSong6", "FakeArtist6", 600);

	cout << "Songs Made" << endl;

	PlayList* pl = new PlayList();

	cout << "Playlist Made" << endl;

	pl->insert(Song1, 0); // 1
	pl->insert(Song2, 0); // 2, 1
	pl->insert(Song3, 0); // 3, 2, 1
	pl->insert(Song4, 0); // 4, 3, 2, 1
	pl->insert(Song5, 0); // 5, 4, 3, 2, 1
	pl->insert(Song6, 0); // 6, 5, 4, 3, 2, 1

	cout << "Pre-swap:  ";
	for(int i = 0; i < 6; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	pl->swap(0, 1); // 5, 6, 4, 3, 2, 1
	pl->swap(4, 5); // 5, 6, 4, 3, 1, 2
	pl->swap(2, 3); // 5, 6, 3, 4, 1, 2

	cout << "Post-swap: ";
	for(int i = 0; i < 6; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	delete pl;

	cout << "-------------------" << "End Swap Test 3" << "--------------------" << endl;	
}

void SwapTest4()
{
	cout << endl << "---------------------" << "Swap Test 4" << "----------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);
	Song Song4 = Song("FakeSong4", "FakeArtist4", 400);
	Song Song5 = Song("FakeSong5", "FakeArtist5", 500);
	Song Song6 = Song("FakeSong6", "FakeArtist6", 600);

	cout << "Songs Made" << endl;

	PlayList* pl = new PlayList();

	cout << "Playlist Made" << endl;

	pl->insert(Song1, 0); // 1
	pl->insert(Song2, 0); // 2, 1
	pl->insert(Song3, 0); // 3, 2, 1
	pl->insert(Song4, 0); // 4, 3, 2, 1
	pl->insert(Song5, 0); // 5, 4, 3, 2, 1
	pl->insert(Song6, 0); // 6, 5, 4, 3, 2, 1

	cout << "Pre-swap:  ";
	for(int i = 0; i < 6; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	pl->swap(0, 4); // 2, 5, 4, 3, 6, 1
	pl->swap(2, 5); // 2, 5, 1, 3, 6, 4

	cout << "Post-swap: ";
	for(int i = 0; i < 6; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	delete pl;

	cout << "-------------------" << "End Swap Test 4" << "--------------------" << endl;	
}

void SwapTest5()
{
	cout << endl << "---------------------" << "Swap Test 5" << "----------------------" << endl;

	Song Song1 = Song("FakeSong1", "FakeArtist1", 100);
	Song Song2 = Song("FakeSong2", "FakeArtist2", 200);
	Song Song3 = Song("FakeSong3", "FakeArtist3", 300);
	Song Song4 = Song("FakeSong4", "FakeArtist4", 400);
	Song Song5 = Song("FakeSong5", "FakeArtist5", 500);
	Song Song6 = Song("FakeSong6", "FakeArtist6", 600);

	cout << "Songs Made" << endl;

	PlayList* pl = new PlayList();

	cout << "Playlist Made" << endl;

	pl->insert(Song1, 0); // 1
	pl->insert(Song2, 0); // 2, 1
	pl->insert(Song3, 0); // 3, 2, 1
	pl->insert(Song4, 0); // 4, 3, 2, 1
	pl->insert(Song5, 0); // 5, 4, 3, 2, 1
	pl->insert(Song6, 0); // 6, 5, 4, 3, 2, 1

	cout << "Pre-swap:  ";
	for(int i = 0; i < 6; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	pl->swap(0, 5); // 1, 5, 4, 3, 2, 6
	pl->swap(2, 4); // 1, 5, 2, 3, 4, 6

	cout << "Post-swap: ";
	for(int i = 0; i < 6; i++) cout << pl->get(i).getName() << " ";
	cout << endl;

	delete pl;

	cout << "-------------------" << "End Swap Test 5" << "--------------------" << endl;	
}

int main()
{

	cout << "------------------" << endl << "Starting Tests " << endl << "------------------" << endl;

	SongTest1();
	NodeTest1();

	PlayListConTest1();
	PlayListConTest2();

	PlayListCopConTest1();
	OverloadedAssignTest1();

	SwapTest1();
	SwapTest2();
	SwapTest3();
	SwapTest4();
	SwapTest5();

	cout << endl << "-------------------" << endl << "Ending Tests " << endl << "-------------------" << endl;
	return 0;

}