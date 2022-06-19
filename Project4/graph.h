#include <vector>
#include <stack>
template <class  type>
class graph {
private:
    struct node{
        type data = {};
        std::vector <node*> neighbors;
        bool isVisited;
        node(type data_, std::vector<node*> v={}) :
        data(data_), neighbors(v), isVisited(false){}
    };
    std::vector<node*> v;
    void topologicalSortHelper(node* curr_v, std::stack<node*>& s){
        //curr_v pointer to current node 
        //neighbours is a vector of node edges
        curr_v->isVisited = true;
        for (auto i:curr_v->neighbors)
        {
            //for each neighbour of curr_v
            if(!i->isVisited){
                topologicalSortHelper(i,s);
            }
        }
        s.push(curr_v);
        
    }
public:
    int addVertex(type data_){
        for (int i=0; i<v.size(); i++){
            if(v[i]->data==data_){
                return i;
            }
        }
        node* value=0;
        value->data= data_;
        v.push_back(value);
        
        
    } //add if not added, return index
    void addNeighbor(int a, int b) {
   
        v[a]->neighbors.push_back(v[b]);
        
    }
    std::vector<type> topologicalSort(){
       std::stack<node*> s;
        for(auto i:v){
            i->isVisited = false; 
        }
        for(auto i:v){
            if(!i->isVisited){
                topologicalSortHelper(i,s);
            }
        }

        std::vector<type> result;
        while(!s.empty()){
            result.push_back(s.top()->data); 
            s.pop();
        
        }
       
        return result;
    }
};
