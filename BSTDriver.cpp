#include "wx/wx.h"
#include "wx/sizer.h"
#include <iostream>
#include "DrawPanel.h"
#include "ImageLoader.h"
#include "BinarySearchTree.h"

#include "Circle.h"
#include "Line.h"
#include "ListArray.h"
#include "CD.h"
using namespace std;
using namespace CSC2110;

class MyApp: public wxApp
{
    bool OnInit();
 
    wxFrame* frame;
    DrawPanel* drawPane;
public:
 
};
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   ListArrayIterator<CD>* iter = cds->iterator();
   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);
   
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;
	
	
   
   //DO THIS
   //test your tree sort method
   CD** unsorted_cds = cds->toArray();
   CD** sorted_cds = bst->treeSort(unsorted_cds, num_items, &CD::compare_items, &CD::compare_keys);
   
   for (int i = 0; i < num_items; i++)
   {
	  CD* cd = sorted_cds[i];
	  cd->displayCD();  
   }
	

   delete cds;
   
   wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
   frame = new wxFrame((wxFrame *)NULL, -1,  wxT("AVL Tree"), wxPoint(500,500), wxSize(1100,600));
 
   drawPane = new DrawPanel((wxFrame*) frame, bst);
   sizer->Add(drawPane, 1, wxEXPAND);
 
   frame->SetSizer(sizer);
   frame->SetAutoLayout(true);
 
   frame->Show();
   return true;

   return 0;
}
