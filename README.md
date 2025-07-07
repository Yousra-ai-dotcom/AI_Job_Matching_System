# Intelligent Job Matching System Using Graph Algorithms & AI

Development of a job matching system using graph algorithms and machine learning.  
**Technologies:** C, Python (Flask), KNN, HTML/CSS, subprocess  
**Features:** Bipartite graph modeling, DFS/BFS traversal, weighted priority matching.  
Integrated KNN model to recommend jobs based on skills, experience, and category.  
Interactive web interface linking Flask frontend with C backend.

---

## 🚀 Objective & Idea

This project aims to intelligently match job seekers with companies by combining **graph theory** and **AI-based recommendation** techniques. It:

- Models job seekers and companies as nodes in a **bipartite graph**.
- Uses **graph traversal algorithms (DFS & BFS)** to explore potential matches.
- Applies **priority-based matching** using edge weights based on skill overlap.
- Integrates a **K-Nearest Neighbors (KNN)** model to enhance personalized job suggestions.

---

## 🔗 Bipartite Graph Modeling

- The graph includes two node sets:
  - **Job Seekers**
  - **Companies**
- An edge is added if there is a potential match based on shared skills.
- Stored using **adjacency lists** for efficient memory and fast lookup.
- Each node (seeker or company) is a **vertex** in the graph.

---

## 🔄 Graph Traversal Algorithms

### ✅ Depth-First Search (DFS)
- Recursively explores companies connected to a seeker.
- Uses `visited[]` to prevent revisiting nodes.
- Ideal for deep search of potential matches.

### ✅ Breadth-First Search (BFS)
- Uses a **queue** to explore companies level-by-level.
- Suitable for finding the **closest relevant job opportunities**.

---

## 🏆 Priority-Based Matching with Edge Weights

- Each seeker-company edge has a **weight based on skills overlap**.
- The system selects the company with the **highest matching score** for each seeker.
- Ensures **quality over quantity** in matching.

---

## ⚙️ Efficient Graph Storage

- Graph is stored as an **adjacency list**, not a matrix.
- Dynamic lists allow faster updates and less memory usage.
- Queries and graph operations are optimized.

---

## 🤖 AI Recommendation: K-Nearest Neighbors (KNN)

- Trained on historical job data.
- Input features:
  - Skills (multi-label)
  - Years of experience
  - Job category
- Converts user input into vectors to find **similar jobs**.
- Enhances graph-based matching with **personalized recommendations**.

---

## 📋 How the System Works

1. **User Input**  
   Job seekers and companies provide details like skills, experience, and category.

2. **Graph Generation**  
   System connects seekers to companies with similar skills.

3. **Traversal & Matching**  
   - Run DFS/BFS to explore matches.
   - Use edge weights for priority-based matching.

4. **AI Recommendation**  
   KNN suggests jobs based on user profile features.

---

## 🌐 Web Interface

- Built using **Flask (Python)**.
- Allows users to:
  - Enter data
  - Trigger graph algorithms
  - Get AI-based suggestions
- Clean and interactive UI with **HTML/CSS**.

---

## 🔄 Backend Integration (C + Flask)

- **C code** handles graph building, traversal, and matching.
- Flask passes user input to `input.txt`.
- Python’s `subprocess` runs the compiled C program.
- C program returns results → Flask displays them on the web interface.

---

## 📌 Example Flow

> User clicks **“Run DFS”** → Flask writes to `input.txt` → C code runs DFS → output displayed on browser  
> Example: “Seeker 0 matched to Company 1”

---

## 🛠️ Technologies Used

- `C` — Graph logic and algorithms (DFS, BFS, priority matching)
- `Python` — Flask for web interface
- `KNN` — Scikit-learn model for AI recommendations
- `HTML/CSS` — User-friendly frontend
- `subprocess` — Python ↔️ C communication via file system

---
## 🛠️ How to Run the Project

### 1. Compile the C Backend

Open a terminal and run:

```` ```bash ````
cd backend_c
gcc -o jobmatching main.c structures.c
 ```` ``` ```` 


### 2. Run the Flask Web Application

Open a terminal and run:

```` ```bash ````
cd webapp
pip install -r ../requirements.txt  # Install required Python packages if not done yet
python app.py
 ```` ``` ```` 


---
## ✅ Conclusion

This system combines **graph theory** and **machine learning** for smarter job matching:

- Graph algorithms ensure **transparent** and **efficient** exploration.
- KNN provides **personalized recommendations**.
- Bipartite graph structure mirrors real-world job-seeker/company
