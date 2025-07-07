#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_VERTICES 100
#define MAX_SKILLS 20
#define MAX_SKILL_NAME_LEN 30

typedef struct Edge {
    int company_index;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Vertex {
    int id;
    char name[50];
    char skills[MAX_SKILLS][MAX_SKILL_NAME_LEN];
    int skill_count;
    Edge* edges;
} Vertex;

typedef struct Graph {
    Vertex seekers[MAX_VERTICES];
    Vertex companies[MAX_VERTICES];
    int num_seekers;
    int num_companies;
} Graph;

void initGraph(Graph* g, int seekers, int companies);
void addEdge(Graph* g, int seekerIndex, int companyIndex, int weight);
void dfs(Graph* g, int start);
void bfs(Graph* g, int start);
void priorityMatching(Graph* g);
void addSkill(Vertex* v, const char* skill);
int countSkillOverlap(Vertex* seeker, Vertex* company);

#endif