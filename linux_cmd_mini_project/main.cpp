#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std ;


//this function remove the spaces and put them in the arr
void split(string str,string* arr,char seprator){
    int tedad = 0 ;
    string now="" ;
    for(int i=0 ; i<int(str.length()) ; i++){
        if(str[i] != seprator){
            now += str[i] ;
        }
        else if(str[i+1] == seprator){
            while(str[i+1] == seprator){
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
private:
    void delete_all(Tree_node *current){
         for(int i=0 ; i<int(current->childs.size()) ; i++){
             if(!current->childs[i]->childs.empty()){
                 delete_all(current->childs[i]) ;
             }
             delete current->childs[i] ;
         }
         current->childs.clear() ;
    }

    Tree_node* copy_Tree_node(Tree_node* example){
        Tree_node *new1 = new Tree_node() ;
        new1->value = example->value ;
        for(int i=0 ; i<int(example->childs.size()) ; i++){
            new1->childs.push_back(copy_Tree_node(example->childs[i])) ;
        }
        return new1 ;
    }
public :
    Tree_node *root ;
    Tree_node *current_path ;
    string current_path_str ;
    Tree(){
        root = new Tree_node() ;
        root->value = "/" ;
        root->isfile = false ;
        current_path = root ;
    }

    string pwd(){
        return current_path_str ;
    }

    void touch(string name){
        Tree_node* temp = cd_return(current_path_str) ;
        for(int i=0 ; i<int(temp->childs.size()) ; i++){
            if(temp->childs[i]->value == name && temp->childs[i]->isfile == true){
                throw std::invalid_argument("repeated") ;
            }
        }
        Tree_node *new1 = new Tree_node() ;
        new1->value = name ; new1->isfile = true ;
        temp->childs.push_back(new1) ;
    }

    void cd(string path){
        if(path == "..."){
            if(current_path == root){
                cout<<"you are in the root"<<endl ;
                return ;
            }
            string address_arr[20] ;
            split(current_path_str,address_arr,'/');
            Tree_node *current = root ;
            int start = 1 ; bool ispossible ;
            while(address_arr[start + 1] != "end of array"){
                ispossible = false ;
                for(int i=0 ; i<int(current->childs.size()) ; i++){
                    if(current->childs[i]->value == address_arr[start] && current->childs[i]->isfile == false){
                        ispossible = true ;
                        current = current->childs[i] ;
                        break ;
                    }
                }
                if(!ispossible && current->childs.size() != 0){
                    throw std::invalid_argument("impossible") ;
                }
                start ++ ;
            }
            current_path = current ; string temp = "" ;
            int size = int(current_path_str.length()) - (int(address_arr[start].length()) + 1);
            for(int i=0 ; i<size ; i++){
                temp += current_path_str[i] ;
            }
            current_path_str = temp ;
        }
        else{
        string address_arr[20] ;
        split(path,address_arr,'/');
        Tree_node *current = root ;
        int start = 1 ; bool ispossible ;
        while(address_arr[start] != "end of array"){
            ispossible = false ;
            for(int i=0 ; i<int(current->childs.size()) ; i++){
                if(current->childs[i]->value == address_arr[start] && current->childs[i]->isfile == false){
                    ispossible = true ;
                    current = current->childs[i] ;
                    break ;
                }
            }
            if(!ispossible && current->childs.size() != 0){
                throw std::invalid_argument("impossible") ;
            }
            start ++ ;
        }
        current_path = current ;
        current_path_str = path ;
        }
    }

    Tree_node* cd_return(string path){
        string address_arr[20] ;
        split(path,address_arr,'/');
        Tree_node *current = root ;
        int start = 1 ; bool ispossible ;
        while(address_arr[start] != "end of array"){
            ispossible = false ;
            for(int i=0 ; i<int(current->childs.size()) ; i++){
                if(current->childs[i]->value == address_arr[start] && current->childs[i]->isfile == false){
                    ispossible = true ;
                    current = current->childs[i] ;
                    break ;
                }
            }
            if(!ispossible && current->childs.size() != 0){
                throw std::invalid_argument("impossible") ;
            }
            start ++ ;
        }
        return current ;
        current_path_str = path ;
    }



    void cp(string path1,string path2){
        //int position = 0 ;
        string new_path1 = "" , new_path2 = "" ;
        Tree_node *finded = cd_return(path1) ;
        Tree_node *copy = copy_Tree_node(finded) ;
        Tree_node *copy_here = cd_return(path2) ;
        copy_here->childs.push_back(copy) ;
    }

    void mv(string path1,string path2){
        cp(path1,path2) ;
        rmdir_absolute_path(path1) ;
    }

    void find(Tree_node* current, char type,string name,string &path_to_name,string path_to_name_str=""){
        if(int(current->childs.size()) == 0){
            return ;
        }
        bool isfile ;
        if(type == 'f'){
            isfile = true ;
        }
        else{
            isfile = false;
        }
        for(int i=0 ; i<int(current->childs.size()) ; i++){
            if(current->childs[i]->isfile == isfile && current->childs[i]->value == name){
                path_to_name_str += "/" + name ;
                path_to_name = path_to_name_str ;
                return ;
            }
            else{
                string temp = path_to_name_str ;
                path_to_name_str += "/" + current->childs[i]->value ;
                find(current->childs[i],type,name,path_to_name, path_to_name_str) ;
                path_to_name_str = temp ;
            }
        }
    }

    void mkdir_absolute_path(string value , string address){
        string address_arr[20] ;
        split(address, address_arr,'/') ;
        int start = 1 ;
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
            if(!ispossible && current->childs.size() != 0){
                throw std::invalid_argument("impossible") ;
            }
            start ++ ;
        }

        if(ispossible || current == root){
            // this for check if the value in this address is repeated throw exception
            for(int i=0 ; i<int(current->childs.size()) ; i++){
                if(current->childs[i]->value == value){
                    throw std::invalid_argument("already existed") ;
                }
            }
            new1->value = value ;
            current->childs.push_back(new1) ;
        }
        else{
            throw std::invalid_argument("impossible") ;
        }
   }

   void rmdir_absolute_path(string address){
        string address_arr[20] ;
        split(address, address_arr,'/') ;
        int start = 1 ;
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
            if(!ispossible && current->childs.size() != 0){
                throw std::invalid_argument("impossible") ;
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


class Accounts{
public :
    Tree *mytree ;
    string name ;
    static vector<Accounts*> ac ;
    Accounts(string name1){
        name = name1 ;
        mytree = new Tree() ;
        ac.push_back(this) ;
    }
    void ask(){
        string input , arr[7];
        cout<<name<<" "<<"you are in "<<mytree->current_path_str<<" :" ;
        getline(cin,input) ;
        split(input,arr,' ') ;
        string order = arr[0] ;
        bool valid_input = false ;
        try {
        if(order == "su"){
            for(int i=0 ; i<3 ; i++){
                if(arr[1] == ac[i]->name){
                    ac[i]->ask() ;
                }
            }
        }
        if(order == "pwd"){
            string a = mytree->pwd() ;
            cout<<"the current path is "<<a<<endl ;
            valid_input = true ;
        }
        if(order == "mkdir" && arr[1][0] == '/'){
            mytree->mkdir_absolute_path(arr[2],arr[1]) ;
             valid_input = true ;
        }
        if(order == "mkdir" && arr[1][0] != '/'){
            mytree->mkdir_absolute_path(arr[2],mytree->current_path_str + '/' + arr[1]) ;
             valid_input = true ;
        }
        if(order == "rmdir" && arr[1][0] == '/'){
            mytree->rmdir_absolute_path(arr[1]) ;
             valid_input = true ;
        }
        if(order == "rmdir" && arr[1][0] != '/'){
            // rmdir relative path
             valid_input = true ;
        }
        if(order == "cp" ){
            mytree->cp(arr[1],arr[2]) ;
             valid_input = true ;
        }
        if(order == "mv"){
            mytree->mv(arr[1],arr[2]) ;
             valid_input = true ;
        }
        if(order == "cd"){
            mytree->cd(arr[1]) ;
             valid_input = true ;
        }
        if(order == "find"){
            string find_ans ;
            mytree->find(mytree->cd_return(arr[1]),arr[2][0],arr[3],find_ans) ;
            cout<<find_ans<<endl ;
            valid_input = true ;
        }
        if(order == "touch"){
            mytree->touch(arr[1]);
             valid_input = true ;
        }
        if(order == "ls"){
            Tree_node *new1 = mytree->cd_return(arr[1]) ;
            for(int i=0 ; i<int(new1->childs.size()) ; i++){
                cout<<new1->childs[i]->value<<"  " ;
            }
            cout<<endl ;
            valid_input = true ;
        }
        } catch (exception ex) {
            cout<<ex.what()<<endl ;
        }
        if(!valid_input){
            cout<<"invalid input"<<endl ;
            ask() ;
        }
        ask() ;
    }
};

vector<Accounts*> Accounts::ac ;

int main()
{

    Accounts *main = new Accounts("main") ;
    Accounts *danial = new Accounts("danial") ;
    Accounts *ali = new Accounts("ali") ;
    Accounts *mohsen = new Accounts("mohsen") ;



    main->ask() ;

    /*Tree main_tree ;
    main_tree.mkdir_absolute_path("a","/") ;
    main_tree.mkdir_absolute_path("b","/") ;
    main_tree.mkdir_absolute_path("b","/a") ;
    main_tree.mkdir_absolute_path("c","/a") ;
    main_tree.mkdir_absolute_path("h","/a/b") ;
    main_tree.mkdir_absolute_path("newone","/a/b/h") ;
    //main_tree.mkdir_absolute_path("c2","/c") ;
    main_tree.cd("/a/b/h") ;
    main_tree.cd("...") ;
    main_tree.cd("...") ;
    main_tree.cd("...") ;
    main_tree.cd("...") ;
    // this 3 line is for find function
    string find_ans ;
    main_tree.find(main_tree.cd_return("/"),'d',"h",find_ans,"") ;
    main_tree.mv("/a","/b") ;

    cout<<"hdcih" ;

    cout<<"hdcih" ;*/


    return 0;
}
