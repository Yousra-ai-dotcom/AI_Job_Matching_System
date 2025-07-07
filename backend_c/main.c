#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

void inputData(Graph* g) {
    printf("Enter number of job seekers: ");
    scanf("%d", &g->num_seekers);
    printf("Enter number of companies: ");
    scanf("%d", &g->num_companies);
    initGraph(g, g->num_seekers, g->num_companies);

    for (int i = 0; i < g->num_seekers; i++) {
        printf("\nEnter name for job seeker %d: ", i);
        scanf("%s", g->seekers[i].name);
        int skill_count;
        printf("Enter number of skills: ");
        scanf("%d", &skill_count);
        for (int j = 0; j < skill_count; j++) {
            char skill[30];
            printf("Enter skill %d: ", j + 1);
            scanf("%s", skill);
            addSkill(&g->seekers[i], skill);
        }
    }

    for (int i = 0; i < g->num_companies; i++) {
        printf("\nEnter name for company %d: ", i);
        scanf("%s", g->companies[i].name);
        int skill_count;
        printf("Enter number of required skills: ");
        scanf("%d", &skill_count);
        for (int j = 0; j < skill_count; j++) {
            char skill[30];
            printf("Enter skill %d: ", j + 1);
            scanf("%s", skill);
            addSkill(&g->companies[i], skill);
        }
    }
}

void generateConnections(Graph* g) {
    printf("\nGenerating connections based on skill match...\n");
    for (int i = 0; i < g->num_seekers; i++) {
        for (int j = 0; j < g->num_companies; j++) {
            int weight = countSkillOverlap(&g->seekers[i], &g->companies[j]);
            if (weight > 0) {
                addEdge(g, i, j, weight);
            }
        }
    }
    printf("Connections generated.\n");
}

void displayMenu() {
    printf("\n=== AI-Based Job Matching System (Using Graph Algorithms) ===\n");
    printf("1. Input job seekers and companies\n");
    printf("2. Generate skill-based connections\n");
    printf("3. Search job matches (DFS)\n");
    printf("4. Search job matches (BFS)\n");
    printf("5. Show best matches (priority matching)\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

int main(int argc, char* argv[]) {
    Graph g;

    // 1. Command-line mode: used by Flask
    if (argc >= 3) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            printf("Error opening input file.\n");
            return 1;
        }

        int seekers, companies;
        fscanf(file, "%d", &seekers);
        fscanf(file, "%d", &companies);
        initGraph(&g, seekers, companies);

        // Load seekers
        for (int i = 0; i < seekers; i++) {
            fscanf(file, "%s", g.seekers[i].name);
            int skill_count;
            fscanf(file, "%d", &skill_count);
            for (int j = 0; j < skill_count; j++) {
                char skill[30];
                fscanf(file, "%s", skill);
                addSkill(&g.seekers[i], skill);
            }
        }

        // Load companies
        for (int i = 0; i < companies; i++) {
            fscanf(file, "%s", g.companies[i].name);
            int skill_count;
            fscanf(file, "%d", &skill_count);
            for (int j = 0; j < skill_count; j++) {
                char skill[30];
                fscanf(file, "%s", skill);
                addSkill(&g.companies[i], skill);
            }
        }

        fclose(file);
        generateConnections(&g);

        if (strcmp(argv[2], "dfs") == 0 && argc == 4) {
            int start = atoi(argv[3]);
            dfs(&g, start);
        } else if (strcmp(argv[2], "bfs") == 0 && argc == 4) {
            int start = atoi(argv[3]);
            bfs(&g, start);
        } else if (strcmp(argv[2], "match") == 0) {
            priorityMatching(&g);
        } else {
            printf("Invalid command.\n");
            return 1;
        }

        return 0;
    }

    // 2. Interactive mode: used in terminal
    int choice;
    int initialized = 0;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inputData(&g);
                initialized = 1;
                break;
            case 2:
                if (!initialized) {
                    printf("\nPlease input data first.\n");
                } else {
                    generateConnections(&g);
                }
                break;
            case 3:
                if (!initialized) {
                    printf("\nPlease input data first.\n");
                } else {
                    int seekerIndex;
                    printf("Enter seeker index to start DFS: ");
                    scanf("%d", &seekerIndex);
                    dfs(&g, seekerIndex);
                }
                break;
            case 4:
                if (!initialized) {
                    printf("\nPlease input data first.\n");
                } else {
                    int seekerIndex;
                    printf("Enter seeker index to start BFS: ");
                    scanf("%d", &seekerIndex);
                    bfs(&g, seekerIndex);
                }
                break;
            case 5:
                if (!initialized) {
                    printf("\nPlease input data first.\n");
                } else {
                    priorityMatching(&g);
                }
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}