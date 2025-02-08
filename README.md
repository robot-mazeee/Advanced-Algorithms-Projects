# Algorithms Course Projects  

This repository contains solutions to three projects I developed as part of my Algorithms course. Additionally, for each project, I have included:  

- The project description (in Portuguese).  
- A Python script I developed (`generate_graph_auto`) to generate a runtime vs. input size graph using Matplotlib and a built-in input generator (not developed by me).  
- A few instances of graphs produced by my generator.  
- An analysis report (in Portuguese).

## Graph Generator

The Python graph generator executes the project solution script using the subprocess module and measures its runtime. It then uses Matplotlib to plot a graph, with runtime on the y-axis and the complexity function applied to the input size on the x-axis.

## Projects  

<details>
  <summary><strong>Project 1 [Dynamic Programming]</strong></summary>
  
  **Description:**  
  We are given a table that defines the result of a binary operator applied to two integer operands. Given a string of operands and a target value, the goal is to determine the correct placement of parentheses within the sequence to achieve the target value.

  **Example:**
  Table: <br>
  <img width="94" alt="image" src="https://github.com/user-attachments/assets/5b56c8ae-e55d-4edf-982e-3b8eb9cad206" />

  Expression: `2 ⊕ 2 ⊕ 2 ⊕ 2 ⊕ 1 ⊕ 3 = 1` <br>
  Answer: `((((2 ⊕ 2) ⊕ 2) ⊕ (2 ⊕ 1)) ⊕ 3) = 1`

  **Files Included:**  
  - `Project1.cpp` – Solution implementation  
  - `generate_graph_auto.py` – Graph generator script  
  - `Report p1.pdf` – Analysis report  
  - `Problem1.pdf` – Problem description
  - `gerador.cpp` – Input generator
</details>

<details>
  <summary><strong>Project 2 [Graphs and Connectivity]</strong></summary>
  
  **Description:**  
  Given a set of subway stations and subway lines, the goal is to determine the minimum number of line changes required to travel between any two stations.

  **Files Included:**  
  - `Project2.cpp` – Solution implementation  
  - `generate_graph_auto.py` – Graph generator script  
  - `Report p2.pdf` – Analysis report  
  - `Problem2.pdf` – Problem description
  - `graphs/` – Sample generated graphs 
  - `gera.cpp` – Input generator
</details>

<details>
<summary><strong>Project 3 [Linear Programming]</strong></summary>
  
  **Description:**  
  We are given a set of countries, factories and children. Each child has a set of wishes, which represent a present produced by a factory, and can receive at most one present. Each factory has a production limit on the number of presents it can produce. Each country has a minimum and a maximum number of presents to be delivered to that country. The goal is to calculate the maximum number of children whose wishes can be granted while respecting all constraints.

  **Files Included:**  
  - `Project3.py` – Solution implementation  
  - `generate_graph_auto.py` – Graph generator script  
  - `Report p3.pdf` – Analysis report  
  - `Problem3.pdf` – Problem description
  - `graphs/` – Sample generated graphs 
  - `gera3.cpp` – Input generator 

</details>
