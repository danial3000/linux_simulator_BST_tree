#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std ;

//this function remove the spaces and put them in the arr
void split(string str,string* arr){
    int tedad = 0 ;
    string now="" ;
    for(int i=0 ; i<int(str.length()) ; i++){
        if(str[i] != '/'){
            now += str[i] ;
        }
        else if(str[i+1] == '/'){
            while(str[i+1] == '/'){
                i ++ ;
            }
            arr[tedad] = now ;
            now = "" ;
            tedad ++ ;
            //break ;
        }
        else{
            arr[tedad] = now ;
            now = "" ;
            tedad ++ ;
        }
    }
    if(now == ""){
        arr[tedad] = "end of array" ;
    }
    else{
        arr[tedad] = now ;
        arr[tedad + 1] = "end of array" ;
    }
}

class Tree_node{
public :
    bool isfile ;
    string value ;
    vector<Tree_node*> childs ;
};

class Tree{
public :
    Tree_node *root ;
    Tree_node *current_path ;
    Tree(){
        root = new Tree_node() ;
        root->value = "/" ;
        root->isfile = false ;
        current_path = new Tree_node ;
        current_path = root ;
    }

    void mkdir_absolute_path(string value , string address){
        string address_arr[20] ;
        split(address, address_arr) ;
        int start = 0 ;
        Tree_node *current = root ;
        Tree_node *new1 = new Tree_node() ;
        //ispossible check if we can go to the address or not
        bool ispossible ;
        while(address_arr[start] != "end of array"){
            ispossible = false ;
            for(int i=0 ; i<int(current->childs.size()) ; i++){
                if(current->childs[i]->value == address_arr[start] && current->childs[i]->isfile == false){
                    ispossible = true ;
                    current = current->childs[i] ;
                    break ;
                }
            }
            start ++ ;
        }

        if(ispossible || current == root){
            new1->value = value ;
            current->childs.push_back(new1) ;
        }
        else{
            throw std::invalid_argument("impossible") ;
        }
   }

   void delete_all(Tree_node *current){
        for(int i=0 ; i<int(current->childs.size()) ; i++){
            if(!current->childs[i]->childs.empty()){
                delete_all(current->childs[i]) ;
            }
            delete current->childs[i] ;
        }
        current->childs.clear() ;
   }
   void rmdir_absolute_path(string address){
        string address_arr[20] ;
        split(address, address_arr) ;
        int start = 0 ;
        // we use need_for_del to access the current(we need the father of it for deleting it)
        Tree_node *current = root , *need_for_del = root ;
        bool ispossible ;
        while(address_arr[start] != "end of array"){
            // here we assaining the father of current into need_for_del
            if(address_arr[start + 1] == "end of array"){
                need_for_del = current ;
            }
            ispossible = false ;
            for(int i=0 ; i<int(current->childs.size()) ; i++){
                if(current->childs[i]->value == address_arr[start] && current->childs[i]->isfile == false){
                    ispossible = true ;
                    current = current->childs[i] ;
                    break ;
                }
            }
            start ++ ;
        }
        if(ispossible){
            int position = 0 ;
            //delete_all delete all directories inside of the current
            delete_all(current) ;
            delete current ;
            //we search for the location of the current in need_for_del
            for(int i=0 ; i<int(need_for_del->childs.size()) ; i++){
                if(need_for_del->childs[i] == current){
                    position = i ;
                    break ;
                }
            }
            //and here we delete the current directory itself
            need_for_del->childs.erase(need_for_del->childs.begin() + position) ;
        }
        else{
            throw std::invalid_argument("impossible") ;
        }
   }
};



int main()
{

    Tree main_tree ;
    main_tree.mkdir_absolute_path("a","/") ;
    main_tree.mkdir_absolute_path("a","/") ;
    main_tree.mkdir_absolute_path("b","/") ;
    main_tree.mkdir_absolute_path("c","/") ;
    main_tree.mkdir_absolute_path("a2","/a") ;
    main_tree.mkdir_absolute_path("b2","/b") ;
    main_tree.mkdir_absolute_path("c2","/c") ;
    main_tree.rmdir_absolute_path("/a") ;
    main_tree.rmdir_absolute_path("/a") ;
    cout<<"end" ;
    cout<<"end" ;




    return 0;
}
