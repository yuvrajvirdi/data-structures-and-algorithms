#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {
private:
    vector<int> parent, rank;   // parent of i-th node, rank of i-th node
    int num_sets;               // number sets
    bool is_finalized = false;  // finalized status

public:
    DisjointSet(int n) : parent(n + 1), rank(n + 1), num_sets(n) {
        for (int i = 1; i <= n; i++) 
            parent[i] = i;
    }

    // creates new set with i as member and as representative
    void make_set(int i) {
        if (is_finalized) return;
        else {
            parent[i] = 0;
            rank[i] = 0;
        }
    }

    // finds representative of set
    int find_set(int i) {
        if (parent[i] != i) 
            // path compression
            parent[i] = find_set(parent[i]);  
        return parent[i];
    }

    // unites sets with i and j members on whosevers depth is larger
    void union_sets(int i, int j) {
        if (is_finalized) return;

        // if in the same set
        int rep_i = find_set(i), rep_j = find_set(j);
        if (rep_i == rep_j) return;

        // union based on depth of i, j tree
        if (rank[rep_i] > rank[rep_j]) 
            parent[rep_j] = rep_i;
        else if (rank[rep_j] > rank[rep_i]) 
            parent[rep_i] = rep_j;
        else {
            // attaching same level trees make result 1 level deeper
            parent[rep_j] = rep_i;
            rank[rep_i]++; 
        }

        // 1 less set
        num_sets--;
    }

    int finalize_sets() {
        if (is_finalized) return num_sets;

        // tmprly store new reps
        vector<int> new_rep(parent.size(), 0);
        int cur_rep = 1;

        // new consecutive reps to roots
        for (int i = 1; i < parent.size(); i++) {
            if (i == find_set(i)) {
                parent[i] = cur_rep;
                new_rep[i] = cur_rep++;
            }
        }   

        // update pointers
        for (int i = 1; i < parent.size(); i++)
            parent[i] = new_rep[find_set(i)];

        // finalize
        num_sets = cur_rep - 1;
        is_finalized = true;

        return num_sets;
    }

};