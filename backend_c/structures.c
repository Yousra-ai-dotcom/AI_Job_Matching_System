#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void initGraph(Graph* g, int seekers, int companies) {
    g->num_seekers = seekers;
    g->num_companies = companies;
    for (int i = 0; i < seekers; i++) {
        g->seekers[i].id = i;
        g->seekers[i].edges = NULL;
        g->seekers[i].skill_count = 0;
    }
    for (int i = 0; i < companies; i++) {
        g->companies[i].id = i;
        g->companies[i].edges = NULL;
        g->companies[i].skill_count = 0;
    }
}

void addEdge(Graph* g, int seekerIndex, int companyIndex, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->company_index = companyIndex;
    newEdge->weight = weight;
    newEdge->next = g->seekers[seekerIndex].edges;
    g->seekers[seekerIndex].edges = newEdge;
}

void dfsUtil(Graph* g, int seekerIndex, int* visited_seekers, int* visited_companies) {
    visited_seekers[seekerIndex] = 1;
    printf("Visited seeker %d (%s)\n", seekerIndex, g->seekers[seekerIndex].name);
    for (Edge* edge = g->seekers[seekerIndex].edges; edge != NULL; edge = edge->next) {
        int compIndex = edge->company_index;
        if (!visited_companies[compIndex]) {
            visited_companies[compIndex] = 1;
            printf("-> Company %d (%s)\n", compIndex, g->companies[compIndex].name);
            // Si besoin, on pourrait explorer les seekers connectés à cette company (pour un graphe complet)
        }
    }
}

void dfs(Graph* g, int start) {
    int visited_seekers[MAX_VERTICES] = {0};
    int visited_companies[MAX_VERTICES] = {0};
    dfsUtil(g, start, visited_seekers, visited_companies);
}

void bfs(Graph* g, int start) {
    int visited_seekers[MAX_VERTICES] = {0};
    int visited_companies[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited_seekers[start] = 1;

    while (front < rear) {
        int seekerIndex = queue[front++];
        printf("Visited seeker %d (%s)\n", seekerIndex, g->seekers[seekerIndex].name);
        for (Edge* edge = g->seekers[seekerIndex].edges; edge != NULL; edge = edge->next) {
            int compIndex = edge->company_index;
            if (!visited_companies[compIndex]) {
                visited_companies[compIndex] = 1;
                printf("-> Company %d (%s)\n", compIndex, g->companies[compIndex].name);
            }
        }
    }
}

void priorityMatching(Graph* g) {
    for (int i = 0; i < g->num_seekers; i++) {
        Edge* bestMatch = NULL;
        for (Edge* edge = g->seekers[i].edges; edge != NULL; edge = edge->next) {
            if (bestMatch == NULL || edge->weight > bestMatch->weight) {
                bestMatch = edge;
            }
        }
        if (bestMatch) {
            printf("Best match for Seeker %d (%s): Company %d (%s) with priority %d\n",
                   i, g->seekers[i].name, bestMatch->company_index, g->companies[bestMatch->company_index].name, bestMatch->weight);
        }
    }
}

void addSkill(Vertex* v, const char* skill) {
    if (v->skill_count < MAX_SKILLS) {
        strncpy(v->skills[v->skill_count], skill, MAX_SKILL_NAME_LEN);
        v->skill_count++;
    }
}

int countSkillOverlap(Vertex* seeker, Vertex* company) {
    int count = 0;
    for (int i = 0; i < seeker->skill_count; i++) {
        for (int j = 0; j < company->skill_count; j++) {
            if (strcmp(seeker->skills[i], company->skills[j]) == 0) {
                count++;
            }
        }
    }
    return count;
}